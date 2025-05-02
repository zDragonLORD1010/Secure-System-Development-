#!/usr/bin/env python3

def patch_binary():
    original = "hack_app"
    patched = "hack_app_patched"
    patches = {
        0x159e: "9090",  # First JNE (0x75 0x09 → 0x90 0x90)
        0x15fc: "9090",   # Second JNE (0x75 0x33 → 0x90 0x90)
    }
    with open(original, "rb") as f:
        data = bytearray(f.read())
    for offset, patch in patches.items():
        data[offset:offset+2] = bytes.fromhex(patch)
    with open(patched, "wb") as f:
        f.write(data)
    import os
    os.chmod(patched, 0o755)
    print(f"Created {patched} with license checks disabled")

if __name__ == "__main__":
    patch_binary()
