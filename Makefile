all: compile

compile:
	g++ -std=c++20 gg.cpp -o gg

clean:
	rm gg
