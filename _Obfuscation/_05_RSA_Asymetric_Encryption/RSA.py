import Cryptodome
from Cryptodome.PublicKey import RSA
from Cryptodome import Random

secret_code = "Unguessable"
key = RSA.generate(2048)
encrypted_key = key.exportKey(passphrase=secret_code, pkcs=8,
                              protection="scryptAndAES128-CBC")

file_out = open("rsa_key.bin", "wb")
file_out.write(encrypted_key)
file_out.close()

print (key.publickey().exportKey())

encoded_key = open("rsa_key.bin", "rb").read()
key = RSA.import_key(encoded_key, passphrase=secret_code)

print (key.publickey().exportKey())