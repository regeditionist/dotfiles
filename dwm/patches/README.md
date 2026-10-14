# Patches

## System tray

`dwm-systray-6.8.diff` is the official suckless.org systray patch for DWM 6.8.
The upstream patch expects vanilla configuration and a slightly different
`dwm.c`, so its tray changes were adapted to the vendored source while keeping
the existing local keybindings and mouse bindings. The tray is enabled in
`upstream/config.def.h`, pinned to the selected monitor, and placed at the
right side of DWM's built-in bar. The status text is laid out to its left.

Patch page: <https://dwm.suckless.org/patches/systray/>
