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


/// g++ -std=c++0x quizzer.cpp -o quiz

void Question::printAnswers(){

	for(int i=0; i<answers.size(); i++){
		int k = i+1;
		cout << k << ". " << answers[i] << endl; 
	}
	cout << endl;
}

void Bank::printChapters(){
		cout << "Available chapters: " ;
	for(int i=0; i<Chapters.size(); i++){
		cout << Chapters[i] << " ";	
	}
	cout << endl << endl;
}

bool Bank::validChapter(int c){
	for(int i=0; i<Chapters.size(); i++){
		if(Chapters[i] == c){
			return 1;
		}
	}	
	return 0;
}

int Bank::takeQuestion(int c, int n){

	int j=0;
	bool finished = 0;
	int results = 0;
	string tmp;
	bool inloop = 1;

	for(int i=0; i<questions.size(); i++){

		if(j>=n){
			continue;
		}

		if(questions[i].retChapter() == c){
			j++;

			cout << questions[i].retQuestion() << endl << endl;
			questions[i].printAnswers();

			do {
			cout << ": ";
					cin >> tmp;

					int ti = atoi(tmp.c_str());

					// only accept 1-5 as valid input
					// add feature to count the number of answers and check the real value...
					if(ti>0 && ti<6){
							inloop = 0;
							if(questions[i].check(ti)){
								cout << "correct " << endl;
								results++;		
							}	
					}
			} while (inloop);			
		}
	}
	return results;
}

Bank::Bank(){

	ifstream infile;
	infile.open("bank.txt");
	string line;

	// if an answer starts with a number, this could cause a problem
	regex n("^([0-9]+)");
	regex c("^CHAPTER ([0-9]+)");
	regex a("^A([0-9])+");

	Question q;

	smatch match;
	int currentChapter;
	int currentQuestion;
	int answer;
	bool nextIsQuestion = 0;
	bool nextIsAnswer = 0;

	while(getline(infile,line)){
		const string s = line;	

		if(nextIsQuestion){	
			q.setup(line,currentChapter);
			//cout << "Question " << line << endl;
			nextIsQuestion = 0;
			nextIsAnswer = 1;
			continue;
		}
		if(regex_search(s.begin(), s.end(), match, c)){
			//cout << "Current Chapter " << match[1] << endl;
			currentChapter = stoi(match[1]);
			Chapters.push_back(currentChapter);
		}
		if(regex_search(s.begin(), s.end(), match, n)){
			currentQuestion = stoi(match[1]);	
			//cout << "Current question number is " << currentQuestion << endl;
			nextIsQuestion = 1;
		}
		//match correct answer
		if(regex_search(s.begin(), s.end(), match, a)){
			answer = stoi(match[1]);
			//cout << "Current answer is " << answer << endl;
			q.addCorrect(answer);
			nextIsAnswer = 0;
			questions.push_back(q);
		}
		if(nextIsAnswer){
			//cout << "Answer " << line << endl;
			q.addAns(line);
		}
	}// end while loop

	//cout << "vector has " << questions.size() << endl;
}

