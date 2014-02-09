#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ngram.h"

static void add_ngram(Ngram *this, int n);
static void remove_ngram(Ngram *this, int n);

void plugin_init(Plugin *this, unsigned char *data, unsigned int size);
void ngram_init(Ngram *this, unsigned char *data, unsigned int size, int n);
void ngram_set_start(Plugin *this, int start);
void ngram_set_width(Plugin *this, int width);
void print(Ngram *this);

void plugin_init(Plugin *this, unsigned char *data, unsigned int size) {
  this->data = data;
  this->size = size;
  this->start = 0;
  this->width = 0;
}

void ngram_init(Ngram *this, unsigned char *data, unsigned int size, int n) {
  plugin_init(&(this->plugin), data, size);
  this->plugin.set_start = &ngram_set_start;
  this->plugin.set_width = &ngram_set_width;
  this->n = n;
  this->ngrams = malloc(sizeof(unsigned int) * (1 << (8 * n)));
}

void ngram_destroy(Ngram *this) {
  free(this->ngrams);
}

void ngram_set_start(Plugin *this, int start) {
  int n = ((Ngram *)this)->n;
  assert(start > 0 && start + this->width <= this->size);

  if (this->width < n) {
    this->start = start;
    return;
  }

  // Always adds one and removes one.
  while (start > this->start) {
    remove_ngram((Ngram *)this, this->start);
    add_ngram((Ngram *)this, this->start + this->width - n); // TODO: check off by one.
    this->start++;
  }
  while (start < this->start) {
    add_ngram((Ngram *)this, this->start);
    remove_ngram((Ngram *)this, this->start + this->width - n);
    this->start--;
  }
}

void ngram_set_width(Plugin *this, int width) {
  int n = ((Ngram *)this)->n;
  assert(width > 0 && this->start + width <= this->size);

  // Increasing width; no n-grams yet.
  while (width > this->width && this->width < n) {
    this->width++;
  }
  while (width > this->width) {
    add_ngram((Ngram *)this, this->start + this->width - n);
    this->width++;
  }

  // Decreasing width.
  while (width < this->width && n <= this->width) {
    this->width--;
    remove_ngram((Ngram *)this, this->start + this->width - n);
    this->width--;
  }
  if (width < this->width) {
    this->width = width;
  }
}

void offsetToHex(Ngram *this, int offset, char *str) {
  if (this->n == 1) {
    sprintf(str, "0x%02x(%c)", offset, offset);
  } else if (this->n == 2) {
    sprintf(str, "0x%02x%02x(%c%c)", offset / 256, offset % 256, offset / 256, offset % 256);
  } else if (this->n == 3) {
    sprintf(str, "0x%02x%02x%02x(%c%c%c)",
        offset / 65336, (offset / 256) % 256, offset % 256,
        offset / 65336, (offset / 256) % 256, offset % 256);
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
    offset = (offset << 8) + ((Plugin *)this)->data[n++];
  }
  return offset;
}

static void add_ngram(Ngram *this, int n) {
  this->ngrams[getOffset(this, n)]++;
}

static void remove_ngram(Ngram *this, int n) {
  this->ngrams[getOffset(this, n)]--;
}


void range_init(Range *this, unsigned char *data, unsigned int size, Plugin **plugins) {
  plugin_init(&(this->plugin), data, size);
  this->plugin.set_start = &range_set_start;
  this->plugin.set_width = &range_set_width;
  this->plugins = plugins;
}

void range_set_start(Plugin *this, int start) {
  int i;
  Plugin **plugins = ((Range *)this)->plugins;
  for (i = 0; plugins[i] != NULL; i++) {
    plugins[i]->set_start(plugins[i], start);
  }
}

void range_set_width(Plugin *this, int width) {
  int i;
  Plugin **plugins = ((Range *)this)->plugins;
  for (i = 0; plugins[i] != NULL; i++) {
    plugins[i]->set_width(plugins[i], width);
  }
}
