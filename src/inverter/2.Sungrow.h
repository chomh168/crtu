#ifndef GROWATT_H_
#define GROWATT_H_

#include "0.inverter_base.h"


class InverterSungrow : public InverterBase {
private:
	int packetSendLength[2];

public:
	short invTemp;

	InverterSungrow(short invno);
	void decodePacket(unsigned char* recvBuffer, int sendPacketCount) override;
	unsigned char* serialize() override;
    void clearValue(bool totalReset) override;
};

#endif /* SUNGROW_H_ */