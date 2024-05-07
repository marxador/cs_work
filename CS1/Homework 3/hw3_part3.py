# Imports needed functions
import math

# Function that finds next year's bears population and berry field area and returns it as a tuple
def find_next(bears, berries, tourists):
    bears_next = int(berries / (50* (bears + 1)) + bears * 0.60 - (math.log(1 + tourists, 10) * 0.1))
    berries_next = (berries * 1.5) - (bears + 1) * (berries / 14) - (math.log(1 + tourists, 10) * 0.05)
    return (max(bears_next, 0), max(berries_next, 0))

# Function to calculate the tourist amount
def calc_tourist(bears):
    tourists = 0
    if bears < 4 or bears > 15:
        tourists = 0
    else:
        if bears <= 10:
            tourists = 10000 * bears
        else:
            tourists = 100000 + 20000 * (bears - 10)
    return tourists

# Gets needed information from user and reprints it
bears = input('Number of bears => ')
print(bears)
bears = int(bears)
berries = input('Size of berry area => ')
print(berries)
berries = float(berries)

# Variables for important information
tourists = calc_tourist(bears)
low = (bears, berries, tourists)
high = (bears, berries, tourists)

# Runs a simulation of the population for the next ten years
print('Year\tBears\tBerry\tTourists')
year = 0
while year < 10:
    year += 1
    print('{}\t\t{}\t{:.1f}\t{}'.format(year, bears, berries, tourists))
    low = (min(bears, low[0]), min(berries, low[1]), min(tourists, low[2]))
    high = (max(bears, high[0]), max(berries, high[1]), max(tourists, high[2]))
    nextYear = find_next(bears, berries, tourists)
    bears = nextYear[0]
    berries = nextYear[1]
    tourists = calc_tourist(bears)

# Reports stats after simulation has ran
print()
print('Min:\t{}\t\t{:.1f}\t{}'.format(low[0], low[1], low[2]))
print('Max:\t{}\t\t{:.1f}\t{}'.format(high[0], high[1], high[2]))