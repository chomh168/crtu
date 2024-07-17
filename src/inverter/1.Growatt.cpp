#include "1.Growatt.h"


InverterGrowatt::InverterGrowatt(short invno) : InverterBase(invno) {
    this->setModel(5);
    this->setBaudRate(9600);
    this->setSerializeLength(58);
    this->packetLength = 8;
    this->sendPacketList.push_back(this->makeModbusSendPacket(4, 0, 0x6f));
}

void InverterGrowatt::decodePacket(unsigned char* recvBuffer, int sendPacketCount){
    this->fault[0] = ucharToShort(&recvBuffer[3]);
    
    int dckw = ucharToUint(&recvBuffer[5]);
    this->dckw = (short)(dckw/1000);
    
    int dcvs[8];
    dcvs[0] = ucharToShort(&recvBuffer[9]);
    dcvs[1] = ucharToShort(&recvBuffer[17]);
    dcvs[2] = ucharToShort(&recvBuffer[25]);
    dcvs[3] = ucharToShort(&recvBuffer[33]);
    dcvs[4] = ucharToShort(&recvBuffer[41]);
    dcvs[5] = ucharToShort(&recvBuffer[49]);
    dcvs[6] = ucharToShort(&recvBuffer[57]);
    dcvs[7] = ucharToShort(&recvBuffer[65]);
    
    this->dcv = *max_element(dcvs, dcvs + 8);

    int dcas[8];
    dcas[0] = ucharToShort(&recvBuffer[11]);
    dcas[1] = ucharToShort(&recvBuffer[19]);
    dcas[2] = ucharToShort(&recvBuffer[27]);
    dcas[3] = ucharToShort(&recvBuffer[35]);
    dcas[4] = ucharToShort(&recvBuffer[43]);
    dcas[5] = ucharToShort(&recvBuffer[51]);
    dcas[6] = ucharToShort(&recvBuffer[59]);
    dcas[7] = ucharToShort(&recvBuffer[67]);

    this->dca = accumulate(dcas, dcas + 8, 0);

    int ackw = ucharToUint(&recvBuffer[73]);
    this->ackw = (short)(ackw/1000);

    this->freq = ucharToShort(&recvBuffer[77]);

    this->acvr = ucharToShort(&recvBuffer[79]);
    this->acar = ucharToShort(&recvBuffer[81]);

    this->acvs = ucharToShort(&recvBuffer[87]);
    this->acas = ucharToShort(&recvBuffer[89]);

    this->acvt = ucharToShort(&recvBuffer[95]);
    this->acat = ucharToShort(&recvBuffer[97]);

    this->dayTotal = ucharToUint(&recvBuffer[109]);
    this->total = ucharToUint(&recvBuffer[113]);

    this->invTemp1 = ucharToShort(&recvBuffer[189]);
    this->invTemp2 = ucharToShort(&recvBuffer[191]);
    this->invTemp3 = ucharToShort(&recvBuffer[193]);

    this->pf = ucharToShort(&recvBuffer[205]);

    this->fault[1] = ucharToShort(&recvBuffer[211]);
    this->fault[2] = ucharToShort(&recvBuffer[213]);
    this->fault[3] = ucharToShort(&recvBuffer[215]);
    this->addtionalFault[0] = ucharToShort(&recvBuffer[217]);
    this->addtionalFault[1] = ucharToShort(&recvBuffer[219]);
    this->addtionalFault[2] = ucharToShort(&recvBuffer[221]);
    this->addtionalFault[3] = ucharToShort(&recvBuffer[223]);
    this->addtionalFault[4] = ucharToShort(&recvBuffer[225]);
}

unsigned char* InverterGrowatt::serialize(){
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
    shortToUcharArray(this->invTemp1, serialBuffer, 26);
    shortToUcharArray(this->invTemp2, serialBuffer, 28);
    shortToUcharArray(this->invTemp3, serialBuffer, 30);
    shortToUcharArray(this->dayTotal/0x10000, serialBuffer, 32);
    shortToUcharArray(this->dayTotal%0x10000, serialBuffer, 34);
    shortToUcharArray(this->total/0x10000, serialBuffer, 36);
    shortToUcharArray(this->total%0x10000, serialBuffer, 38);

    shortToUcharArray(this->fault[0], serialBuffer, 40);
    shortToUcharArray(this->fault[1], serialBuffer, 42);
    shortToUcharArray(this->fault[2], serialBuffer, 44);
    shortToUcharArray(this->fault[3], serialBuffer, 46);
    shortToUcharArray(this->addtionalFault[0], serialBuffer, 48);
    shortToUcharArray(this->addtionalFault[1], serialBuffer, 50);
    shortToUcharArray(this->addtionalFault[2], serialBuffer, 52);
    shortToUcharArray(this->addtionalFault[3], serialBuffer, 54);
    shortToUcharArray(this->addtionalFault[4], serialBuffer, 56);

    return serialBuffer;
}

void InverterGrowatt::clearValue(bool totalReset){
    this->clearBaseValue(totalReset);
    this->invTemp1 = 0;
	this->invTemp2 = 0;
	this->invTemp3 = 0;
	this->addtionalFault[0] = 0;
	this->addtionalFault[1] = 0;
	this->addtionalFault[2] = 0;
	this->addtionalFault[3] = 0;
	this->addtionalFault[4] = 0;
}