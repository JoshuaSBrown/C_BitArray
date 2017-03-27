#include <stdio.h>
#include <stdlib.h>

#include "BitArray.h"

// The number of bits in a single byte
#define BITS_BYTE 8

struct _BitArray{
  int size;
  char array[];
};

BitArray newBitArray(int size){
  if(size<1) {printf("ERROR BitArray must be larger than 0\n"); return NULL;}

  // Determine how many bytes are in a char
  int bits = sizof(char)*BITS_BYTE;
  int num_chars = size/bits;

  // Malloc memory for bit array
  BitArray bit_array = malloc(sizeof(struct _BitArray)+sizeof(char)*num_chars);
  // If malloc return NULL then there is not enough space in the heap
  if(bit_array==NULL){
    printf("ERROR bit_array malloc returned NULL");
    return NULL
  }

  bit_array->size = size;
  return bit_array;
}

int deleteBitArray(BitArray bit_array){

  if(bit_array==NULL){printf("ERROR BitArray is NULL cannot free\n"); return -1;}
  free(bit_array);
  return 0;
}

int setElemBitArray(BitArray bit_array, int elem){

  if(bit_array==NULL){
    printf("ERROR bit_array is NULL cannot setElemBitArray\n");
    return -1;
  }
  if(elem>=bit_array->size || elem<0){
    printf("ERROR cannot access elem %d out side of the scope of the bit_array"
           " bit_array is of size %d\n",elem,bit_array->size);
    return -1;
  }

  /* Determine which elem in the int array corresponds to elem, integer       *
   * division will automatically round down which is what we want.            */
  int char_elem = elem/(sizeof(char)*BITS_BYTE);
  // We also need to know which bit, thus we will also calculate the modulus
  int char_bit = elem%(sizeof(char)*BITS_BYTE);

  switch(char_bit){
    case 0:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) | 1;
      break;
    case 1:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) | (1<<1);
      break;
    case 2:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) | (1<<2);
      break;
    case 3:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) | (1<<3);
      break;
    case 4:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) | (1<<4);
      break;
    case 5:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) | (1<<5);
      break;
    case 6:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) | (1<<6);
      break;
    case 7:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) | (1<<7);
      break;
  }
  return 0;
}

int unsetElemBitArray(BitArray bit_array, int elem){

  if(bit_array==NULL){
    printf("ERROR bit_array is NULL cannot unsetElemBitArray\n");
    return -1;
  }
  if(elem>=bit_array->size || elem<0){
    printf("ERROR cannot access elem %d out side of the scope of the bit_array"
           " bit_array is of size %d\n",elem,bit_array->size);
    return -1;
  }

  /* Determine which elem in the int array corresponds to elem, integer       *
   * division will automatically round down which is what we want.            */
  int char_elem = elem/(sizeof(int)*BITS_BYTE);
  // We also need to know which bit, thus we will also calculate the modulus
  int char_bit = elem%(sizeof(int)*BITS_BYTE);

  switch(char_bit){
    case 0:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) ^ 1;
      break;
    case 1:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) ^ (1<<1);
      break;
    case 2:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) ^ (1<<2);
      break;
    case 3:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) ^ (1<<3);
      break;
    case 4:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) ^ (1<<4);
      break;
    case 5:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) ^ (1<<5);
      break;
    case 6:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) ^ (1<<6);
      break;
    case 7:
      bit_array->array[char_elem] = (bit_array->array[char_elem]) ^ (1<<7);
      break;
  }
  return 0;
}

int getElemBitArray(BitArray bit_array, int elem){

  if(bit_array==NULL){
    printf("ERROR bit_array is NULL cannot getElemBitArray\n");
    return -1;
  }
  if(elem>=bit_array->size || elem<0){
    printf("ERROR cannot access elem %d out side of the scope of the bit_array"
           " bit_array is of size %d\n",elem,bit_array->size);
    return -1;
  }

  /* Determine which elem in the int array corresponds to elem, integer       *
   * division will automatically round down which is what we want.            */
  int char_elem = elem/(sizeof(int)*BITS_BYTE);
  // We also need to know which bit, thus we will also calculate the modulus
  int char_bit = elem%(sizeof(int)*BITS_BYTE);

  switch(char_bit){
    case 0:
      return (bit_array->array[char_elem]) | 1;
      break;
    case 1:
      return ((bit_array->array[char_elem]) | (1<<1))>>1;
      break;
    case 2:
      return ((bit_array->array[char_elem]) | (1<<2))>>2;
      break;
    case 3:
      return ((bit_array->array[char_elem]) | (1<<3))>>3;
      break;
    case 4:
      return ((bit_array->array[char_elem]) | (1<<4))>>4;
      break;
    case 5:
      return ((bit_array->array[char_elem]) | (1<<5))>>5;
      break;
    case 6:
      return ((bit_array->array[char_elem]) | (1<<6))>>6;
      break;
    case 7:
      return ((bit_array->array[char_elem]) | (1<<7))>>7;
      break;
  }
  printf("ERROR it appears that char is larger than a single byte on your "
         "architecture.\n")
  return -1;
}
