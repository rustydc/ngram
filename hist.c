#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "hist.h"

static void addByte(Hist *this, int n);
static void removeByte(Hist *this, int n);
static void resetMax(Hist *this);

Hist *new(unsigned char *data, unsigned int size) {
  Hist *this = malloc(sizeof(Hist)); 
  this->data = data;
  this->size = size;
  return this;
}

void setStart(Hist *this, int n) {
  assert(n > 0 && n <= this->size);
  while (n > this->start) {
    removeByte(this, this->start);
    this->start++;
  }
  while (n < this->start) {
    this->start--;
    addByte(this, this->start);
  }
  assert(this->start <= this->end);
}

void setEnd(Hist *this, int n) {
  assert(n > 0 && n <= this->size);
  while (n > this->end) {
    addByte(this, this->end);
    this->end++;
  }
  while (n < this->end) {
    this->end--;
    removeByte(this, this->end);
  }
  assert(this->start <= this->end);
}

void print(Hist *this) {
  int i;
  for (i = 0; i < 256; i++) {
    if (i > 0 && i % 16 == 0) {
      putchar('\n');
    }
    printf("%2d ", this->histogram[i]);
  }

  printf("\nMax: %2d", this->max);
}

static void addByte(Hist *this, int n) {
  unsigned char value = this->data[n];
  if (this->histogram[value] == this->max) {
    this->max++;
  }
  this->histogram[value]++;
}

static void removeByte(Hist *this, int n) {
  unsigned char value = this->data[n];
  this->histogram[value]--;
  if (this->histogram[value] == this->max - 1) {
    resetMax(this);
  }
}
  
static void resetMax(Hist *this) {
  int i;
  this->max = 0;
  for (i = 0; i < 256; i++) {
    if (this->max < this->histogram[i]) {
      this->max = this->histogram[i];
    }
  }
}
