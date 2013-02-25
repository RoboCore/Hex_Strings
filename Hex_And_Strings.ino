
#include "String_Functions.h"
#include "Hex_Strings.h"
#include <Memory.h>

//-------------------------------------------------------------------------------------------------

//extern int __heap_start;


void setup(){
  Serial.begin(9600);
}



void loop(){
//  Serial.println((int)&__heap_start, HEX);
  Serial.print("<Memory> ");
  if(UsingMemory())
    Serial.println("OK");
  else
    Serial.println("no");
  AvailableMemory(&Serial, true);
  Serial.println();
  
  
  
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  

  ByteArray ba1;
  InitializeByteArray(&ba1);
  DisplayByteArray(&Serial, &ba1, true);
  
  ResizeByteArray(&ba1, 2);
  DisplayByteArray(&Serial, &ba1, true);

  ResizeByteArray(&ba1, 2);
    ba1.ptr[0] = 13;
    ba1.ptr[1] = 89;
  DisplayByteArray(&Serial, &ba1, true);
  
  ResizeByteArray(&ba1, 2);
  DisplayByteArray(&Serial, &ba1, true);
  
  HexStringToByteArray("41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF41FF", &ba1);
  DisplayByteArray(&Serial, &ba1, true);

  Serial.println("\n1***"); //*************************************
  AvailableMemory(&Serial, true);
  Serial.println("freeing");
  FreeByteArray(&ba1);
  ResizeByteArray(&ba1, 2);
  DisplayByteArray(&Serial, &ba1, true);
  
  ResizeByteArray(&ba1, 2);
  DisplayByteArray(&Serial, &ba1, true);
  
  FreeByteArray(&ba1);
  DisplayByteArray(&Serial, &ba1, true);
  ResizeByteArray(&ba1, 2);
  DisplayByteArray(&Serial, &ba1, true);

  Serial.println("\n1.5***"); //*************************************
  AvailableMemory(&Serial, true);
  Serial.println("joining");
  ResizeByteArray(&ba1, 2);
    ba1.ptr[0] = 13;
    ba1.ptr[1] = 89;
  DisplayByteArray(&Serial, &ba1, true);
  ByteArray ba2;
  InitializeByteArray(&ba2);
  ResizeByteArray(&ba2, 2);
    ba2.ptr[0] = 11;
    ba2.ptr[1] = 66;
  DisplayByteArray(&Serial, &ba2, true);
  
  JoinByteArray(&ba1, &ba2);
  DisplayByteArray(&Serial, &ba1, true);
  
  FreeByteArray(&ba1);
  ResizeByteArray(&ba1, 2);
  DisplayByteArray(&Serial, &ba1, true);

  FreeByteArray(&ba1);
  ResizeByteArray(&ba1, 2);
  DisplayByteArray(&Serial, &ba1, true);

  Serial.println("\n2***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  Serial.println(0x41);
  Serial.println(0x41, HEX);
  Serial.println((char)0x41);
  
  Serial.println("\n3***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);

  Serial.println(ByteToHexChar(65));
  Serial.println(ByteToHexChar(0xFF));
  Serial.println(ByteToASCIIChar(0x41));
  Serial.println(ByteToASCIIChar(65));
  Serial.println(HexCharToASCIIChar("41"));
  Serial.println(HexCharToByte("41"));
  Serial.println(StrLength(ByteToHexChar(0xFF))); //ok

  
  Serial.println("\n4***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  ByteArray barray;
  InitializeByteArray(&barray);
  HexStringToByteArray("4141FF", &barray);
  DisplayByteArray(&Serial, &barray, true);

  Serial.println("\n5***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);

  Serial.println(StrLength("12345"));

  Serial.println("\n6***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  StringToByteArray("AAF9", &barray);
  DisplayByteArray(&Serial, &barray, true);
  char* string = ByteArrayToString(&barray);
  Serial.println(string);
  string = ByteArrayToHexString(&barray);
  Serial.println(string);

  Serial.println("\n7***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  char* lala = "A";
  char* ooo = "BC";
  Serial.println(StrConcat(lala, ooo));

  Serial.println("\n8***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  Serial.println("joining");
//  ByteArray barray;
  
  StringToByteArray("AA", &barray);
  StringToByteArray("FF", &ba2);
  DisplayByteArray(&Serial, &barray, true);
  DisplayByteArray(&Serial, &ba2, true);
  HexStringToByteArray("4141FF", &barray); //-------------------------------------------------
  HexStringToByteArray("41FFFF", &barray); //-------------------------------------------------
  HexStringToByteArray("4141FF", &barray); //-------------------------------------------------
  HexStringToByteArray("41FFFF", &barray); //-------------------------------------------------
  HexStringToByteArray("4141FF", &barray); //-------------------------------------------------
  HexStringToByteArray("41FFFF", &barray); //-------------------------------------------------
  HexStringToByteArray("4141FF", &barray); //-------------------------------------------------
  HexStringToByteArray("41FFFF", &barray); //-------------------------------------------------
  HexStringToByteArray("4141FF", &barray); //-------------------------------------------------
  HexStringToByteArray("41FFFF", &barray); //-------------------------------------------------
  HexStringToByteArray("4141FF", &barray); //-------------------------------------------------
  HexStringToByteArray("41FFFF", &barray); //-------------------------------------------------
  
  HexStringToByteArray("4141FF", &ba2); //-------------------------------------------------
  HexStringToByteArray("FF41FF", &ba2); //-------------------------------------------------
  HexStringToByteArray("4141FF", &ba2); //-------------------------------------------------
  HexStringToByteArray("FF41FF", &ba2); //-------------------------------------------------
  HexStringToByteArray("4141FF", &ba2); //-------------------------------------------------
  HexStringToByteArray("FF41FF", &ba2); //-------------------------------------------------
  HexStringToByteArray("4141FF", &ba2); //-------------------------------------------------
  HexStringToByteArray("FF41FF", &ba2); //-------------------------------------------------
  DisplayByteArray(&Serial, &barray, true);
  DisplayByteArray(&Serial, &ba2, true);
  
  JoinByteArray(&barray, &ba2);
  DisplayByteArray(&Serial, &barray, true);
  JoinByteArray(&barray, &barray);
  DisplayByteArray(&Serial, &barray, true);

  Serial.println("\n9***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  byte b;
  for(int i=0 ; i <= 16 ; i++){
    Serial.print(i);
    Serial.print(" >> ");
    b = ASCIIByteToHexByte(i);
    Serial.print(b);
    Serial.print(" | ");
    Serial.println((char)b);
  }

  Serial.println("\n10***"); //*************************************
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  Serial.println("--- FIM ---");
  FreeByteArray(&barray);
  FreeByteArray(&ba2);
  
  Serial.print("count: "); Serial.println(PointerList::ListCount());
  PointerList::DisplayList(&Serial);
  Serial.println("boom");
  MReset();
  PointerList::DisplayList(&Serial);
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  while(1){
    delay(100);
  }
}






