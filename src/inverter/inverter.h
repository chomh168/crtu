#define GROWATT 5
#define SUNGROW 7

#include "1.Growatt.h"
#include "2.Sungrow.h"

InverterBase* getInverterInstance(short model, short id){
    InverterBase* result;
    switch(model){
        case GROWATT:
            result = new InverterGrowatt(id);
            break;
        case SUNGROW:
            result = new InverterSungrow(id);
            break;
        default:
            result = nullptr;
            break;
    }
    return result;
}