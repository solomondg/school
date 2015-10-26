rot = int(input("Enter what ROT you want: "))
toencrypt = input("Enter string to be encrypted: ")
encrypted = []
for x in toencrypt:
    encrypted += chr(ord(x) + rot)
print (''.join(encrypted))
