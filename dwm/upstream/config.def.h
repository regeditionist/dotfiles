/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* Appearance: keep DWM's native bar and a restrained dark palette. */
static const unsigned int borderpx = 2;
static const unsigned int snap = 24;
static const unsigned int systraypinning = 0;
static const unsigned int systrayonleft = 1;
static const unsigned int systrayspacing = 2;
static const int systraypinningfailfirst = 1;
static const int showsystray = 1;
static const int showbar = 1;
static const int topbar = 1;
static const char *fonts[] = { "monospace:size=10" };
static const char col_bg[] = "#181a1f";
static const char col_norm[] = "#c8ccd4";
static const char col_border[] = "#414854";
static const char col_selbg[] = "#3b4252";
static const char col_accent[] = "#88c0d0";
static const char *colors[][3] = {
	[SchemeNorm] = { col_norm, col_bg, col_border },
	[SchemeSel]  = { col_bg, col_accent, col_accent },
};

/* DWM tags act as persistent workspaces; Mod+number selects one. */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* Sentinel: C requires a non-empty array; it matches no real app class. */
	{ "__no_dwm_rule__", NULL, NULL, 0, 0, -1 },
};

/* Vanilla layouts: master/stack, floating, and monocle. */
static const float mfact = 0.55;
static const int nmaster = 1;
static const int resizehints = 1;
static const int lockfullscreen = 1;
static const int refreshrate = 120;

static const Layout layouts[] = {
	{ "[]=", tile },
	{ "><>", NULL },
	{ "[M]", monocle },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG) \
	{ MODKEY, KEY, view, {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask, KEY, tag, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask, KEY, toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY, toggletag, {.ui = 1 << TAG} },
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const char *termcmd[] = { "kitty", NULL };
static const char *browsercmd[] = { "zen-browser", NULL };
static const char *filecmd[] = { "nautilus", NULL };
/* Retain DWM's launcher symbols for its spawn() helper; no dmenu binding is set. */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = {
	"/home/void/dotfiles/dwm/scripts/run-app",
	"-i", "-fn", "monospace:size=10",
	"-nb", "#181a1f", "-nf", "#c8ccd4",
	"-sb", "#88c0d0", "-sf", "#181a1f",
	NULL
};
static const char *volupcmd[] = { "wpctl", "set-volume", "-l", "1.5", "@DEFAULT_AUDIO_SINK@", "5%+", NULL };
static const char *voldowncmd[] = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-", NULL };
static const char *volmutecmd[] = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };
static const char *micmutecmd[] = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SOURCE@", "toggle", NULL };

/* Reorder tiled clients in DWM's client list, approximating Niri column moves. */
static void
movestack(const Arg *arg)
{
	Client *c, **p, *target = NULL;

	if (!selmon->sel || selmon->sel->isfloating || !selmon->lt[selmon->sellt]->arrange)
		return;
	if (arg->i > 0) {
		for (c = nexttiled(selmon->sel->next); c && !ISVISIBLE(c); c = nexttiled(c->next));
		if (!c)
			return;
		target = c;
		for (p = &selmon->clients; *p && *p != selmon->sel; p = &(*p)->next);
		if (*p)
			*p = selmon->sel->next;
		selmon->sel->next = target->next;
		target->next = selmon->sel;
	} else {
		for (c = nexttiled(selmon->clients); c && c != selmon->sel; c = nexttiled(c->next))
			if (ISVISIBLE(c))
				target = c;
		if (!target)
			return;
		for (p = &selmon->clients; *p && *p != selmon->sel; p = &(*p)->next);
		if (*p)
			*p = selmon->sel->next;
		for (p = &selmon->clients; *p && *p != target; p = &(*p)->next);
		selmon->sel->next = *p;
		*p = selmon->sel;
	}
	arrange(selmon);
}

static void
togglefullscreen(const Arg *arg)
{
	if (selmon->sel)
		setfullscreen(selmon->sel, !selmon->sel->isfullscreen);
}

static const Key keys[] = {
	/* Applications: preserve Niri's Super+Enter/B/E shortcuts. */
	{ MODKEY, XK_Return, spawn, {.v = termcmd} },
	{ MODKEY, XK_b, spawn, {.v = browsercmd} },
	{ MODKEY, XK_e, spawn, {.v = filecmd} },
	{ MODKEY|ControlMask, XK_Return, spawn, {.v = dmenucmd} },
	{ MODKEY|ShiftMask, XK_b, togglebar, {0} },

	/* DWM focus is a single client order, so all Niri directions map to it. */
	{ MODKEY, XK_h, focusstack, {.i = -1} },
	{ MODKEY, XK_Left, focusstack, {.i = -1} },
	{ MODKEY, XK_k, focusstack, {.i = -1} },
	{ MODKEY, XK_Up, focusstack, {.i = -1} },
	{ MODKEY, XK_l, focusstack, {.i = +1} },
	{ MODKEY, XK_Right, focusstack, {.i = +1} },
	{ MODKEY, XK_j, focusstack, {.i = +1} },
	{ MODKEY, XK_Down, focusstack, {.i = +1} },
	{ MODKEY|ControlMask, XK_h, movestack, {.i = -1} },
	{ MODKEY|ControlMask, XK_Left, movestack, {.i = -1} },
	{ MODKEY|ControlMask, XK_k, movestack, {.i = -1} },
	{ MODKEY|ControlMask, XK_Up, movestack, {.i = -1} },
	{ MODKEY|ControlMask, XK_l, movestack, {.i = +1} },
	{ MODKEY|ControlMask, XK_Right, movestack, {.i = +1} },
	{ MODKEY|ControlMask, XK_j, movestack, {.i = +1} },
	{ MODKEY|ControlMask, XK_Down, movestack, {.i = +1} },

	{ MODKEY, XK_q, killclient, {0} },
	{ MODKEY, XK_t, togglefloating, {0} },
	{ MODKEY|ShiftMask, XK_v, togglefloating, {0} },
	{ MODKEY, XK_f, setlayout, {.v = &layouts[2]} },
	{ MODKEY, XK_m, setlayout, {.v = &layouts[2]} },
	{ MODKEY|ShiftMask, XK_f, togglefullscreen, {0} },
	{ MODKEY, XK_space, setlayout, {0} },
	{ MODKEY|ShiftMask, XK_space, togglefloating, {0} },
	{ MODKEY, XK_c, zoom, {0} },

	/* Approximate Niri's column width presets with master/stack ratio steps. */
	{ MODKEY, XK_r, setmfact, {.f = +0.05} },
	{ MODKEY|ShiftMask, XK_r, setmfact, {.f = -0.05} },
	{ MODKEY|ControlMask, XK_r, setmfact, {.f = 1.55} },
	{ MODKEY|ControlMask, XK_f, setmfact, {.f = 1.95} },
	{ MODKEY, XK_minus, setmfact, {.f = -0.05} },
	{ MODKEY, XK_equal, setmfact, {.f = +0.05} },
	{ MODKEY|ControlMask|ShiftMask, XK_r, incnmaster, {.i = +1} },

	/* Monitor movement/focus: DWM uses Xinerama monitor order. */
	{ MODKEY|ShiftMask, XK_Left, focusmon, {.i = -1} },
	{ MODKEY|ShiftMask, XK_Right, focusmon, {.i = +1} },
	{ MODKEY|ShiftMask, XK_Up, focusmon, {.i = -1} },
	{ MODKEY|ShiftMask, XK_Down, focusmon, {.i = +1} },
	{ MODKEY|ShiftMask|ControlMask, XK_Left, tagmon, {.i = -1} },
	{ MODKEY|ShiftMask|ControlMask, XK_Right, tagmon, {.i = +1} },
	{ MODKEY|ShiftMask|ControlMask, XK_Up, tagmon, {.i = -1} },
	{ MODKEY|ShiftMask|ControlMask, XK_Down, tagmon, {.i = +1} },

	{ MODKEY, XK_Tab, view, {0} },
	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)
	{ ControlMask|Mod1Mask, XK_Delete, quit, {0} },
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd} },
	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd} },
	{ 0, XF86XK_AudioMute, spawn, {.v = volmutecmd} },
	{ 0, XF86XK_AudioMicMute, spawn, {.v = micmutecmd} },
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0, Button1, setlayout, {0} },
	{ ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]} },
	{ ClkWinTitle, 0, Button2, zoom, {0} },
	{ ClkClientWin, MODKEY, Button1, movemouse, {0} },
	{ ClkClientWin, MODKEY, Button2, togglefloating, {0} },
	{ ClkClientWin, MODKEY, Button3, resizemouse, {0} },
	{ ClkTagBar, 0, Button1, view, {0} },
	{ ClkTagBar, 0, Button3, toggleview, {0} },
	{ ClkTagBar, MODKEY, Button1, tag, {0} },
	{ ClkTagBar, MODKEY, Button3, toggletag, {0} },
};
