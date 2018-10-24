#include<string>
#include<vector>
using namespace std;

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

class Bank {
    public:
	vector <Question> questions;
	vector <int> Chapters;

	
    Bank();
	int takeQuestion(int c, int n);
	void printChapters();
	bool validChapter(int c);
};

