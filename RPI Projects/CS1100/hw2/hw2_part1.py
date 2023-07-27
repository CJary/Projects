#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Sep 17 13:25:03 2022

@author: jarychen
"""

import math
pi = math.pi

# find volume of sphere and cube
def find_volume_sphere(radius):
    return (4/3)*pi*radius**3
def find_volume_cube(side):
    return side**3

#ask for a radius and weekly sales
gb_radius = input('Enter the gum ball radius (in.) => ').strip()
print(gb_radius)
weeklys = input('Enter the weekly sales => ').strip()
print(weeklys)

#all the variables 
#gb is gumball
gb_radius = float(gb_radius)
weeklys = int(weeklys)
targetgb = math.ceil(1.25*weeklys)
side_length= math.ceil(targetgb**(1/3)) 
edgel = gb_radius*2*side_length #edge length
extra_gb = (find_volume_cube(side_length))-(math.ceil(targetgb))
wasted_space_t = (find_volume_cube(edgel)-(find_volume_sphere(gb_radius)*targetgb))#wasted space for target gb
gbmax = find_volume_cube(side_length)
wasted_space_m = (find_volume_cube(edgel)-(find_volume_sphere(gb_radius)*gbmax))#wasted space for machine

print('\nThe machine needs to hold',side_length,'gum balls along each edge.')
print('Total edge length is {0:.2f} inches.'.format(edgel))
print('Target sales were ',targetgb,', but the machine will hold ',extra_gb,' extra gum balls.',sep='')
print('Wasted space is {0:.2f} cubic inches with the target number of gum balls,'.format(wasted_space_t))
print('or {0:.2f} cubic inches if you fill up the machine.'.format(wasted_space_m))