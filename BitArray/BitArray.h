/******************************************************************************
 * Created: 27 March 2017                                                     *
 * Author:  Joshua S Brown                                                    *
 *                                                                            *
 * Purpose: This library was designed to enable easy manipulation of an array *
 *          of bits.                                                          *
 *                                                                            *
 * Conventions:                                                               *
 *  size -            Used to refer to the total size of the array in bits.   *
 *  elem -            Used to refer to an element in the bit array.           *
 ******************************************************************************/
#ifndef _BITARRAY_H_
#define _BITARRAY_H_

typedef unsigned char byte;

struct _BitArray{
  int size;
  byte * array;
};

typedef struct _BitArray * BitArray;

/* Creator                                                                    */
/* Creates a BitArray object by mallocing memory. Return value is given:      *
 * NULL    - indicates either size is less than 1                             *
 *           or that there was not room in the heap                           *
 * NonNULL - indicates that the pointer to the bit array was returned         */
BitArray newBitArray(int size);

/* Destructor                                                                 */
/* Deletes a BitArray object by calling free. Return value is given:          *
 * -1 - indicates that bit_array was NULL and thus nothing was done           *
 *  0 - indicates success and the memory was freed                            */
int deleteBitArray(BitArray * bit_array);

/* Displayer                                                                  */
/* Prints the contents of the bit array in 1s and 0s return value is given:   *
 * -1 - indcates failure a result of a NULL bit_array                         *
 *  0 - indicates success                                                     */
int printBitArray(const BitArray bit_array);

/* Setters                                                                    */
/* Sets the value of the bit located at position indicated by elem to 1.      *
 * Return value is given:                                                     *
 * -1 - indicates that the bit_array was NULL                                 *
 *      or that the position indicated by elem was outside the scope of the   *
 *      memory malloced to the array                                          *
 *  0 - indicates success                                                     */
int setElemBitArray(BitArray bit_array, const int elem);

/* Unsets the value of the bit located at position indicated by elem to 0.    *
 * Return value is given:                                                     *
 * -1 - indicates that the bit_array was NULL                                 *
 *      or that the position indicated by elem was outside the scope of the   *
 *      memory malloced to the array                                          *
 *  0 - indicates success                                                     */
int unsetElemBitArray(BitArray bit_array, const int elem);

/* Getters                                                                    */
/* Determines the size of the BitArray in terms of the number of bits, the    *
 * number of bits is passed back through the return value. The return value is*
 * given by:                                                                  *
 * -1  - if there is an error i.e. the bit_array is NULL                      *
 * >-1 - if success a value greater than -1 to indicate the size of the array */
int getSizeBitArray(const BitArray bit_array);

/* Finds the value of the bit located at position indicated by elem           *
 * Return value is given:                                                     *
 * -1 - indicates that the bit_array was NULL                                 *
 *      or that the position indicated by elem was outside the scope of the   *
 *      memory malloced to the array                                          *
 *      or that the char on the gven architecture is larger than a byte and   *
 *      thus will not work with this library                                  *
 *  1 - indicates success and that the bit is set to 1                        *
 *  0 - indicates success and that the bit is set to 0                        */
int getElemBitArray(const BitArray bit_array, const int elem);

/* Testers                                                                    */
/* Designed to test the internal functions of the library that the user does  *
 * not have access to. Will return:                                           *
 *  0 - if success                                                            *
 * -1 - if error and will print error messages                                */
 int test_BitArrayInternal(void);

#endif
