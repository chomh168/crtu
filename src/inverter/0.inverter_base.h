#ifndef INVERTER_BASE_H_
#define INVERTER_BASE_H_


#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>
#include "../util/util.h"

using namespace std;

class InverterBase{
private:
    bool recvOk;
    bool valid;
    int baudRate;
    short model;
    int serializeLength;
protected:
    vector<unsigned char*> sendPacketList;
public:
    short invno;
	short dcv;
	short dca;
	short dckw;
	short acar;
	short acas;
	short acat;
	short acvr;
	short acvs;
	short acvt;
	short ackw;
	short pf;
	short freq;
	unsigned int dayTotal;
	unsigned int total;
	short fault[4];

    InverterBase(short invno);

    virtual void decodePacket(unsigned char* recvBuffer) = 0;
    virtual unsigned char* serialize() = 0;
    virtual void clearValue() = 0;

    bool isValidRecvPacket(unsigned char* recvBuffer, int length);
    unsigned char* makeSendPacket(int func, int start, int length);
    vector<unsigned char*> getSendPacketList();
    void clearBaseValue();
    bool getRecvOk();
    void setRecvOk(bool recvOk);
    int getBaudRate();
    void setBaudRate(int baudRate);
    short getModel();
    void setModel(short num);
    bool getValid();
    void setValid(bool valid);
    int getSerializeLength();
    void setSerializeLength(int length);
};


#endif