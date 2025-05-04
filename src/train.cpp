// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (first) {
    Car* current = first->next;
    while (current != first) {
      Car* temp = current;
      current = current->next;
      delete temp;
    }
    delete first;
  }
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (!first) return 0;
  if (first->next == first) return 1;
  countOp = 0;
  Car* current = first;
  current->light = true;
  countOp++;
  while (true) {
    current = current->next;
    countOp++;
    if (current->light) {
      current->light = false;
      int stepsBack = 0;
      while (stepsBack < countOp) {
        current = current->prev;
        stepsBack++;
        countOp++;
      }
      if (!current->light) {
        return countOp / 2;
      }
      while (stepsBack > 0) {
        current = current->next;
        stepsBack--;
        countOp++;
      }
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
