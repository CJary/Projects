#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 12 12:27:32 2022

@author: jarychen
"""

''' 
program that calculates either daily, pct, quar, or high 
of a user's input week
'''

import hw4_util


#index(week) starts at 1 to start the loop
index = 1
while index >= 0:

    
    #changes the index to the user's week and will keep looping
    print('...')
    week = input('Please enter the index for a week: ') 
    print(week)
    index = int(week)


    #if the user's week is 0 or over 29 it will print no data
    if index == 0 or index > 29: 
        print('No data for that week')
        

    #if the user's week is over 0 and lower than 29 it will ask for the info
    if index > 0 and index <= 29: 
        x = hw4_util.part2_get_week(index)


        request = input('Request (daily, pct, quar, high): ')
        print(request)
        request = request.lower() # turns any request into lower case 


        avgdaily = 0


        #if the request is equal to daily it will perform the daily request
        if request == 'daily':
            daily = input('Enter the state: ')
            print(daily)

            error = 0

            for lists in x:
                if lists[0] == daily.upper():
                    error += 1
                    
                    i = 2
                    while i <= 8:
                        avgdaily += (lists[i]/lists[1])*100000
                        i += 1
                    avgdaily = avgdaily/7
                    print(
                        'Average daily positives per 100K population: {0:.1f}'.format(avgdaily))
                
                
            #if error is still 0 after going through each state means that state doesnt exist
            if error == 0:
                print('State {} not found'.format(daily))


            #if the request is equal to pct it will perform the pct request
        elif request == 'pct':
            pct = input('Enter the state: ')
            print(pct)

            error = 0

            for lists in x:
                if lists[0] == pct.upper():
                    error += 1
                    
                    positive = 0
                    i = 2
                    while i <= 8:
                        positive += lists[i]
                        i += 1

                    negative = 0
                    i = 9
                    while i <= 15:
                        negative += lists[i]
                        i += 1
                    avgpct = (positive/(positive+negative))*100
                    print(
                        'Average daily positive percent: {0:.1f}'.format(avgpct))
                    
                    
            #if error is still 0 after going through each state means that state doesnt exist
            if error == 0:
                print('State {} not found'.format(pct))
                
                
            #if the request is equal to quar it will perform the quar request
        elif request == 'quar':
            quarantineS = []

            for lists in x:
                dailyP = 0
                percentP = 0
                percentN = 0

                i = 2
                while i <= 8:
                    dailyP += (lists[i]/lists[1])*100000
                    i += 1
                dailyP = dailyP/7

                ii = 2
                while ii <= 8:
                    if lists[ii] > 0:
                        percentP += lists[ii]
                        percentN += lists[ii+7]
                    ii += 1

                dailyP = round(dailyP, 1)
                percentage = round((percentP/(percentP+percentN))*100, 1)

                if dailyP > 10 or percentage > 10:
                    quarantineS.append(lists[0])
            print('Quarantine states:')
            hw4_util.print_abbreviations(quarantineS)


            #if the request is equal to high it will perform the high request
        elif request == 'high':
            high = (0, 0)

            for lists in x:
                i = 2
                dailyP = 0
                while i <= 8:
                    dailyP += (lists[i]/lists[1])*100000
                    i += 1

                dailyP = dailyP/7
                if dailyP > high[1]:
                    high = (lists[0], dailyP) 
            print('State with highest infection rate is {0}\nRate is {1:.1f} per 100,000 people'.format(
                high[0], high[1]))
            
            
            #if the request is not one of the four it will return a error
        else:
            print('Unrecognized request')
