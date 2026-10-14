# dmenu

This is the unpatched upstream dmenu 5.4 source retained in the repository.
DWM now invokes the system package's `/usr/bin/dmenu_run`; the build script no
longer builds or uses this copy.

- Source: <https://dl.suckless.org/tools/dmenu-5.4.tar.gz>
- SHA-256: `8fbace2a0847aa80fe861066b118252dcc7b4ca0a0a8f3a93af02da8fb6cd453`
- Launcher: `../scripts/run-app`
- Key: `Super+Ctrl+Enter`

`dmenu_run` presents executable commands from the session `PATH`. The local
session launcher puts `/usr/bin` first and calls `/usr/bin/dmenu_run` directly,
so the system `dmenu`, `dmenu_path`, and `stest` are used consistently.
