#ifndef __RECOMMENDATIONSYSTEM_H
#define __RECOMMENDATIONSYSTEM_H

class RecommendationSystem
{
private:
	

public:
	// Member variables
	int numUsers;
	int numMovies;
	int numShows;
	int** userMovieRatingsMatrix;
	int** userShowRatingsMatrix;
	
	// Constuctor
	RecommendationSystem();
	// Destructor
	~RecommendationSystem();

	// Setters
	void setMovieRatings(const int& user, const int& movie, const int& rating);
	void setShowRatings(const int& user, const int& show, const int& rating);

	// Member Functions const
	void recommendMovies(int userId, int numRecommendations, int* recommendedMovies) const;
	void recommendShows(int userId, int numRecommendations, int* recommendedShows) const;
};
#endif