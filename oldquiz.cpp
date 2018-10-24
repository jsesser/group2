#include<string> 
#include<iostream> 
#include<vector> 
#include<fstream> 
#include<regex> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include "oldquiz.h"
using namespace std;


/*oldquiz::oldquiz(){
	ifstream infile;
	infile.open("oldquiz.txt");
	string line;

}*/

	void oldquiz::printQuizes(){

	ifstream infile;
	infile.open("oldquiz.txt");
	string line;
	regex c("([0-9])");	
	smatch match;

		while(getline(infile,line)){
			const string s = line;

				 while(regex_search(s, match, c)) {
						cout << match[0] << endl;
			}

		}	

	}

	// old quizes are just an integer array of chapters and number of questions
	void saveQuiz(int* c, int n);
