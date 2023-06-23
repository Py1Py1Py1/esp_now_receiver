#include <stdio.h>
#include "main.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "wlc.h"
#include "driver/uart.h"

esp_err_t err;
volatile can_data data = {0};

void app_main(void)
{

    wlc_init();
    


    while(1){

        vTaskDelay(100 / portTICK_PERIOD_MS);
      
         
        // printf("\n");
        printf("temp:%.2f°C", data.temp_degre);
        printf("humm:%.2f%%", data.humm_per);
        // printf("\n");
        printf("acc_x:%dmg", data.acc_X);
        printf("acc_y:%dmg", data.acc_Y);
        printf("acc_z:%dmg", data.acc_Z);
        // printf("\n");
        printf("gyro_X:%ldmdps", data.gyro_X);
        printf("gyro_Y:%ldmdps", data.gyro_Y);
        printf("gyro_Z:%ldmdps", data.gyro_Z);
        // printf("\n");
        printf("damper_fr:%fV", (float) data.damper_fr * 2.5 / 4095);
        printf("damper_fh:%fV", (float) data.damper_fh * 2.5 / 4095);  
        printf("\n");
        //printf("\n");
        //uart_write_bytes(UART_NUM_0, &data,sizeof(can_data));

    }

}
