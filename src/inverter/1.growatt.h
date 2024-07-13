#ifndef GROWATT_H_
#define GROWATT_H_

// #include "../util/util.h"
#include "0.inverter_base.h"


class InverterGrowatt : public InverterBase {
private:

public:
	short invTemp1;
	short invTemp2;
	short invTemp3;
	short addtionalFault[5];

	InverterGrowatt(short invno);
	void decodePacket(unsigned char* recvBuffer) override;
	unsigned char* serialize() override;
    void clearValue(bool totalReset) override;
};

#endif /* GROWATT_H_ */