# dmenu

This is the unpatched upstream dmenu 5.4 release, built locally alongside
DWM. Upstream lists version 5.4 as released 2025-08-09.

- Source: <https://dl.suckless.org/tools/dmenu-5.4.tar.gz>
- SHA-256: `8fbace2a0847aa80fe861066b118252dcc7b4ca0a0a8f3a93af02da8fb6cd453`
- Launcher: `../scripts/run-app`
- Key: `Super+Ctrl+Enter`

`dmenu_run` presents executable commands from the session `PATH`. The local
launcher prepends `dwm/build`, where the build script places `dmenu` and its
`stest` helper. Nothing is installed under `/usr`.
