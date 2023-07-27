    #!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 11 19:52:14 2022

@author: jarychen
"""

print('Let\'s play Mad Libs for Homework 1')
print('Type one word responses to the following:')
print()

propername = input('proper_name ==>  ').strip()
print(propername)
adjective1 = input('adjective ==>  ').strip()
print(adjective1)
noun1 = input('noun ==>  ').strip()
print(noun1)
verb1 = input('verb ==>  ').strip()
print(verb1)
verb2 = input('verb ==>  ').strip()
print(verb2)
noun2 = input('noun ==>  ').strip()
print(noun2)
emotion1 = input('emotion ==>  ').strip()
print(emotion1)
verb3 = input('verb ==>  ').strip()
print(verb3)
noun3 = input('noun ==>  ').strip()
print(noun3)
season = input('season ==>  ').strip()
print(season)
adjective2 = input('adjective ==>  ').strip()
print(adjective2)
emotion2 = input('emotion ==>  ').strip()
print(emotion2)
team_name = input('team-name ==>  ').strip()
print(team_name)
noun4 = input('noun ==>  '  ).strip()
print(noun4)
adjective3 = input('adjective ==>  ').strip()
print(adjective3)

print('\nHere is your Mad Lib...')
print('\nGood morning ',propername,'!',sep='')
print('\n\tThis will be a/an ',adjective1,' ',noun1,'! Are you ',verb1,' forward to it?',sep='')
print('\tYou will',verb2,'a lot of',noun2,'and feel',emotion1,'when you do.')
print('\tIf you do not, you will',verb3,'this',noun3+'.')
print('\n\tThis ',season,' was ',adjective2,'. Were you ',emotion2,' when ',team_name,' won',sep='')
print('\tthe ',noun4,'?',sep='')
print('\n\tHave a/an',adjective3,'day!')