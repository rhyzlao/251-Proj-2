//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h" 
using namespace std;
int NumberOfMovies = 0;
double NumberOfReviews = 0.0;

struct MovieData {
	string NameofMovie;
	int PubYear = -1;
	int Num5Stars = 0;
	int Num4Stars = 0;
	int Num3Stars = 0;
	int Num2Stars = 0;
	int Num1Stars = 0;
	};

//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}

void InputMovieReviews(string reviewsFilename, binarysearchtree<int, MovieData> &ID){
  ifstream reviewsFile(reviewsFilename);
  int      RatingId, movieID;
  int      currentReview;
	
  if (!reviewsFile.good())
  {
    cout << "**Error: unable to open movies file '" << reviewsFilename << "', exiting" << endl;
    return;
  }

  reviewsFile >> RatingId;
	
  while(!reviewsFile.eof()){
	  reviewsFile >> movieID;
	  MovieData* MovieStruct;
	  MovieStruct = ID.search(movieID);
	  reviewsFile >> currentReview;

//Input reviews to correct stars	  
	 if(MovieStruct != nullptr){ 
		  switch(currentReview) {
			  case 1: 
				  MovieStruct->Num1Stars++;	
				  break;
			  case 2:
				  MovieStruct->Num2Stars++;
				  break;
			  case 3:
				  MovieStruct->Num3Stars++;
				  break;
			  case 4:
				  MovieStruct->Num4Stars++;
				  break;
			  case 5:
				  MovieStruct->Num5Stars++;
				  break;
		  }
	 }

	  
	  NumberOfReviews = NumberOfReviews + 1;
	  reviewsFile >> RatingId;
  }
	
}

//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
void InputMovies(string moviesFilename, binarysearchtree<int, MovieData> &ID, binarysearchtree<string, int>  &Name)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
	

    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name);  
    // debugging:
    //cout << id << "," << pubYear << "," << name << endl;
	  
	MovieData MovieNames;
	MovieNames.NameofMovie = name;
	MovieNames.PubYear = pubYear;
	MovieNames.Num1Stars = 0;
	MovieNames.Num2Stars = 0;
	MovieNames.Num3Stars = 0;
	MovieNames.Num4Stars = 0;
	MovieNames.Num5Stars = 0;
	  
	ID.insert(id, MovieNames);
	Name.insert(name, id);
	NumberOfMovies = NumberOfMovies + 1;
	  
    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
}


bool CheckVal(string MovieName){ //False means id
	for(size_t i = 0; i < MovieName.length(); i++){
		if(isalpha(MovieName[i])){
			return true; //true means Name
		}
	}
	return false;
}

int main()
{
  //MovieData* movie_info;
  binarysearchtree<int, MovieData> ID_movies;
  binarysearchtree<string, int> Name_movies;
		 
  string moviesFilename;
  string reviewsFilename;

  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;

  string junk;
  getline(cin, junk);  // discard EOL following last input:

  InputMovies(moviesFilename, ID_movies, Name_movies);
  InputMovieReviews(reviewsFilename, ID_movies);
	
  cout << "Num movies: " << NumberOfMovies << endl;
  cout << "Num reviews: " << NumberOfReviews << endl << endl;

  cout << "Tree by movie id: size=" << ID_movies.size() << ", height=" << ID_movies.height() << endl; //edit this
  cout << "Tree by movie name: size=" << Name_movies.size() <<  ", height=" << Name_movies.height() << endl << endl; //edit  this 
	
  string input;
	
  
  while(input != "#"){
	  

	  cout << "Enter a movie id or name (or # to quit)> ";
	  
	  getline(cin,input);
	  
	  
	  //cout << "After getline" << endl;
	  
	  if(input.compare("#") == 0){
		  break;
	  }
	  
	  //cout << "After check sentinal" << endl;
	  
	  bool value = CheckVal(input);
	  
	  //cout << "input is: " << input << "#"<< endl;
	  //cout << value << endl;
	  MovieData* MovieNode = new MovieData();
	  int* MovieNum;
	  int total;
	  if(value == false){	//ID	
		  //cout<<"in first if\n";
		  int new_input = std::stoi(input); 
		  //cout << "after stoi\n";
	  
		  MovieNode = ID_movies.search(new_input);	 
		  
		  if(MovieNode == nullptr){
			  cout << "not found..." << endl << endl;
			  continue;
		  }
		  else{
			  cout << "Movie ID: " << new_input << endl; 
			  cout << "Movie Name: " << MovieNode->NameofMovie << endl; 
			  //Get total number of reviews
			  double total = MovieNode->Num1Stars+
						  MovieNode->Num2Stars+
						  MovieNode->Num3Stars+
						  MovieNode->Num4Stars+
						  MovieNode->Num5Stars;
			  //Get weighter reviews
			  double AvgVal = ((5*MovieNode->Num5Stars)+
							   (4*MovieNode->Num4Stars)+
							   (3*MovieNode->Num3Stars)+
							   (2*MovieNode->Num2Stars)+
							   (MovieNode->Num1Stars)) / total;
			  if(total == 0){
				  AvgVal = 0;
			  }
			  cout << "Avg rating: " << AvgVal << endl;
			  cout << "5 stars: " << MovieNode->Num5Stars << endl;
			  cout << "4 stars: " << MovieNode->Num4Stars << endl;
			  cout << "3 stars: " << MovieNode->Num3Stars << endl;
			  cout << "2 stars: " << MovieNode->Num2Stars << endl;
			  cout << "1 star: " << MovieNode->Num1Stars << endl << endl;		  
		  }		  
	  }
	  else if(value == true){ //Name
		  MovieNum = Name_movies.search(input);
		  if(MovieNum == nullptr){
			  cout << "not found..." << endl << endl;
			  continue;
		  }
		  MovieData* newMovieNode = ID_movies.search(*MovieNum);
		  //cout << newMovieNode->PubYear;
		  if(newMovieNode == nullptr){
			  cout << "not found..." << endl << endl;
			  continue;;
 		  }
		  else{
			  cout << "Movie ID: " << *MovieNum << endl; //edit
			  cout << "Movie Name: " << input << endl; //edit
			  //Get total number of reviews
			  double total = newMovieNode->Num1Stars+
						  newMovieNode->Num2Stars+
						  newMovieNode->Num3Stars+
						  newMovieNode->Num4Stars+
						  newMovieNode->Num5Stars;
			  //Get weighted reviews
			  double AvgVal = ((5*newMovieNode->Num5Stars)+
							   (4*newMovieNode->Num4Stars)+
							   (3*newMovieNode->Num3Stars)+
							   (2*newMovieNode->Num2Stars)+
							   (newMovieNode->Num1Stars)) / total;
			  if(total == 0){
				  AvgVal = 0;
			  }
			  cout << "Avg rating: " << AvgVal << endl;
			  cout << "5 stars: " << newMovieNode->Num5Stars << endl;
			  cout << "4 stars: " << newMovieNode->Num4Stars << endl;
			  cout << "3 stars: " << newMovieNode->Num3Stars << endl;
			  cout << "2 stars: " << newMovieNode->Num2Stars << endl;
			  cout << "1 star: " << newMovieNode->Num1Stars << endl << endl;		  
		  }		  
	  }
  }
// //checking insert and search
// 	binarysearchtree<int, int> bst1;
// 	//binarysearchtree<int,string> bst2;
// 	//binarysearchtree<string,int> bst3;
// 	bst1.insert(123, 456);
	
// 	int* value = bst1.search(123);
// 	cout << *value << endl; // should output 456
// 	*value = 789; // change value to 789
// binarysearchtree<int,int> bst1;
// bst1.insert(123, 456);

// binarysearchtree<int, int> bst2 = bst1;
// // copy construct:
// cout << bst1.size() << " vs. " << bst2.size() << endl;
// cout << bst1.height() << " vs. " << bst2.height() << endl;
// int* value1 = bst1.search(123);
// int* value2 = bst2.search(123);
// cout << *value1 << " vs. " << *value2 << endl; // both 456
// *value2 = 789; // this should only change bst2:
// cout << *value1 << " vs. " << *value2 << endl; // 456 vs. 789
  // done:
//   MovieData* temp = ID_movies.search(123);
// 	if(temp == nullptr){
// 		printf("is null");
// 	}
	
// 	cout << temp->Num5Stars << endl;
	//printf("Name: %c, ID: %c", )
  
  return 0;
  
}



