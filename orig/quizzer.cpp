#include<string> 
#include<iostream> 
#include<vector> 
#include<fstream> 
#include<regex> 
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;


/// g++ -std=c++0x quizzer.cpp -o quiz

class Question {
	int correct;
	vector <string> answers;
	string question;
	int cNum;

	public:
		bool check(int ua) {if(ua==correct) return 1; return 0;}
		void setup(string tmpquestion, int c){ 
			question = tmpquestion; 
			cNum = c; 
			answers.clear();}
		void addAns(string tmpans){ answers.push_back(tmpans);}
		void addCorrect(int tc){correct = tc;}
		string retQuestion(){return question;} 
		int retChapter(){return cNum;} 
		void printAnswers();	
};

void Question::printAnswers(){

	for(int i=0; i<answers.size(); i++){
		int k = i+1;
		cout << k << ". " << answers[i] << endl; 
	}
	cout << endl;
}

class Bank {
	vector <Question> questions;
	vector <int> Chapters;

	public:
    Bank();
	int* takeQuestion(int c, int n);
	void printChapters();
	bool validChapter(int c);
};

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

int* Bank::takeQuestion(int c, int n){

	int j=0;
	bool finished = 0;
	int* results = new int[2];
	results[0] = 0;	
	results[1] = 0;	

	for(int i=0; i<questions.size(); i++){

		if(j>=n){
			continue;
		}

		if(questions[i].retChapter() == c){
			j++;

			cout << questions[i].retQuestion() << endl << endl;
			questions[i].printAnswers();

			results[0]++;
			results[1]++;


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
	regex c("^CHAPTER ([0-9])");
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


int main () {

  int total_questions=0;
  int correct_questions = 0;
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
		Chapters.push_back(atoi(tmp.c_str()));
		cout << tmp << " added" << endl;
	}

	cout << "tmp is: " << tmp << endl;
  } while (tmp != "e");	

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

  for(int i=0; i<Chapters.size(); i++){
  	mainbank.takeQuestion(Chapters[i],questions_to_take);
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
