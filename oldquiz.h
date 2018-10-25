using namespace std;


class quizholder {

	int question_number;
	int id;

	public:
	
		vector <int> Chapters;
		quizholder(int tid, int qnum);	
		void addChapter(int tmp){ Chapters.push_back(tmp);}

		int getID(){return id;}
		int getQnumber(){return question_number;}
		vector <int> getChapters(){return Chapters;}
};


class oldquiz {

	int highestID;

	public:
	vector <quizholder> quizholders;	

	oldquiz();
	void highID(int tid){ highestID=tid; }
	int getNextID(){ return (highestID+1); }
	void printQuizes();
	// old quizes are just an integer array of chapters and number of questions	
	void saveQuiz(int c[], int total_chapters, int questions_to_take);
	bool doesQuizExist(int c[], int total_chapters, int questions_to_take);
};


