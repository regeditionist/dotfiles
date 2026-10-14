#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <string.h>

int
main(void)
{
	Display *display = XOpenDisplay(NULL);
	int count, changed = 0;
	XIDeviceInfo *devices;
	Atom property;

	if (display == NULL)
		return 1;

	property = XInternAtom(display, "libinput Accel Profile Enabled", True);
	if (property == None) {
		XCloseDisplay(display);
		return 0;
	}

	devices = XIQueryDevice(display, XIAllDevices, &count);
	for (int i = 0; i < count; i++) {
		unsigned char *value = NULL;
		Atom type;
		int format;
	unsigned long items, remaining;

		if (devices[i].use != XISlavePointer &&
		    devices[i].use != XIFloatingSlave)
			continue;
		if (XIGetProperty(display, devices[i].deviceid, property, 0, 2,
		                  False, XA_INTEGER, &type, &format, &items,
	                  &remaining, &value) != Success)
			continue;
		if (type == XA_INTEGER && format == 8 && items >= 2) {
			unsigned char flat_profile[2] = { 0, 1 };
			XIChangeProperty(display, devices[i].deviceid, property,
			                 XA_INTEGER, 8, PropModeReplace,
			                 flat_profile, 2);
			changed++;
		}
		if (value != NULL)
			XFree(value);
	}

	XIFreeDeviceInfo(devices);
	XSync(display, False);
	XCloseDisplay(display);
	return changed > 0 ? 0 : 1;
}
