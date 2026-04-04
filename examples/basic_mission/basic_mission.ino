/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 GINP UGA CSUG LIG

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

extern "C" {
#include "loragw_com.h"
#include "loragw_aux.h"
#include "loragw_hal.h"
#include "lgw_utils.h"
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

void setup(){
    Serial.begin(115200);

    while(!Serial){
        delay(1000);
    }

    Serial.print("INFO: ===========================\n");
    Serial.print("INFO: Thingsat Basic Mission\n");
    Serial.print("INFO: ===========================\n");

    lgw_config(SX1302_CS, SX1302_RESET, false);

    /* connect, configure and start the LoRa concentrator */
    if (lgw_start() != 0) {
        Serial.print("ERROR: failed to start the gateway\n");
        while(true);
    }
    Serial.print("INFO: Gateway is started\n");

    // TODO lgw_eui();

    // TODO lgw_freq_plan();
}

void loop(){

    lgw_listen();

    // TODO lgw_stats();
}
