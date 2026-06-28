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

#include "networks.h"
#include "endpoints.h"

using namespace std;

extern "C" {
int _write(int fd, char *ptr, int len) {
  (void) fd;
  return Serial.write(ptr, len);
}
}

#include "config.h"

/*
static void print_i2c(void) {
    // I2C scan
    for (inqt idx = 0; idx < (int) I2C_NUMOF; idx++) {
        (void) mission_i2c_scan(idx);
        (void) mission_i2c_scan_and_check(idx);
    }
} */

static uint64_t eui = 0;

void print_eui64(void) {
    // Get lgw EUI
    int err = lgw_get_eui(&eui);
    if (err != 0) {
        Serial.print("ERROR: failed to get EUI\n");
        //return EXIT_FAILURE;
    }

    char eui_hex[20] = { 0 };
    fmt_u64_hex(eui_hex, eui);
    Serial.print("0x");
    Serial.print(eui_hex);
}

void print_i2c(void) {
    // TODO https://github.com/RobTillaart/I2C_SCANNER/blob/master/I2C_SCANNER.h
}


void setup_sx1302(void) {

    SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));

    pinMode(SX1302_RESET, OUTPUT);
    pinMode(SX1302_CS, OUTPUT);

    digitalWrite(SX1302_RESET, LOW);
    digitalWrite(SX1302_CS, HIGH);

}


void setup(void) {
    Serial.begin(115200);

    while(!Serial){
        delay(1000);
    }

    delay(1000);

    puts("\nINFO: ===========================");
    puts("INFO: Thingsat Basic Mission");
    puts("INFO: ===========================\n");

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

    print_i2c(); // I2C scanner

    lgw_config(SX1302_CS, SX1302_RESET, false);

    /* connect, configure and start the LoRa concentrator */
    while (lgw_start() != 0) {
        Serial.print("ERROR: failed to start the gateway\n");
        delay(1000);
    }
    Serial.print("INFO: Gateway is started\n");

    Serial.print(F("INFO: Concentrator EUI: "));
    print_eui64();
    Serial.println();

    const lorawan_endpoint_t* lorawan_endpoint_myself = endpoints_set_myself(eui);
    if(lorawan_endpoint_myself == NULL) {
        Serial.print("WARN: no endpoint for EUI ");
        print_eui64();
        Serial.println();
    } else {
        Serial.print(F("INFO: my endpoint is "));
        Serial.print(F(lorawan_endpoint_myself->label));
        Serial.print(F(" 0x"));
        Serial.println(lorawan_endpoint_myself->devaddr, HEX);
    }

    Serial.println(F("INFO: friend endpoints are: "));
    endpoints_print_all();

    // TODO lgw_freq_plan();

    // TODO configure default mission (including ZoI)
    // TODO display friends (networks , endpoints)

    // TODO set callback on rx
    // TODO set callback on period

    // TODO lgw_freq_plan();

}

void loop(void){

    lgw_listen();

    // TODO lgw_stats();
}
