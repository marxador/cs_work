from BerryField import BerryField
from Bear import Bear
from Tourist import Tourist
import json

if __name__ == '__main__':
    # Gets information from file and adds its to the classes
    file = input('Enter the json file name for the simulation => ')
    print(file)
    print()
    
    f = open(file)
    data = json.loads(f.read())
    
    bearQueue = data['reserve_bears']
    touristQueue = data['reserve_tourists']
    
    bears = list()
    for bear in data['active_bears']:
        bears.append(Bear(bear[0], bear[1], bear[2]))
    tourists = list()
    for tourist in data['active_tourists']:
        tourists.append(Tourist(tourist[0], tourist[1]))
    berryField = BerryField(data['berry_field'], bears, tourists, bearQueue, touristQueue)
    
    # Runs the simulation 5 times
    print('Starting Configuration')
    print('Field has {} berries.'.format(berryField.berry_count()))
    print(str(berryField))
    print('Active Bears:')
    for bear in berryField.bears:
        print(str(bear))
    print()
    print('Active Tourists:')
    for tourist in berryField.tourists:
        print(str(tourist))
    print()
    turn = 0
    while turn < 5:
        turn += 1
        print('Turn: {}'.format(turn))
        
        berryField.grow_field()
        berryField.bear_turn()
        berryField.bear_seen()
        
        print('Field has {} berries.'.format(berryField.berry_count()))
        print(str(berryField))
        print('Active Bears:')
        for bear in berryField.bears:
            print(str(bear))
        print()
        print('Active Tourists:')
        for tourist in berryField.tourists:
            print(str(tourist))
        print()
        if turn < 5:
            print()