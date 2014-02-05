#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ngram.h"

static void addNgram(Ngram *this, int n);
static void removeNgram(Ngram *this, int n);

Ngram *new(unsigned char *data, unsigned int size, int n) {
  Ngram *this = malloc(sizeof(Ngram)); 
  this->data = data;
  this->size = size;
  this->n = n;
  this->ngrams = malloc(sizeof(unsigned int) * (1 << (8 * n)));
  return this;
}

void setStart(Ngram *this, int n) {
  assert(n > 0 && n <= this->size);

  // Increasing start.
  while (n > this->start && this->start + this->n <= this->end) {
    removeNgram(this, this->start);
    this->start++;
  }
  while (n > this->start) {
    this->start++;
  }

  // Decreasing start, no n-grams yet.
  while (n < this->start && this->start + this->n > this->end) {
    this->start--;
  }
  while (n < this->start) {
    this->start--;
    addNgram(this, this->start);
  }

  assert(this->start <= this->end);
}

void setEnd(Ngram *this, int n) {
  assert(n > 0 && n <= this->size);

  // Increasing end; no n-grams yet.
  while (n > this->end && this->start + this->n >= this->end) {
    this->end++;
  }
  while (n > this->end) {
    addNgram(this, this->end);
    this->end++;
  }

  // Decreasing end.
  while (n < this->end && this->start + this->n <= this->end) {
    this->end--;
    removeNgram(this, this->end);
  }
  while (n < this->end) {
    this->end--;
  }

  assert(this->start <= this->end);
}

void offsetToHex(Ngram *this, int offset, char *str) {
  if (this->n == 1) {
    sprintf(str, "0x%02x(%c)", offset, offset);
  } else if (this->n == 2) {
    sprintf(str, "0x%02x%02x(%c%c)", offset / 256, offset % 256, offset / 256, offset % 256);
  } else if (this->n == 3) {
    sprintf(str, "0x%02x%02x%02x(%c%c%c)", offset / 65336, (offset / 256) % 256, offset % 256, offset / 65336, (offset / 256) % 256, offset % 256);
  }
}; 

void print(Ngram *this) {
  int i;
  char hex[16];
  for (i = 0; i < 1 << (8 * this->n); i++) {
    if (this->ngrams[i] > 10) {
      offsetToHex(this, i, hex);
      printf("%s: %d\n", hex, this->ngrams[i]);
    }
  }
}

static int getOffset(Ngram *this, int n) {
  int i;
  int offset = 0;
  for (i = 0; i < this->n; i++) {
    offset = (offset << 8) + this->data[n++];
  }
  return offset;
}

static void addNgram(Ngram *this, int n) {
  this->ngrams[getOffset(this, n)]++;
}

static void removeNgram(Ngram *this, int n) {
  this->ngrams[getOffset(this, n)]--;
}
