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
  countOp = 0;
  Car* current = first;
  int n = 0;
  do {
    current = current->next;
    ++n;
  } while (current != first);
  bool orig = first->light;
  countOp = 0;
  for (int i = 0; i < n + (orig ? 1 : 1); ++i) {
    first->light = !first->light;
    Car* p = first;
    do {
      p = p->next;
      ++countOp;
    } while (p->light != first->light);
  }
  first->light = orig;
  return n;
}

int Train::getOpCount() {
  return countOp;
}
