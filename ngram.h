typedef struct Ngram Ngram;
typedef struct Plugin Plugin;

struct Plugin {
  void (*set_start)(struct Plugin *this, int start);
  void (*set_width)(struct Plugin *this, int width);
  int start;
  int width;
  int size;
  unsigned char *data;
};

struct Ngram {
  Plugin plugin;
  int n;
  unsigned int *ngrams;
};

void plugin_init(Plugin *this, unsigned char *data, unsigned int size);
void ngram_init(Ngram *this, unsigned char *data, unsigned int size, int n);
void ngram_set_start(Plugin *this, int start);
void ngram_set_width(Plugin *this, int width);
void print(Ngram *this);
