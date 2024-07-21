#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include <string>
#include <cstring>

using namespace std;

unsigned int calCRC(unsigned char bArray[], unsigned int bCnt);
bool checkCRC(unsigned char recvCRC[], unsigned int calcCRC);
short ucharToShort(unsigned char* recvBuffer, bool reverse=false);
unsigned int ucharToUint(unsigned char* recvBuffer, bool reverse=false);
void shortToUcharArray(short value, unsigned char* array, short offset = 0);
vector<string> split(const char* str, char delimiter);

#endif /* UTIL_H_ */