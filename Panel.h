// Identification Comments Code Block
// Programmer: Fulati Aizihaer
// Programmer's ID: 1716403

#ifndef Panel_h
#define Panel_h

//C++ Libraries
#include <iostream>
#include <vector>
using namespace std;

//Panel Class
class Panel {

	//Button Struct inside the Panel Class
	struct Button {
		string label;
		bool lit;
		int sequence;
		static int count;
	};
	vector<Button> buttons;

public:
	void addButton(string);
	void press(string);
	void clear(string);
	string getFirstLit() const;
	bool isLit(string) const;
	bool areAnyLit() const;
	friend ostream& operator<<(ostream&, const Panel&);
};

#endif