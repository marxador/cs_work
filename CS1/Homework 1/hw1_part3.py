# -*- coding: utf-8 -*-
"""
Created on Mon Sep 11 14:58:29 2023

@author: mjethree
"""

# method that asks the str input then prints and returns the response
def question(str):
    answer = input(str)
    print(answer)
    return answer

# ask all questions and stores all responses
char = question('Enter frame character ==> ').strip()
height = int(question('Height of box ==> '))
width = int(question('Width of box ==> '))
print('')

# strings that makes the box
topBottom = char * width
row = char + ' ' * (width - 2) + char
dimension = str(width) + 'x' + str(height)
widthSpace = (width - len(dimension) - 2)
center = char + ' ' * (widthSpace // 2) + dimension + ' ' * (widthSpace // 2 + widthSpace % 2) + char
heightSpace = (height - 3) // 2

# printing the strings together
print('Box:')
print(topBottom.strip() + '\n' +
      (row.strip() + '\n') * heightSpace +
      center + '\n' +
      (row + '\n') * (heightSpace + (height + 1) % 2) +
      topBottom)