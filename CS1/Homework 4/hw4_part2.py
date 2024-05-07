from hw4_util import part2_get_week, print_abbreviations

# Returns a list of states in the data set
def get_state_list(data):
    states = []
    for state in data:
        states.append(state[0])
    return states

# Calculates the average daily cases per 100k population for the given week
def get_daily(data, i):
    per100K = data[i][1] / 100000
    positive = 0
    x = 2
    while x <= 8:
        positive += data[i][x] / per100K
        x += 1
    return positive / 7

# Prints the average daily cases per 100k population for the given week
def print_daily(data, state):
    states = get_state_list(data)
    if states.count(state) > 0:
        i = states.index(state)
        avg = get_daily(data, i)
        print('Average daily positives per 100K population: {:.1f}'.format(avg))
    else:
        print('State {} not found'.format(state))
        
# Calculates the percent of daily cases for the given week
def get_pct(data, i):
    positive = 0
    negative = 0
    x = 2
    while x <= 15:
        if x <= 8:
            positive += data[i][x]
        elif x <= 15:
            negative += data[i][x]
        x += 1
    total = positive + negative
    return positive / total * 100

# Prints the percent of daily cases for the given week
def print_pct(data, state):
    states = get_state_list(data)
    if states.count(state) > 0:
        i = states.index(state)
        pct = get_pct(data, i)
        print('Average daily positive percent: {:.1f}'.format(pct))
    else:
        print('State {} not found'.format(state))
    
# Prints all the quarantine states for the given week
def print_quar(data):
    states = []
    i = 0
    for i in range(len(data)):
        if get_daily(data, i) > 10 or get_pct(data, i) > 10:
            states.append(data[i][0])
    print('Quarantine states:')
    print_abbreviations(states)
    
# Calculates and prints the state with the highest infection rate for the given week
def print_high(data):
    high = (0, '')
    i = 0
    for i in range(len(data)):
        if get_daily(data, i) > high[0]:
            high = (get_daily(data, i), data[i][0])
    print('State with highest infection rate is {}'.format(high[1]))
    print('Rate is {:.1f} per 100,000 people'.format(high[0]))
    
if __name__ == "__main__":
    i = 0
    while i > -1:
        print("...")
        i = int(input('Please enter the index for a week: '))
        print(i)
        if i > -1:
            data = part2_get_week(i)           
            if data == []:
                print('No data for that week')
            else:
                request = input('Request (daily, pct, quar, high): ').strip() 
                print(request)
                request = request.lower()
                if request == 'daily':
                    state = input('Enter the state: ').strip()
                    print(state)
                    print_daily(data, state)
                elif request == 'pct':
                    state = input('Enter the state: ').strip()
                    print(state)
                    print_pct(data, state)
                elif request == 'quar':
                    print_quar(data)
                elif request == 'high':
                    print_high(data)
                else:
                    print('Unrecognized request')