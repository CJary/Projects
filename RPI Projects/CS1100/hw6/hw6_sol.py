#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  1 21:23:38 2022

@author: jarychen
"""

'''
This program will take in 2 files and output the analyze
of each file and the summery between them
'''

# Function that returns the text that contains only words
def parsing(text):
    
    words = []
    for line in text:
        words.append(line.split())
    words = [i for i in words if i]
    
    engw = []
    for lists in words:
        for words in lists:
            wor = ''
            for letter in words:
                if letter.isalpha() == True:
                    wor = wor + letter.lower()
            if wor != '':
                engw.append(wor)
                
    return engw

# Function that returns the text without the stop words
def remove(text_w, stop):
    
    stop_words = []
    for words in text_w:
        if words in stop:
            stop_words.append(words)
    
    for words in stop_words:
        text_w.remove(words)
    
    return text_w

# Function that gets the maximum length of a word in a group of sentence
def maxlength_w(text_w):
    
    maxl_w = 0
    for word in text_w:
        if len(word) >= maxl_w:
            maxl_w = len(word)
            
    return maxl_w

# Function that returns a list of word with that certain amount of length
def wordset(file,length):
    word_list = []
    word_count = 0
    for word in set(file):
        if len(word) == length:
            word_list.append(word)
            word_count += 1
        
    word_list.sort()
    word_listn = ' '.join(word_list)
    
    return [word_list, word_listn, word_count]

# Function that returns a list of pairs, length of all pairs, and the set pairs
def word_pair(file):
    pairs = []
    for i in range(len(file)):
        if i == len(file):
            break
            
        for ii in range(i + 1, max_sep + i + 1):
            if ii == len(file):
                break
            else:
                pairs.append(tuple(sorted([file[i], file[ii]])))
        
    totalp = len(pairs)
    Rpair = pairs
    pairs = sorted(list(set(pairs)))
    
    return [totalp, pairs, Rpair]
    

''' MAIN BODY '''
if __name__ == "__main__":
    
    ''' INPUTS '''
    file1 = input('Enter the first file to analyze and compare ==> ')
    print(file1)
    file2 = input('Enter the second file to analyze and compare ==> ')
    print(file2)
    max_sep = input('Enter the maximum separation between words in a pair ==> ')
    print(max_sep)
    max_sep = int(max_sep)
    print()
    
    ''' STOP FILES STUFF '''
    stop_file = open('stop.txt', encoding = "utf-8")
    stop_file_r = stop_file.readlines()
    stop_set = set(parsing(stop_file_r))
    
    
    ''' FILE 1 STUFF '''
    file1_o = open(file1, encoding = "utf-8")
    file1_r = file1_o.readlines()
    file1_w = parsing(file1_r)
        
    
    ''' FILE 2 STUFF '''
    file2_o = open(file2, encoding = "utf-8")
    file2_r = file2_o.readlines()
    file2_w = parsing(file2_r)
    
    
    ''' REMOVE STOP WORDS '''
    f1_new = remove(file1_w,stop_set)
    f2_new = remove(file2_w,stop_set)

    
    ''' PRINT EVALUATING '''
    print('Evaluating document {}'.format(file1))
    
    
    ''' AVERAGE '''
    avgf1 = sum(len(word) for word in f1_new)/(len(f1_new))
    avgf2 = sum(len(word) for word in f2_new)/(len(f2_new)) 
    print('1. Average word length: {:.2f}'.format(avgf1))


    ''' Ratio '''
    lfile1 = len(f1_new)
    lfile1_set = len(set(f1_new))
    dratio1 = lfile1_set/lfile1
    
    lfile2 = len(f2_new)
    lfile2_set = len(set(f2_new))
    dratio2 = lfile2_set/lfile2
    print('2. Ratio of distinct words to total words: {:.3f}'.format(dratio1))
    
    
    ''' WORDS SET FOR FILE 1'''
    superlist1 = []
    print('3. Word sets for document {}:'.format(file1))
    length = 1
    while length <= maxlength_w(f1_new):
        wlists = wordset(f1_new, length)[0]
        wlists_n = wordset(f1_new, length)[1]
        wordc = wordset(f1_new, length)[2]
        
        slength = ' ' * (4-len(str(length)))
        scount = ' ' * (4 - len(str(wordc)))
        
        if wordc > 0 and len(wlists) <= 6:
            print(('{}{}:{}{}: {}'.format(
                slength, length, scount, wordc, wlists_n)))
            superlist1.append(list(wlists_n.split()))
            
        elif wordc > 0 and len(wlists) > 6:
            word_3l = wlists[0:3]
            word_3l = ' '.join(word_3l)
            
            word_3r = wlists[-3:]
            word_3r = ' '.join(word_3r)

            print(('{}{}:{}{}: {} ... {}'.format(
                slength, length, scount, wordc, word_3l, word_3r)))
            superlist1.append(list(wlists_n.split()))
            
        else:
            print(('{}{}:{}{}:'.format(
                slength, length, scount, wordc)))
            superlist1.append([])

        length += 1
        
    ''' WORD PAIRS FOR FILE 1 '''
    print('4. Word pairs for document {}'.format(file1))
    
    totalp_1 = word_pair(f1_new)[0]
    pairs_1 = word_pair(f1_new)[1]
    Rpairs_1 = word_pair(f1_new)[2]
    print('  {} distinct pairs'.format(len(pairs_1)))
    
    if len(pairs_1) >= 10:
        for i in range(0,5):
            pairs_1[i] = ' '.join(pairs_1[i])
            print('  {}'.format(pairs_1[i]))
        print('  ...')
        for i in range(-5,0,1):
            pairs_1[i] = ' '.join(pairs_1[i])
            print('  {}'.format(pairs_1[i]))
    elif len(pairs_1) == 5:
        for i in range(0,5):
            pairs_1[i] = ' '.join(pairs_1[i])
            print('  {}'.format(pairs_1[i]))
            
    
    ''' RATIO BETWEEN DISTINCT PAIRS AND TOTAL PAIRS '''
    ratio5_1 = len(pairs_1)/totalp_1
    print('5. Ratio of distinct word pairs to total: {:.3f}'.format(ratio5_1))
    
    
    ''' OUTPUT FOR FILE 2 '''
    print()
    print('Evaluating document {}'.format(file2))
    print('1. Average word length: {:.2f}'.format(avgf2))
    print('2. Ratio of distinct words to total words: {:.3f}'.format(dratio2))
    print('3. Word sets for document {}:'.format(file2))
    
    superlist2 = []
    length2 = 1
    while length2 <= maxlength_w(f2_new):
        wlists2 = wordset(f2_new, length2)[0]
        wlists_n2 = wordset(f2_new, length2)[1]
        wordc2 = wordset(f2_new, length2)[2]
        
        slength = ' ' * (4- len(str(length2)))
        scount = ' ' * (4 - len(str(wordc2)))
        
        if wordc2 > 0 and len(wlists2) <= 6:
            print(('{}{}:{}{}: {}'.format(
                slength, length2, scount, wordc2, wlists_n2)))
            superlist2.append(list(wlists_n2.split()))
            
        elif wordc2 > 0 and len(wlists2) > 6:
            word_3l_2 = wlists2[0:3]
            word_3l_2 = ' '.join(word_3l_2)
            
            word_3r_2 = wlists2[-3:]
            word_3r_2 = ' '.join(word_3r_2)

            print(('{}{}:{}{}: {} ... {}'.format(
                slength, length2, scount, wordc2, word_3l_2, word_3r_2)))
            superlist2.append(list(wlists_n2.split()))
            
        else:
            print(('{}{}:{}{}:'.format(
                slength, length2, scount, wordc2)))
            superlist2.append([])
            
        length2 += 1
        
    print('4. Word pairs for document {}'.format(file2))
    
    totalp_2 = word_pair(f2_new)[0]
    pairs_2 = word_pair(f2_new)[1]
    Rpairs_2 = word_pair(f2_new)[2]
    print('  {} distinct pairs'.format(len(pairs_2)))
    
    if len(pairs_2) >= 10:
        for i in range(0,5):
            pairs_2[i] = ' '.join(pairs_2[i])
            print('  {}'.format(pairs_2[i]))
        print('  ...')
        for i in range(-5,0,1):
            pairs_2[i] = ' '.join(pairs_2[i])
            print('  {}'.format(pairs_2[i]))
    elif len(pairs_2) == 5:
        for i in range(0,5):
            pairs_2[i] = ' '.join(pairs_2[i])
            print('  {}'.format(pairs_2[i]))
    
    ratio5_2 = len(pairs_2)/totalp_2
    print('5. Ratio of distinct word pairs to total: {:.3f}'.format(ratio5_2))
        
    
    ''' SUMMARY '''
    print()
    print('Summary comparison')
    if avgf1 > avgf2:
        print('1. {} on average uses longer words than {}'.format(file1,file2))
    elif avgf2 > avgf1:
        print('1. {} on average uses longer words than {}'.format(file2,file1))
        
    match_w = len(set(f1_new) & set(f2_new))
    union_w = len(set(f1_new) | set(f2_new))
    jacc_w = match_w/union_w
    print('2. Overall word use similarity: {:.3f}'.format(jacc_w))
    
    print('3. Word use similarity by length:')
    maxl = max(maxlength_w(f1_new),maxlength_w(f2_new))
    minl = min(maxlength_w(f1_new),maxlength_w(f2_new))
    for i3 in range(0,maxl):
        spaces_s3 =  ' ' * (4-len(str(i3+1)))
        if i3 > minl-1:
            jacc_l = 0
        elif (superlist1[i3] == [] or superlist2[i3] == []) and i3 <= minl:
            jacc_l = 0
        elif i3 <= minl:
            match_l = len(set(superlist1[i3]) & set(superlist2[i3]))
            union_l = len(set(superlist1[i3]) | set(superlist2[i3]))
            jacc_l = match_l/union_l
        else:
            jacc_l = 0
        
        print('{}{}: {:.4f}'.format(spaces_s3, i3+1, jacc_l))

    match_p = len(set(Rpairs_1) & set(Rpairs_2))
    union_w = len(set(Rpairs_1) | set(Rpairs_2))
    jacc_p = match_p/union_w
    print('4. Word pair similarity: {:.4f}'.format(jacc_p))

    
        
    
    
    
    
    
    
    
    
    
