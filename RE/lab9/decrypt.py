def transform_password(hardcoded_str):
    data = bytearray(hardcoded_str.encode())
    
    # Initial XOR on first byte
    if len(data) > 0:
        data[0] ^= 0xAB
    
    # Process subsequent bytes
    for i in range(1, len(data)):
        if data[i] == 0:
            break
        
        # Step 1: Subtract index
        data[i] = (data[i] - i) & 0xFF
        
        # Step 2: XOR with previous byte
        data[i] ^= data[i-1]
        
        # Step 3: Add previous byte
        data[i] = (data[i] + data[i-1]) & 0xFF
        
        # Step 4: XOR with previous byte again
        data[i] ^= data[i-1]
        
        # Step 5: XOR with 9th byte (index 8)
        if len(data) > 8:
            data[i] ^= data[8]
        
        # Step 6: If zero, set to 1
        if data[i] == 0:
            data[i] = 1
    
    # Convert to hex string
    password = ''.join(f'{b:02x}' for b in data if b != 0)
    return password


init_password = "THEPASSWORDISEASYTOCRACK"
password = transform_password(init_password)
print(f"The correct password is: {password}")
