#ifndef SUNGROW_H_
#define SUNGROW_H_

#include "0.inverter_base.h"


class InverterSungrow : public InverterBase {
private:
	int packetSendLength[2];
	short dcvs[12];
	short dcas[12];

public:
	short invTemp;

	InverterSungrow(short invno);
	void decodePacket(unsigned char* recvBuffer, int sendPacketCount) override;
	unsigned char* serialize() override;
    void clearValue(bool totalReset) override;
};

#endif /* SUNGROW_H_ */