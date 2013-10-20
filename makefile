Library.out: Main.o Library.o Member.o Asset.o Book.o Periodical.o Date.o 
	g++ -g -o Library.out Main.o Library.o Member.o Asset.o Book.o Periodical.o Date.o 

Main.o: Main.cpp Library.h Member.h Asset.h Book.h Periodical.h Date.h 
	g++ -g -c Main.cpp 

Library.o: Library.cpp Library.h 
	g++ -g -c Library.cpp  

Member.o: Member.cpp Member.h Library.h
	g++ -g -c Member.cpp 

Asset.o: Asset.cpp Asset.h Library.h
	g++ -g -c Asset.cpp 

Book.o: Book.cpp Book.h Asset.h
	g++ -g -c Book.cpp 

Periodical.o: Periodical.cpp Periodical.h Asset.h
	g++ -g -c Periodical.cpp 

Date.o: Date.cpp Date.h
	g++ -g -c Date.cpp

clean:
	rm *.o*

test: 	Main.o Library.o Member.o Asset.o Book.o Periodical.o Date.o 	
	g++ -g -o Library.out Main.o Library.o Member.o Asset.o Book.o Periodical.o Date.o 	
	./Library.out 
