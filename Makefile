main.out: main.cpp ellipse.cpp ellipse.h
	g++ main.cpp ellipse.cpp -o main.out -lsfml-graphics -lsfml-window -lsfml-system
