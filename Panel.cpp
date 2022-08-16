#include "Panel.h"

//C++ Libraries
#include <iostream>
using namespace std;

//count variable
int Panel::Button::count = 0;

//addButton function
void Panel::addButton(string label) {
	Button b;
	b.label = label;
	b.lit = false;
	Panel::buttons.push_back(b);
}

//press function
void Panel::press(string label) {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].label == label) {
			if (!buttons[i].lit) {
				buttons[i].lit = true;
				buttons[i].sequence == ++Button::count;
			}
		}
	}
}

//clear function
void Panel::clear(string label) {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].label == label) {
			buttons[i].lit = false;
		}
	}
}

//getFirstList function
string Panel::getFirstLit() const {
	int least = Button::count;
	int j = 0;

	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].lit && buttons[i].sequence < least) {
			least = buttons[i].sequence;
			j = i;
		}
	}
	return buttons[j].label;
}

//isList function
bool Panel::isLit(string label) const {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].label == label) {
			return buttons[i].lit;
		}
	}
	return false;
}

//areAnyLit function
bool Panel::areAnyLit() const {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].lit) {
			return true;
		}
	}
	return false;
}

//ostream& operator 
ostream& operator<<(ostream& out, const Panel& panel) {
	for (unsigned int i = 0; i < panel.buttons.size(); i++) {
		if (panel.buttons[i].lit) {
			out << '[' << panel.buttons[i].label << ']';
		}
	}
	return out;
}

