#include<string> 
#include<iostream> 
#include<vector> 
#include<fstream> 
#include<regex> 
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_set>
#include "oldquiz.h"
using namespace std;

quizholder::quizholder(int tid, int qnum){
	id = tid;
	question_number = qnum;
}


oldquiz::oldquiz(){

	ifstream infile;
	infile.open("oldquiz.txt");
	string line;
	while(getline(infile, line))
   	{
        vector<int>   lineData;
        stringstream  lineStream(line);

		int value;
      	while(lineStream >> value)
   	 	{
       		     lineData.push_back(value);
        }	

		int id = lineData.back();
		lineData.pop_back();
		int q = lineData.back();
		lineData.pop_back();

		//create a quizholder and populate it, and push to a quizholders vector
		quizholder Quiz(id,q);
		highestID = id;	

		for(int i=0; i<lineData.size(); i++){
			Quiz.addChapter(lineData[i]);
		}
		quizholders.push_back(Quiz);	
	}

};


void oldquiz::saveQuiz(int c[], int total_chapters, int questions_to_take){

	if(doesQuizExist(c, total_chapters, questions_to_take)){
		cout << "This quiz format already exists as a saved format.\n";
	}else{
		//cout << "need to write quiz to file \n";

		ofstream outfile;
		outfile.open("oldquiz.txt",ios::app);
	
		string output;
	
		stringstream ss;
		for(int i=0; i<total_chapters; i++){
			ss << c[i];
			output += ss.str();
			output += ' ';
			ss.str("");
		}	
		ss << questions_to_take;
		output += ss.str();
		output += ' ';
		ss.str("");

		highestID++;
		ss << highestID;
		output += ss.str();

		outfile << output << endl;
		outfile.close();
	}
	
}

bool oldquiz::doesQuizExist(int c[], int total_chapters, int questions_to_take){

		for(int i=0; i<quizholders.size(); i++){
			if(quizholders[i].getQnumber() == questions_to_take){
				if(quizholders[i].Chapters.size() == total_chapters){
					bool test = 1;

					for(int j=0; j<total_chapters; j++){
						if(quizholders[i].Chapters[j] != c[j]){
							//cout << quizholders[i].Chapters[j] << " not equal to " << c[j] << endl;
							test = 0;
						}
					if(!test){continue;}
					}
					if(test){
						return 1;
					}
				}
			}
		}
	return 0;
}

void oldquiz::printQuizes(){
		cout << "Quiz ID\t\tQuestions\tChapters" << endl;

		for(int i=0; i<quizholders.size(); i++){
				cout << quizholders[i].getID() << "\t\t" << quizholders[i].getQnumber() << "\t\t";
				for(int j=0; j<quizholders[i].Chapters.size();j++){
					cout << quizholders[i].Chapters[j] << " ";
				}
				cout << "\n";
		}
		cout << "\n\n";
	}
    

