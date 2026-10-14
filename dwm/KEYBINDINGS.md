# Niri to DWM keybindings

`Mod` means Super/Windows. DWM's default layout is master/stack; visible
windows live on numbered tags. Bindings are defined in `upstream/config.def.h`.

| Niri control | DWM control | Notes |
|---|---|---|
| `Mod+Return` terminal | `Mod+Return` | Kitty |
| `Mod+B` browser | `Mod+B` | Zen Browser |
| `Mod+E` file manager | `Mod+E` | Nautilus |
| `Mod+Q` close window | `Mod+Q` | DWM kill client |
| *(no Niri equivalent)* | `Mod+Shift+B` | Toggle the native DWM bar |
| `Mod+H/J/K/L` or arrows focus | same keys | DWM has one cyclic client order; left/up go backward and right/down forward |
| `Mod+Ctrl+H/J/K/L` or arrows move | same keys | Local helper reorders the selected tiled client by one place in DWM's client list |
| `Mod+1…9` focus workspace | `Mod+1…9` view tag | DWM tags are persistent and can be combined |
| `Mod+Ctrl+1…9` move window | `Mod+Ctrl+1…9` tag window | Preserves the Niri chord; `Mod+Shift+number` toggles a tag in the current view |
| `Mod+Tab` previous workspace | `Mod+Tab` | DWM toggles the previous tag view |
| `Mod+T` floating | `Mod+T` | Also `Mod+Shift+V` and `Mod+Shift+Space` |
| `Mod+F` maximize column | `Mod+F` monocle | Monocle shows one tag client at a time; cycle clients with focus keys |
| `Mod+Shift+F` fullscreen | `Mod+Shift+F` | Local config helper toggles DWM's fullscreen state |
| `Mod+M` maximize window | `Mod+M` monocle | DWM's closest built-in maximize-like layout |
| `Mod+R` / `Mod+Shift+R` width presets | same keys | Adjust master/stack ratio by 5%; not Niri's three column-width presets |
| `Mod+Ctrl+R` reset height | `Mod+Ctrl+R` reset master ratio | Resets to 55%; DWM has no per-window height control |
| `Mod+Ctrl+Shift+R` height presets | same keys | Increases master client count; no window-height equivalent |
| `Mod+Ctrl+F` expand column | `Mod+Ctrl+F` | Sets the master area to 95% width |
| `Mod+-` / `Mod+=` column width | same keys | Adjust master/stack ratio by 5% |
| `Mod+C` center column | `Mod+C` | Promotes the selected tiled client to DWM's master area |
| `Mod+Shift+arrows` focus monitor | same keys | DWM cycles Xinerama monitor order; up/down follow left/right order |
| `Mod+Shift+Ctrl+arrows` move to monitor | same keys | Tags the selected client to the adjacent Xinerama monitor |
| `Ctrl+Alt+Delete` quit Niri | `Ctrl+Alt+Delete` | Exits DWM |
| XF86 volume up/down/mute, mic mute | same keys | Uses installed `wpctl` against the default PipeWire sink/source |

## Not carried over

- Noctalia launcher, wallpaper picker, control center, settings, lock screen,
  and session menu: they are Wayland/Niri session features and are not started
  here. No replacement shell or launcher was added.
- `Mod+Home/End` first/last column, consume/expel column actions, tabbed
  columns, centering visible columns, and preset window heights: DWM has no
  equivalent column model.
- Workspace and column mouse-wheel navigation: DWM's vanilla button bindings
  do not provide the same directional workspace/column behavior.
- Overview and keyboard-inhibitor escape: no vanilla DWM equivalent.
- Screenshot keys: no screenshot utility is installed; none was added.
- Media play/pause/next/previous and brightness keys: no MPRIS or brightness
  command was available in the audited setup, so these remain unbound.
- `Mod+Shift+P` monitor power off: no existing X11 monitor power command was
  available, and a guessed output name could leave the display off.

DWM's native bar shows tags, layout symbol, window title, and the clock status
text supplied by `scripts/status`.
