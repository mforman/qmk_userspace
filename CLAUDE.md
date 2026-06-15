# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

`qmk` is not installed locally. Build via Docker (`qmk_firmware` must be cloned alongside this repo):

```sh
docker run --rm \
  -w /qmk_firmware \
  -v /Users/mforman/src/qmk_firmware:/qmk_firmware:z \
  -v /Users/mforman/src/qmk_userspace:/qmk_userspace:z \
  -e QMK_USERSPACE=/qmk_userspace \
  ghcr.io/qmk/qmk_cli \
  bash -c "git config --global --add safe.directory /qmk_firmware && \
           git config --global --add safe.directory /qmk_firmware/lib/chibios && \
           git config --global --add safe.directory /qmk_firmware/lib/chibios-contrib && \
           git config --global --add safe.directory /qmk_userspace && \
           make SILENT=true -r -R -C /qmk_firmware -f builddefs/build_keyboard.mk all \
           KEYBOARD=crkbd/rev1 KEYMAP=mforman QMK_BIN=qmk"
```

**Pitfalls:** `SILENT=true` is **required** (not optional noise suppression) — the `qmk_cli` image uses `dash` as `/bin/sh`, which chokes on the `$(SILENT) ||` pattern in `common_rules.mk` without it. The `safe.directory` entries for ChibiOS submodules are also required or the version-string step fails.

Output: `qmk_firmware/.build/crkbd_rev1_mforman.uf2` (also copied to repo root).

Flash both halves the same `.uf2` via BOOTSEL or `QK_BOOT`.

**Pitfall:** `qmk.json` must be strict JSON (no trailing commas). The `qmk_cli` wrapper uses `json.loads` — if it fails validation it silently wipes `QMK_USERSPACE`, breaking community module lookup with a cryptic "Module not found" error.

## Architecture

The repo is a [QMK userspace](https://docs.qmk.fm/newbs_external_userspace) — a standalone overlay that builds against a separate `qmk_firmware` checkout without forking it.

### File layout

```
users/mforman/          # Shared user code, compiled into every keymap
  mforman.h             # Layer enum, key aliases, HRM defines, layer macros
  mforman.c             # process_record_user, tap dance, layer callbacks
  config.h              # Timing: TAPPING_TERM, FLOW_TAP_TERM, CHORDAL_HOLD
  rules.mk              # Feature flags shared across keymaps
  combos.def            # gboards-style combo definitions (COMB macro)
  oled/                 # OLED rendering (conditionally compiled)
  switcher/             # App-switcher helper (conditionally compiled)

keyboards/crkbd/rev1/keymaps/mforman/
  keymap.c              # LAYOUT_crkbd_wrapper + chordal_hold_layout
  keymap.json           # Community modules: getreuer/lumino, getreuer/palettefx
  config.h              # Hardware config: EE_HANDS, RGB, OLED font path
  rules.mk              # Board config: RP2040, RGB_MATRIX, OLED driver

modules/getreuer/       # Git submodule — Getreuer community modules
```

### Key design decisions

**Home row mods** follow CASG order (Ctrl-Alt-Shift-GUI, pinky→index on each hand). Mac-native: no Karabiner entry for this keyboard, unlike the ZMK boards. `CG_TOGG` on the ADJUST layer swaps to Windows order if needed.

**Layers** activate via tri-layer: `_LOWER` + `_RAISE` simultaneously → `_ADJUST`. Defined in `layer_state_set_user` with `update_tri_layer_state`.

**MAGIC_SHIFT** (`LSFT_T(KC_F24)`) on right thumb — hold = shift; tap behavior in `process_record_user`:
- If shift is active (mod or one-shot): caps word
- If last alpha was within 1200 ms: repeat that character
- Otherwise: one-shot shift

Alpha tracking for MAGIC_SHIFT: `last_alpha_*` statics updated on every key press. Basic non-alpha keycodes (`> KC_TRANSPARENT && < 0x100`) clear the valid flag (word boundary). MAGIC_SHIFT is excluded from this tracking to prevent its own initial press (tap.count=0, tap_kc=KC_F24) from clobbering the state.

**Flow Tap** (`FLOW_TAP_TERM 150`): forces mod-tap keys to resolve as tap when pressed within 150 ms of the previous key — equivalent to ZMK's `require-prior-idle-ms`.

**Tap dance nav keys** (`TD(NAV_*)` on LOWER layer): tap = arrow/bspc/del, hold = line/doc navigation. The tap fallback fires on release if the dance didn't finish (handled in `process_record_user`). `KC_HOME`/`KC_END` holds strip Ctrl to prevent accidental doc-start/doc-end.

**Combos** use gboards-style `COMB` macros in `combos.def`, included via `#include "g/keymap_combo.h"` (generated at build time from `VPATH += keyboards/gboards/`).

**Community modules** (`keymap.json`): `getreuer/lumino` and `getreuer/palettefx` are loaded from `modules/getreuer/` submodule. These provide RGB effects; the ADJUST layer exposes their controls. Must use strict JSON in `keymap.json`.
