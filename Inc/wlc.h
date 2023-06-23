#ifndef WLC_H
#define WLC_H

#include <esp_system.h>
#include "main.h"


void wlc_init();

void recv_data(can_data*);

#endif //ESP_NOW_H