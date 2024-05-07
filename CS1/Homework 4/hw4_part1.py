from hw4_util import part1_get_top

# Returns a score based on the length of the passed password
def length_rule(password):
    assert type(password) is str, "the password isn't a string"
    score = 0
    if len(password) == 6 or len(password) == 7:
        score = 1
        print('Length: +{}'.format(score))
    elif len(password) >= 8 and len(password) <= 10:
        score = 2
        print('Length: +{}'.format(score))
    elif len(password) > 10:
        score = 3
        print('Length: +{}'.format(score))
    return score

# Returns a score based on the variety of upper and lower case letters in the password
def case_rule(password):
    assert type(password) is str, "the password isn't a string"
    score = 0
    lower = 0
    upper = 0
    for letter in password:
        if letter.islower():
            lower += 1
        elif letter.isupper():
            upper += 1
    if upper >= 2 and lower >= 2:
        score = 2
        print('Cases: +{}'.format(score))
    elif upper >= 1 and lower >= 1:
        score = 1
        print('Cases: +{}'.format(score))
    return score

# Returns a score based on the amount of digits in the password
def digits_rule(password):
    assert type(password) is str, "the password isn't a string"
    score = 0
    digit = 0
    for letter in password:
        if letter.isnumeric():
            digit += 1
    if digit >= 2:
        score = 2
        print('Digits: +{}'.format(score))
    elif digit == 1:
        score = 1
        print('Digits: +{}'.format(score))
    return score

# Returns a score based on the amount of special characters in the password
def punctuation_rule(password):
    assert type(password) is str, "the password isn't a string"
    score1 = 0
    score2 = 0
    for letter in password:
        if letter == '%' or letter == '^' or letter == '&' or letter == '*':
            score1 = 1
        elif letter == '!' or letter == '@' or letter == '#' or letter == '$':
            score2 = 1
    if score1 == 1:
        print('%^&*: +{}'.format(score1))
    if score2 == 1:
        print('!@#$: +{}'.format(score2))
    total = score1 + score2
    return total

# Return a score based on if it potentially matches a NY state license plate
def ny_license_rule(password):
    assert type(password) is str, "the password isn't a string"
    score = 0
    char = 0
    digit = 0
    for letter in password:
        if letter.isalpha():
            char += 1
        elif letter.isnumeric():
            if char == 3:
                digit += 1
            else:
                char = 0
                digit = 0
        else:
            char = 0
            digit = 0
        if digit == 4:
            score = -2
            print('License: {}'.format(score))
            return score
    return score

# Returns a score based on if the password is a common password
def common_password_rule(password):
    assert type(password) is str, "the password isn't a string"
    score = 0
    for word in part1_get_top():
        if password.lower() == word:
            score = -3
            print('Common: {}'.format(score))
            return score
    return score

# Returns a password rating based on the score
def calc_password_strength(score):
    assert type(score) is int, "the score isn't a integer"
    strength = ''
    if score <= 0:
        strength = 'rejected'
    elif score == 1 or score == 2:
        strength = 'poor'
    elif score == 3 or score == 4:
        strength = 'fair'
    elif score == 5 or score == 6:
        strength = 'good'
    else:
        strength = 'excellent'
    return strength

if __name__ == "__main__":
    password = input('Enter a password => ').strip()
    print(password)
    
    score = length_rule(password)
    score += case_rule(password)
    score += digits_rule(password)
    score += punctuation_rule(password)
    score += ny_license_rule(password)
    score += common_password_rule(password)
    print('Combined score: {}'.format(score))
    
    strength = calc_password_strength(score)
    print('Password is {}'.format(strength))