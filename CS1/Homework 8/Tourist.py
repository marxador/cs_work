# Tourist Class
class Tourist():
    def __init__(self, row, column):
        self.local = (row, column)
        self.seeBear = 0
    
    def __str__(self):
        return 'Tourist at ({},{}), {} turns without seeing a bear.'.format(self.local[0], self.local[1], self.seeBear)
    