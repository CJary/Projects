#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Nov  7 22:53:30 2022

@author: jarychen
"""

'''
This program will take in a year(min/max),
weight for IMDB/TWITTER, and genre. Which then 
returns the best and worst movies within that range.
'''


''' MAIN BODY '''
import json
if __name__ == "__main__":
    movies = json.loads(open("movies.json").read())
    ratings = json.loads(open("ratings.json").read())


    ''' INPUTS '''
    miny = input('Min year => ').strip()
    print(miny)
    miny = int(miny)

    maxy = input('Max year => ').strip()
    print(maxy)
    maxy = int(maxy)

    wimdb = input('Weight for IMDB => ').strip()
    print(wimdb)
    wimdb = float(wimdb)

    wtwit = input('Weight for Twitter => ').strip()
    print(wtwit)
    wtwit = float(wtwit)
    print()


    ''' Turns some the key/values in movies dict into a movie list '''
    moviel = []
    for code in movies:
        moviel.append([code, movies[code]['genre'], movies[code]['name'],
                      movies[code]['movie_year'], movies[code]['rating']])


    ''' Creates a movielist with all the possible movies within the range of the year '''
    rangeMl = []
    for i in range(0, len(moviel)):
        if moviel[i][3] >= miny and moviel[i][3] <= maxy:
            rangeMl.append([moviel[i][0], moviel[i][1], moviel[i]
                           [2], moviel[i][3], moviel[i][4]])


    ''' Creates a list that has the combined avg and important info related to the movie '''
    superlist = []
    for lists in rangeMl:

        if not(lists[0] in ratings):
            continue
        else:
            if len(ratings[lists[0]]) >= 3:
                avgt = sum(ratings[lists[0]])/len(ratings[lists[0]])
                combavg = (wimdb * float(lists[4]) +
                           wtwit * avgt)/(wimdb + wtwit)
                superlist.append(
                    [combavg, lists[0], lists[1], lists[3], lists[2]])

            elif len(ratings[lists[0]]) < 3:
                continue


    ''' LOOP '''
    while True:
        genre = input('What genre do you want to see? ').strip()
        print(genre)

        if genre.lower() == 'stop':
            break
        print()

        ''' LOOP that looks if the input genre is in a movie '''
        valm = []
        for lists in superlist:
            if genre.lower() in (' '.join(lists[2]).lower()):
                valm.append((lists[0], lists[4], lists[3]))

        if valm == []:  # If the valm is empty it means that entered genre isn't in any of the movies
            print('No {} movie found in {} through {}'.format(
                genre.title(), miny, maxy))
            print()
        else:
            x = sorted(valm)
            print('Best:')
            print('        Released in {}, {} has a rating of {:.2f}'.format(
                x[-1][2], x[-1][1], x[-1][0]))
            print()
            print('Worst:')
            print('        Released in {}, {} has a rating of {:.2f}'.format(
                x[0][2], x[0][1], x[0][0]))
            print()
