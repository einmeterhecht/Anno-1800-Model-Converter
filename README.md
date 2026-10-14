# Anno 1800 Model Converter    <img width="128" align="center" src="https://github.com/kskudlik/Anno-1800-Model-Converter/blob/master/resources/icon_anim.gif?raw=true" alt="Icon"/>
[![Build Status](https://dev.azure.com/kskudlik/Anno-1800-Model-Converter/_apis/build/status/kskudlik.Anno-1800-Model-Converter?branchName=master)](https://dev.azure.com/kskudlik/Anno-1800-Model-Converter/_build/latest?definitionId=1&branchName=master)

This model converter for the Anno Series - allows you to convert from and into their proprietary .rdm format

## Building

Requires `g++` (or `clang++`) and `make`. Clone with submodules (spdlog is a header-only dependency):

```
git submodule update --init
```

| Command                | Result                                                   |
| ---------------------- | -------------------------------------------------------- |
| `make`                 | `build/linux/rdm-converter`                              |
| `make windows`         | `build/windows/rdm-converter.exe` (cross-compiled, needs `x86_64-w64-mingw32-g++` and `windres`, e.g. `apt install mingw-w64`) |
| `make test`            | converts all sample `.rdm` files and compares with `Unit-Tests/rdm-files/expected` |
| `make test-windows`    | same, running the Windows binary through `wine`          |

On Windows you can build natively with [w64devkit](https://github.com/skeeto/w64devkit) (`make` in its shell).
