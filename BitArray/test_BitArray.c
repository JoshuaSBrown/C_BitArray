#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "BitArray.h"

int main(void){

  printf("Beginning Test of BitArray Library\n");
  
  printf("Testing internal functions\n");
  int rv = test_BitArrayInternal();
  assert(rv==0);

  printf("Testing newBitArray\n");
  BitArray BitA = newBitArray(0);
  assert(BitA==NULL);
  BitA = newBitArray(1);
  assert(BitA!=NULL);

  printf("Testing deleteBitArray\n");
  rv = deleteBitArray(NULL);
  assert(rv==-1);
  rv = deleteBitArray(BitA);
  assert(rv==0);

  return 0;
}
