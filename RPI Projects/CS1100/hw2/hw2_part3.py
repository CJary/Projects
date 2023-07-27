#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Sep 17 22:26:19 2022

@author: jarychen
"""
#function for the number of happy and sad characters
def number_happy(sentence):
    sentence = str.lower(sentence)
    hapc = 0
    hapc += sentence.count('laugh')
    hapc += sentence.count('happiness')
    hapc += sentence.count('love')
    hapc += sentence.count('excellent')
    hapc += sentence.count('good')
    hapc += sentence.count('smile')  
    return hapc

def number_sad(sentence):
    sentence = str.lower(sentence)
    sadc = 0
    sadc += sentence.count('bad')
    sadc += sentence.count('sad')
    sadc += sentence.count('terrible')
    sadc += sentence.count('horrible')
    sadc += sentence.count('problem')
    sadc += sentence.count('hate')
    return sadc


sentence = input('Enter a sentence => ')

#variables for the + and - 
plus = (number_happy(sentence))*'+'
minus = (number_sad(sentence))*'-'

print(sentence)
print('Sentiment:',plus+minus)
if len(plus)>len(minus):
    print('This is a happy sentence.')
elif len(plus)<len(minus):
    print('This is a sad sentence.')
else:
    print('This is a neutral sentence.')

