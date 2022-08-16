#ifndef Rider_h
#define Rider_h

//C++ Libraries
#include <iostream>
using namespace std;

//Rider struct
struct Rider {
	const int from, to;
	const bool goingUp, goingDown;
	Rider(int, int);
	Rider& operator=(const Rider&);
};

#endif
