# -*- coding: utf-8 -*-
"""
Created on Thu Sep 14 12:02:24 2023

@author: mjethree
"""

import math

# methods to calculate specified volumes
def find_volume_sphere(radius) :
    volume = (4 / 3) * math.pi * radius ** 3
    return volume
def find_volume_cube(side) :
    volume = side ** 3
    return volume

# method to ask a question, print the response, and store it as a float
def question(str) :
    answer = input(str).strip()
    print(answer)
    answer = float(answer)
    return answer

# uses question method to ask and store the radius and weekly sales
radius = question('Enter the gum ball radius (in.) => ')
weeklySales = question('Enter the weekly sales => ')
print()

# calculations
totalGumBalls = math.ceil(weeklySales * 1.25)
gumBallPerSide = math.ceil(math.pow(totalGumBalls, 1/3))
sideMachine = gumBallPerSide * (radius * 2)
finalGumBalls = find_volume_cube(gumBallPerSide)
cubeVolume = find_volume_cube(sideMachine)
gumBallVolume = find_volume_sphere(radius)
wastedSpaceMin = cubeVolume - (gumBallVolume * totalGumBalls) 
wastedSpaceMax = cubeVolume - (gumBallVolume * finalGumBalls)

# outputs
print('The machine needs to hold {0} gum balls along each edge.'.format(gumBallPerSide))
print('Total edge length is {0:.2f} inches.'.format(sideMachine))
print('Target sales were {0}, but the machine will hold {1} extra gum balls.'.format(totalGumBalls, (finalGumBalls - totalGumBalls)))
print('Wasted space is {0:.2f} cubic inches with the target number of gum balls,'.format(wastedSpaceMin))
print('or {0:.2f} cubic inches if you fill up the machine.'.format(wastedSpaceMax))