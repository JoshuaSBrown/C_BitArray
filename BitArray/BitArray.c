/******************************************************************************
 * Created: 27 March 2017                                                     *
 * Author:  Joshua S Brown                                                    *
 *                                                                            *
 * Purpose: This library was designed to enable easy manipulation of an array *
 *          of bits.                                                          *
 *                                                                            *
 * Conventions:                                                               *
 *  size -            Used to refer to the total size of the array in bits.   *
 *  bits -            Used to refer to an arbitrary number of bits.           *
 *  elem_bit -        Used to refer to the elem in the array corresponding to *
 *                    the bit of interest.                                    *
 *  elem_byte -       Used to refer to the elem in the array corresponding to *
 *                    byte of interest                                        *
 *  index -           Refers to the bit of interest within a given byte should*
 *                    never excede a value of 7 and must not be less than 0   *
 *  num_bytes -       Refers to the total number of bytes in the array.       *
 *                                                                            *
 * File Organization is as follows:                                           *
 *  o Internal Library Functions                                              *
 *  o User Library Functions                                                  *
 *    - Creator                                                               *
 *    - Destructor                                                            *
 *    - Displayer                                                             *
 *    - Setters                                                               *
 *    - Getters                                                               *
 *    - Testers                                                               *
 *                                                                            *
 ******************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BitArray.h"

// The number of bits in a single byte
#define BITS_BYTE 8

/******************************************************************************
 * Internal Library Functions                                                 *
 ******************************************************************************/
// For a given number of bits determine the index of the byte in the array
static inline int getElemByte(const int bits){
  return bits/BITS_BYTE;
}

// For a given number of bits determine the number of bytes that are needed
static inline int getBytes(const int bits){
  return getElemByte(bits)+1;
}

// For a given bit determine the index of the bit within the closest byte.
static inline int getBitInd(const int bits){
  return bits%BITS_BYTE;
}

// Given a byte and the index within the byte determine the value of the bit it
// should be either a 1 or a 0, index must be between 0 and 7 inclusive.
static inline unsigned int getBit(byte byt, const int index){

  switch(index){
    case 0:
      return byt & 0x1;
    case 1:
      return (byt&(0x1<<1))>>1 ;
    case 2:
      return (byt&(0x1<<2))>>2;
    case 3:
      return (byt&(0x1<<3))>>3;
    case 4:
      return (byt&(0x1<<4))>>4;
    case 5:
      return (byt&(0x1<<5))>>5;
    case 6:
      return (byt&(0x1<<6))>>6;
    case 7:
      return (byt&(0x1<<7))>>7;
    default:
      return -1;
  }
}

inline static int getElem(const BitArray bit_array,const int elem_bit){
  /* Determine which byte in the array corresponds to elem_bit                */
  int elem_byte = getElemByte(elem_bit);
  // We also need to know which bit, thus we will also calculate the modulus
  int index = getBitInd(elem_bit);
  return getBit(bit_array->array[elem_byte],index);
}

// Given a byte and the index within the byte set the bit to a value of 1
// index must be between 0 and 7 inclusive.
static inline void setBit(byte * byt, const int index){
  switch(index){
    case 0:
      *byt = *byt | 1;
      break;
    case 1:
      *byt = *byt | (1<<1);
      break;
    case 2:
      *byt = *byt | (1<<2);
      break;
    case 3:
      *byt = *byt | (1<<3);
      break;
    case 4:
      *byt = *byt | (1<<4);
      break;
    case 5:
      *byt = *byt | (1<<5);
      break;
    case 6:
      *byt = *byt | (1<<6);
      break;
    case 7:
      *byt = *byt | (1<<7);
      break;
  }
}

inline static void setElem(BitArray bit_array, const int elem_bit){
  /* Determine which byte in the array corresponds to elem_bit                */
  int elem_byte = getElemByte(elem_bit);
  // We also need to know which bit, thus we will also calculate the modulus
  int index = getBitInd(elem_bit);
  setBit(&(bit_array->array[elem_byte]),index);
}
// Given a byte and the index within the byte set the bit to a value of 0
// index must be between 0 and 7 inclusive.
static inline void unsetBit(byte * byt, const int index){
  switch(index){
    case 0:
      *byt = *byt ^ 1;
      break;
    case 1:
      *byt = *byt ^ (1<<1);
      break;
    case 2:
      *byt = *byt ^ (1<<2);
      break;
    case 3:
      *byt = *byt ^ (1<<3);
      break;
    case 4:
      *byt = *byt ^ (1<<4);
      break;
    case 5:
      *byt = *byt ^ (1<<5);
      break;
    case 6:
      *byt = *byt ^ (1<<6);
      break;
    case 7:
      *byt = *byt ^ (1<<7);
      break;
  }
}

inline static void unsetElem(BitArray bit_array, const int elem_bit){
  /* Determine which byte in the array corresponds to elem_bit                */
  int elem_byte = getElemByte(elem_bit);
  // We also need to know which bit, thus we will also calculate the modulus
  int index = getBitInd(elem_bit);
  unsetBit(&(bit_array->array[elem_byte]),index);
}

/******************************************************************************
 * User Library Functions                                                     *
 ******************************************************************************/
/* Creator                                                                    */
BitArray newBitArray(int size){
  if(size<1) {printf("ERROR BitArray must be larger than 0\n"); return NULL;}
  // Determine how many bytes are in the array
  int num_bytes = getBytes(size);
  // Malloc memory for bit array size and array pointer
  BitArray bit_array = (BitArray) malloc(sizeof(struct _BitArray));
  // If malloc return NULL then there is not enough space in the heap
  if(bit_array==NULL){
    fprintf(stderr,"ERROR bit_array malloc returned NULL\n");
    return NULL;
  }
  // Malloc memory for bit array pointer
  bit_array->array = (byte *) malloc(BITS_BYTE*num_bytes);
  // If malloc returned NULL then there is not enough space in the heap
  if(bit_array->array==NULL){
    fprintf(stderr,"ERROR byte array in bit_array returned NULL when "
                   "malloced\n");
    free(bit_array);
    return NULL;
  }
  bit_array->size = size;
  // Initialize elements of byte array to 0
  for(int elem_byte=0;elem_byte<num_bytes;elem_byte++){
    bit_array->array[elem_byte]=0;
  }
  return bit_array;
}

/* Destructor                                                                 */
int deleteBitArray(BitArray * bit_array){
  if(bit_array==NULL){
    fprintf(stderr,"ERROR *bit_array passed to deleteBitArray is NULL "
                   "cannot free\n");
    return -1;
  }
  if(*bit_array==NULL){
    fprintf(stderr,"ERROR *bit_array passed to deleteBitArray is NULL "
                   "cannot free\n");
    return -1;
  }
  if((*bit_array)->array!=NULL){
    free((*bit_array)->array);
  }
  free((*bit_array));
  *bit_array = NULL;
  return 0;
}

/* Displayer                                                                  */
int printBitArray(const BitArray bit_array){
  if(bit_array==NULL){
      fprintf(stderr,"ERROR bit_array is NULL when passed to printBitArray\n");
      return -1;
  }
  printf("Array size:     %5d\n",bit_array->size);
  printf("Required bytes: %5d\n",getBytes(bit_array->size));

  printf("Bits\n");
  int BitsPerRow = 80;
  int i=0;
  while(i<bit_array->size){
    if(i%BitsPerRow==0){
      printf("\n");
    }
    printf("%d",getElem(bit_array,i));
    i++;
  }
  printf("\n");
  return 0;
}

/* Setters                                                                    */
int setElemBitArray(BitArray bit_array, const int elem_bit){
  if(bit_array==NULL){
    fprintf(stderr,"ERROR bit_array is NULL cannot setElemBitArray\n");
    return -1;
  }
  if(elem_bit>=bit_array->size || elem_bit<0){
    fprintf(stderr,"ERROR cannot access elem %d out side of the scope of the "
                   "bit_array, bit_array is of size %d\n",elem_bit,
                   bit_array->size);
    return -1;
  }
  setElem(bit_array, elem_bit);
  return 0;
}

int unsetElemBitArray(BitArray bit_array, const int elem_bit){
  if(bit_array==NULL){
    printf("ERROR bit_array is NULL cannot unsetElemBitArray\n");
    return -1;
  }
  if(elem_bit>=bit_array->size || elem_bit<0){
    printf("ERROR cannot access elem %d out side of the scope of the bit_array"
           " bit_array is of size %d\n",elem_bit,bit_array->size);
    return -1;
  }

  unsetElem(bit_array, elem_bit);
  return 0;
}

/* Getters                                                                    */
int getSizeBitArray(const BitArray bit_array){
  if(bit_array==NULL){
    fprintf(stderr,"ERROR bit_array is NULL cannot getSizeBitArray\n");
    return -1;
  }
  return bit_array->size;
}

int getElemBitArray(const BitArray bit_array, const int elem_bit){
  if(bit_array==NULL){
    fprintf(stderr,"ERROR bit_array is NULL cannot getElemBitArray\n");
    return -1;
  }
  if(elem_bit>=bit_array->size || elem_bit<0){
    fprintf(stderr,"ERROR cannot access elem %d out side of the scope of the "
                   "bit_array, bit_array is of size %d\n",
                   elem_bit,bit_array->size);
    return -1;
  }
  return getElem(bit_array, elem_bit);
}

/* Testers                                                                    */
// Meant for testing internal functions
int test_BitArrayInternal(void){
  // Ensure that the library will funtion correctly internally
  if(sizeof(char)!=1){
    fprintf(stderr,"ERROR This library was designed assuming that the number of"
                   "bytes in char is 1. However, on this machine it is %ld\n",
                   sizeof(char));
    return -1;
  }

  printf("Testing: getElemByte\n");
  assert(getElemByte(0)==0);
  assert(getElemByte(7)==0);
  assert(getElemByte(8)==1);
  assert(getElemByte(16)==2);

  printf("Testing: getBytes\n");
  assert(getBytes(0)==1);
  assert(getBytes(7)==1);
  assert(getBytes(8)==2);
  assert(getBytes(16)==3);

  printf("Testing: getBitInd\n");
  assert(getBitInd(0)==0);
  assert(getBitInd(1)==1);
  assert(getBitInd(7)==7);
  assert(getBitInd(8)==0);
  assert(getBitInd(9)==1);
  assert(getBitInd(15)==7);
  assert(getBitInd(16)==0);

  printf("Testing: getBit\n");
  byte byt = 0;
  for(int i=0;i<8;i++) assert(getBit(byt,0)==0);

  byt = 255;
  for(int i=0;i<8;i++) assert(getBit(byt,i)==1);

  printf("Testing: getElem\n");
  BitArray bit_array = newBitArray(16);
  assert(bit_array!=NULL);
  for(int i=0;i<16;i++) assert(getElem(bit_array,i)==0);

  printf("Testing: setBit\n");
  for(int i=0;i<8;i++) setBit(&byt,i);
  for(int i=0;i<8;i++) assert(getBit(byt,i)==1);

  printf("Testing: setElem\n");
  for(int i=0;i<16;i++) setElem(bit_array,i);
  for(int i=0;i<16;i++) assert(getElem(bit_array,i)==1);

  printf("Testing: unsetBit\n");
  for(int i=0;i<8;i++) unsetBit(&byt,i);
  for(int i=0;i<8;i++) assert(getBit(byt,i)==0);

  printf("Testing: unsetElem\n");
  for(int i=0;i<16;i++) unsetElem(bit_array,i);
  for(int i=0;i<16;i++) assert(getElem(bit_array,i)==0);

  deleteBitArray(&bit_array);

  return 0;
}
