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
static inline int _getElemByte(const int bits){
  return bits/BITS_BYTE;
}

// For a given number of bits determine the number of bytes that are needed
static inline int _getBytes(const int bits){
  return _getElemByte(bits)+1;
}

// For a given bit determine the index of the bit within the closest byte.
static inline int _getBitInd(const int bits){
  return bits%BITS_BYTE;
}

// Given a byte and the index within the byte determine the value of the bit it
// should be either a 1 or a 0, index must be between 0 and 7 inclusive.
static inline unsigned int _getBit(byte byt, const int index){

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

inline static int _getElem(const BitArray bit_array,const int elem_bit){
  /* Determine which byte in the array corresponds to elem_bit                */
  int elem_byte = _getElemByte(elem_bit);
  // We also need to know which bit, thus we will also calculate the modulus
  int index = _getBitInd(elem_bit);
  return _getBit(bit_array->array[elem_byte],index);
}

// Given a byte and the index within the byte set the bit to a value of 1
// index must be between 0 and 7 inclusive.
static inline void _setBit(byte * byt, const int index){
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

inline static void _setElem(BitArray bit_array, const int elem_bit){
  /* Determine which byte in the array corresponds to elem_bit                */
  int elem_byte = _getElemByte(elem_bit);
  // We also need to know which bit, thus we will also calculate the modulus
  int index = _getBitInd(elem_bit);
  _setBit(&(bit_array->array[elem_byte]),index);
}

// Given a byte and the index within the byte set the bit to a value of 0
// index must be between 0 and 7 inclusive.
static inline void _unsetBit(byte * byt, const int index){
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

inline static void _unsetElem(BitArray bit_array, const int elem_bit){
  /* Determine which byte in the array corresponds to elem_bit                */
  int elem_byte = _getElemByte(elem_bit);
  // We also need to know which bit, thus we will also calculate the modulus
  int index = _getBitInd(elem_bit);
  _unsetBit(&(bit_array->array[elem_byte]),index);
}

/******************************************************************************
 * User Library Functions                                                     *
 ******************************************************************************/
/* Creator                                                                    */
BitArray newBitArray(int size){
  if(size<1) {printf("ERROR BitArray must be larger than 0\n"); return NULL;}
  // Determine how many bytes are in the array
  int num_bytes = _getBytes(size);
  // Malloc memory for bit array size and array pointer
  BitArray bit_array = (BitArray) malloc(sizeof(struct _BitArray));
  // If malloc return NULL then there is not enough space in the heap
  if(bit_array==NULL){
    fprintf(stderr,"ERROR bit_array malloc returned NULL\n");
    return NULL;
  }
  // Malloc memory for bit array pointer
  bit_array->array = (byte *) malloc(num_bytes);
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
  printf("Required bytes: %5d\n",_getBytes(bit_array->size));

  printf("Bits\n");
  int BitsPerRow = 80;
  int i=0;
  while(i<bit_array->size){
    if(i%BitsPerRow==0){
      printf("\n");
    }
    printf("%d",_getElem(bit_array,i));
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
  _setElem(bit_array, elem_bit);
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

  _unsetElem(bit_array, elem_bit);
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
  return _getElem(bit_array, elem_bit);
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

  printf("Testing: _getElemByte\n");
  assert(_getElemByte(0)==0);
  assert(_getElemByte(7)==0);
  assert(_getElemByte(8)==1);
  assert(_getElemByte(16)==2);

  printf("Testing: _getBytes\n");
  assert(_getBytes(0)==1);
  assert(_getBytes(7)==1);
  assert(_getBytes(8)==2);
  assert(_getBytes(16)==3);

  printf("Testing: _getBitInd\n");
  assert(_getBitInd(0)==0);
  assert(_getBitInd(1)==1);
  assert(_getBitInd(7)==7);
  assert(_getBitInd(8)==0);
  assert(_getBitInd(9)==1);
  assert(_getBitInd(15)==7);
  assert(_getBitInd(16)==0);

  printf("Testing: _getBit\n");
  byte byt = 0;
  for(int i=0;i<8;i++) assert(_getBit(byt,0)==0);

  byt = 255;
  for(int i=0;i<8;i++) assert(_getBit(byt,i)==1);

  printf("Testing: _getElem\n");
  BitArray bit_array = newBitArray(16);
  assert(bit_array!=NULL);
  for(int i=0;i<16;i++) assert(_getElem(bit_array,i)==0);

  printf("Testing: _setBit\n");
  for(int i=0;i<8;i++) _setBit(&byt,i);
  for(int i=0;i<8;i++) assert(_getBit(byt,i)==1);

  printf("Testing: _setElem\n");
  for(int i=0;i<16;i++) _setElem(bit_array,i);
  for(int i=0;i<16;i++) assert(_getElem(bit_array,i)==1);

  printf("Testing: _unsetBit\n");
  for(int i=0;i<8;i++) _unsetBit(&byt,i);
  for(int i=0;i<8;i++) assert(_getBit(byt,i)==0);

  printf("Testing: _unsetElem\n");
  for(int i=0;i<16;i++) _unsetElem(bit_array,i);
  for(int i=0;i<16;i++) assert(_getElem(bit_array,i)==0);

  deleteBitArray(&bit_array);

  return 0;
}
