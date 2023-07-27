#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Oct 14 15:01:28 2022

@author: jarychen
"""

'''
Program that ask user which grid and if they 
wanted it printed or not. Also gives back the paths
that it can take.
'''
import hw5_util

#function that returns a lists of all the valid paths around a location
def get_nbrs(row,col,totalr,totalc):
    listN = []
    if (row-1) >= 0 and (row-1) < totalr:
        listN.append((row-1,col))
        
    if (col-1) >= 0 and (col-1) < totalc:
        listN.append((row,col-1))
        
    if (col+1) >= 0 and (col+1) < totalc:
        listN.append((row,col+1))
        
    if (row+1) >= 0 and (row+1) < totalr:
        listN.append((row+1,col))
    
    return listN

#Starts the while loop
index = 100

#if the user's index is over 3 or less than 0 it will ask again for a vaid index
while index > 3 or index < 0:
        
    index = input('Enter a grid index less than or equal to 3 (0 to end): ')
    print(index)
    index = int(index)
    
    #the grid
    grid = hw5_util.get_grid(index)
    #start location
    startL = hw5_util.get_start_locations(index)
    
    #if the user's enter week is zero it will end the loop
    if index == 0:
        break
      
    #start of the program
    if index > 0 and index <= 3:
        printed = input('Should the grid be printed (Y or N): ')
        print(printed)
        printed = printed.lower()
        
        #if grid wants to be printed
        if printed == 'y':
            print('Grid',index)
            for lists in hw5_util.get_grid(index):
                for number in lists:
                    spaces = ' ' * (4-len(str(number)))
                    print(spaces,number,sep='',end='')
                print()
                
        #gives the amount of rows and columns for the grid
        row = len(hw5_util.get_grid(index))
        col = len(hw5_util.get_grid(index)[0])
        print('Grid has {} rows and {} columns'.format(row,col))
        
        #prints the valid location around a give start location
        for startL in hw5_util.get_start_locations(index):
            neighbors = get_nbrs(startL[0],startL[1],row,col)
            print('Neighbors of {}: {}'.format(startL,' '.join(str(e) for e in neighbors)))
        
        
        i = 0
        error = False
        step1 = 0
        step2 = 0
        down = 0
        up = 0
        while i < len(hw5_util.get_path(index)) - 1:
            x = hw5_util.get_path(index)
            x0 = hw5_util.get_path(index)[i][0]
            x1 = hw5_util.get_path(index)[i][1]
            x0n = hw5_util.get_path(index)[i+1][0]
            x1n = hw5_util.get_path(index)[i+1][1]
            grid = hw5_util.get_grid(index)
            
            #for the downward paths
            if (grid[x0][x1] - grid[x0n][x1n]) > 0:
                down += abs(grid[x0][x1] - grid[x0n][x1n]) 
                
            #for the upward paths
            elif (grid[x0][x1] - grid[x0n][x1n]) < 0:
                up += abs(grid[x0][x1] - grid[x0n][x1n]) 
                
            #if the path location is not detected within the neighbors path then 
            #the count of it will be less than 1 
            if get_nbrs(x[i][0],x[i][1],row,col).count(x[i+1]) < 1:
                error = True 
                step1 = x[i] 
                step2 = x[i+1]
            i += 1
        
        #if error becomes True then there is a invalid path
        if error == True:
            print('Path: invalid step from {} to {}'.format(step1,step2))
        
        #if error still False prints the valid path and down/upward
        else:
            print('Valid path')
            print('Downward',down)
            print('Upward',up)
            
                    
                
            
        
                
