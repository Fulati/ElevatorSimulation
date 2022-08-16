#include "Elevator.h"
#include "Panel.h"
#include "Building.h"

#include <iostream>
#include <vector>
using namespace std;

#include <cstdlib>

//Elevator constructor
Elevator::Elevator(unsigned int capacity, int speed, int start) :speed(speed), CAPACITY(capacity), location(Building::floors[start]) {
  direction = IDLE;
  timer = 0;
  atFloorIndex = -1;

  for (unsigned int i = 0; i < Building::FLOORS; i++) {
    panel.addButton(Building::floors[i].label);
  }
}

//ostream operator
ostream& operator<<(ostream& out, const Elevator& e) {
  out << "Elevator at";
  out.width(6);
  out << e.location;
  out.width(12);
  if (e.direction == 1) {
    out << "going UP";
  }
  else if (e.direction == -1) {
    out << "going DOWN";
  }
  else {
    out << "IDLE";
  }
  out.width(3);
  out << e.riders.size() << " riders ";
  if (e.atFloorIndex >= 0) {
    out << "door is OPEN|" << e.timer;
  }

  out << " " << e.panel;

  return out;
}

//openDoorTo function
void Elevator::openDoorTo(int i) {
  panel.clear(Building::floors[i].label);
  atFloorIndex = i;
  resetTimer();
}

//board function
void Elevator::board(const Rider& r) {
  riders.push_back(r);
  panel.press(Building::floors[r.to].label);
  if (r.goingUp) {
    direction = UP;
  }
  else {
    direction = DOWN;
  }
  resetTimer();
}

//hasRiderForFloor function
bool Elevator::hasRiderForFloor() const {
  if (atFloorIndex == -1) {
    return false;
  }
  for (unsigned int i = 0; i < riders.size(); i++) {
    if (riders[i].to == atFloorIndex) {
      return true;
    }
  }
  return false;
}

//removeRider function
void Elevator::removeRider() {
  for (unsigned int i = 0; i < riders.size(); i++) {
    if (riders[i].to == atFloorIndex) {
      panel.clear(Building::floors[riders[i].to].label);
      riders.erase(riders.begin() + i);
      resetTimer();
      break;
    }
  }
}

//Isidle function
bool Elevator::isIdle() const {
  return direction == 0;
}

//closedoor function
bool Elevator::closeDoor() {
  if (atFloorIndex == -1) {
    return false;
  }
  else {
    if (goingUp() && !Building::floors[atFloorIndex].hasUpRider()) {
      Building::floors[atFloorIndex].panel.clear(Building::floors[atFloorIndex].UP);
    }
    if (goingDown() && !Building::floors[atFloorIndex].hasDownRider()) {
      Building::floors[atFloorIndex].panel.clear(Building::floors[atFloorIndex].DOWN);
    }
    atFloorIndex = -1;
  }
  return true;
}

//move function
bool Elevator::move()
{
  //Up elevator
  if (direction == UP) {
    for (int i = 0; i < Building::FLOORS; i++) {
      if (Building::floors[i].elevation <= location || ((location + speed) < Building::floors[i].elevation)) {
        continue;
      }
      if (Building::floors[i].panel.isLit(Floor::UP) || panel.isLit(Building::floors[i].label)) {
        if (location != Building::floors[i].elevation) {
          location = Building::floors[i].elevation;
          openDoorTo(i);
          return true;
        }
      }
    }
    if (location == Building::floors[Building::FLOORS - 1].elevation) {
      return false;
    }
    else {
      location = location + speed;
      return true;
    }
  }

  //Down elevator
  if (direction == DOWN) {
    for (int i = 0; i < Building::FLOORS; i++) {
      if (Building::floors[i].elevation >= location || ((location - speed) > Building::floors[i].elevation)) {
        continue;
      }
      if (Building::floors[i].panel.isLit(Floor::DOWN) || panel.isLit(Building::floors[i].label)) {
        if (location != Building::floors[i].elevation){
          location = Building::floors[i].elevation;
          openDoorTo(i);
          return true;
        }
      }
    }

    if (location == Building::floors[0].elevation) {
      return false;
    }
    else {
      location = location - speed;
      return true;
    }
  }
  return false;
}
