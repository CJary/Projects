#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Nov 30 13:23:05 2022

@author: jarychen
"""

import json
import BerryField
import Bear
import Tourist


file = input("Enter the json file name for the simulation => ").strip()
print(file)
f = open(file)
data = json.loads(f.read())
field = (data["berry_field"])
abears = (data["active_bears"])
rbears = (data["reserve_bears"])
atours = (data["active_tourists"])
rtours = (data["reserve_tourists"])


if __name__ == "__main__":
    # tourist list
    tourists = []
    i = 0
    while i < len(atours):
        tourists.append(Tourist.Tourist(atours[i][0], atours[i][1]))
        i += 1
        
    # bear list
    bears = []
    i = 0
    while i < len(abears):
        bears.append(Bear.Bear(abears[i][0], abears[i][1], abears[i][2]))
        i += 1
        
    
    # prints the field and etc
    berryfield = BerryField.BerryField(field, tourists, bears)
    print()
    print("Field has {} berries.".format(berryfield.totalbears()))
    print(berryfield)

    print("Active Bears:")
    for b in bears: print(b)

    print()

    print("Active Tourists:")
    for t in tourists: print(t)
