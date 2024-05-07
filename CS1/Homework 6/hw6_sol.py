# Function that passes a file and returns a list of words stripped of all nonalphabetic characters
def get_words(file):
    text = file.readlines()
    words_final = list()
    for line in text:
        words = line.strip().split(' ')
        for word in words:
            word = word.lower()
            word = list(word)
            string = ''
            for char in word:
                if char.isalpha() and char != 'â':
                    string += char
            if string != '':
                words_final.append(string)
    return words_final

# Function that passes a set of stop words and a list of words and returns a list of words that aren't in the set of stop words
def remove_stop_words(stop, words):
    words_final = list()
    for word in words:
        if not word in stop:
            words_final.append(word)
    return words_final
    
# Function that passes a list of words and returns the average word length
def avg_word_len(words):
    avg = 0
    for word in words:
        avg += len(word)
    return avg / len(words)

# Function that passes a list of words and returns a list of lists of the words
def word_sets(words):
    word_len = list()
    for word in set(words):
        if len(word) > len(word_len):
            for i in range(len(word) - len(word_len)):
                word_len.append(list())
        word_len[len(word) - 1].append(word)
    return word_len

# Function that prints the word sets as described in the assingment
def print_word_sets(word_len):
    output = ''
    i = 0
    for length in word_len:
        i += 1
        output += '{:>4}:{:>4}:'.format(i, len(length))
        if word_len[-1] is length:
            length.sort()
            if len(length) == 0:
                output += ''
            elif len(length) <= 6:
                output += ' ' + ' '.join(length).strip(' ')
            else:
                output += ' ' + length[0] + ' ' + length[1] + ' ' + length[2] + ' ... ' + length[-3] + ' ' + length[-2] + ' ' + length[-1]
        else:
            length.sort()
            if len(length) == 0:
                output += '\n'
            elif len(length) <= 6:
                output += ' ' + ' '.join(length) + '\n'
            else:
                output += ' ' + length[0] + ' ' + length[1] + ' ' + length[2] + ' ... ' + length[-3] + ' ' + length[-2] + ' ' + length[-1] + '\n'
    print(output)

# Function that passes a list of words and the max seperation of a pair and returns a list of distinct word pairs
def distinct_word_pairs(words, max_sep):
    all_word_pairs = set()
    distinct_word_pairs = list()
    for i in range(len(words)):
        for j in range(i + 1, min(i + 1 + max_sep, len(words))):
            word = sorted([words[i], words[j]])     # Ensure a consistent order
            word1, word2 = word[0], word[1]
            if (word1, word2) not in all_word_pairs and (word2, word1) not in all_word_pairs:
                distinct_word_pairs.append((word1, word2))
            all_word_pairs.add((word1, word2))
    distinct_word_pairs.sort()
    return distinct_word_pairs

# Function that passes a list of pairs and prints it out as the assignment described
def print_word_pairs(pairs):
    string = '  {} distinct pairs\n'.format(len(pairs))
    if len(pairs) > 10:
        for i in range(5):
            if i != 4:
                string += '  ' + ' '.join(pairs[i]) + '\n'
            else:
                string += '  ' + ' '.join(pairs[i]) + '\n  ...\n'
        for i in range(5, 0, -1):
            if i != 1:
                string += '  ' + ' '.join(pairs[-i]) + '\n'
            else:
                string += '  ' + ' '.join(pairs[-i])
    else:
        for i in range(5):
            if i != 4:
                string += '  ' + ' '.join(pairs[i]) + '\n'
            else:
                string += '  ' + ' '.join(pairs[i])
    print(string)
    
# Fucntion that passes a list of words and the max seperation of a pair and returns the ratio of distinct pairs to all pairs
def ratio_distinct_words_pairs(words, max_sep):
    all_word_pairs = list()
    distinct_word_pairs = list()
    for i in range(len(words)):
        for j in range(i + 1, min(i + 1 + max_sep, len(words))):
            word = sorted([words[i], words[j]])     # Ensure a consistent ordered pair
            word1, word2 = word[0], word[1]
            if (word1, word2) not in all_word_pairs and (word2, word1) not in all_word_pairs:
                distinct_word_pairs.append((word1, word2))
            all_word_pairs.append((word1, word2))
    return len(distinct_word_pairs) / len(all_word_pairs)

# Prints an evaluation for a list of words
def print_evaluation(name, words, max_sep):
    print()
    print('Evaluating document {}'.format(name))
    print('1. Average word length: {:.2f}'.format(avg_word_len(words)))
    print('2. Ratio of distinct words to total words: {:.3f}'.format(len(set(words)) / len(words)))
    print('3. Word sets for document {}:'.format(name))
    print_word_sets(word_sets(words))
    print('4. Word pairs for document {}'.format(name))
    print_word_pairs(distinct_word_pairs(words, max_sep))
    print('5. Ratio of distinct word pairs to total: {:.3f}'.format(ratio_distinct_words_pairs(words, max_sep)))

if __name__ == '__main__':
    # Gets info from user
    file_name1 = input('Enter the first file to analyze and compare ==> ').strip()
    print(file_name1)
    file_name2 = input('Enter the second file to analyze and compare ==> ').strip()
    print(file_name2)
    max_sep = int(input('Enter the maximum separation between words in a pair ==> '))
    print(max_sep)
    
    # Makes file into a list of words without words in the stop file
    words1 = remove_stop_words(set(get_words(open('stop.txt'))), get_words(open(file_name1)))
    words2 = remove_stop_words(set(get_words(open('stop.txt'))), get_words(open(file_name2)))
    
    # Evaluates infomation on each document
    print_evaluation(file_name1, words1, max_sep)
    print_evaluation(file_name2, words2, max_sep)
    
    # Calculations for summary comparison
        # Finds who has higher word length
    if avg_word_len(words1) > avg_word_len(words2):
        highest_avg = (file_name1, file_name2)
    else:
        highest_avg = (file_name2, file_name1)
    
        # Finds word similiarity
    word_sim = len(set(words1) & set(words2)) / len(set(words1) | set(words2))
    
        # Finds word similiarity for each word length
    word_len1 = word_sets(words1)
    word_len2 = word_sets(words2)
    word_len = list()
    for i in range(max(len(word_len1), len(word_len2))):
        if i < min(len(word_len1), len(word_len2)) - 1:
            if len(set(word_len1[i]) | set(word_len2[i])) != 0:
                word_len_sim = len(set(word_len1[i]) & set(word_len2[i])) / len(set(word_len1[i]) | set(word_len2[i]))
            else:
                word_len_sim = 0
        elif i == len(word_len1) - 1 == len(word_len2) - 1:
            if len(set(word_len1[i]) | set(word_len2[i])) != 0:
                word_len_sim = len(set(word_len1[i]) & set(word_len2[i])) / len(set(word_len1[i]) | set(word_len2[i]))
            else:
                word_len_sim = 0
        else:
            word_len_sim = 0
        word_len.append(word_len_sim)
    
    output = ''
    i = 0
    for sim in word_len:
        i += 1
        output += '{:>4}: '.format(i)
        if i == len(word_len):
            output += '{:.4f}'.format(sim)
        else:
            output += '{:.4f}'.format(sim) + '\n'
    
        # Finds word similiarity for word pairs
    word_pair1 = set(distinct_word_pairs(words1, max_sep))
    word_pair2 = set(distinct_word_pairs(words2, max_sep))
    word_pair_sim = len(word_pair1 & word_pair2) / len(word_pair1 | word_pair2)
    
    # Gives a summary comparison of both documents
    print()
    print('Summary comparison')
    print('1. {} on average uses longer words than {}'.format(highest_avg[0], highest_avg[1]))
    print('2. Overall word use similarity: {:.3f}'.format(word_sim))
    print('3. Word use similarity by length:')
    print(output)
    print('4. Word pair similarity: {:.4f}'.format(word_pair_sim))