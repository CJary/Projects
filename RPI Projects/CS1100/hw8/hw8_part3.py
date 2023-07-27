#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec  1 11:20:57 2022

@author: jarychen
"""


#This program checks and read the file for bear's and tourist,
#active or waiting to enter. It updates the field and continues 
#for some # of turns until there aren't any more bears left'


import json
import BerryField
import Bear
import Tourist


#function to return a list of tourists that left the field
def countT(tourists):
    listT = []
    counter = 0
    for t in range(0, len(tourists)):
        if tourists[t-counter].dead == True or tourists[t-counter].bored == True or tourists[t-counter].scared == True:
            listT.append(["{} - Left the Field".format(tourists[t-counter])])
            del tourists[t-counter]
            counter += 1
    
    return listT

#function to return a list of bears that left the field
def countB(bears):
    listB = []
    counter = 0
    for b in range(0, len(bears)):
        if bears[b-counter].exit == True:
            listB.append(["{} - Left the Field".format(bears[b-counter])])
            del bears[b-counter]
            counter += 1
    
    return listB

#function to return a list of bears that is asleep
def asleepB(bears):
    listB = []
    for b in bears:
        if b.turns - 1 > 0 and b.sleep == True:
            listB.append(
                ["{} - Asleep for {} more turns".format(b, (b.turns-1))])
            
        else:
            listB.append([str(b)])
    
    return listB


file = input("Enter the json file name for the simulation => ").strip()
print(file)
f = open(file)
data = json.loads(f.read())
field = (data["berry_field"])
abear = (data["active_bears"])
rbear = (data["reserve_bears"])
atour = (data["active_tourists"])
rtour = (data["reserve_tourists"])


if __name__ == "__main__":
    # tourist list
    tourists = []
    i = 0
    while i < len(atour):
        tourists.append(Tourist.Tourist(atour[i][0], atour[i][1]))
        i += 1
        
    # bear list
    bears = []
    i = 0
    while i < len(abear):
        bears.append(Bear.Bear(abear[i][0], abear[i][1], abear[i][2]))
        i += 1

    # reserve tourist list
    rtourists = []
    i = 0
    while i < len(rtour):
        rtourists.append(Tourist.Tourist(rtour[i][0], rtour[i][1]))
        i += 1
        
    # reserve bear list
    rbears = []
    i = 0
    while i < len(rbear):
        rbears.append(Bear.Bear(rbear[i][0], rbear[i][1], rbear[i][2]))
        i += 1
        
        
    print()
    print("Starting Configuration")


    # creates berryfield 
    berryfield = BerryField.BerryField(field, tourists, bears)
    print("Field has {} berries.".format(berryfield.totalbears()))
    print(berryfield)

    # print active bears
    print("Active Bears:")
    for b in bears: print(b)
        
    print()

    # print active tourists
    print("Active Tourists:")
    for t in tourists: print(t)


    turn = 1
    while True:
        berryfield.growbears()
        berryfield.spreadbears()
        
        if turn == 1:
            print()
            print("Turn: {}".format(turn))
        else:
            print("\n\nTurn: {}".format(turn))
            
            
        # determine if any tourists and bears occupy the exact same spot
        for b in bears:
            for t in tourists:
                if b.r == t.r:
                    if b.c == t.c:
                        t.dead = True
                        b.kill = True


        # print out the left field
        for i in countT(tourists): print(''.join(i))
                
        
        # loops through every single bear
        # loops through every single bear
        for b in bears:
            if b.kill == True:
                b.kill = False
                b.sleep = True
                b.turns = 4
                
                
            # if bear is sleeping it changes the turn by -1
            if b.sleep == True:
                b.turns -= 1
                
                
            # if bear's turn is 0 the bear doesn't sleep
            if b.turns == 0:
                b.sleep = False
                
                
            if b.sleep != True and b.exit != True:
                while True:
                    # bear eats all the bearies at that position
                    b.eat += berryfield.field[b.r][b.c]
                    berryfield.field[b.r][b.c] = 0
                    
                    b.move()
                    
                    # check to see if a tourist get eaten, then bear stops moving
                    for t in tourists:
                        if b.r == t.r and b.c == t.c:
                            t.dead = True
                            b.kill = True
                            
                            
                    if b.kill == True:
                        break
                    
                    
                    # bear goes off field 
                    elif b.r > len(berryfield.field)-1 or b.c > len(berryfield.field)-1:
                        b.exit = True
                        break
    
                    
                    elif b.r < 0 or b.c < 0:
                        b.exit = True
                        break
                    
                    
                    # bear eats all the bears leave the field with 0 berries at that spot
                    b_r = b.r
                    b_c = b.c
                    b.eat += berryfield.field[b_r][b_c]
                    berryfield.field[b_r][b_c] = 0
                    
                    # bear eats more than 30 bearries breaks and the extra beries go back
                    if b.eat >= 30:
                        berryfield.field[b_r][b_c] = b.eat - 30
                        break
                    
            # resets 
            b.eat = 0


        # checks if a bear eats a tourist
        for b in bears:
            for t in tourists:
                if b.r == t.r and b.c == t.c:
                    t.dead = True
                    b.kill = True
                    
                    
         # if tourist is alive it looks if a bears is around
        for t in tourists:
            if t.dead == False:
                if t.findb(bears) >= 3:
                    t.scared = True
                if t.findb(bears) > 0:
                    t.turns = 0
                if t.findb(bears) == 0:
                    t.turns += 1
                    
                    
         # if a tourist didn't see a single bear it leaves
        for t in tourists:
            if t.turns == 3:
                t.bored = True
            if t.findb(bears) >= 3:
                t.scared = True
                
                
         # if bear gets a kill it goes to sleep
        for b in bears:
            if b.kill == True:
                b.sleep = True
                b.turns = 3
                b.kill = False
                
                
         # print out the left field 
        for i in countB(bears): print(''.join(i))
        
        
        # print out the left field 
        for i in countT(tourists): print(''.join(i))
            

        # checks if a bear can enter
        if len(rbears) > 0 and berryfield.totalbears() > 500:
            bears.append(rbears[0])
            del rbears[0]
            print("{} - Entered the Field".format(bears[-1]))
            
            
         # checks if a tourist can enter
        if len(rtourists) > 0 and len(bears) > 0:
            tourists.append(rtourists[0])
            del rtourists[0]
            print("{} - Entered the Field".format(tourists[-1]))
            
            
        # prints field and etc every 5 turns
        if turn % 5 == 0:
            print("Field has {} berries.".format(berryfield.totalbears()))
            print(berryfield)
            print("Active Bears:")
            
            
            # print out the asleep bear
            for i in asleepB(bears): print(''.join(i))
                    
            print()
            
            print("Active Tourists:")
            for t in tourists: print(t)
            
        turn += 1
        
        
        # if are no more bears it ends
        if len(bears) == 0 and len(rbears) == 0:
            break
        
    # prints final field and etc
    print("Field has {} berries.".format(berryfield.totalbears()))
    print(berryfield)
    print("Active Bears:")


    # print out the asleep bear
    for i in asleepB(bears): print(''.join(i))

    print()
    
    print("Active Tourists:")
    for t in tourists: print(t)
        
    print()
