#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <sys/select.h>
#include <unistd.h>

static int
apply_flat_profile(Display *display, Atom property)
{
	int count, changed = 0;
	XIDeviceInfo *devices = XIQueryDevice(display, XIAllDevices, &count);

	if (devices == NULL)
		return 0;
	for (int i = 0; i < count; i++) {
		unsigned char *value = NULL;
		Atom type;
		int format;
		unsigned long items, remaining;
		static unsigned char flat_profile[3] = { 0, 1, 0 };

		if (devices[i].use != XISlavePointer &&
		    devices[i].use != XIFloatingSlave)
			continue;
		if (XIGetProperty(display, devices[i].deviceid, property, 0, 3,
		                  False, XA_INTEGER, &type, &format, &items,
		                  &remaining, &value) != Success)
			continue;
		if (type == XA_INTEGER && format == 8 && items >= 3 &&
		    (value[0] != 0 || value[1] != 1 || value[2] != 0)) {
			XIChangeProperty(display, devices[i].deviceid, property,
			                 XA_INTEGER, 8, PropModeReplace,
			                 flat_profile, 3);
			changed++;
		}
		if (value != NULL)
			XFree(value);
	}
	XIFreeDeviceInfo(devices);
	XSync(display, False);
	return changed;
}

int
main(int argc, char **argv)
{
	Display *display = XOpenDisplay(NULL);
	Atom property;
	int watch = argc == 2 && argv[1][0] == '-' && argv[1][1] == 'w';

	if (display == NULL)
		return 1;
	property = XInternAtom(display, "libinput Accel Profile Enabled", True);
	if (property == None) {
		XCloseDisplay(display);
		return 0;
	}
	apply_flat_profile(display, property);
	if (!watch) {
		XCloseDisplay(display);
		return 0;
	}

	{
		unsigned char mask[XIMaskLen(XI_LASTEVENT)] = { 0 };
		XIEventMask event_mask = { XIAllDevices, sizeof mask, mask };
		int fd = ConnectionNumber(display);

		XISetMask(mask, XI_HierarchyChanged);
		if (XISelectEvents(display, DefaultRootWindow(display),
		                   &event_mask, 1) != Success) {
			XCloseDisplay(display);
			return 1;
		}
		XFlush(display);
		for (;;) {
			fd_set readfds;
			struct timeval timeout = { 5, 0 };
			int ready;

			FD_ZERO(&readfds);
			FD_SET(fd, &readfds);
			ready = select(fd + 1, &readfds, NULL, NULL, &timeout);
			if (ready < 0)
				break;
			if (ready == 0) {
				apply_flat_profile(display, property);
				continue;
			}
			while (XPending(display)) {
				XEvent event;
				XNextEvent(display, &event);
				if (event.type == GenericEvent &&
				    event.xcookie.evtype == XI_HierarchyChanged &&
				    XGetEventData(display, &event.xcookie)) {
					apply_flat_profile(display, property);
					XFreeEventData(display, &event.xcookie);
				}
			}
		}
	}
	XCloseDisplay(display);
	return 1;
}
