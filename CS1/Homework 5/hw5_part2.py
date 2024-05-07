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

# Prints a list of lists in a grid | Part 1
def print_grid(n):
    grid = hw5_util.get_grid(n)
    print('Grid {}'.format(n))
    for row in grid:
        numbers = ''
        for number in row:
            if number < 10:
                numbers += '\t {}'.format(number)
            else:
                numbers += '\t{}'.format(number)
        print(numbers)

# Prints all neighbors of starting locations | Part 1
def print_nbrs(n):
    startLocations = hw5_util.get_start_locations(n)
    for location in startLocations:
        nbrs = ''
        neighbors = get_nbrs(location[0], location[1], n)
        for nbr in neighbors:
            nbrs += '{} '.format(nbr)
        print('Neighbors of {}: {}'.format(location, nbrs))
             
# If there is a valid path, calculates the change in elevation | Part 1
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

# Calculates the global max of the grid
def global_max(n):
    grid = hw5_util.get_grid(n)
    maximum = 0
    location = ()
    for r in range(len(grid)):
        for c in range(len(grid[r])):
             if maximum < grid[r][c]:
                 location = (r, c)
                 maximum = grid[r][c]
    return location

# Checks if the location is a local max
def local_max(n, location):
    grid = hw5_util.get_grid(n)
    nbrs = get_nbrs(location[0], location[1], n)
    for nbr in nbrs:
        if grid[nbr[0]][nbr[1]] > grid[location[0]][location[1]]:
            return False
    return True

def print_max(path, n):
    if path[-1] == global_max(n):
        print('global maximum')
    elif local_max(n, path[-1]):
        print('local maximum')
    else:
        print('no maximum')

# Returns the steepest path avaliable from a location
def calc_steep_path(n, location, steepest):
    # important inital variables
    path = [location]
    grid = hw5_util.get_grid(n)
    highest = location   
    newPath = True
    
    # loop to find the next best location until there are no more
    while newPath:
        # variables that need to be rest for each step
        newPath = False
        nbrs = get_nbrs(location[0], location[1], n)
        
        # loop to find next step
        for nbr in nbrs:
            if grid[nbr[0]][nbr[1]] - grid[location[0]][location[1]] <= steepest:
                if grid[nbr[0]][nbr[1]] > grid[highest[0]][highest[1]]:
                    highest = nbr
                    newPath = True    
                    
        # if statement to check if you should contiune
        if not newPath:
            return path
        else:
            path.append(highest)
            location = highest

# Returns the most gradual path avaliable from a location
def calc_gradual_path(n, location):
    # important inital variables
    path = [location]
    grid = hw5_util.get_grid(n)
    lowest = global_max(n)
    previous = location
    newPath = True
    
    # loop to find the next best location until there are no more
    while newPath:
        # variables that need to be rest for each step
        newPath = False
        nbrs = get_nbrs(location[0], location[1], n)
        
        # loop to find next step
        for nbr in nbrs:
            if grid[nbr[0]][nbr[1]] - grid[location[0]][location[1]] > 0 and nbr != previous and grid[nbr[0]][nbr[1]] - grid[location[0]][location[1]] <= steepest:
                if grid[nbr[0]][nbr[1]] < grid[lowest[0]][lowest[1]] or nbr == global_max(n):
                    lowest = nbr
                    newPath = True
                    
                    
        # if statement to check if you should contiune
        if not newPath:
            return path
        else:
            path.append(lowest)
            previous = location
            location = lowest
            lowest = global_max(n) 

# Prints the steep path as requested
def print_path(path, n):
    count = 0
    statement = ''
    for local in path:
        if count < 5:
            statement += '{} '.format(local)
            count += 1
        else:
            print(statement)
            statement = '{} '.format(local)
            count = 1
    print(statement)
    print_max(path, n)

def print_path_grid(locations, n):
    pathGrid = []
    grid = hw5_util.get_grid(n)
    for r in range(len(grid)):
        row = []
        for c in range(len(grid[r])):
            row.append(0)
        pathGrid.append(row)
    for location in locations:
        pathGrid[location[0]][location[1]] += 1
    for r in range(len(grid)):
        for c in range(len(grid[r])):
            if pathGrid[r][c] == 0:
                pathGrid[r][c] = '.'
    for row in pathGrid:
        numbers = ''
        for number in row:
            numbers += '  {}'.format(number)
        print(numbers)
    
            

if __name__ == "__main__":
    n = -1
    while n < 0 or n > 3:
        n = int(input('Enter a grid index less than or equal to 3 (0 to end): '))
        print(n)
    grid = hw5_util.get_grid(n)
    
    steepest = int(input('Enter the maximum step height: '))
    print(steepest)
    
    answer = input('Should the path grid be printed (Y or N): ').strip()
    print(answer)
    
    print('Grid has {} rows and {} columns'.format(len(grid), len(grid[0])))
    
    globalMax = global_max(n)
    print('global max: {} {}'.format(globalMax ,grid[globalMax[0]][globalMax[1]]))
    
    locations = []
    startLocations = hw5_util.get_start_locations(n)
    for location in startLocations:
        print('===')
        print('steepest path')
        steepPath = calc_steep_path(n, location, steepest)
        print_path(steepPath, n)
        
        print('...')
        print('most gradual path')
        gradualPath = calc_gradual_path(n, location)
        print_path(gradualPath, n)                
        
        for location in steepPath:
            locations.append(location)
        for location in gradualPath:
            locations.append(location)
        
    if answer.lower() == 'y':
        print('===')
        print('Path grid')
        print_path_grid(locations, n)