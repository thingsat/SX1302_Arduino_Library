/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 GINP UGA CSUG LIG

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

extern "C" {
#include "loragw_aux.h"
#include "loragw_hal.h"
#include "lgw_utils.h"
#include "fmt.h"
}

#include <SPI.h>
#include <Arduino.h>
#include <stdio.h>
#include <iostream>

using namespace std;

extern "C" {
int _write(int fd, char *ptr, int len) {
  (void) fd;
  return Serial.write(ptr, len);
}
}

// TODO Add conditional module : For Thingsat INISAT and Thingsat ProtoSEED with Nucleo L432KC

#define SX1302_RESET    D3
#define SX1302_CS       D6

/*
static void print_i2c(void) {
    // I2C scan
    for (inqt idx = 0; idx < (int) I2C_NUMOF; idx++) {
        (void) mission_i2c_scan(idx);
        (void) mission_i2c_scan_and_check(idx);
    }
} */

void setup() {
    Serial.begin(115200);

    SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));

    pinMode(SX1302_RESET, OUTPUT);
    pinMode(SX1302_CS, OUTPUT);

    digitalWrite(SX1302_RESET, LOW);
    digitalWrite(SX1302_CS, HIGH);

    while(!Serial){
        delay(1000);
    }

    //printf("INFO: ===========================\n");  //was: Serial.print
    puts("INFO: Thingsat Basic Mission");  //was: Serial.print
    delay(100);
    //printf("INFO: ===========================\n");  //was: Serial.print

/*
#if GPS_UART_ENABLE == 1
    puts("INFO: Starting the GNSS parsing ...");

    printf("GPS_UART_DEV: %d\n", GPS_UART_DEV);
    printf("GPS_BAUDRATE: %d\n", GPS_BAUDRATE);
    gps_start(GPS_UART_DEV,GPS_UART_BAUDRATE);
#else
    puts("WARN: No GNSS module");
#endif */

#if MESHTASTIC_ENABLE == 1
    puts("INFO: Meshtastic EU868 gateway configuration");
#elif CHIRPSTACK_MESH_ENABLE == 1
    puts("INFO: Chirpstack Mesh Relay is enabled");
#else
    puts("INFO: LoRaWAN EU868 gateway configuration");
#endif

//  print_git();

//  print_i2c();

    lgw_config(SX1302_CS, SX1302_RESET, false);

    /* connect, configure and start the LoRa concentrator */
    if (lgw_start() != 0) {
        Serial.print("ERROR: failed to start the gateway\n");
        while(true);
    }
    Serial.print("INFO: Gateway is started\n");

    // Get lgw EUI
    uint64_t eui;
    int err = lgw_get_eui(&eui);
    if (err != 0) {
        Serial.print("ERROR: failed to get EUI\n");
        //return EXIT_FAILURE;
    }

    char eui_hex[20] = { 0 };
    fmt_u64_hex(eui_hex, eui);
    Serial.print("Concentrator EUI: 0x");
	Serial.println(eui_hex);
    //Serial.print("Concentrator EUI: 0x" PRIx64 "\n", eui);

    // TODO lgw_freq_plan();

}

void loop(){

    lgw_listen();

    // TODO lgw_stats();
}
