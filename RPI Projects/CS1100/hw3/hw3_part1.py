#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Sep 30 21:15:27 2022

@author: jarychen
"""

'''
program that returns the average length per
sentence, readability, percentage of words 
that are "hard" in a paragraph
'''

import syllables # import syllables to use def find_num_syllables(word)

text = input('Enter a paragraph => ')
print(text)

text = text.split() 

#average sentence length
dots = 0
for word in text:
    dots += word.count('.')
ASL = len(text)/dots


#percent hard work
hardwlist = []
hardw = 0
for word in text:
    if syllables.find_num_syllables(word) >= 3 and word.count('-') == 0 and (word[len(word)-2])+(word[len(word)-1]) != ('es' or 'ed'):
        hardw += 1                                                        #^to combine the last 2 strings together^
        hardwlist.append(word)
PHW = (hardw/len(text))*100


#average number of syllabes
totals = 0
for word in text:
    totals += syllables.find_num_syllables(word)
ASYL = totals/len(text)


#GFRI
GFRI = 0.4*(ASL + PHW)


#FKRI
FKRI = round(206.835-1.015*ASL-86.4*ASYL, 2)


#print statements
print('Here are the hard words in this paragraph:\n', hardwlist, sep='')
print('Statistics: ASL:{0:.2f} PHW:{1:.2f}% ASYL:{2:.2f}'.format(
    ASL, PHW, ASYL))
print('Readability index (GFRI): {0:.2f}'.format(GFRI))
print('Readability index (FKRI):', FKRI)
