#include <stdio.h>

#include "esp_now.h"
#include "main.h"
#include "esp_wifi.h"
#include "wlc.h"
#include "nvs_flash.h"
#include "esp_mac.h"
#include "string.h"


static void receive_msg(const esp_now_recv_info_t* esp_now_info, const uint8_t* raw_data, int data_len){
    memcpy(&data, raw_data, sizeof(can_data));

}

static uint8_t sender_mac[6] = {0xf4,0x12,0xfa,0x15,0xdc,0x94};


void wlc_init()
{
    // Initialisiere ESPNOW UND WIFI

    uint8_t mac[6] = {0};
    esp_efuse_mac_get_default(mac);
    printf("mac: %x:%x:%x:%x:%x:%x\n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);


    esp_err_t ret = nvs_flash_init();
    if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
        ESP_ERROR_CHECK( nvs_flash_erase() );
        ret = nvs_flash_init();
    }

    CHECK(ret);

    CHECK(esp_netif_init());
    CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    CHECK(esp_wifi_init(&cfg));
    CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
    CHECK(esp_wifi_start());
    CHECK(esp_wifi_set_channel(1,1));


    CHECK_M(esp_now_init(), "ESP-NOW Init fail");

    esp_now_peer_info_t peer = {0};
    peer.channel = 1;
    peer.ifidx = ESP_IF_WIFI_STA;
    peer.encrypt = false;
    memcpy(peer.peer_addr,sender_mac,6);

    CHECK_M(esp_now_add_peer(&peer), "Add peer fail");

    CHECK_M(esp_now_register_recv_cb(receive_msg), "ESPNOW register rcv cb")

}
