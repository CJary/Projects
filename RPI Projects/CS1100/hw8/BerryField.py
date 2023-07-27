#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 30 15:00:19 2022

@author: jarychen
"""

class BerryField:
    def __init__(self, field, tourists, bears):
        self.lenf = len(field)
        self.field = field
        self.bears = bears
        self.tourists = tourists

    
    # function that returns the field 
    def __str__(self):
        field = ''
        X = False
        B = False
        T = False
        
        tourlist = []
        for t in self.tourists:
            tourlist.append((t.r,t.c))
        
        bearlist = []
        for b in self.bears:
            bearlist.append((b.r,b.c))
        
        for x in range(0, self.lenf):
            for y in range(0, self.lenf):
                if (x,y) in bearlist and (x,y) in tourlist:
                    field += ("{:>4}".format("X"))
                    X = True
                    
                if X == False:
                    if (x,y) in tourlist:
                        field += ("{:>4}".format("T"))
                        T = True

                    if (x,y) in bearlist:
                        field += ("{:>4}".format("B"))
                        B = True

                if X == False:
                    if B == False :
                        if T == False:
                            field += ("{:>4}".format(self.field[x][y]))
                X = False
                B = False
                T = False
            field += "\n"
                    
        return field
    

    # grows all the berries by +1
    def growbears(self):
        for i in range(self.lenf):
            for ii in range(self.lenf):
                if self.field[i][ii] >= 1 and self.field[i][ii] < 10:
                    self.field[i][ii] += 1
    
    
    # returns total berries
    def totalbears(self):
        totalb = 0
        for i in range(self.lenf):
            for ii in range(self.lenf):
                totalb += self.field[i][ii]
                
        return totalb
    
    
    # determines if the position gets an extra berry
    def spreadbears(self):
        for x in range(self.lenf):
            for y in range(len(self.field[x])):
                if self.field[x][y] == 0:
                    inside = False
                    if 0 <= x+1 < self.lenf and 0 <= y < len(self.field[0]) and self.field[x+1][y] == 10:
                        inside = True
                    elif 0 <= x-1 < self.lenf and 0 <= y < len(self.field[0]) and self.field[x-1][y] == 10:
                        inside = True
                    elif 0 <= x < self.lenf and 0 <= y+1 < len(self.field[0]) and self.field[x][y+1] == 10:
                        inside = True
                    elif 0 <= x < self.lenf and 0 <= y-1 < len(self.field[0]) and self.field[x][y-1] == 10:
                        inside = True
                    elif 0 <= x+1 < self.lenf and 0 <= y+1 < len(self.field[0]) and self.field[x+1][y+1] == 10:
                        inside = True
                    elif 0 <= x-1 < self.lenf and 0 <= y-1 < len(self.field[0]) and self.field[x-1][y-1] == 10:
                        inside = True
                    elif 0 <= x-1 < self.lenf and 0 <= y+1 < len(self.field[0]) and self.field[x-1][y+1] == 10:
                        inside = True
                    elif 0 <= x+1 < self.lenf and 0 <= y-1 < len(self.field[0]) and self.field[x+1][y-1] == 10:
                        inside = True
                    
                    if inside == True:
                        self.field[x][y] += 1
