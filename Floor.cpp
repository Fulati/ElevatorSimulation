// Identification Comments Code Block
// Programmer: Fulati Aizihaer
// Programmer's ID: 1716403

#include "Floor.h"
#include "Rider.h"
#include "Panel.h"
#include "Building.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <climits>

//variables
const char* const Floor::UP = "Up";
const char* const Floor::DOWN = "Down";
int Floor::TOP = INT_MIN; // defined in climits
int Floor::BOTTOM = INT_MAX; // also in climits

//Floor constructor
Floor::Floor(const int elevation, const char* const name, const char* const label) :elevation(elevation), name(name), label(label) {
	panel.addButton(UP);
	panel.addButton(DOWN);
	if (TOP < elevation) TOP = elevation;
	if (elevation < BOTTOM) BOTTOM = elevation;
}

//ostream operator
ostream& operator<<(ostream& out, const Floor& floor) {
	out.width(3);
	out << floor.label;
	out.width(15);
	out << floor.name << " at ";
	out.width(5);
	out << floor.elevation << "\" Up/Down:";
	out.width(4);
	out << floor.upRiders.size() << "/" << floor.downRiders.size();
	out.width(13);
	out << "Button:  " << floor.panel;
	return out;
}

//addRider function
void Floor::addRider(const Rider& r) {
	if (r.goingUp) {
		upRiders.push(r);
		panel.press(UP);
	}
	if (r.goingDown) {
		downRiders.push(r);
		panel.press(DOWN);
	}
}

//removeUpRider function
Rider Floor::removeUpRider() {
	if (upRiders.empty()) {
		throw "Up Rider empty!";
	}
	Rider rd = upRiders.front();
	upRiders.pop();
	return rd;
}

//removeDownRider function
Rider Floor::removeDownRider() {
	if (downRiders.empty()) {
		throw "Down Rider empty!";
	}
	Rider rd = downRiders.front();
	downRiders.pop();
	return rd;
}