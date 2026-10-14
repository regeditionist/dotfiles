# DWM quick cheat sheet

`Super` means the Windows key. These shortcuts apply in the **DWM (dotfiles)** session.

## Open apps

| Shortcut | Action |
|---|---|
| `Super+Ctrl+Enter` | Open dmenu. Type an executable name (such as `zen-browser` or `nautilus`), then press Enter. `Esc` closes the menu. |
| `Super+Enter` | Open Kitty terminal |
| `Super+B` | Open Zen Browser |
| `Super+E` | Open Nautilus |

## Windows and layouts

| Shortcut | Action |
|---|---|
| `Super+H` / `Super+K` or Left / Up | Focus previous window |
| `Super+L` / `Super+J` or Right / Down | Focus next window |
| `Super+Ctrl+H/J/K/L` or arrows | Reorder the selected tiled window |
| `Super+Q` | Close focused window |
| `Super+T` | Set focused window to floating layout |
| `Super+Shift+V` or `Super+Shift+Space` | Toggle floating for focused window |
| `Super+Space` | Cycle tile, floating, and monocle layouts |
| `Super+F` or `Super+M` | Use monocle layout (one window fills the tiled area) |
| `Super+Shift+F` | Toggle fullscreen for focused window |
| `Super+C` | Promote focused tiled window to master |
| `Super+R` / `Super+Shift+R` | Widen / narrow master area by 5% |
| `Super+Ctrl+R` | Reset master area to 55% |
| `Super+Ctrl+F` | Set master area to 95% |
| `Super+-` / `Super+=` | Narrow / widen master area by 5% |
| `Super+Ctrl+Shift+R` | Add one master window |
| `Super+Shift+B` | Show or hide DWM's built-in bar |

The built-in bar also hosts XEmbed system tray icons on its right side, when
applications provide them.

## Workspaces (tags)

| Shortcut | Action |
|---|---|
| `Super+1` … `Super+9` | View that numbered tag |
| `Super+Ctrl+1` … `Super+Ctrl+9` | Send focused window to that tag |
| `Super+Shift+1` … `Super+Shift+9` | Add or remove that tag from current view |
| `Super+Ctrl+Shift+1` … `Super+Ctrl+Shift+9` | Add or remove that tag on focused window |
| `Super+Tab` | Return to previous tag view |

Tags can be shown together. DWM's focus keys move through its window order; they do not navigate directional Niri columns.

## Sound and monitors

| Shortcut | Action |
|---|---|
| Volume up / down / mute keys | Change or mute default PipeWire output |
| Microphone mute key | Mute or unmute default PipeWire input |
| Pointer acceleration | DWM startup selects libinput's flat profile on supported X11 pointer devices |
| `Super+Shift+Left/Right` | Focus previous / next monitor |
| `Super+Shift+Ctrl+Left/Right` | Send focused window to previous / next monitor |
| `Super+Shift+Up/Down` and `Super+Shift+Ctrl+Up/Down` | Same actions, following DWM's monitor order |

## Log out or choose another session

Press **`Ctrl+Alt+Delete`** to quit DWM. This ends the DWM session and returns to the SDDM greeter; it does not shut down the computer. At the greeter, open the session selector and choose **Niri**, **Gamescope**, or **DWM (dotfiles)**, then sign in as usual. The existing Gamescope autologin setting remains in place; logging out returns to the greeter and its session selector.

`Super+Q` only closes the focused window; use `Ctrl+Alt+Delete` to leave DWM.

## Controls not provided in this setup

There is no DWM shortcut here for a lock screen, Niri/Noctalia control center, screenshot, brightness, media transport, or graphical session menu. Dmenu provides app launching; the SDDM greeter provides session selection after logging out. The bar is DWM's built-in bar and shows tags, layout, window title, and clock/status text.
