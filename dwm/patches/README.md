# Patches

## System tray

`dwm-systray-6.8.diff` is the official suckless.org systray patch for DWM 6.8.
The upstream patch expects vanilla configuration and a slightly different
`dwm.c`, so its tray changes were adapted to the vendored source while keeping
the existing local keybindings and mouse bindings. The tray is enabled in
`upstream/config.def.h`, pinned to the selected monitor, and placed immediately
to the left of DWM's status text. The date and audio status remain at the
right end of the built-in bar.

Patch page: <https://dwm.suckless.org/patches/systray/>
