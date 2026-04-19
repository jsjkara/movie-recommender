#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "User.h"    
#include "Rating.h"  

class Manager {
private:

    std::vector<Movie> movies;
    std::vector<User> users;      
    std::vector<Rating> ratings; 

public:
    
    void addMovie();         
    void searchByTitle();    
    void printAllMovies();  
    void sortByRating();     

    
    void addUser();          
    void printAllUsers();    

    void addRating();        
    void showMovieRatings(); 

    void run();              
};