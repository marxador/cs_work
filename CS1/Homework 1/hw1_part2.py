# -*- coding: utf-8 -*-
"""
Created on Mon Sep 11 14:41:42 2023

@author: mjethree
"""

# method that asks the str input then prints and returns the response
def question(str):
    answer = input(str)
    print(answer)
    return answer

# ask all questions and stores all responses
minutes = int(question('Minutes ==> '))
seconds = int(question('Seconds ==> '))
miles = float(question('Miles ==> '))
targetMiles = float(question('Target Miles ==> '))
print('')

# calculations
time = minutes + (seconds / 60)
averagePace = time / miles
avgPaceMinutes = int(averagePace)
avgPaceSeconds = int((averagePace - int(averagePace)) * 60)
averageSpeed = miles / (time / 60)
targetTime = targetMiles / (averageSpeed / 60)
targetMinutes = int(targetTime)
targetSeconds = int((targetTime - int(targetTime)) * 60)

# prints out calculated information
print('Pace is {0} minutes and {1} seconds per mile.'.format(avgPaceMinutes, avgPaceSeconds))
print('Speed is{0: .2f} miles per hour.'.format(averageSpeed))
print('Time to run the target distance of{0: .2f} miles is {1} minutes and {2} seconds.'.format(targetMiles, targetMinutes, targetSeconds))