#include "0.inverter_base.h"


InverterBase::InverterBase(short invno) : invno(invno) {}

bool InverterBase::isValidRecvPacket(unsigned char* recvBuffer, int length){
    if (recvBuffer[0] != this->invno) return false;
    if (length != recvBuffer[2] + 5) return false;
    if (!checkCRC(&(recvBuffer[length - 2]), calCRC(recvBuffer, length - 2))) return false;
    return true;
}

unsigned char* InverterBase::makeSendPacket(int func, int start, int length){
    unsigned char* packet = new unsigned char[8];
    memset(packet, 0, 8);
    packet[0] = invno;
    packet[1] = func;
    packet[2] = start / 0x100;
    packet[3] = start % 0x100;
    packet[4] = length / 0x100;
    packet[5] = length % 0x100;
    unsigned int crc = calCRC(packet, 6);
    packet[6] = crc % 0x100;
    packet[7] = crc / 0x100;

    return packet;
}

void InverterBase::clearBaseValue(){
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

void InverterBase::setModel(short num){
    this->model = num;
}