# Anno 1800 Model Converter    <img width="128" align="center" src="https://github.com/kskudlik/Anno-1800-Model-Converter/blob/master/resources/icon_anim.gif?raw=true" alt="Icon"/>

This model converter for the Anno Series - allows you to convert from and into their proprietary .rdm format

---

This repo is a fork of [kskudlik's RDM <-> OBJ Converter](ttps://github.com/kskudlik/Anno-1800-Model-Converter) with a vibecoded build system to compile on linux.

## Building

Run `git submodule update --init` once to fetch the spdlog dependency.

Requires `g++` (or `clang++`) and `make`.

| Command                | Builds                                                   |
| ---------------------- | -------------------------------------------------------- |
| `make`                 | `build/linux/rdm-converter`                              |
| `make windows`         | `build/windows/rdm-converter.exe` (cross-compiled, needs `x86_64-w64-mingw32-g++` and `windres`, e.g. `apt install mingw-w64`) |
| `make test`            | converts all sample `.rdm` files and compares with `Unit-Tests/rdm-files/expected` |
| `make test-windows`    | same, running the Windows binary through `wine`          |

On Windows, you can build natively with [w64devkit](https://github.com/skeeto/w64devkit) (`make` in its shell).
