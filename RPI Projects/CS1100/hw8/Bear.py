#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 30 14:59:58 2022

@author: jarychen
"""

class Bear:
    def __init__(self, row, col, direction):
        self.r = row
        self.c = col
        self.d = direction
        self.kill = False
        self.sleep = False
        self.turns = 0
        self.exit = False
        self.eat = 0

    def __str__(self):
        return "Bear at ({},{}) moving {}".format(str(self.r), str(self.c), self.d)
    
    # change position depeding on the direction it's going
    def move(self):
        lists = ['N','S','E','W','NE','NW','SE','SW']
        if self.d.upper() in lists:
            if self.d.upper() == "N":
                self.r = self.r - 1
                
            elif self.d.upper() == "S":
                self.r = self.r + 1
                
            elif self.d.upper() == "E":
                self.c = self.c + 1
                
            elif self.d.upper() == "W":
                self.c = self.c - 1
                    
            elif self.d.upper() == "NE":
                self.r = self.r - 1
                self.c = self.c + 1
                
            elif self.d.upper() == "NW":
                self.r = self.r - 1
                self.c = self.c - 1
                
            elif self.d.upper() == "SE":
                self.r = self.r + 1
                self.c = self.c + 1
                
            elif self.d.upper() == "SW":
                self.r = self.r + 1
                self.c = self.c - 1
    

