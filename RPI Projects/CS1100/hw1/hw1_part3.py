#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 12 21:07:07 2022

@author: jarychen
"""
framec = input('Enter frame character ==> ').strip()
print(framec)
height = input('Height of box ==> ').strip()
print(height)
width = input('Width of box ==> ').strip()

mid = width+'x'+height
width = int(width)
height= int(height)

print(width)
print()
print('Box:') 

cTB = framec*width
spacesm = framec+(width-2)*' '+framec
heightT = int(((height-3))/2)
heightB = int(((height-2))/2)
spacesmL = int(((width-2)-len(mid))/2)
spacesmR = int(width-len(mid)-spacesmL-2)


print(cTB)
print(heightT*(spacesm+'\n'),end='')
print(framec+spacesmL*' ',mid,spacesmR*' '+framec,sep='')
print(heightB*(spacesm+'\n'),end='')
print(cTB)