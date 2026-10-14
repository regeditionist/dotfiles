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
bar's root-window status text using the already-installed `xprop` command. It
does not start Noctalia, since the current Noctalia setup is tied to Niri's
Wayland session. The bar itself remains DWM's built-in bar; there is no
Polybar.

At DWM session start, a small local XInput2 helper selects libinput's flat
acceleration profile for pointer devices that expose that property. This
removes speed-dependent acceleration without adding a package or changing
Niri/Gamescope settings. This is an X11 session setting; it cannot affect the
current Wayland session. Devices without the libinput property keep their own
driver settings.

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

None. Patch directory: `patches/README.md`.
