#include "2.Sungrow.h"


InverterSungrow::InverterSungrow(short invno) : InverterBase(invno) {
    this->setModel(7);
    this->setBaudRate(9600);
    this->setSerializeLength(42);
    this->packetLength = 8;
    this->packetSendLength[0] = 80;
    this->sendPacketList.push_back(this->makeModbusSendPacket(4, 5003 - 1, this->packetSendLength[0]));
    this->packetSendLength[1] = 23;
    this->sendPacketList.push_back(this->makeModbusSendPacket(4, 5115 - 1, this->packetSendLength[1]));
}

void InverterSungrow::decodePacket(unsigned char* recvBuffer, int sendPacketCount){
    if(recvBuffer[2] == this->packetSendLength[0] * 2){
        this->dayTotal = ucharToShort(&recvBuffer[3]);
        this->total = ucharToUint(&recvBuffer[5], true);
        this->invTemp = ucharToShort(&recvBuffer[13]);

        this->dcvs[0] = ucharToShort(&recvBuffer[19]);
        this->dcas[0] = ucharToShort(&recvBuffer[21]);
        this->dcvs[1] = ucharToShort(&recvBuffer[23]);
        this->dcas[1] = ucharToShort(&recvBuffer[25]);
        this->dcvs[2] = ucharToShort(&recvBuffer[27]);
        this->dcas[2] = ucharToShort(&recvBuffer[29]);

        int dckw = ucharToUint(&recvBuffer[31], true);
        this->dckw = (short)(dckw/100);

        this->acvr = ucharToShort(&recvBuffer[35]);
        this->acvs = ucharToShort(&recvBuffer[37]);
        this->acvt = ucharToShort(&recvBuffer[39]);

        this->acar = ucharToShort(&recvBuffer[41]);
        this->acas = ucharToShort(&recvBuffer[43]);
        this->acat = ucharToShort(&recvBuffer[45]);

        int ackw = ucharToUint(&recvBuffer[59], true);
        this->ackw = (short)(ackw/100);

        this->pf = ucharToShort(&recvBuffer[67])/100;
        this->freq = ucharToShort(&recvBuffer[69]);

        // Work state
        this->fault[0] = ucharToShort(&recvBuffer[73]);
        // Fault/Alarm code 1
        this->fault[1] = ucharToShort(&recvBuffer[87]);
        // Work state
        this->fault[2] = ucharToShort(&recvBuffer[159]);
        this->fault[3] = ucharToShort(&recvBuffer[161]);
    }
    if(recvBuffer[2] == this->packetSendLength[1] * 2){
        dcvs[3] = ucharToShort(&recvBuffer[3]);
        dcvs[4] = ucharToShort(&recvBuffer[7]);
        dcvs[5] = ucharToShort(&recvBuffer[11]);
        dcvs[6] = ucharToShort(&recvBuffer[15]);
        dcvs[7] = ucharToShort(&recvBuffer[19]);
        dcvs[8] = ucharToShort(&recvBuffer[33]);
        dcvs[9] = ucharToShort(&recvBuffer[37]);
        dcvs[10] = ucharToShort(&recvBuffer[41]);
        dcvs[11] = ucharToShort(&recvBuffer[45]);

        dcas[3] = ucharToShort(&recvBuffer[5]);
        dcas[4] = ucharToShort(&recvBuffer[9]);
        dcas[5] = ucharToShort(&recvBuffer[13]);
        dcas[6] = ucharToShort(&recvBuffer[17]);
        dcas[7] = ucharToShort(&recvBuffer[21]);
        dcas[8] = ucharToShort(&recvBuffer[35]);
        dcas[9] = ucharToShort(&recvBuffer[39]);
        dcas[10] = ucharToShort(&recvBuffer[43]);
        dcas[11] = ucharToShort(&recvBuffer[47]);

        this->dcv = *max_element(this->dcvs, this->dcvs + 12);
        this->dca = accumulate(this->dcas, this->dcas + 12, 0);
    }
}

unsigned char* InverterSungrow::serialize(){
    unsigned char* serialBuffer = new unsigned char[this->getSerializeLength()];
    shortToUcharArray(this->invno, serialBuffer, 0);
    shortToUcharArray(this->dcv, serialBuffer, 2);
    shortToUcharArray(this->dca, serialBuffer, 4);
    shortToUcharArray(this->dckw, serialBuffer, 6);
    shortToUcharArray(this->acar, serialBuffer, 8);
    shortToUcharArray(this->acas, serialBuffer, 10);
    shortToUcharArray(this->acat, serialBuffer, 12);
    shortToUcharArray(this->acvr, serialBuffer, 14);
    shortToUcharArray(this->acvs, serialBuffer, 16);
    shortToUcharArray(this->acvt, serialBuffer, 18);
    shortToUcharArray(this->ackw, serialBuffer, 20);
    shortToUcharArray(this->pf, serialBuffer, 22);
    shortToUcharArray(this->freq, serialBuffer, 24);
    shortToUcharArray(this->invTemp, serialBuffer, 26);
    shortToUcharArray(this->dayTotal, serialBuffer, 28);
    shortToUcharArray(this->total/0x10000, serialBuffer, 30);
    shortToUcharArray(this->total%0x10000, serialBuffer, 32);

    shortToUcharArray(this->fault[0], serialBuffer, 34);
    shortToUcharArray(this->fault[1], serialBuffer, 36);
    shortToUcharArray(this->fault[2], serialBuffer, 38);
    shortToUcharArray(this->fault[3], serialBuffer, 40);

    return serialBuffer;
}

void InverterSungrow::clearValue(bool totalReset){
    this->clearBaseValue(totalReset);
    this->invTemp = 0;
}