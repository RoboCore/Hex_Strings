#ifndef RC_HEX_STRINGS
#define RC_HEX_STRINGS

/*
	RoboCore Hex_Strings Library
		(v1.2 - 26/02/2013)

  Library to manipulate Hex values with strings
    (tested only in Arduino 1.0.1)

  Released under the Beerware licence


  IMPORTANT: ALWAYS initialize the Byte Array BEFORE using it

  NOTE: the library uses malloc() to create Byte Arrays and
        the Pointer List in <Memory.h> is usedby default .
        To use regular malloc(), undefine USE_POINTER_LIST
        in <Memory.h>
  
*/

//NOTE: good results weren't obtained using 'realloc', so the code
//        is written using 'malloc'.


#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h> //for Arduino 1.0 or later
#else
#include <WProgram.h> //for Arduino 22
#endif

#include <Memory.h>
#include <String_Functions.h>


//#define RC_HEX_DEBUG


//--------------------------------------

//ByteArray structure
//	# array of bytes using a pointer
//  !!! careful when manipulating, ALWAYS update both length and ptr
//  !!! ALWAYS initialize the Byte Array BEFORE using it
typedef struct {
  byte *ptr;
  int length;
} ByteArray;

//-------------------------------------------------------------------------------------------------

// Convert an ASCII byte to a hex byte
//    ex: byte=3 >> 0x30 = '3'
//    Note: if char='3' -> use (byte)'3' to obtain 0x30
byte ASCIIByteToHexByte(byte c);

//-------------------------------------------------------------------------------------------------

// Convert a ByteArray into a string
//    ex: {65, 65} >> "AA"
char* ByteArrayToString(ByteArray* barray_ptr);

//-------------------------------------------------------------------------------------------------

// Convert a ByteArray into a Hex string
//    ex: {65, 65} >> "4141"
char* ByteArrayToHexString(ByteArray* barray_ptr);

//-------------------------------------------------------------------------------------------------

// Convert to ASCII char from a byte
//    ex: 0x41 >> 'A'
//    ex:   65 >> 'A'
char ByteToASCIIChar(byte b);

//-------------------------------------------------------------------------------------------------

// Convert to Hex char from a byte
//    ex: 0x41 >> '41'
//    ex:   65 >> '41'
char* ByteToHexChar(byte b);

//-------------------------------------------------------------------------------------------------

// Display a Byte Array
void DisplayByteArray(HardwareSerial* serial, ByteArray* barray_ptr);
void DisplayByteArray(HardwareSerial* serial, ByteArray* barray_ptr, boolean display_values);

//-------------------------------------------------------------------------------------------------

// Free the memory used by ByteArray
void FreeByteArray(ByteArray* barray_ptr);

//-------------------------------------------------------------------------------------------------

// Convert to ASCII char from a Hex char[2]
//    ex: "41" >> 'A'
char HexCharToASCIIChar(char* HexChar);

//-------------------------------------------------------------------------------------------------

// Convert to byte from a Hex char[2]
//    ex: "41" >> 65
//    NOTE: the byte is the DEC format. To have it in HEX, just use
//              the HEX format option when printing
byte HexCharToByte(char* HexChar);

//-------------------------------------------------------------------------------------------------

// Convert to an array of byte from a Hex string
//    ex: "4141" >> {65, 65}
//    NOTE: cannot return an array
void HexStringToByteArray(char* HexString, ByteArray *barray_ptr);

//-------------------------------------------------------------------------------------------------

// Initializes the values in Byte Array (NULL and 0)
//    NOTE: ALWAYS initialize Byte Array before using it!
void InitializeByteArray(ByteArray* barray_ptr);

//-------------------------------------------------------------------------------------------------

// Joins ByteArray 2 at the end of ByteArray1
//    NOTE: ByteArray 1 must exist
boolean JoinByteArray(ByteArray* ba1, ByteArray* ba2);

//-------------------------------------------------------------------------------------------------

// Resize ByteArray
boolean ResizeByteArray(ByteArray* barray_ptr, int new_length);

//-------------------------------------------------------------------------------------------------

// Convert to an array of byte from a string
//    ex: "AA" >> {65, 65}
//    NOTE: cannot return an array
void StringToByteArray(char* string, ByteArray* barray_ptr);

//-------------------------------------------------------------------------------------------------



#endif
