from Bear import Bear
from Tourist import Tourist

# Function that returns a list of neighboring locations
def get_nbrs(r, c, grid):
    nbrs = []
    rMax = len(grid) - 1
    cMax = len(grid[0]) - 1
    if r != 0:
        nbrs.append((r - 1, c))
    if c != 0:
        nbrs.append((r, c - 1))
    if c != cMax:
        nbrs.append((r, c + 1))
    if r != rMax:
        nbrs.append((r + 1, c))
    if r != 0 and c != 0:
        nbrs.append((r - 1, c - 1))
    if r != 0 and c != cMax:
        nbrs.append((r - 1, c + 1))
    if r != rMax and c != 0:
        nbrs.append((r + 1, c - 1))
    if r != rMax and c != cMax:
        nbrs.append((r + 1, c + 1))
    return nbrs

# Berry Field Class
class BerryField(object):
    def __init__(self, data, bears, tourists, bearQueue, touristQueue):
        self.grid = data
        self.bears = list()
        for bear in bears:
            self.bears.append(bear)
        self.tourists = list()
        for tourist in tourists:
            self.tourists.append(tourist)
        self.bearQueue = bearQueue
        self.touristQueue = touristQueue
    
    def __str__(self):
        final = ''
        bears = list()
        for bear in self.bears:
            bears.append(bear.local)
        tourists = list()
        for tourist in self.tourists:
            tourists.append(tourist.local)
        for r in range(len(self.grid)):
            out = ''
            for c in range(len(self.grid[r])):
                if (r, c) in bears and (r, c) in tourists:
                    out += '{:>4}'.format('X')
                elif (r, c) in bears:
                    out += '{:>4}'.format('B')
                elif (r, c) in tourists:
                    out += '{:>4}'.format('T')
                else:
                    out += '{:>4}'.format(self.grid[r][c])
            final += out + '\n'
        return final
    
    # Grows the berry field
    def grow_field(self):
        for r in range(len(self.grid)):
            for c in range(len(self.grid[r])):
                if 1 <= self.grid[r][c] < 10:
                    self.grid[r][c] += 1
        for r in range(len(self.grid)):
            for c in range(len(self.grid[r])):
                if self.grid[r][c] == 10:
                    nbrs = get_nbrs(r, c, self.grid)
                    for nbr in nbrs:
                        if self.grid[nbr[0]][nbr[1]] == 0:
                            self.grid[nbr[0]][nbr[1]] = 1
    
    # counts the total berrys in the field
    def berry_count(self):
        count = 0
        for r in range(len(self.grid)):
            for c in range(len(self.grid[r])):
                count += self.grid[r][c]
        return count
    
    # makes all the bears complete a turn
    def bear_turn(self):
        tourists = list()
        for tourist in self.tourists:
            tourists.append(tourist.local)
        badBears = list()
        for bear in self.bears:
            ate = 0
            while not bear.local in tourists and bear.sleep == 0 and ate < 30 and not (bear.local[0] < 0 or bear.local[0] > len(self.grid) - 1 or bear.local[1] < 0 or bear.local[1] > len(self.grid[0]) - 1):
                ate += self.grid[bear.local[0]][bear.local[1]]
                self.grid[bear.local[0]][bear.local[1]] = 0
                if ate < 30:
                    bear.walk()
            if bear.local in tourists:
                bear.sleep = 3
                for tourist in self.tourists:
                    if bear.local == tourist.local:
                        print(str(tourist) + ' - Left the Field')
                        self.tourists.remove(tourist)
            if bear.sleep > 0:
                bear.sleep -= 1
            if bear.local[0] < 0 or bear.local[0] > len(self.grid) - 1 or bear.local[1] < 0 or bear.local[1] > len(self.grid[0]) - 1:
                print(str(bear) + ' - Left the Field')
                badBears.append(bear)
        for bear in badBears:
            self.bears.remove(bear)
    
    # checks to see if a tourist sees a bear
    def bear_seen(self):
        bears = list()
        for bear in self.bears:
            bears.append(bear.local)
        badTourist = list()
        for tourist in self.tourists:
            seen = 0
            for bear in bears:
                if (abs(bear[0] - tourist.local[0])**2 + abs(bear[1] - tourist.local[1])**2)**0.5 <= 4:
                    tourist.seeBear = 0
                    seen += 1
            if seen == 0:
                tourist.seeBear += 1
            if seen >= 3 or tourist.seeBear >= 3:
                print(str(tourist) + ' - Left the Field')
                badTourist.append(tourist)
        for tourist in badTourist:
            self.tourists.remove(tourist)
    
    # adds a bear to the bear list from the queue
    def add_bear(self):
        count = 0
        for r in self.grid:
            count += sum(r)
        if len(self.bearQueue) > 0 and count >= 500:
            self.bears.append(Bear(self.bearQueue[0][0], self.bearQueue[0][1], self.bearQueue[0][2]))
            print(str(self.bears[-1]), '- Entered the Field')
            self.bearQueue.pop(0)
            
    # adds a tourist to the tourist list from the queue
    def add_tourist(self):
        if len(self.touristQueue) > 0 and len(self.bears) > 0:
            self.tourists.append(Tourist(self.touristQueue[0][0], self.touristQueue[0][1]))
            print(str(self.tourists[-1]), '- Entered the Field')
            self.touristQueue.pop(0)
