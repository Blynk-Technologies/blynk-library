#!/usr/bin/env python3
"""Compile and run the offline ESP8266 TLS adapter tests with a host C++ compiler.

Usage: python3 tests/run_esp8266_ssl.py [--cxx g++]
Arduino/SDK headers are replaced with empty shims; their minimal interfaces are
defined in esp8266_ssl.cpp. The production adapter headers are used unchanged.
This checks connection control flow, not BearSSL or actual SNTP networking.
"""

import argparse
import os
from pathlib import Path
import subprocess
import tempfile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--cxx", default=os.environ.get("CXX", "g++"))
    args = parser.parse_args()
    root = Path(__file__).resolve().parent.parent
    with tempfile.TemporaryDirectory(prefix="blynk-ssl-test-") as directory:
        build = Path(directory)
        for header in ("ESP8266WiFi.h", "WiFiClientSecure.h", "Client.h",
                       "BlynkWidgets.h"):
            (build / header).write_text("// Host test shim.\n", encoding="utf-8")
        (build / "version.h").write_text(
            "#define ESP_SDK_VERSION_NUMBER 0x030000\n"
            "#define wificlientbearssl_h\n", encoding="utf-8")
        executable = build / ("test.exe" if os.name == "nt" else "test")
        subprocess.run([
            args.cxx, "-std=c++11", "-Wall", "-Wextra", "-Werror",
            "-I", str(build), "-I", str(root / "src"),
            str(root / "tests" / "esp8266_ssl.cpp"), "-o", str(executable),
        ], check=True)
        subprocess.run([str(executable)], check=True, timeout=10)


if __name__ == "__main__":
    main()
