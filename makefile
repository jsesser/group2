all: quizzer

quiz: quizzer.o
	g++ -std=c++0x quizzer.cpp bank.cpp -o quiz	
	
clean:
	\rm *.o quiz

    
