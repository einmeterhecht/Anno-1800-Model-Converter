#!/usr/bin/env python3
"""Convert every rdm-files/*.rdm and compare it byte-for-byte with rdm-files/expected/*.obj.

Usage: unittest.py <converter-binary> [runner ...]   e.g. unittest.py rdm-converter.exe wine
"""
import pathlib, subprocess, sys, tempfile

here = pathlib.Path(__file__).resolve().parent / "rdm-files"


def normalize(path):  # Windows writes CRLF, the expected files use LF
    return pathlib.Path(path).read_bytes().replace(b"\r\n", b"\n")

cmd = sys.argv[2:] + [str(pathlib.Path(sys.argv[1]).resolve())]
failed = 0
with tempfile.TemporaryDirectory() as tmp:
    for rdm in sorted(here.glob("*.rdm")):
        out = pathlib.Path(tmp) / (rdm.stem + ".obj")
        subprocess.run(cmd + [str(rdm), str(out)], cwd=tmp, stdin=subprocess.DEVNULL,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        ok = out.is_file() and normalize(out) == normalize(here / "expected" / out.name)
        failed += not ok
        print("PASS" if ok else "FAIL", rdm.name)
print(f"{failed} failed" if failed else "all passed")
sys.exit(failed > 0)
