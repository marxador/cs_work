if __name__ == '__main__': 
    # Makes a dictionary of word frequencies using the dict_file
    word_freq = dict()
    dict_file = input('Dictionary file => ').strip()
    print(dict_file)
    for line in open(dict_file, 'r'):
        L = line.strip().split(',')
        word_freq[L[0]] = L[1]
    
    # Makes a list of the input words from the input_file
    input_words = list()
    input_file = input('Input file => ').strip()
    print(input_file)
    for line in open(input_file, 'r'):
        input_words.append(line.strip())
    
    # Makes a dictionary of possible substitutions for a letter based on it's location on a keyboard using the keyboard_file
    possible_subs = dict()
    keyboard_file = input('Keyboard file => ').strip()
    print(keyboard_file)
    for line in open(keyboard_file, 'r'):
        L = line.strip().split(' ')
        possible_subs[L.pop(0)] = L
    
    # Tries to autocorrect each word in input_words
    for word in input_words:
        if word in word_freq.keys():
            print('{:>15} -> FOUND'.format(word))
        else:
            # Attempts following corrections and adds them to candidates
            candidates = set()
            
            # DROP - attemps to drop a single character to see if it's a word
            for i in range(len(word)):
                letters = list(word)
                letters.pop(i)
                if ''.join(letters) in word_freq.keys():
                    candidates.add((word_freq[''.join(letters)], ''.join(letters)))
            
            # INSERT - attemps to insert a letter into the word to see if it's a word
            for i in range(len(word) + 1):
                for letter in possible_subs.keys():
                    letters = list(word)
                    letters.insert(i, letter)
                    if ''.join(letters) in word_freq.keys():
                        candidates.add((word_freq[''.join(letters)], ''.join(letters)))
            
            # SWAP - attempts to swap consecutive letters to see if it's a word
            for i in range(len(word) - 1):
                letters = list(word)
                replace = letters[i]
                letters[i] = letters[i + 1]
                letters[i + 1] = replace
                if ''.join(letters) in word_freq.keys():
                    candidates.add((word_freq[''.join(letters)], ''.join(letters)))
                    
            # REPLACE - attempts to replace each letter with possible_subs to see if it's a word
            for i in range(len(word)):
                for letter in possible_subs[word[i]]:
                    letters = list(word)
                    letters[i] = letter
                    if ''.join(letters) in word_freq.keys():
                        candidates.add((word_freq[''.join(letters)], ''.join(letters)))
            
            # Checks and prints if a correction can be made
            # If a correction can be made, list top three corrections based on word use
            if len(candidates) > 0:
                candidates = sorted(candidates, reverse= True)
                corrections = list()
                for i in range(min(3, len(candidates))):
                    corrections.append(candidates[i][1])
                print('{:>15} -> FOUND {:>2}:  {}'.format(word, len(candidates), ' '.join(corrections)))
            else:
                print('{:>15} -> NOT FOUND'.format(word))