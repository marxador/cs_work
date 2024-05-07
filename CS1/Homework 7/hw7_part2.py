import json
if __name__ == '__main__':
    # Gets inportant info from user
    movies = json.loads(open("movies.json").read())
    ratings = json.loads(open("ratings.json").read())
    
    min_year = int(input('Min year => '))
    print(min_year)
    
    max_year = int(input('Max year => '))
    print(max_year)
    
    w1 = input('Weight for IMDB => ').strip()
    print(w1)
    w1 = float(w1)
    
    w2 = input('Weight for Twitter => ').strip()
    print(w2)
    w2 = float(w2)
    print()
    
    # Find all movies in range of years and finds it's rating if avalible/valid
    # Stores it's rating and movie info as a tuple
    valid_moives = list()
    for key in movies.keys():
        if min_year <= movies[key]['movie_year'] <= max_year:
            if key in ratings.keys() and not len(ratings[key]) < 3:
                imdb_rating = movies[key]['rating']
                average_twitter_rating = 0
                for rating in ratings[key]:
                    average_twitter_rating += rating
                average_twitter_rating /= len(ratings[key])
                rating = (w1 * imdb_rating + w2 * average_twitter_rating) / (w1 + w2)
                valid_moives.append((rating, movies[key]))
            
    # Keeps calculating the best and worse movie in a genre until 'stop'.lower() is typed
    genre = ''
    while genre != 'stop':
        genre = input('What genre do you want to see? ').strip()
        print(genre)
        genre = genre.lower()
        
        # Finds movies of specified genre
        # Stores those movies into a list of tuples as (rating, name, year)
        important_movies = list()
        for movie in valid_moives:
            for movie_type in movie[1]['genre']:
                if movie_type.lower() == genre:
                    important_movies.append((movie[0], movie[1]['name'], movie[1]['movie_year']))
        important_movies.sort(reverse= True)
        
        # Prints info related to specified genre
        if len(important_movies) > 0:
            print()
            print('Best:')
            print('        Released in {}, {} has a rating of {:.2f}'.format(important_movies[0][2], important_movies[0][1], important_movies[0][0]))
            print()
            print('Worst:')
            print('        Released in {}, {} has a rating of {:.2f}'.format(important_movies[-1][2], important_movies[-1][1], important_movies[-1][0]))
            print()
        elif genre != 'stop':
            print()
            print('No {} movie found in {} through {}'.format(genre.title(), min_year, max_year))
            print()