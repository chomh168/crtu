#ifndef UTIL_H_
#define UTIL_H_


unsigned int calcCRC(unsigned char bArray[], unsigned int bCnt);
bool checkCRC(unsigned char recvCRC[], unsigned int calcCRC);
short ucharToShort(unsigned char* recvBuffer, bool reverse=false);
unsigned int ucharToUint(unsigned char* recvBuffer, bool reverse=false);
void shortToUcharArray(short value, unsigned char* array, short offset = 0);

#endif /* UTIL_H_ */