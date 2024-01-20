try:
    while True:
        a = input()
        cidr, port, allow = a.split()
        if cidr == '-':
            break
        prefix, length = cidr.split('/')
        slices = list(map(int, prefix.split('.')))
        ip = slices[0] * 256 ** 3 + slices[1] * 256 ** 2 + slices[2] * 256 + slices[3]
        print(bin(ip)[2:], length, port, allow)
    print("- 0 0 0")
    while True:
        a = input()
        ip, port = a.split()
        slices = list(map(int, ip.split('.')))
        ip = slices[0] * 256 ** 3 + slices[1] * 256 ** 2 + slices[2] * 256 + slices[3]
        print(bin(ip)[2:], port)

except Exception:
    pass
