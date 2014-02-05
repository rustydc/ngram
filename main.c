#include <stdio.h>
#include <string.h>
#include "ngram.h"

int main(int argc, char **argv) {
  char data[] = "We have been up all night, my friends and I, beneath mosque lamps whose brass cupolas are bright as our souls, because like them they were illuminated by the internal glow of electric hearts. And trampling underfoot our native sloth on opulent Persian carpets, we have been discussing right up to the limits of logic and scrawling the paper with demented writing. Our hearts were filled with an immense pride at feeling ourselves standing quite alone, like lighthouses or like the sentinels in an outpost, facing the army of enemy stars encamped in their celestial bivouacs. Alone with the engineers in the infernal stokeholes of great ships, alone with the black spirits which rage in the belly of rogue locomotives, alone with the drunkards beating their wings against the walls. Then we were suddenly distracted by the rumbling of huge double decker trams that went leaping by, streaked with light like the villages celebrating their festivals, which the Po in flood suddenly knocks down and uproots, and, in the rapids and eddies of a deluge, drags down to the sea. Then the silence increased. As we listened to the last faint prayer of the old canal and the crumbling of the bones of the moribund palaces with their green growth of beard, suddenly the hungry automobiles roared beneath our windows.";

  Ngram *n1 = new((unsigned char *) data, strlen(data), 1);
  setEnd(n1, strlen(data));
  print(n1);

  Ngram *n2 = new((unsigned char *) data, strlen(data), 2);
  setEnd(n2, strlen(data));
  print(n2);

  Ngram *n3 = new((unsigned char *) data, strlen(data), 3);
  setEnd(n3, strlen(data));
  print(n3);
  return 0;
}
