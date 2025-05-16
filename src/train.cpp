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
  Car* current = first->next;
  int n = 1;
  while (current != first) {
    current = current->next;
    ++n;
  }
  bool orig = first->light;
  countOp = 0;
  int loops = orig ? (n + 1) : 2;
  for (int i = 0; i < loops; ++i) {
    first->light = !first->light;
    const Car* p = first;
    for (int j = 0; j < n; ++j) {
      p = p->next;
      ++countOp;
    }
  }
  first->light = orig;
  return n;
}

int Train::getOpCount() {
  return countOp;
}
