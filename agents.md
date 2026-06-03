# Agent Notes

This repo is being used to maintain a QMK keymap for a Ferris Sweep v2 with Choc v1 switches.

Primary keymap:

- Keyboard: `ferris/sweep`
- Keymap: `ferris_sweep_layout_split_3x5_2_2026-04-30`
- Main files:
  - `keyboards/ferris/keymaps/ferris_sweep_layout_split_3x5_2_2026-04-30/keymap.c`
  - `keyboards/ferris/keymaps/ferris_sweep_layout_split_3x5_2_2026-04-30/config.h`

## User Preferences

- Prefer a human-readable `keymap.c` with semantic layer names, helper macros, and custom functions over QMK Configurator JSON as the source of truth.
- Keep the layer names semantic:
  - `_ALPHA`
  - `_NUMPAD`
  - `_NAVIGATION`
  - `_SHIFT_NUMPAD`
- Keep the base thumb behavior simple:
  - Space is a plain space key.
  - Enter is a plain enter key.
  - The layer keys should be immediate `MO(...)` holds, not delayed layer-tap keys.
- The two layer keys together should activate `_SHIFT_NUMPAD` via tri-layer behavior.
- `_SHIFT_NUMPAD` should contain shifted number variants such as `!`, `@`, `#`, `$`, `%`, `^`, `&`, `*`, `(`, and `)`.
- Keep arrow keys on HJKL-style positions in `_NAVIGATION`.
- Keep an accessible Page Down key.
- Keep Backspace and Enter accessible from the left split while the right hand is on the mouse.

## Current Layer Placement Rules

- In `_NAVIGATION`, the left split should keep this punctuation shape:
  - Top row: `Esc`, `(`, `)`, `_`, `\`
  - Home row: `~`, `{`, `}`, `-`, `'`
  - Bottom row: `|`, `[`, `]`, `=`, `Tab`
- The bracket pairs should be vertically grouped:
  - parentheses on the top row
  - curly brackets directly below them
  - square brackets directly below those
- `\` belongs on the physical `T` key in `_NAVIGATION`.
- `_` belongs in the easier top-row punctuation slot that previously held pipe.
- `|` is seldom used and should live under `~` on the left split.
- `-` should be above `=` in `_NAVIGATION`.
- In `_NUMPAD`, Backspace and Enter should mirror the top-right and center-right positions of a MacBook Pro keyboard, but relative to the left split:
  - Backspace on the physical `T` position
  - Enter on the physical `G` position
- Do not move those Backspace/Enter keys to the right split when interpreting that preference.
- Preserve the right-side numpad operator shape unless the user says otherwise:
  - top-right `-`
  - home-row-right `+`

## Home-Row Mods

- Use proper home-row mods on the main home row, not the bottom row.
- Current intended home-row mod shape:
  - Left: `A` Shift, `S` Control, `D` Alt, `F` GUI/Command
  - Right: `J` GUI/Command, `K` Alt, `L` Control, `;` Shift
- Home-row mods should activate quickly enough to feel responsive.
- The user has wanted a balanced home-row-mod flavor with:
  - tapping term originally requested as 380 ms, later made faster
  - quick tap period 175 ms
  - prior-idle / flow-tap style behavior
  - permissive hold behavior
- Do not let GUI home-row mods emit their tap key after being used as a mouse-assisted modifier. In particular, holding `F` as Command and clicking in Xcode must not type `f` on release. This is why retro tapping is disabled for the GUI home-row mods.

## App Switcher

- The user often keeps the right hand on the mouse and wants app switching to be available from the left split.
- App switching should work like macOS Command-Tab:
  - Hold the left-side layer key.
  - Press the forward key once to open the switcher and move forward.
  - Press it again to keep moving forward.
  - Press the backward key to move backward.
  - Release the layer key to release Command and select the highlighted app.
- Use custom keycodes for this behavior rather than plain `LGUI(KC_TAB)`, because the Command modifier must remain held.
- Keep the physical direction intuitive:
  - backward is on the left
  - forward is on the right
- Put app switching on the left-triggered layer, not on `_NAVIGATION`, because `_NAVIGATION` is triggered from the right split.
- Prefer strong/easy left-hand positions for app switching. The current intent is `_NUMPAD` left home-row positions:
  - `D` position: app backward
  - `F` position: app forward
- The user asked whether app switcher actions can repeat while held. That behavior is possible with a repeat timer in `matrix_scan_user`, but it has not necessarily been implemented unless present in `keymap.c`.

## Mouse Buttons

- `MS_BTN1` / `MB1` is mouse left click.
- `MS_BTN2` / `MB2` is mouse right click.
- The user did not know what these were and did not express a need to preserve them. Do not prioritize keeping mouse button bindings over app switching, Backspace, or Enter.

## Printable Keymap

- The user wants a printable keymap PDF with only the first overview page, not separate per-layer pages.
- Current generated artifacts live at the repo root:
  - `ferris-keymap.json`
  - `ferris-keymap.yaml`
  - `ferris-sweep-keymap.pdf`
- The PDF should show all layers in one overview page using the `ferris/sweep` `LAYOUT_split_3x5_2` geometry.
- Keep the overview labels short, especially for layer keys and app switcher actions:
  - `NUM`
  - `NAV`
  - `App Back`
  - `App Fwd`
- If `keymap-drawer` is available, it is fine to use it, but do not generate a multi-page PDF. If local PDF tooling is unavailable, a small custom renderer that uses `ferris-keymap.json` and `keyboards/ferris/sweep/keyboard.json` is acceptable.
- Keep generated diagram sources in sync with `keymap.c` when key placement changes:
  - `ferris-keymap.json`
  - `ferris-keymap.yaml`
  - `ferris-sweep-layout_split_3x5_2_2026-04-30.json`, if present

## Verification

- After editing the keymap, run:

```sh
qmk compile -kb ferris/sweep -km ferris_sweep_layout_split_3x5_2_2026-04-30
```

- If printable artifacts are affected, regenerate the PDF after the compile passes.
