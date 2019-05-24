msg = b'PTNLSNM,0125,01'
checksum = 0
for b in msg:
    checksum ^= b
print("${}*{:02X}".format(msg.decode('ascii'),checksum))
