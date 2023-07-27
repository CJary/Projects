#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct 11 12:29:41 2022

@author: jarychen
"""

'''
program will return the strength of a password 
and each component that affects the score of how 
strong the password is
'''

import hw4_util


#function that returns the score from just length
def length(passw):
    lscore = 0
    
    lpassw = len(passw)
    
    #Length score
    if lpassw == 6 or lpassw == 7:
        lscore +=1
    elif lpassw == 8 or lpassw == 9 or lpassw == 10:
        lscore +=2
    elif lpassw > 10:
        lscore +=3
    return lscore


#function that returns the score from just cases
def cases(passw):
    cscore = 0
    letterUP = 0
    letterLOW = 0
    for letter in passw:
        if ord(letter) >= 65 and ord(letter) <= 90:
            letterUP +=1
        elif ord(letter) >= 97 and ord(letter) <= 122:
            letterLOW +=1
    if letterUP >= 2 and letterLOW >= 2:
        cscore +=2
    elif letterUP >= 1 and letterLOW >= 1:
        cscore +=1
    return cscore


#function that returns the score from just digits
def digits(passw):
    dscore = 0
    number = 0
    for digits in passw:
        if ord(digits) >= 48 and ord(digits) <= 57:
            number +=1
    if number >= 2:
        dscore +=2
    elif number >= 1:
        dscore +=1
    return dscore


#function that returns the score from just punctuation
def punt(passw):
    pun1 = 0 
    pun2 = 0
    for punctuation in passw:
        if punctuation == '!' or punctuation == '@' or punctuation == '#' or punctuation == '$':
            pun1 =1 
        elif punctuation == '%' or punctuation == '^' or punctuation == '&' or punctuation == '*':
            pun2 =1   
    return (pun1,pun2)


#function that returns the score from just NY License
def NYL(passw):
    nscore = 0
    a_z = 0
    num = 0
    for letters in passw:
        if letters.isalpha() and a_z < 3:
            a_z += 1
        elif letters.isnumeric() and num < 4 and a_z == 3:
            num += 1
        if a_z == 3 and num == 4:
            nscore -= 2
    return nscore


#function that returns the score from just Common password
def common(passw):
    comscore = 0
    passw = passw.lower()
    wordl = hw4_util.part1_get_top()
    for words in wordl:
        if passw == words:
            comscore = -3
    return comscore
            
    
#input
password = input('Enter a password => ')
print(password)


#output if the rules affected the score
if length(password) > 0:
    print('Length: +',length(password),sep='')
if cases(password) > 0:
    print('Cases: +',cases(password),sep='')
if digits(password) > 0:
    print('Digits: +',digits(password),sep='')
if (punt(password))[0] > 0:
    print('!@#$: +',(punt(password))[0],sep='')
if (punt(password))[1] > 0:
    print('%^&*: +',(punt(password))[1],sep='')
if NYL(password) == -2:
    print('License: -2')
if common(password) == -3:
    print('Common: -3')


#Total score
total = length(password) + cases(password) + digits(password) + (punt(password))[0] + (punt(password))[1] + NYL(password) + common(password)
print('Combined score: ',total,sep='')


#Gives the rating of the password in terms of Rejected, Poor, Fair, Good, and Excellent
if total <= 0:
    print('Password is rejected')
if total == 1 or total == 2:
    print('Password is poor')
if total == 3 or total ==4:
    print('Password is fair')
if total == 5 or total == 6:
    print('Password is good')
if total >= 7:
    print('Password is excellent')


