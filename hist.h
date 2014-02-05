typedef struct hist_s {
  int start;
  int end;
  unsigned int max;
  unsigned int size;
  unsigned int histogram[256];
  unsigned char *data;
} Hist;

Hist *new(unsigned char *data, unsigned int size);
void setStart(Hist *this, int n);
void setEnd(Hist *this, int n);
void print(Hist *this);
