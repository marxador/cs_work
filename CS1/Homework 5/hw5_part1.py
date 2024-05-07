import hw5_util

# Finds neighboring locations from a given location
def get_nbrs(rLocation, cLocation, n):
    nbrs = []
    grid = hw5_util.get_grid(n)
    rMax = len(grid) - 1
    cMax = len(grid[0]) - 1
    if rLocation != 0:
        nbrs.append((rLocation - 1, cLocation))
    if cLocation != 0:
        nbrs.append((rLocation, cLocation - 1))
    if cLocation != cMax:
        nbrs.append((rLocation, cLocation + 1))
    if rLocation != rMax:
        nbrs.append((rLocation + 1, cLocation))
    return nbrs

# Prints a list of lists in a grid
def print_grid(n):
    grid = hw5_util.get_grid(n)
    print('Grid {}'.format(n))
    for row in grid:
        numbers = ''
        for number in row:
            if number < 10:
                numbers += '   {}'.format(number)
            else:
                numbers += '  {}'.format(number)
        print(numbers)

# Prints all neighbors of starting locations
def print_nbrs(n):
    startLocations = hw5_util.get_start_locations(n)
    for location in startLocations:
        nbrs = ''
        neighbors = get_nbrs(location[0], location[1], n)
        for nbr in neighbors:
            nbrs += ' {}'.format(nbr)
        print('Neighbors of {}:{}'.format(location, nbrs))
             
# If there is a valid path, calculates the change in elevation
def calc_path(n):
    path = hw5_util.get_path(n)
    grid = hw5_util.get_grid(n)
    downward = 0
    upward = 0
    # This loop checks if there is a valid path
    for i in range(len(path) - 1):                      
        nbrs = get_nbrs(path[i][0], path[i][1], n)
        nbring = False
        for nbr in nbrs:
            if nbr == path[i + 1]:
                nbring = True
        if not nbring:
            return 'Path: invalid step from {} to {}'.format(path[i], path[i + 1])
    # This loop calculates change in elevation if there is a path
    for i in range(len(path) - 1):
        if grid[path[i][0]][path[i][1]] > grid[path[i + 1][0]][path[i + 1][1]]:
            downward += grid[path[i][0]][path[i][1]] - grid[path[i + 1][0]][path[i + 1][1]]
        elif grid[path[i][0]][path[i][1]] < grid[path[i + 1][0]][path[i + 1][1]]:
            upward += abs(grid[path[i][0]][path[i][1]] - grid[path[i + 1][0]][path[i + 1][1]])
    return 'Valid path\n' + 'Downward {}\n'.format(downward) + 'Upward {}'.format(upward)

if __name__ == "__main__":
    n = -1
    while n < 0 or n > 3:
        n = int(input('Enter a grid index less than or equal to 3 (0 to end): '))
        print(n)
    grid = hw5_util.get_grid(n)
    
    answer = input('Should the grid be printed (Y or N): ').strip()
    print(answer)
    
    if answer.lower() == 'y':
        print_grid(n)
    
    print('Grid has {} rows and {} columns'.format(len(grid), len(grid[0])))
    print_nbrs(n)
    print(calc_path(n))