# Handoff for future agents

## Scope and constraints

- This repository contains the user's personal DWM setup at `dwm/`.
- Preserve Niri, Gamescope, SDDM autologin, and unrelated system configuration.
- Do not run commands as root or use elevation without first showing the exact
  command, its effects and risks, and receiving explicit user approval.
- Prefer unprivileged, repository-scoped changes. Do not install/remove
  packages or change system session registration unless the user explicitly
  requests it.
- Continue from the existing audit and documentation; do not repeat system or
  Niri inspection without a specific need.

## Current session setup

- SDDM has Niri and Gamescope as Wayland sessions and **DWM (dotfiles)** as an
  X11 session. DWM's entry is `/usr/local/share/xsessions/dwm.desktop`; its
  tracked source is `dwm/session/dwm.desktop` and it launches
  `dwm/scripts/session`.
- SDDM autologin remains Gamescope. Do not change it. The home directory is
  private; the DWM entry uses `/usr/bin/sh` as `TryExec` so SDDM can list it.
- The DWM session script builds if needed, applies the local pointer helper,
  runs `~/.fehbg` if present, starts the status updater, then starts DWM.
  `~/.xinitrc` is not used for this SDDM-launched session.
- `dwm/scripts/status` keeps the date and appends default sink volume/mute
  from `wpctl`; it prefers `xsetroot -name` and falls back to `xprop`. Volume
  up/down/output-mute keybindings invoke its one-shot mode for immediate
  refresh; the session updater still polls every 30 seconds for the clock and
  external volume changes. The `xorg-xsetroot` package was not installed at
  last check, so `xsetroot` mode still needs the user's explicit approval for
  installation. The current tool environment could not connect to PipeWire to
  read a live volume.
- The system currently has pacman `dmenu` installed, but the DWM shortcut uses
  the repository's local dmenu runner by design after commit `6d6260d` reverted
  the attempted switch to `/usr/bin/dmenu_run`. That attempt made the launcher
  fail. Do not repeat that change without diagnosing why and confirming with
  the user.

## DWM implementation

- DWM source is the vendored 6.8 tree in `dwm/upstream/`; local config is
  `dwm/upstream/config.def.h`. Build with `./dwm/scripts/build` from the repo
  root. The build writes ignored binaries in `dwm/build/` and needs no root.
- The official DWM 6.8 systray patch is saved at
  `dwm/patches/dwm-systray-6.8.diff` and adapted in the vendored `dwm.c`.
  Tray is enabled immediately left of DWM's right-aligned status text.
  Existing local key and mouse bindings were preserved.
- Pointer acceleration is set to libinput's flat profile for supported X11
  pointer devices by `dwm/scripts/pointer-accel.c`. This only applies in DWM;
  the live effect has not been visually verified from a DWM session.
- `Ctrl+Alt+Delete` exits DWM to SDDM. `Super+Q` closes a window. The app
  launcher is `Super+Ctrl+Enter`; `Super+Enter` launches Kitty, `Super+B`
  Zen Browser, and `Super+E` Nautilus.
- Practical keys and limitations are documented in `dwm/CHEATSHEET.md` and
  `dwm/KEYBINDINGS.md`. Build/session notes are in `dwm/README.md`.

## Recent history

- `6d6260d` reverted the change to use pacman dmenu; this is the active state.
- `b7b709d` added the DWM 6.8 system tray patch.
- `401cbf6` runs `~/.fehbg` at DWM login.
- `183f615` added DWM-session pointer acceleration handling.

Check `git status` before editing and keep future changes scoped to the user's
current request.
