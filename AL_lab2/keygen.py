import hashlib
import sys

def generate_license(hwid):
    md5_hash = hashlib.md5(hwid.encode()).hexdigest()
    byte_pairs = [md5_hash[i:i+2] for i in range(0, len(md5_hash), 2)]
    reversed_pairs = byte_pairs[::-1]
    license_key = ''.join(reversed_pairs)
    return license_key

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python keygen.py <HWID>")
        sys.exit(1)
    hwid = sys.argv[1]
    license_key = generate_license(hwid)
    print(f"HWID: {hwid}")
    print(f"License Key: {license_key}")
