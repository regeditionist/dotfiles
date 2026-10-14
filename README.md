# DWM dotfiles

This repository contains a small DWM desktop setup for CachyOS and other
Arch-based Linux systems using SDDM. DWM is an **X11** window manager. The
setup adds a DWM choice to SDDM; it does not replace Niri or Gamescope, change
their configuration, or change SDDM's autologin choice.

The guide assumes you can log into your normal desktop and open a terminal.
Commands marked with `sudo` make system-level changes; read each command
before running it.

## What you need

- An Arch-based Linux installation with SDDM and an X11 server.
- Git and an internet connection to clone this repository.
- The packages below to compile DWM. The repository includes its own DWM and
  dmenu source; you do not need to install a dmenu package.

Install missing build and runtime dependencies with pacman:

```sh
sudo pacman -S --needed base-devel libx11 libxft libxinerama libxi xorg-server xorg-xprop
```

If you already have these packages, pacman will leave them installed. `feh`
is only needed if you have a `~/.fehbg` wallpaper script. The default app
shortcuts expect Kitty, Zen Browser, and Nautilus; change the commands in
`dwm/upstream/config.def.h` if you use different applications.

## Install the DWM session

### 1. Get the repository

Clone it into `~/dotfiles`. This location matches the configuration in this
repository and avoids having to edit the launcher paths:

```sh
cd ~
git clone YOUR-PRIVATE-REPOSITORY-URL dotfiles
cd ~/dotfiles
```

Replace `YOUR-PRIVATE-REPOSITORY-URL` with the HTTPS or SSH URL from GitHub.
If you downloaded a ZIP instead, extract it as `~/dotfiles`.

If your home directory is not `/home/void`, update the app-launcher path in
`dwm/upstream/config.def.h` before building. Replace
`/home/void/dotfiles` with the full path to your cloned repository.

### 2. Build DWM

Run the build script from the repository root:

```sh
./dwm/scripts/build
```

This compiles DWM, the bundled dmenu app runner, and a small pointer helper.
The programs are written to `dwm/build/`; nothing is installed system-wide by
the build. If compilation reports a missing header or library, install the
package listed in the error and run the build again.

### 3. Register DWM with SDDM

SDDM needs a small session file so it can show DWM in its session selector.
First create a copy with your own home-directory path:

```sh
sed "s|/home/void|$HOME|g" dwm/session/dwm.desktop > /tmp/dwm.desktop
```

Then install that one session file:

```sh
sudo install -Dm644 /tmp/dwm.desktop /usr/local/share/xsessions/dwm.desktop
```

This registers DWM as an X11 session. It does not edit SDDM configuration or
remove any session files. On systems where SDDM uses a different session
directory, check its configured `SessionDir` before choosing the install
location.

### 4. Choose DWM at login

Log out to the SDDM greeter. Open the session selector, choose **DWM
(dotfiles)**, and sign in. To return to SDDM from DWM, press `Ctrl+Alt+Delete`.
Choose Niri or Gamescope from the selector to use either existing session.

If autologin is enabled, it may log you straight into its configured session;
this setup does not change that setting. Use the normal logout route to reach
the greeter and select DWM.

## First steps in DWM

`Super` means the Windows key.

- `Super+Enter`: open Kitty.
- `Super+Ctrl+Enter`: open the app menu. Type an app command and press Enter.
- `Super+B`: open Zen Browser.
- `Super+E`: open Nautilus.
- `Super+1` through `Super+9`: switch tags (workspaces).
- `Super+Q`: close the focused window.
- `Ctrl+Alt+Delete`: leave DWM and return to SDDM.

See [the full cheat sheet](dwm/CHEATSHEET.md) for window layouts, tags,
monitor controls, sound keys, and available differences from Niri. The setup
uses DWM's built-in bar with a system tray; it does not use Polybar or a full
desktop environment.

## Rebuild after changing settings

Edit `dwm/upstream/config.def.h`, then run:

```sh
./dwm/scripts/build
```

The installed SDDM entry points to the repository's session launcher, so the
next DWM login uses the newly built program. For the patch source and local
adaptations, see [the patch notes](dwm/patches/README.md). More setup details
are in [dwm/README.md](dwm/README.md).

## Keep the repository private on GitHub

This repository is already a local Git repository. To publish it privately,
create a **new private repository** on GitHub and push this existing history;
do not upload a public copy.
