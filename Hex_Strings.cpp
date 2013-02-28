
/*
	RoboCore Hex_Strings Library
		(v1.2 - 26/02/2013)

  Library to manipulate Hex values with strings
    (tested with Arduino 0022 and 1.0.1)

  Released under the Beerware licence


  IMPORTANT: ALWAYS initialize the Byte Array BEFORE using it

  NOTE: the library uses malloc() to create Byte Arrays and
        the Pointer List in <Memory.h> is usedby default .
        To use regular malloc(), undefine USE_POINTER_LIST
        in <Memory.h>
  
*/

//NOTE: good results weren't obtained using 'realloc', so the code
//        is written using 'malloc'.


#include "Hex_Strings.h"



//-------------------------------------------------------------------------------------------------

// Convert an ASCII byte to a hex byte
//    ex: byte=3 >> 0x30 = '3'
//    Note: if char='3' -> use (byte)'3' to obtain 0x30
byte ASCIIByteToHexByte(byte c){
  byte res;
  switch(c){
    case 0: res = 0x30; break;
    case 1: res = 0x31; break;
    case 2: res = 0x32; break;
    case 3: res = 0x33; break;
    case 4: res = 0x34; break;
    case 5: res = 0x35; break;
    case 6: res = 0x36; break;
    case 7: res = 0x37; break;
    case 8: res = 0x38; break;
    case 9: res = 0x39; break;
    
    case 10: res = 0x41; break; // A
    case 11: res = 0x42; break; // B
    case 12: res = 0x43; break; // C
    case 13: res = 0x44; break; // D
    case 14: res = 0x45; break; // E
    case 15: res = 0x46; break; // F
    
    default: res = 0x23; // #
  }
  return res;
}

//-------------------------------------------------------------------------------------------------

// Convert a ByteArray into a string
//    ex: {65, 65} >> "AA"
char* ByteArrayToString(ByteArray* barray_ptr){
  //allocate
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  char* string = (char*)Mmalloc((barray_ptr->length + 1) * sizeof(char));
#else
  char* string = (char*)malloc((barray_ptr->length + 1) * sizeof(char));
#endif

  if(string == NULL){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in ByteArrayToString: cannot allocate memory!");
#endif
    return NULL;
  }
  
  string[barray_ptr->length] = '\0'; //insert End Of String
  for(int i=0 ; i < barray_ptr->length ; i++)
    string[i] = (char)barray_ptr->ptr[i];
  
  return string;
}

//-------------------------------------------------------------------------------------------------

// Convert a ByteArray into a Hex string
//    ex: {65, 65} >> "4141"
char* ByteArrayToHexString(ByteArray* barray_ptr){
  //allocate
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  char* string = (char*)Mmalloc((barray_ptr->length * 2 + 1) * sizeof(char));
#else
  char* string = (char*)malloc((barray_ptr->length * 2 + 1) * sizeof(char));
#endif

  if(string == NULL){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in ByteArrayToHexString: cannot allocate memory!");
#endif
    return NULL;
  }
  
  byte msb, lsb;
  int index = 0;
  
  string[barray_ptr->length * 2] = '\0'; //insert End Of String
  for(int i=0 ; i < (barray_ptr->length) ; i++){
    msb = (barray_ptr->ptr[i] >> 4);
    lsb = (barray_ptr->ptr[i] & 0x0F);
    
    if(msb <= 9)
      string[index] = msb + 48;
    else
      string[index] = msb - 10 + 65;
    
    if(lsb <= 9)
      string[index+1] = lsb + 48;
    else
      string[index+1] = lsb - 10 + 65;
      
    index += 2;
  }
  
  return string;
}

//-------------------------------------------------------------------------------------------------

// Convert to ASCII char from a byte
//    ex: 0x41 >> 'A'
//    ex:   65 >> 'A'
char ByteToASCIIChar(byte b){
  byte msb = (b >> 4);
  byte lsb = (b & 0x0F);
  return (char)(msb * 16 + lsb);
}

//-------------------------------------------------------------------------------------------------

// Convert to Hex char from a byte
//    ex: 0x41 >> '41'
//    ex:   65 >> '41'
char* ByteToHexChar(byte b){
  byte msb = (b >> 4);
  byte lsb = (b & 0x0F);

  //allocate
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  char* res = (char*)Mmalloc(3 * sizeof(char));
#else
  char* res = (char*)malloc(3 * sizeof(char));
#endif

  if(res == NULL){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in ByteToHexChar: cannot allocate memory!");
#endif
    return NULL;
  }
  
  res[2] = '\0'; //null termination of strings
  if(msb <= 9)
    res[0] = msb + 48;
  else
    res[0] = msb - 10 + 65;
  
  if(lsb <= 9)
    res[1] = lsb + 48;
  else
    res[1] = lsb - 10 + 65;
  
  return res;
}

//-------------------------------------------------------------------------------------------------

// Display a Byte Array
void DisplayByteArray(HardwareSerial* serial, ByteArray* barray_ptr){
  serial->print("> ptr: ");
  serial->print((int)barray_ptr->ptr, HEX);
  serial->print("\n> length: ");
  serial->println(barray_ptr->length);
  serial->println();
}


// Display a Byte Array and its values
void DisplayByteArray(HardwareSerial* serial, ByteArray* barray_ptr, boolean display_values){
  serial->print("> ptr: ");
  serial->print((int)barray_ptr->ptr, HEX);
  serial->print("\n> length: ");
  serial->println(barray_ptr->length);
  if(display_values && (barray_ptr->length > 0)){
    for(int i=0 ; i < barray_ptr->length ; i++){
      serial->print("\t.");
      serial->println((int)barray_ptr->ptr[i]);
    }
  }
  serial->println();
}

//-------------------------------------------------------------------------------------------------

// Free the memory used by ByteArray
void FreeByteArray(ByteArray* barray_ptr){
#ifdef USE_POINTER_LIST
  Mfree(barray_ptr->ptr); //free memory
#else
  free(barray_ptr->ptr); //free memory
#endif

  barray_ptr->ptr = NULL; //point to null
  barray_ptr->length = 0; //reset length
}

//-------------------------------------------------------------------------------------------------

// Convert to ASCII char from a Hex char[2]
//    ex: "41" >> 'A'
char HexCharToASCIIChar(char* HexChar){
  byte res;
  
  //check if valid string
  if(StrLength(HexChar) != 2){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in HexCharToASCIIChar: invalid string length! (must be of 2 characters)");
#endif
    return 0;
  }

  //Most Significant Bits
  if(((byte)HexChar[0] >= 48) && ((byte)HexChar[0] <= 57)) //0-9
    res = (((byte)HexChar[0] - 48) << 4);
  else if(((byte)HexChar[0] >= 65) && ((byte)HexChar[0] <= 70)) //A-F
    res = (((byte)HexChar[0] - 65 + 10) << 4);
  else if(((byte)HexChar[0] >= 97) && ((byte)HexChar[0] <= 102)) //a-f
    res = (((byte)HexChar[0] - 102 + 10) << 4);
  else
    return 0;

  //Less Significant Bits    
  if(((byte)HexChar[1] >= 48) && ((byte)HexChar[1] <= 57)) //0-9
    res |= ((byte)HexChar[1] - 48);
  else if(((byte)HexChar[1] >= 65) && ((byte)HexChar[1] <= 70)) //A-F
    res |= ((byte)HexChar[1] - 65 + 10);
  else if(((byte)HexChar[1] >= 97) && ((byte)HexChar[1] <= 102)) //a-f
    res |= ((byte)HexChar[1] - 102 + 10);
  else
    return 0;

  return (char)res;
}

//-------------------------------------------------------------------------------------------------

// Convert to byte from a Hex char[2]
//    ex: "41" >> 65
//    NOTE: the byte is the DEC format. To have it in HEX, just use
//              the HEX format option when printing
byte HexCharToByte(char* HexChar){
  byte res;
  
  //check if valid string
  if(StrLength(HexChar) != 2){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in HexCharToByte: invalid string length! (must be of 2 characters)");
#endif
    return 0;
  }

  //Most Significant Bits
  if(((byte)HexChar[0] >= 48) && ((byte)HexChar[0] <= 57)) //0-9
    res = (((byte)HexChar[0] - 48) << 4);
  else if(((byte)HexChar[0] >= 65) && ((byte)HexChar[0] <= 70)) //A-F
    res = (((byte)HexChar[0] - 65 + 10) << 4);
  else if(((byte)HexChar[0] >= 97) && ((byte)HexChar[0] <= 102)) //a-f
    res = (((byte)HexChar[0] - 102 + 10) << 4);
  else
    return 0;

  //Less Significant Bits    
  if(((byte)HexChar[1] >= 48) && ((byte)HexChar[1] <= 57)) //0-9
    res |= ((byte)HexChar[1] - 48);
  else if(((byte)HexChar[1] >= 65) && ((byte)HexChar[1] <= 70)) //A-F
    res |= ((byte)HexChar[1] - 65 + 10);
  else if(((byte)HexChar[1] >= 97) && ((byte)HexChar[1] <= 102)) //a-f
    res |= ((byte)HexChar[1] - 102 + 10);
  else
    return 0;

  return res;
}

//-------------------------------------------------------------------------------------------------

// Convert to an array of byte from a Hex string
//    ex: "4141" >> {65, 65}
//    NOTE: cannot return an array
void HexStringToByteArray(char* HexString, ByteArray* barray_ptr){
  int length = StrLength(HexString);

  //check if empty string
  if(length == 0){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in HexStringToByteArray: empty string!");
#endif
    return;
  }

  //check if pair number of chars
  if(length % 2 != 0){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in HexStringToByteArray: number of chars isn't pair!");
#endif
    return;
  }

  if(!ResizeByteArray(barray_ptr, length / 2)){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in HexStringToByteArray: couldn't resize the array!");
#endif
    return;
  }
  
  int index = 0;
//  char* str = "--"; //see Note below
  for(int i=0 ; i < length - 1 ; i=i+2){
//    str[0] = HexString[i]; //see Note below
//    str[1] = HexString[i+1]; //see Note below
//    barray_ptr->ptr[index] = HexCharToByte(str); //see Note below

  //NOTE: use code below (extracted from HexCharToByte() because it is
              //stabler than calling HexCharToByte() each time
              //(too much memory consuming)
  
    //Most Significant Bits
    if(((byte)HexString[i] >= 48) && ((byte)HexString[i] <= 57)) //0-9
      barray_ptr->ptr[index] = (((byte)HexString[i] - 48) << 4);
    else if(((byte)HexString[i] >= 65) && ((byte)HexString[i] <= 70)) //A-F
      barray_ptr->ptr[index] = (((byte)HexString[i] - 65 + 10) << 4);
    else if(((byte)HexString[i] >= 97) && ((byte)HexString[i] <= 102)) //a-f
      barray_ptr->ptr[index] = (((byte)HexString[i] - 102 + 10) << 4);
    else
      barray_ptr->ptr[index] = 0;
  
    //Less Significant Bits    
    if(((byte)HexString[i+1] >= 48) && ((byte)HexString[i+1] <= 57)) //0-9
      barray_ptr->ptr[index] |= ((byte)HexString[i+1] - 48);
    else if(((byte)HexString[i+1] >= 65) && ((byte)HexString[i+1] <= 70)) //A-F
      barray_ptr->ptr[index] |= ((byte)HexString[i+1] - 65 + 10);
    else if(((byte)HexString[i+1] >= 97) && ((byte)HexString[i+1] <= 102)) //a-f
      barray_ptr->ptr[index] |= ((byte)HexString[i+1] - 102 + 10);
    else
      barray_ptr->ptr[index] = 0;
    
    index++;
  }
}

//-------------------------------------------------------------------------------------------------

// Initializes the values in Byte Array (NULL and 0)
//    NOTE: ALWAYS initialize Byte Array before using it!
void InitializeByteArray(ByteArray* barray_ptr){
  barray_ptr->ptr = NULL;
  barray_ptr->length = 0;
}

//-------------------------------------------------------------------------------------------------

// Joins ByteArray 2 at the end of ByteArray1
//    NOTE: ByteArray 1 must exist
boolean JoinByteArray(ByteArray* ba1_ptr, ByteArray* ba2_ptr){
  if(ba1_ptr->length <= 0)
    return false;
  
  if(ba2_ptr->length <= 0)
    return true;
  
  //allocate memory
  byte *ptr;
  int new_length = ba1_ptr->length + ba2_ptr->length;
//  ptr = (byte*)realloc(ba1_ptr->ptr, new_length * sizeof(byte));
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  ptr = (byte*)Mmalloc(new_length * sizeof(byte));
#else
  ptr = (byte*)malloc(new_length * sizeof(byte));
#endif

  if(ptr == NULL){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in JoinByteArray: cannot allocate memory!");
#endif
    return false;
  }
  
  //store values
  for(int i=0 ; i < ba1_ptr->length ; i++)
    ptr[i] = ba1_ptr->ptr[i];
  for(int i=0 ; i < ba2_ptr->length ; i++)
    ptr[ba1_ptr->length+i] = ba2_ptr->ptr[i];
  
  //update pointer
  FreeByteArray(ba1_ptr);
  ba1_ptr->ptr = ptr;
  ba1_ptr->length = new_length;
  ptr = NULL;
  
  return true;
}

//-------------------------------------------------------------------------------------------------

// Resize ByteArray
boolean ResizeByteArray(ByteArray* barray_ptr, int new_length){
  //allocate memory
  byte *ptr;
#ifdef USE_POINTER_LIST
  PointerList::Initialize();
  ptr = (byte*)Mmalloc(new_length * sizeof(byte));
#else
  ptr = (byte*)malloc(new_length * sizeof(byte));
#endif

  if(ptr == NULL){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in ResizeByteArray: cannot allocate memory!");
#endif
    return false;
  }
  
  //copy the values
  for(int i=0 ; i < barray_ptr->length ; i++){
    ptr[i] = barray_ptr->ptr[i];
  }
  //fill with '0'
  for(int i=barray_ptr->length ; i < new_length ; i++){
    ptr[i] = 0;
  }
  
  //update values
  FreeByteArray(barray_ptr); //free the previous memory block
  barray_ptr->ptr = ptr;
  barray_ptr->length = new_length;
  ptr = NULL;

  return true;
}


//previous version of the function, using 'realloc'
        //(might not be finished)
//boolean ResizeByteArray(ByteArray* barray_ptr, int new_length){
//  //reallocate memory
//  byte *ptr;
//  ptr = (byte*)realloc(barray_ptr->ptr, new_length * sizeof(byte));
//  if(ptr == NULL){
//#ifdef RC_HEX_DEBUG
////    Serial.println("ERROR in ResizeByteArray: cannot allocate memory!");
//#endif
//    return false;
//  }
//  
//  //fill with '0'
////  for(int i=barray_ptr->length ; i < new_length ; i++){
////    barray_ptr->ptr[i] = 0;
////  }
//  
//  //update values
//  barray_ptr->length = new_length;
////  if(ptr != barray_ptr->ptr)
//    barray_ptr->ptr = ptr;
////  ptr = NULL;
//
// return true;
//}

//-------------------------------------------------------------------------------------------------

// Convert to an array of byte from a string
//    ex: "AA" >> {65, 65}
//    NOTE: cannot return an array
void StringToByteArray(char* string, ByteArray *barray_ptr){
  int length = StrLength(string);

  //check if empty string
  if(length == 0){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in StringToByteArray: empty string!");
#endif
    return;
  }
  
  if(!ResizeByteArray(barray_ptr, length)){
#ifdef RC_HEX_DEBUG
    Serial.println("ERROR in StringToByteArray: couldn't resize the array!");
#endif
    return;
  }

  for(int i=0 ; i < length ; i++){
    barray_ptr->ptr[i] = (byte)string[i];
  }
}

//-------------------------------------------------------------------------------------------------









