# Function that returns the next location of pikachu as a tuple
def move_pokemon(row, column, direction, steps):
    direction = direction.lower()
    if direction == 'n':
        row -= steps
        row = max(row, 0)
    elif direction == 's':
        row += steps
        row = min(row, 150)
    elif direction == 'e':
        column += steps
        column = min(column, 150)
    elif direction == 'w':
        column -= steps
        column = max(column, 0)
    return (row, column)

# Gets needed information from user and reprints it
turns = int(input('How many turns? => '))
print(turns)
name = input('What is the name of your pikachu? => ').strip()
print(name)
often = int(input('How often do we see a Pokemon (turns)? => '))
print(often)
print()

# Variables for important information
location = (75, 75)
direction = ''
record = []

# Runs the simulation using a while loop
print('Starting simulation, turn 0 {} at (75, 75)'.format(name))
i = 0
while i < turns:
    i += 1
    direction = input('What direction does {} walk? => '.format(name)).strip()
    print(direction)
    location = move_pokemon(location[0], location[1], direction, 5)
    if i % often == 0:
        print('Turn {}, {} at {}'.format(i, name, location))
        element = input('What type of pokemon do you meet (W)ater, (G)round? => ').strip()
        print(element)
        element = element.lower()
        if element == 'w':
            location = move_pokemon(location[0], location[1], direction, 1)
            print('{} wins and moves to {}'.format(name, location))
            record.append('Win')
        elif element == 'g':
            location = move_pokemon(location[0], location[1], direction, -10)
            print('{} runs away to {}'.format(name, location))
            record.append('Lose')
        else:
            record.append('No Pokemon')
print('{} ends up at {}, Record: {}'.format(name, location, record))