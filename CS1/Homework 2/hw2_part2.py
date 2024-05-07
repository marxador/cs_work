# -*- coding: utf-8 -*-
"""
Created on Thu Sep 14 12:57:50 2023

@author: mjethree
"""

# ask user for a string to encrypt
string = input('Enter a string to encode ==> ').strip()
print(string)
print()

# methods to encrypt and decrypt the given string
def replacement(word, search, replace) :
    if(word.find(search) >= 0) :
        word = word.replace(search, replace)
    return word
def encrypt(word) :
    word = replacement(word, ' a', '%4%')
    word = replacement(word, 'he', '7!')
    word = replacement(word, 'e', '9(*9(')
    word = replacement(word, 'y', '*%$')
    word = replacement(word, 'u', '@@@')
    word = replacement(word, 'an', '-?')
    word = replacement(word, 'th', '!@+3')
    word = replacement(word, 'o', '7654')
    word = replacement(word, '9', '2')
    word = replacement(word, 'ck', '%4')
    return word
def decrypt(word) :
    word = replacement(word, '%4', 'ck')
    word = replacement(word, '2', '9')
    word = replacement(word, '7654', 'o')
    word = replacement(word, '!@+3', 'th')
    word = replacement(word, '-?', 'an')
    word = replacement(word, '@@@', 'u')
    word = replacement(word, '*%$', 'y')
    word = replacement(word, '9(*9(', 'e')
    word = replacement(word, '7!', 'he')
    word = replacement(word, '%4%', ' a')
    return word

# encrypts and decrypts the given string then prints the requested information
encrypt = encrypt(string)
decrypt = decrypt(encrypt)
print('Encrypted as ==> {0}'.format(encrypt))
print('Difference in length ==> {0}'.format((len(encrypt) - len(string))))
print('Deciphered as ==> {0}'.format(decrypt))
if(string == decrypt) :
    print('Operation is reversible on the string.')
else :
    print('Operation is not reversible on the string.')