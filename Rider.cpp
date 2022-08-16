// Identification Comments Code Block
// Programmer: Fulati Aizihaer
// Programmer's ID: 1716403

#include "Rider.h"
#include "Building.h"

//C++ Libraries
#include <iostream>
using namespace std;

//Rider Constructor
Rider::Rider(int start, int destination)
	:from(start), to(destination), goingDown((Building::floors[from] > Building::floors[to]) ? true : false), goingUp((Building::floors[to] > Building::floors[from]) ? true : false) {}

//Rider Assignment Operator
Rider& Rider::operator=(const Rider& copyThis) {
	Rider& host = *this;
	if (this != &copyThis) {
		const_cast<int&>(host.to) = copyThis.to;
		const_cast<int&>(host.from) = copyThis.from;
		const_cast<bool&>(host.goingUp) = copyThis.goingUp;
		const_cast<bool&>(host.goingDown) = copyThis.goingDown;
	}
	return host;
}