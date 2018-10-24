all: quiz

quiz: quiz.o
	g++ -std=c++0x quizzer.cpp bank.cpp -o quiz	
	
clean:
	\rm *.o quiz

    
