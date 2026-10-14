# DWM setup

This directory contains a small DWM 6.8 setup for this machine. It is based on
the official suckless release archive, with the local configuration in
`upstream/config.def.h`. No third-party patches or optional desktop utilities
are used.

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

This compiles DWM locally and writes the executable to `dwm/build/dwm`. It does
not install packages or copy anything into system directories. Edit
`dwm/upstream/config.def.h`, then rerun the build command.

## Session integration state

The machine uses SDDM. Its current configuration sets `DisplayServer=x11` for
the greeter but autologs into `gamescope-session.desktop`, which is a Wayland
session. The installed session list has Niri and Gamescope under
`/usr/share/wayland-sessions` and no X11 session directory/entry. DWM is an X11
window manager, so it is built here but is not registered or selected at
login. `session/dwm.desktop` is the entry to install if you later approve the
system-level integration. No SDDM config, Niri file, package, or unrelated
system setting is changed by this repository.

The DWM session script runs the compiled DWM binary and updates the native DWM
bar's root-window status text using the already-installed `xprop` command. It
does not start Noctalia, since the current Noctalia setup is tied to Niri's
Wayland session. The bar itself remains DWM's built-in bar; there is no
Polybar.

## Controls

`Mod` is Super/Windows. DWM retains its native tags, bar, and tile/floating/
monocle layouts. The bindings port the core Niri controls where DWM has a
reasonable equivalent; see [KEYBINDINGS.md](KEYBINDINGS.md) for the complete
mapping and differences. Vanilla DWM does not provide Niri's horizontal
columns, per-window heights, overview, shell panels, screenshots, lock screen,
or session menu.

## Patches

None. Patch directory: `patches/README.md`.
