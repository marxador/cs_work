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
    
    # Prints the intial field
    print('Field has {} berries.'.format(berryField.berry_count()))
    print(str(berryField))
    print('Active Bears:')
    for bear in bears:
        print(str(bear))
    print()
    print('Active Tourists:')
    for tourist in tourists:
        print(str(tourist))
        