#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct  2 15:23:28 2022

@author: jarychen
"""

'''
program where user determines the character's turns
and fights like a simulation
'''

#function that gives the new position of the pokemon
def move_pokemon(rowcol, direction, steps):
    direction = direction.lower() # convert all incomign strings to lowercase
    if direction == 'n':
        rowcol[0] = min(max(0, rowcol[0]-steps), 150)
    elif direction == 's':
        rowcol[0] = min(max(0, rowcol[0]+steps), 150)
    elif direction == 'e':
        rowcol[1] = min(rowcol[1]+steps, 150)
    elif direction == 'w':
        rowcol[1] = min(rowcol[1]-steps, 150)


#beginning inputs
turns = input('How many turns? => ').strip()
print(turns)
turns = int(turns)

name = input('What is the name of your pikachu? => ').strip()
print(name)

often = input('How often do we see a Pokemon (turns)? => ').strip()
print(often)
often = int(often)


#Starting position
rowcol = [75, 75]
print('\nStarting simulation, turn 0 '+name+' at (75, 75)')

t = 1  # amount of turns
o = 0  # amount of often
wllists = []  # win lost lists

while t <= turns:
    if o < often:# o is less than the user requested often it will continue to ask for directon
        x = input('What direction does '+name+' walk? => ').strip()
        print(x)
        
        move_pokemon(rowcol, x, 5)
        
        o += 1
        t += 1
    if o == often:# o is equal to the user requested often it will stop and ask for which opponent
        print('Turn {0}, {1} at ({2}, {3})'.format(
            t-1, name, rowcol[0], rowcol[1]))
        
        y = input('What type of pokemon do you meet (W)ater, (G)round? => ').strip()
        print(y)
        
        if y.lower() == 'w':
            move_pokemon(rowcol, x, 1)
            
            print('{0} wins and moves to ({1}, {2})'.format(
                name, rowcol[0], rowcol[1]))
            
            wllists.append('Win')
            
        elif y.lower() == 'g':
            move_pokemon(rowcol, x, -10)
            
            print('{0} runs away to ({1}, {2})'.format(
                name, rowcol[0], rowcol[1]))
            
            wllists.append('Lose')
            
        else:
            wllists.append('No Pokemon')
        o = 0


#end statement
print('{0} ends up at ({1}, {2}), Record: {3}'.format(
    name, rowcol[0], rowcol[1], wllists))

