#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "BitArray.h"

int main(void){

  printf("Beginning Test of BitArray Library\n");

  printf("Testing: internal functions\n");
  int rv = test_BitArrayInternal();
  assert(rv==0);

  printf("Testing: newBitArray\n");
  BitArray BitA = newBitArray(0);
  assert(BitA==NULL);
  BitA = newBitArray(1);
  assert(BitA!=NULL);

  printf("Testing: deleteBitArray\n");
  rv = deleteBitArray(NULL);
  assert(rv==-1);
  rv = deleteBitArray(&BitA);
  assert(rv==0);
  assert(BitA==NULL);

  printf("Testing: printBitArray\n");
  rv = printBitArray(NULL);
  assert(rv==-1);
  BitA = newBitArray(16);
  assert(BitA!=NULL);
  rv = printBitArray(BitA);
  assert(rv==0);

  printf("Testing: setElemBitArray\n");
  rv = setElemBitArray(NULL,0);
  assert(rv==-1);
  rv = setElemBitArray(BitA,-1);
  assert(rv==-1);
  rv = setElemBitArray(BitA,16);
  assert(rv==-1);
  for(int i=0;i<16;i++) assert(setElemBitArray(BitA,i)==0);
  rv = printBitArray(BitA);

  printf("Testing: unsetElemBitArray\n");
  rv = unsetElemBitArray(NULL,0);
  assert(rv==-1);
  rv = unsetElemBitArray(BitA,-1);
  assert(rv==-1);
  rv = unsetElemBitArray(BitA,16);
  assert(rv==-1);
  for(int i=0;i<16;i++) assert(unsetElemBitArray(BitA,i)==0);
  rv = printBitArray(BitA);

  printf("Testing: getSizeBitArray");
  rv = getSizeBitArray(NULL);
  assert(rv==-1);
  rv = getSizeBitArray(BitA);
  assert(rv==16);

  printf("Testing: getElemBitArray\n");
  rv = getElemBitArray(NULL,0);
  assert(rv==-1);
  rv = getElemBitArray(BitA,-1);
  assert(rv==-1);
  rv = getElemBitArray(BitA,16);
  assert(rv==-1);
  for(int i=0;i<16;i++){
    rv = getElemBitArray(BitA,i);
    assert(rv==0);
  }
  rv = deleteBitArray(&BitA);
  assert(rv==0);
  assert(BitA==NULL);

  return 0;
}
