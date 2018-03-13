import Cryptodome
from Cryptodome.PublicKey import RSA
from Cryptodome import Random
#this is the RSA encryption protocol according to PKCS#1 OAEP
from Cryptodome.Cipher import PKCS1_OAEP

key = RSA.generate(2048)

#prints private key
print(key.exportKey(), '\n')

#prints public key
print(key.publickey().exportKey())

#this is the sender encrypting the message, so it uses the public key of intended reciever
cipher_rsa = PKCS1_OAEP.new(key.publickey())
encrypted_message = cipher_rsa.encrypt(b'Super Secret Message')
print("\nThe Message Encrypted:")
print(encrypted_message)


#this is the reciever of encrypted message, he has the private key
cipher_rsa = PKCS1_OAEP.new(key)
decrypted_message = cipher_rsa.decrypt(encrypted_message)
print("\nThe Message Decrypted:")
print(decrypted_message)

'''
Questions to Consider:

* What did this code just do? Is this how RSA would actually be implemented?
* How could you use RSA to sign/authenticate a message instead of encrypt a message?
* Can you think of any uses of Public Key algorithms on a CAN BUS?
* How credible is Cryptodome? Would a company trust these algorithms to encrypt user data?

'''