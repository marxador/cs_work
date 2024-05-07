# -*- coding: utf-8 -*-
"""
Created on Mon Sep 11 13:28:08 2023

@author: mjethree
"""

# introduction
print("Let's play Mad Libs for Homework 1")
print("Type one word responses to the following:", end= '\r\n\r\n')

# method that asks the str input then prints and returns the response
def question(str):
    answer = input(str)
    print(answer)
    return answer.strip()

# ask all question and stores all responses
proper_name = question('proper_name ==> ')
adjective1 = question('adjective ==> ')
noun1 = question('noun ==> ')
verb1 = question('verb ==> ')
verb2 = question('verb ==> ')
noun2 = question('noun ==> ')
emotion1 = question('emotion ==> ')
verb3 = question('verb ==> ')
noun3 = question('noun ==> ')
season = question('season ==> ')
adjective2 = question('adjective ==> ')
emotion2 = question('emotion ==> ')
teamName = question('team-name ==> ')
noun4 = question('noun ==> ')
adjective3 = question('adjective ==> ')
print('')

# prints the stored responses into the mad lib
print('Here is your Mad Lib...', end= '\r\n\r\n')
print('Good morning {0}!'.format(proper_name),end= '\r\n\r\n')
print('  This will be a/an {0} {1}! Are you {2} forward to it?'.format(adjective1, noun1, verb1))
print('  You will {0} a lot of {1} and feel {2} when you do.'.format(verb2, noun2, emotion1))
print('  If you do not, you will {0} this {1}.'.format(verb3, noun3), end= '\r\n\r\n')
print('  This {0} was {1}. Were you {2} when {3} won'.format(season, adjective2, emotion2, teamName))
print('  the {0}?'.format(noun4), end= '\r\n\r\n')
print('  Have a/an {0} day!'.format(adjective3))