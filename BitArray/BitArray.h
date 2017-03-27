
typedef struct * _BitArray BitArray;

/* Creates a BitArray object by mallocing memory. Return value is given:      *
 * NULL    - indicates either size is less than 1                             *
 *           or that there was not room in the heap                           *
 * NonNULL - indicates that the pointer to the bit array was returned         */
BitArray newBitArray(int size);

/* Deletes a BitArray object by calling free. Return value is given:          *
 * -1 - indicates that bit_array was NULL and thus nothing was done           *
 *  0 - indicates success and the memory was freed                            */
int deleteBitArray(BitArray bit_array);

/* Sets the value of the bit located at position indicated by elem to 1.      *
 * Return value is given:                                                     *
 * -1 - indicates that the bit_array was NULL                                 *
 *      or that the position indicated by elem was outside the scope of the   *
 *      memory malloced to the array                                          *
 *  0 - indicates success                                                     */
int setElemBitArray(BitArray bit_array, int elem);

/* Unsets the value of the bit located at position indicated by elem to 0.    *
 * Return value is given:                                                     *
 * -1 - indicates that the bit_array was NULL                                 *
 *      or that the position indicated by elem was outside the scope of the   *
 *      memory malloced to the array                                          *
 *  0 - indicates success                                                     */
int unsetElemBitArray(BitArray bit_array, int elem);

/* Finds the value of the bit located at position indicated by elem           *
 * Return value is given:                                                     *
 * -1 - indicates that the bit_array was NULL                                 *
 *      or that the position indicated by elem was outside the scope of the   *
 *      memory malloced to the array                                          *
 *      or that the char on the gven architecture is larger than a byte and   *
 *      thus will not work with this library                                  *
 *  1 - indicates success and that the bit is set to 1                        *
 *  0 - indicates success and that the bit is set to 0                        */
int getElemBitArray(BitArray bit_array, int elem);
