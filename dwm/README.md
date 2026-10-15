# DWM setup

This directory contains a small DWM 6.8 setup for this machine. It is based on
the official suckless DWM release archive, with the local configuration in
`upstream/config.def.h`. The app runner is upstream dmenu; no third-party
patches or additional shell utilities are used.

## Source and build

- Upstream: <https://dwm.suckless.org/> and <https://git.suckless.org/dwm>
- Version: `6.8` (official release dated 2026-01-30)
- Source archive: <https://dl.suckless.org/dwm/dwm-6.8.tar.gz>
- SHA-256: `bcf540589ad174d4073f4efa658828411e2f5ba63196cfaf6b71363700f590b7`
- Dependencies already present at audit: `base-devel`, `libx11`, `libxft`,
  `libxinerama`, and `xorg-server`.

From the repository root:

```sh
./dwm/scripts/build
```

This compiles DWM and dmenu locally and writes their executables to
`dwm/build/`. It does not install packages or copy anything into system
directories. Edit the respective `config.def.h` files, then rerun the build
command.

`Super+Ctrl+Enter` opens dmenu's command list. It filters executable commands
in the session `PATH`; type an app command and press Enter. The launcher and
`stest` stay inside this repository.

## Session integration state

The machine uses SDDM. Niri and Gamescope remain registered as Wayland
sessions, and DWM is registered as the X11 session **DWM (dotfiles)** via
`/usr/local/share/xsessions/dwm.desktop`. The entry invokes this repository's
session launcher. The existing Gamescope autologin configuration is unchanged;
choose another session from SDDM's session selector when signing in manually.
No Niri configuration or unrelated system setting is changed by this
repository.

The DWM session script runs the compiled DWM binary and updates the native DWM
bar's root-window status text with the date, default sink volume, and mute
state. Volume keys refresh the value immediately; the periodic updater keeps
the clock current and picks up volume changes made elsewhere. It uses
`xsetroot -name` when available, with the existing `xprop` fallback. It does
not start Noctalia, since the current Noctalia setup is tied to Niri's
Wayland session. The bar itself remains DWM's built-in bar; there is no
Polybar.

During the DWM session, a small local XInput2 helper selects libinput's flat
acceleration profile for pointer devices that expose that property. It watches
for added or reconfigured devices and checks periodically for profile resets.
The property is the three-flag libinput profile array (adaptive, flat, custom).
This removes speed-dependent acceleration without adding a package or changing
Niri/Gamescope settings. This is an X11 session setting; it cannot affect the
current Wayland session. Devices without the libinput property keep their own
driver settings.

The session launcher also runs `~/.fehbg` when present, restoring the wallpaper
configured by feh for DWM. This is handled in the SDDM DWM launcher, so no
`~/.xinitrc` change is needed and other sessions are unaffected.

The launcher starts the installed Dunst notification daemon for the DWM
session and stops it when DWM exits. `libnotify` is available for applications
that send notifications; no extra DWM patch or notification panel is used.

`Ctrl+Shift+1` uses the installed ImageMagick `import` command to save a
full-screen PNG under `~/Pictures/Screenshots` and notify you of its path.

The SDDM entry's `TryExec` checks `/usr/bin/sh`, which is visible to the SDDM
greeter. The DWM binary and launcher remain under the private `/home/void`
directory; after authentication SDDM runs the session as `void`, so that
session can access them without changing home-directory permissions.

## Controls

`Mod` is Super/Windows. DWM retains its native tags, bar, and tile/floating/
monocle layouts. The bindings port the core Niri controls where DWM has a
reasonable equivalent; see [KEYBINDINGS.md](KEYBINDINGS.md) for the complete
mapping and differences. Vanilla DWM does not provide Niri's horizontal
columns, per-window heights, overview, shell panels, screenshots, lock screen,
or session menu. For daily use, see [CHEATSHEET.md](CHEATSHEET.md).

## Patches

The official DWM 6.8 system tray patch is applied and adapted to this local
source; see [patches/README.md](patches/README.md). It adds tray icons to the
left of the date/volume status text in DWM's built-in bar.
