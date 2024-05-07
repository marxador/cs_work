# imports needed functions
import syllables

# Gets a paragraph from the user, stores it as a str and a tuple str, and reprints the str version
paragraph = input('Enter a paragraph => ').strip()
print(paragraph)
words = paragraph.split()

"""
Calculation to find average sentence length (asl)
Does this by going through the words tuple with a loop and finding a word that contains a '.'
Then finds the length of that sentence and adds it to the average
Once the loop ends it divides the average by how many '.' the paragraph has to get the actual average
"""
asl = 0
i = 0
lastSentence = 0
while i < len(words):
    if words[i].find('.') != -1:
        i += 1
        asl += (i - lastSentence)
        lastSentence = i
    else:
        i += 1
asl /= paragraph.count('.')

"""
Calculation to find percent of hard words (phw)
Does this by going through the words tuple with a loop and checks each word for the conditions of a hard word
If they are met, then it adds it to the hardWord list
Then calculates the phw by using the lenght of each list
"""
hardWords = []
i = 0
while i < len(words):
    if syllables.find_num_syllables(words[i]) >= 3 and words[i].find('-') == -1 and words[i].find('es', len(words[i]) - 2) == -1 and words[i].find('ed', len(words[i]) - 2) == -1:
        hardWords.append(words[i])
    i += 1
phw = len(hardWords) / len(words) * 100

"""
Calculation to find average number of syllables (asyl)
Does this by going through the words tuple with a loop and adds the total number of syllables of each word to the average
After the loop ends it divides the average by the number of words in the paragraph to get the actual average
"""
asyl = 0
i = 0
while i < len(words):
    asyl += syllables.find_num_syllables(words[i])
    i += 1
asyl /= len(words)

# Uses given formulas and previous info to find GFRI and FKRI
gfri = 0.4 * (asl + phw)
fkri = 206.835 - 1.015 * asl - 86.4 * asyl

# Prints calculated information
print('Here are the hard words in this paragraph:')
print(hardWords)
print('Statistics: ASL:{:.2f} PHW:{:.2f}% ASYL:{:.2f}'.format(asl, phw, asyl))
print('Readability index (GFRI): {:.2f}'.format(gfri))
print('Readability index (FKRI): {:.2f}'.format(fkri))