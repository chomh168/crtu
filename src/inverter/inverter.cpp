#include "inverter.h"

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