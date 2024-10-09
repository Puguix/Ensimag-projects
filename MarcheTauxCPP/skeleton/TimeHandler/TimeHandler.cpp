#include "TimeHandler.hpp"

int TimeHandler::monitoringHandleIndex(bool isMonitoringDate, int indiceConstat){
    if(isMonitoringDate) {
        return indiceConstat-1;
    } else {
        return indiceConstat;
    }
}