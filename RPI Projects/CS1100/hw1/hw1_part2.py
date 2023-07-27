#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 11 21:24:36 2022

@author: jarychen
"""

Minutes = input('Minutes ==> ').strip()
print(Minutes)
Minutes = int(Minutes)
Seconds = input('Seconds ==> ').strip()
print(Seconds)
Seconds =int(Seconds)
Miles = input('Miles ==> ').strip()
print(Miles)
Miles = float(Miles)
Target_miles = input('Target Miles ==> ').strip()
print(Target_miles)

Target_miles = float(Target_miles)
paceforminutes = int(((Minutes*60+Seconds)/Miles)/60)
paceforseconds = int((((Minutes*60+Seconds)/Miles)/60-paceforminutes)*60)
speed = (3600/((Minutes*60+Seconds)/Miles))
pace = (Minutes*60+Seconds)/Miles
tmm = int((Target_miles*pace)//60)
tms = int(((Target_miles*pace)/60-tmm)*60)


print('\nPace is',paceforminutes,'minutes and',paceforseconds,'seconds per mile.')
print('Speed is {0:.2f} miles per hour.'.format(speed))
tmstring ='Time to run the target distance of {0:.2f} miles is'.format(Target_miles)
print(tmstring,tmm,'minutes and',tms,'seconds.')