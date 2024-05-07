# Bear Class
class Bear():
    def __init__(self, row, column, direction):
        self.local = (row, column)
        self.direction = direction
        self.sleep = 0
    
    def __str__(self):
        if self.sleep == 0:
            return 'Bear at ({},{}) moving {}'.format(self.local[0], self.local[1], self.direction)
        else:
            return 'Bear at ({},{}) moving {} - Asleep for {} more turns'.format(self.local[0], self.local[1], self.direction, self.sleep)
    
    # moves the bear in the direction it's pointing in
    def walk(self):
        if self.direction == 'N':
            self.local = (self.local[0] - 1, self.local[1])
        elif self.direction == 'S':
            self.local = (self.local[0] + 1, self.local[1])
        elif self.direction == 'E':
            self.local = (self.local[0], self.local[1] + 1)
        elif self.direction == 'W':
            self.local = (self.local[0], self.local[1] - 1)
        elif self.direction == 'NE':
            self.local = (self.local[0] - 1, self.local[1] + 1)
        elif self.direction == 'NW':
            self.local = (self.local[0] - 1, self.local[1] - 1)
        elif self.direction == 'SE':
            self.local = (self.local[0] + 1, self.local[1] + 1)
        elif self.direction == 'SW':
            self.local = (self.local[0] + 1, self.local[1] - 1)
    