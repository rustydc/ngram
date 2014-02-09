typedef struct Ngram Ngram;
typedef struct Plugin Plugin;
typedef struct Range Range;

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

struct Range {
  Plugin plugin;
  Plugin **plugins;
};

void plugin_init(Plugin *this, unsigned char *data, unsigned int size);

void ngram_init(Ngram *this, unsigned char *data, unsigned int size, int n);
void ngram_set_start(Plugin *this, int start);
void ngram_set_width(Plugin *this, int width);

void range_init(Range *this, unsigned char *data, unsigned int size, Plugin **plugins);
void range_set_start(Plugin *this, int start);
void range_set_width(Plugin *this, int width);

void print(Ngram *this);
