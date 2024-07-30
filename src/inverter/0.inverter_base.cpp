#include "0.inverter_base.h"


InverterBase::InverterBase(short invno) : invno(invno) {}

bool InverterBase::isValidRecvPacket(unsigned char* recvBuffer, int length){
    if (!checkCRC(&(recvBuffer[length - 2]), calCRC(recvBuffer, length - 2))) return false;
    return true;
}

unsigned char* InverterBase::makeModbusSendPacket(int func, int start, int count){
    unsigned char* packet = new unsigned char[8];
    packet[0] = invno;
    packet[1] = func;
    packet[2] = start / 0x100;
    packet[3] = start % 0x100;
    packet[4] = count / 0x100;
    packet[5] = count % 0x100;
    unsigned int crc = calCRC(packet, 6);
    packet[6] = crc % 0x100;
    packet[7] = crc / 0x100;

    return packet;
}

void InverterBase::clearBaseValue(bool totalReset){
    this->dcv = 0;
	this->dca = 0;
	this->dckw = 0;
	this->acar = 0;
	this->acas = 0;
	this->acat = 0;
	this->acvr = 0;
	this->acvs = 0;
	this->acvt = 0;
	this->ackw = 0;
	this->pf = 0;
	this->freq = 0;
	this->fault[0] = 0;
	this->fault[1] = 0;
	this->fault[2] = 0;
	this->fault[3] = 0;
    if(totalReset){
        this->dayTotal = 0;
        this->total = 0;
    }
}

void InverterBase::clearDayTotal(){
    this->dayTotal = 0;
}

vector<unsigned char*> InverterBase::getSendPacketList(){
    return this->sendPacketList;
}

bool InverterBase::getRecvOk(){
    return this->recvOk;
}

void InverterBase::setRecvOk(bool recvOk){
    this->recvOk = recvOk;
}

int InverterBase::getBaudRate(){
    return this->baudRate;
}

void InverterBase::setBaudRate(int baudRate){
    this->baudRate = baudRate;
}

short InverterBase::getModel(){
    return this->model;
}

void InverterBase::setModel(short num){
    this->model = num;
}

bool InverterBase::getValid(){
    return this->valid;
}
void InverterBase::setValid(bool valid){
    this->valid = valid;
}

int InverterBase::getSerializeLength(){
    return this->serializeLength;
}

void InverterBase::setSerializeLength(int length){
    this->serializeLength = length;
}

int InverterBase::getPacketLength(){
    return this->packetLength;
}