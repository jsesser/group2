#include<string> 
#include<iostream> 
#include<vector> 
#include<fstream> 
#include<regex> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include "bank.h"
#include "oldquiz.h"
using namespace std;


/// g++ -std=c++0x quizzer.cpp bank.cpp -o quiz

int main () {

  int total_questions=0;
  //int correct_questions = 0;
  int correct_answers = 0;
  int questions_to_take = 0;
  vector <int> Chapters;
  string tmp;
  bool inloop = 1;
  bool custom_quiz = 1;

  // build bank of questions and old quiz formats
  Bank mainbank;
  oldquiz Oldquiz;
   
   
  cout << "Would you like to take a predefined quiz or design your own?" << endl;
  cout << "1. Predefined " << endl; 
  cout << "2. Design my own " << endl; 

  inloop = 1;
  do{
	cin >> tmp;
	if(atoi(tmp.c_str()) == 1){
		custom_quiz = 0;
		inloop = 0;
	}
	else if(atoi(tmp.c_str()) == 2){
		inloop = 0;
	}else{
		cout << "Invalid response, please try again." << endl;
	}
  }
  while(inloop);
// done with selection of quiz type



// build quiz if that was the option picked
if(custom_quiz){ 
  // chapter selector 
  cout << "Your ID for this quiz is " << Oldquiz.get_highest_ID() << ". Please take note of this value, you will use it to take this quiz again in the future." << endl;
  mainbank.printChapters();
  cout << "Please select chapters " << endl;

  do {
	cout << "Enter e to end: ";
	cin >> tmp;

  	if(mainbank.validChapter(atoi(tmp.c_str()))){

		// only add chapters that have not been added yet 
		bool isUnique = 1;
		for(int i=0; i<Chapters.size(); i++){
			if(Chapters[i] == atoi(tmp.c_str())){
				cout << "Chapter " << tmp << " has already been added" << endl;
				isUnique = 0;
				continue;
			}
		}
			if(isUnique){
				Chapters.push_back(atoi(tmp.c_str()));
				cout << "added Chapter " << tmp << endl;
			}
	}else{
			if(tmp != "e"){
				cout << tmp << " is an invalid chapter number" << endl;
			}
	}
  } while (tmp != "e");	

  if(Chapters.size() > 0){

  //cout << "Chapters.size() = " << Chapters.size() << endl;
  // number of questions selector
  cout << "Please select number of questions from each chapter " << endl;

  	inloop = 1;
  	do {
		cout << ": ";
		cin >> tmp;

		int ti = atoi(tmp.c_str());

		// only accept 1-99 as valid input
		// this needs the real range
		if(ti>0 && ti<100){
			questions_to_take = ti;
			inloop = 0;
		}
  	} while (inloop); 
  }

  // do not allow tests to be taken out of chapter order
  // this sort also ensures that the save file will always have chapters in order
  sort(Chapters.begin(),Chapters.end());


} ///// END if custom_quiz

/// time to pick and build a predefined quiz
if(!custom_quiz){

	Oldquiz.printQuizes();
	int ti;
  
	inloop = 1;
  	do {
	cout << "Quiz ID: ";
	cin >> tmp;

	ti = atoi(tmp.c_str());

	// only accept 1-99 as valid input
	// needs to be fixed to actually know valid quiz IDs
	if(ti>0 && ti<100){
		questions_to_take = ti;
		inloop = 0;
		}
  	} while (inloop); 

	
	ti--;
	questions_to_take = Oldquiz.quizholders[ti].getQnumber();

	// copy the chapter vector from the old quizes
	Chapters = Oldquiz.quizholders[ti].Chapters;

}// end predefined quiz picker



cout << "questions_to_take is " << questions_to_take << endl;

// this for loop is the gives the entire quiz
  for(int i=0; i<Chapters.size(); i++){
  	correct_answers += mainbank.takeQuestion(Chapters[i],questions_to_take);
	total_questions += questions_to_take;
  }


// calculate score
	cout << "\n\nTotal questions: " << total_questions << "  Correct answers: " << correct_answers << endl;

	float score = 0;
	if(correct_answers > 0){
			score = ((float)correct_answers / (float)total_questions) * 100;
            cout << endl << "Final Score: " << score << "%" << endl;
	}
	if(correct_answers == 0){
            cout << endl << "Final Score: 0%" << endl;
	}
//	if((correct_answers == total_questions) && total_questions > 0){
//			score = 100;
//            cout << endl << "Final Score: " << score << "%" << endl;
//  }	
    if((correct_answers == total_questions) && total_questions == 0){
			score = 0;
            cout << endl << "NO QUIZ WAS TAKEN" << endl;
	}	
// done with scoring


// save quiz if it was a custom one
if(custom_quiz){
	cout << "\n\nWould you like to save this quiz format for a future attempt?" << endl;

	int save_quiz_answer = 0; 
	int ti = 0;

	inloop = 1;
    do {
    cout << "1. Yes" << endl << "2. No" << endl << ": ";
    cin >> tmp;

    ti = atoi(tmp.c_str());

    // only accept 1-99 as valid input
    // needs to be fixed to actually know valid quiz IDs
    if(ti>0 && ti<3){
        save_quiz_answer = ti;
        inloop = 0;
        }
    } while (inloop);

	// save quiz. Conver chapters to an array reference
	Oldquiz.saveQuiz(&Chapters[0],Chapters.size(),questions_to_take);
    


}



  return 0;
}
