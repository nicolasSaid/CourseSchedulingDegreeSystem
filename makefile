all: execp execs execw

execw: waitlist.cpp pr_check.cpp sch_check.cpp priorityQueue.o
	g++ -Wall -Wextra -O3 -g waitlist.cpp priorityQueue.o -o waitlist

priorityQueue.o: priorityQueue.cpp priorityQueue.h
	g++ -Wall -Wextra -O3 -c priorityQueue.cpp -o priorityQueue.o

execs: sch_main.cpp pr_check.cpp sch_check.cpp
	g++ -Wall -Wextra -O3 sch_main.cpp -o sch_check

execp: pr_main.cpp pr_check.cpp
	g++ -Wall -Wextra -O3 pr_main.cpp -o pr_check

clean:
	rm -f *.o *.tar.gz pr_check sch_check waitlist

tar: clean
	tar cvvf CP5_Group8.tar .
	gzip CP5_Group8.tar