typedef struct ngram_s {
  int start;
  int end;
  unsigned char *data;
  unsigned int size;
  int n;
  unsigned int *ngrams;
} Ngram;

Ngram *new(unsigned char *data, unsigned int size, int n);
void setStart(Ngram *this, int n);
void setEnd(Ngram *this, int n);
void print(Ngram *this);
