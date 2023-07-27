#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 30 15:00:34 2022

@author: jarychen
"""
import math

class Tourist:
    def __init__(self, row, col):
        self.r = row
        self.c = col
        self.turns = 0
        self.dead = False
        self.scared = False
        self.exit = False
        self.bored = False

    def __str__(self):
        return "Tourist at ({},{}), {} turns without seeing a bear.".format(str(self.r), str(self.c), str(self.turns))
    
    # detects if a tourists sees a bear
    def findb(self, bears):
        count = 0
        for b in range(len(bears)):
            x = abs(bears[b].r - self.r)
            y = abs(bears[b].c - self.c)
            if math.hypot(x,y) <= 4:
                count += 1
                
        return count
