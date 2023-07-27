#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct 17 13:53:35 2022

@author: jarychen
"""
'''
Program gives back the most steepes path or 
most gradual path to the global/local maximum.
Also, prints out the pathway grid of how many location 
it went through
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
      
    if index > 0 and index <= 3:

        stepH = input('Enter the maximum step height: ')
        print(stepH)
        stepH = int(stepH)
        
        printed = input('Should the path grid be printed (Y or N): ')
        print(printed)
        printed = printed.lower()
                
        row = len(grid)
        col = len(grid[0])
        print('Grid has {} rows and {} columns'.format(row,col))
        
        #to find the global max value
        maxnum = []
        for lists in grid:
            for num in lists:
                maxnum.append(num)
        maxnum = max(maxnum)
        
        #to find the row and col for the global max
        locX = 0
        correct = False
        while locX <= len(grid):
            lists = grid[locX]
            locY = 0
        
            for num in lists:
                if num == maxnum:
                    correct = True
                    break
                else:
                    locY += 1
            
            if correct == True:
                break
            
            locX += 1
        print('global max: ({}, {}) {}'.format(locX,locY,maxnum))
        Gmax = grid[locX][locY]
        
        #local max
        x = 0
        y = 0
        for lists in grid:
            for num in lists:
                numgreater = 0
                for location in get_nbrs(x,y,row,col):
                    if num > grid[location[0]][location[1]]:
                        numgreater += 1
                    
                #if it's greater than all it's neighbors it it will be the local max
                if numgreater == len(get_nbrs(x,y,row,col)) and not grid[x][y] == Gmax: 
                    local_max = ((x,y),num)
                y += 1
            y = 0
            x += 1
        
        ''' Start of the steepest and gradual path code '''
        super_L = []# made a super lists for future path grid use
        
        for start in startL:#access each location in the startL function
            
            ''' Steepest Path '''
            Cstart = start
            GCstart = start
            steep = []
            
            #To start the while loop
            i = False
            while i == False:
                neigh = get_nbrs(Cstart[0],Cstart[1],row,col)
                steep.append(Cstart)
                super_L.append(Cstart)
                max_diff = 0 #the difference between each neighbors
                rc = (0,0) 
                
                #for every value in the neighbors
                for num in neigh:
                    
                    #the difference between the neighbors and the current location
                    diff = grid[num[0]][num[1]] - grid[Cstart[0]][Cstart[1]]
                    if diff <= stepH and diff > 0 and diff > max_diff:
                        max_diff = diff
                        rc = (num[0],num[1])
                
                #if it equals to the global or local max it will append the location
                if rc == (locX,locY) or rc == local_max[0]:
                    Cstart = rc
                    steep.append(Cstart)
                    super_L.append(Cstart)
                    break
                
                #if the max diff didn't change it means no neigh is valid
                elif max_diff == 0:
                    break
                
                #if all if statements doesnt work then the current location is set to the rc
                Cstart = rc
            
            print('===')
            print('steepest path')
            i_s = 0
            for i in range(len(steep)):
                print(steep[i],' ',sep = '',end = '')
                i_s += 1
                #if the path is equal to the length of the gradual path it means that it's just one line.
                #When the i_g divided by 5 is 0 it means that it is the mutiple of 5 which skips a line.
                if not i_s == len(steep) and i_s % 5 == 0 and not i_s == 0 :
                    print()
                    i_s = 0

            #prints which type of path it reached      
            if steep[-1] == (locX,locY):
                print()
                print('global maximum')
                
            elif steep[-1] == local_max[0]:
                print()
                print('local maximum')
                
            else:
                print()
                print('no maximum')
        
            
            ''' Gradual Path '''
            grad = []
            
            #To start the while loop
            ii = False
            while ii == False:
                neigh = get_nbrs(GCstart[0],GCstart[1],row,col)
                grad.append(GCstart)
                super_L.append(GCstart)
                min_diff = 100 #the difference between each neighbors
                Nrc = (0,0)
                
                #for every value in the neighbors
                for num in neigh:
                    
                    #the difference between the neighbors and the current location
                    diff_G = grid[num[0]][num[1]] - grid[GCstart[0]][GCstart[1]]
                    if diff_G <= stepH and diff_G > 0 and diff_G < min_diff:
                        min_diff = diff_G
                        Nrc = (num[0],num[1])
                
                #if it equals to the global or local max it will append the location
                if Nrc == (locX,locY) or Nrc == local_max[0]:
                    GCstart = Nrc
                    grad.append(GCstart)
                    super_L.append(GCstart)
                    break
                
                #if the max diff didn't change it means no neigh is valid
                elif min_diff == 100:
                    break
                
                #if all if statements doesnt work then the current location is set to the Nrc
                GCstart = Nrc
            
            print('...')
            print('most gradual path')
            i_g = 0
            for i in range(len(grad)):
                print(grad[i],' ',sep = '',end = '')
                i_g += 1
            #if the path is equal to the length of the gradual path it means that it's just one line.
            #When the i_g divided by 5 is 0 it means that it is the mutiple of 5 which skips a line.
                if not i_g == len(grad) and i_g % 5 == 0 and not i_g == 0 :
                    print()
                    i_g = 0
            
            #prints which type of path it reached  
            if grad[-1] == (locX,locY):
                print()
                print('global maximum')
                
            elif grad[-1] == local_max[0]:
                print()
                print('local maximum')
                
            else:
                print()
                print('no maximum')
              
        
        ''' Path Grid '''
        #prints the path if the user answered Y       
        if printed == 'y':
            print('===')
            print('Path grid')
            path = grid.copy() # creates a copy of the original grid
            
            #empties the new lists
            for lists in range(len(path)):
                for num in range(len(path[lists])):
                    path[lists][num] = 0
                    
            #scans the super lists to find the recurring path locations
            for row in range(len(path)):
                for col in range(len(path[row])):
                    
                     path[row][col] += super_L.count((row,col))
                     if super_L.count((row,col)) == 0:
                         path[row][col] = '.'
                     
                     print('  ',path[row][col],sep = '',end = '')
                print()
            
            
                
                    
                
                        
                        
                    
                    
                
            
            
    
                    
                    
                    
                
                
                        
            
                

            


                        
                
        
        
        
        