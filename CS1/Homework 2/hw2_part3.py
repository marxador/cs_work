# -*- coding: utf-8 -*-
"""
Created on Thu Sep 14 14:12:00 2023

@author: User
"""

# ask question, stores response and prints response
sentence = input('Enter a sentence => ').strip()
print(sentence)

# functions that determine the "happiness" or "sadness" of the inputted string
def number_happy(sentence) :
    count = sentence.lower().count('laugh')
    count += sentence.lower().count('happiness')
    count += sentence.lower().count('love')
    count += sentence.lower().count('excellent')
    count += sentence.lower().count('good')
    count += sentence.lower().count('smile')
    return count
def number_sad(sentence) :
    count = sentence.lower().count('bad')
    count += sentence.lower().count('sad')
    count += sentence.lower().count('terrible')
    count += sentence.lower().count('horrible')
    count += sentence.lower().count('problem')
    count += sentence.lower().count('hate')
    return count

# converts the "happiness" and "sadness" levels to +'s and -'s
happy = '+' * number_happy(sentence)
sad = '-' * number_sad(sentence)

# prints requested info from homework
print('Sentiment: {0}{1}'.format(happy, sad))
if(number_happy(sentence) > number_sad(sentence)) :
    print('This is a happy sentence.')
elif(number_happy(sentence) < number_sad(sentence)) :
    print('This is a sad sentence.')
else :
    print('This is a neutral sentence.')