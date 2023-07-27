#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct  3 19:46:15 2022

@author: jarychen
"""

'''
program that calculates the population of
the following year of bears and berries, in 
addition the amount of tourists
'''

import math


#functions to get the next bear population and next berries area
def find_next(bears, berry_area, tourists):
    bears_next = max(0.0, (berry_area/(50*(bears+1)) + bears *
                     0.60 - (math.log(1+tourists, 10)*0.1)))
    berries_next = max(0.0, (berry_area*1.5) - (bears+1) *
                       (berry_area/14) - (math.log(1+tourists, 10)*0.05))
    return (bears_next, berries_next)


#inputs
bears = input('Number of bears => ').strip()
print(bears)
bears = int(bears)

berry_area = input('Size of berry area => ').strip()
print(berry_area)
berry_area = float(berry_area)


#top headings
print('Year'+' '*6+'Bears'+' '*5+'Berry'+' '*5+'Tourists')


#lists
lbears = []
lberry = []
ltourists = []


#starting values
year = 1
tourists = 0

while year <= 10:
    if bears >= 4 and bears <= 15:
        tourists = (100000)+(bears-10)*20000
        if bears >= 4 and bears <= 10:
            tourists = bears*10000
    else:
        tourists = 0

    x = find_next(bears, berry_area, tourists)
    pbear = '{0}'.format(bears)  # the print statement for bears
    pberry = '{0:.1f}'.format(berry_area)  # the print statement for berry

    # append lists
    lbears.append(bears)
    lbears.sort()
    lberry.append(berry_area)
    lberry.sort()
    ltourists.append(tourists)

    # spaces
    spacesy = (10-len(str(year)))*' '
    spacesb = (10-len(str(bears)))*' '
    spacesba = (10-len(pberry))*' '

    print(str(year)+spacesy+pbear+spacesb+pberry+spacesba+str(tourists))
    bears = math.floor(x[0])
    berry_area = x[1]
    year += 1


#min and max
print()
print('Min:'+6*' '+str(lbears[0])+(10-len(str(lbears[0])))*' '+str(
    round(lberry[0], 1))+(10-len(str(round(lberry[0], 1))))*' '+str(min(ltourists)))
print('Max:'+6*' '+str(lbears[-1])+(10-len(str(lbears[-1])))*' '+str(round(
    lberry[-1], 1))+(10-len(str(round(lberry[-1], 1))))*' '+str(max(ltourists)))
