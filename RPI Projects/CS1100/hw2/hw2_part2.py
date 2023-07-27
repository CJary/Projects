#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Sep 17 21:25:27 2022

@author: jarychen
"""

#function to encrypt and decrypt word
def encrypt(word):
    word = word.replace(' a','%4%')
    word = word.replace('he','7!')
    word = word.replace('e','9(*9(')
    word = word.replace('y','*%$')
    word = word.replace('u','@@@')
    word = word.replace('an','-?')
    word = word.replace('th','!@+3')
    word = word.replace('o','7654')
    word = word.replace('9','2')
    word = word.replace('ck','%4')
    return word 

def decrypt(word):
    word = word.replace('%4','ck')
    word = word.replace('2','9')
    word = word.replace('7654','o')
    word = word.replace('!@+3','th')
    word = word.replace('-?','an')
    word = word.replace('@@@','u')
    word = word.replace('*%$','y')
    word = word.replace('9(*9(','e')    
    word = word.replace('7!','he')
    word = word.replace('%4%',' a')
    return word

word = input('Enter a string to encode ==> ')

#all the variables
loriginal = len(word)
lencrypt = len(encrypt(word))
encryptw = encrypt(word)

print(word)
print('\nEncrypted as ==>',encrypt(word))
print('Difference in length ==>',abs(loriginal-lencrypt))
print('Deciphered as ==>',decrypt(encryptw))
if word == decrypt(encryptw):
    print('Operation is reversible on the string.')
else:
    print('Operation is not reversible on the string.')
    
