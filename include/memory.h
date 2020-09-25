
int availableMemory(uint16_t min, uint16_t max) {
  if (min==max-1)
    return min;

  int size=max;
  int lastSize=size;
  byte *buf;
  while ((buf = (byte *) malloc(size)) == NULL)
  {
    lastSize=size;
    size-=(max-min)/2;
  };

  free(buf);
  return availableMemory(size,lastSize);
};