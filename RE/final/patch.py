def patch(input_path, output_path):
    with open(input_path, 'rb') as f:
        data = bytearray(f.read())
    
    # This appears at address 0x004011c9 in Ghidra
    pattern = bytes.fromhex('6A 1C 68 08 20 40 00')
    pos = data.find(pattern)
    
    if pos == -1:
        raise ValueError("Error")
    
    # Patch: Change 0x1C (28 bytes) to 0xFF (process up to 255 bytes or until null)
    data[pos + 1] = 0xFF
    
    # Write in file
    with open(output_path, 'wb') as f:
        f.write(data)
    print(f"Successfully patched: {output_path}")

patch('1.exe', '1_patched.exe')
