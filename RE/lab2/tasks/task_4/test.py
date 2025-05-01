encrypted = "kaljv44o<kk5k<<:5<89<k:k54k4oi9<n9l<:p"
key = 13
flag = ''.join([chr(ord(c) ^ key) for c in encrypted])
print(flag)
