#include<string> 
#include<iostream> 
#include<vector> 
#include<fstream> 
#include<regex> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include "bank.h"
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

  Bank mainbank;
  mainbank.printChapters();
 
  // chapter selector 
  cout << "Please select chapters " << endl;

  do {
	cout << "Enter e to end: ";
	cin >> tmp;

  	if(mainbank.validChapter(atoi(tmp.c_str()))){
		// need check here to not add already added chapters
		Chapters.push_back(atoi(tmp.c_str()));
		cout << "added chapter " << tmp << endl;
	}
	//cout << "tmp is: " << tmp << endl;
  } while (tmp != "e");	

  if(Chapters.size() > 0) 
{
  cout << "Chapters.size() = " << Chapters.size() << endl;
  // number of questions selector
  cout << "Please select number of questions from each chapter " << endl;

  do {
	cout << ": ";
	cin >> tmp;

	int ti = atoi(tmp.c_str());

	// only accept 1-99 as valid input
	if(ti>0 && ti<100){
		questions_to_take = ti;
		inloop = 0;
	}

  } while (inloop); 
}

  for(int i=0; i<Chapters.size(); i++){
  	correct_answers += mainbank.takeQuestion(Chapters[i],questions_to_take);
	total_questions++;
  }
	cout << "Total questions: " << total_questions << "  Correct answers: " << correct_answers << endl;

	float score = 0;
	if(correct_answers > 0){
			score = (total_questions / correct_answers) * 100;
            cout << endl << "Final Score: " << score << "%" << endl;
	}
	if((correct_answers == total_questions) && total_questions > 0){
			score = 100;
            cout << endl << "Final Score: " << score << "%" << endl;
	}	
    if((correct_answers == total_questions) && total_questions == 0){
			score = 0;
            cout << endl << "NO QUIZ WAS TAKEN" << endl;
	}	

/*
  do {
    cout << "Enter e to end: ";
    cin >> tc;
  	if(mainbank.validChapter(tc)){
		Chapters.push_back(tc);
		cout << tc << " added" << endl;
  	}else{
		cout << tc << " not valid" << endl;
  	}
  } while (tc != 0);
  
  cout << "How many questions from each chapter " << endl;

*/

 // mainbank.takeQuestion(2,14);

/*
  Question one;
  one.setup("Which of the items listed below is not one of the software engineering layers?");

  one.addAns("Process");
  one.addAns("Manufacturing");
  one.addAns("Methods");
  one.addAns("Tools");
 */ 

//  cout << one.retQuestion() << endl << endl;
//  one.printAnswers();

  return 0;
}
