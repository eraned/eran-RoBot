Prog: main.o Game.o Map.o Robot.o
	g++ main.o Game.o Map.o Robot.o -o Prog

main.o: main.cpp Game.h Robot.h Map.h
	g++ -c main.cpp

Game.o: Game.cpp Game.h Robot.h Map.h
	g++ -c Game.cpp

Map.o: Map.cpp Map.h
	g++ -c Map.cpp

Robot.o: Robot.cpp Robot.h
	g++ -c Robot.cpp

clean: rm -r *.o
