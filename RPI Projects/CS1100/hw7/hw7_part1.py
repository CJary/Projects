#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Nov  7 22:53:10 2022

@author: jarychen
"""

'''
This program will go through each word provided by a file
and see if the word is valid, if not it tries to correct it 
by either drop, insert, swap, replace.
'''

''' MAIN BODY '''
if __name__ == "__main__":

    ''' Inputs '''
    dictF = input('Dictionary file => ').strip()
    print(dictF)
    inpF = input('Input file => ').strip()
    print(inpF)
    keyF = input('Keyboard file => ').strip()
    print(keyF)


    ''' List of all the alphabets '''
    alphalist = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']


    ''' Dictionary of the file  '''
    diction = dict()
    for line in open(dictF):
        line = line.split(',')
        diction[line[0]] = line[1].replace('\n', '')


    ''' Dictionary of the Keyboard File '''
    keydict = dict()
    for line in open(keyF):
        line = line.split()
        keydict[line[0]] = line[1:len(line)+1]


    ''' Goes through each word in the inputfile '''
    for word in open(inpF):
        word = word.replace('\n', '').strip()
        spaces = ' ' * (15 - len(str(word)))

        if word in diction:
            print('{}{} -> FOUND'.format(spaces, word))
        else:
            validw = []


            ''' DROP '''
            dropW = ''
            for i in range(0, len(word)):
                if i == 0 and word[i+1:len(word)+1] in diction:
                    dropW = word[i+1:len(word)+1]
                    validw.append((diction[dropW], dropW))

                elif i > 0:
                    dropW = word[0:i] + word[i+1:len(word)+1]

                    if dropW in diction:
                        validw.append((diction[dropW], dropW))


            ''' INSERT '''
            wordl = list(word)
            for letter in range(0, len(word)+1):
                for alpha in alphalist:
                    wordl.insert(letter, alpha)
                    str_wordl = ''.join(wordl)

                    if str_wordl in diction:
                        validw.append((diction[str_wordl], str_wordl))
                    wordl.pop(letter)


            ''' SWAP '''
            swapW = ''
            for i in range(0, len(word)-1):

                if i == 0:
                    swapW += word[i+1] + word[i] + word[i+2:len(word)+1]

                    if swapW in diction:
                        validw.append((diction[swapW], swapW))
                    swapW = ''

                elif i > 0:
                    swapW += word[0:i] + word[i+1] + \
                        word[i] + word[i+2:len(word)+1]

                    if swapW in diction:
                        validw.append((diction[swapW], swapW))
                    swapW = ''


            ''' REPLACE '''
            repW = list(word)
            for i in range(0, len(word)):
                repkey = keydict[word[i]]

                for letter in range(0, len(repkey)):
                    repW[i] = repkey[letter]
                    str_repw = ''.join(repW)

                    if str_repw in diction:
                        validw.append((diction[str_repw], str_repw))

                repW = list(word)


            ''' PRINT OUT '''
            validw = list(set(validw))
            validw.sort(reverse = True)

            if validw == []:
                print('{}{} -> NOT FOUND'.format(spaces, word))

            elif len(validw) > 0:
                superlist = []
                spavalid = ' ' * (3-len(str(len(validw))))

                if len(validw) > 3:
                    for i in range(0, 3):
                        superlist.append(validw[i][1])
                else:
                    for ii in validw:
                        superlist.append(ii[1])
                print('{}{} -> FOUND{}{}:  {}'.format(spaces, word,
                      spavalid, len(validw), ' '.join(superlist)))
