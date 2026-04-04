/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 UGA CSUG LIG

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

// TODO add config for SX1250 and EU868 in a dedicated header file
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#ifndef SPI_CLK_SPEED
#define SPI_CLK_SPEED 5000000
#endif

#define ENABLE_SX1250

#ifdef ENABLE_SX1250
#define RSSI_OFFSET			    (-215.4)
#define RSSI_TCOMP_COEFF_A	(0)
#define RSSI_TCOMP_COEFF_B	(0)
#define RSSI_TCOMP_COEFF_C	(20.41)
#define RSSI_TCOMP_COEFF_D	(2162.56)
#define RSSI_TCOMP_COEFF_E	(0)
#endif

#ifndef MAX_RX_PKT
#define MAX_RX_PKT  4
#endif

// Config for EU868
#define FREQ_A_EU868  (867500000u)
#define FREQ_B_EU868  (868500000u)

uint8_t clocksource = 0;
lgw_radio_type_t radio_type = LGW_RADIO_TYPE_SX1250; //LGW_RADIO_TYPE_SX1255, LGW_RADIO_TYPE_SX1257, LGW_RADIO_TYPE_SX1250
bool single_input_mode = false;
float rssi_offset = RSSI_OFFSET;
bool full_duplex = false;

struct lgw_conf_board_s boardconf;
struct lgw_conf_rxrf_s rfconf;
struct lgw_conf_rxif_s ifconf;

const int32_t channel_if_mode[9] = {
    -400000,
    -200000,
    0,
    -400000,
    -200000,
    0,
    200000,
    400000,
    -200000 /* lora service */
};

const uint8_t channel_rfchain_mode[9] = { 1, 1, 1, 0, 0, 0, 0, 0, 1 };

void lgw_config(const uint32_t SX1302_CS_Pin, const uint32_t SX1302_RESET_Pin, const bool rx_only) { // TODO add rx_cb flag,

    SPI.beginTransaction(SPISettings(SPI_CLK_SPEED, MSBFIRST, SPI_MODE0));

    pinMode(SX1302_RESET_Pin, OUTPUT);
    pinMode(SX1302_CS_Pin, OUTPUT);

    digitalWrite(SX1302_RESET_Pin, LOW);
    digitalWrite(SX1302_CS_Pin, HIGH);
    
    Serial.print("SX1302 Reset\n");
    /* Board reset */
    digitalWrite(SX1302_RESET_Pin,HIGH);
    delay(100);
    digitalWrite(SX1302_RESET_Pin,LOW);
    delay(100);

    Serial.print("Configure SX1302/SX1303 concentrator\n");

    int i, j, x;
    /* Configure the gateway */
    memset( &boardconf, 0, sizeof boardconf);
    boardconf.lorawan_public = true;
    boardconf.cs = SX1302_CS_Pin;
    boardconf.clksrc = clocksource;
    boardconf.full_duplex = full_duplex;
    if (lgw_board_setconf(&boardconf) != LGW_HAL_SUCCESS) {
        Serial.print("ERROR: failed to configure board\n");
        while(1);
    }

    /* set configuration for RF chains */
    memset( &rfconf, 0, sizeof rfconf);
    rfconf.enable = true;
    rfconf.freq_hz = FREQ_A_EU868;
    rfconf.type = radio_type;
    rfconf.rssi_offset = rssi_offset;
    rfconf.tx_enable = !rx_only;
    rfconf.single_input_mode = single_input_mode;
 	rfconf.rssi_tcomp.coeff_a = RSSI_TCOMP_COEFF_A;
	rfconf.rssi_tcomp.coeff_b = RSSI_TCOMP_COEFF_B;
	rfconf.rssi_tcomp.coeff_c = RSSI_TCOMP_COEFF_C;
	rfconf.rssi_tcomp.coeff_d = RSSI_TCOMP_COEFF_D;
	rfconf.rssi_tcomp.coeff_e = RSSI_TCOMP_COEFF_E;

   if (lgw_rxrf_setconf(0, &rfconf) != LGW_HAL_SUCCESS) {
        Serial.print("ERROR: failed to configure rxrf 0\n");
        while(1);
        // return error
    }

    memset( &rfconf, 0, sizeof rfconf);
    rfconf.enable = true;
    rfconf.freq_hz = FREQ_B_EU868;
    rfconf.type = radio_type;
    rfconf.rssi_offset = rssi_offset;
    rfconf.tx_enable = false;
    rfconf.single_input_mode = single_input_mode;
  	rfconf.rssi_tcomp.coeff_a = RSSI_TCOMP_COEFF_A;
	rfconf.rssi_tcomp.coeff_b = RSSI_TCOMP_COEFF_B;
	rfconf.rssi_tcomp.coeff_c = RSSI_TCOMP_COEFF_C;
	rfconf.rssi_tcomp.coeff_d = RSSI_TCOMP_COEFF_D;
	rfconf.rssi_tcomp.coeff_e = RSSI_TCOMP_COEFF_E;
   if (lgw_rxrf_setconf(1, &rfconf) != LGW_HAL_SUCCESS) {
        Serial.print("ERROR: failed to configure rxrf 1\n");
        while(1);
        // return error
    }

    /* set configuration for LoRa multi-SF channels (bandwidth cannot be set) */
    memset(&ifconf, 0, sizeof(ifconf));
    for (i = 0; i < 8; i++) {
        ifconf.enable = true;
        ifconf.rf_chain = channel_rfchain_mode[i];
        ifconf.freq_hz = channel_if_mode[i];
        ifconf.datarate = DR_LORA_SF7;
        if (lgw_rxif_setconf(i, &ifconf) != LGW_HAL_SUCCESS) {
            Serial.print("ERROR: failed to configure rxif");
            Serial.println(i);
            while(1);
        // return error
        }
    }

    /* set configuration for LoRa Service channel */
    memset(&ifconf, 0, sizeof(ifconf));
    ifconf.rf_chain = channel_rfchain_mode[i];
    ifconf.freq_hz = channel_if_mode[i];
    ifconf.datarate = DR_LORA_SF7;
    ifconf.bandwidth = BW_250KHZ;
    if (lgw_rxif_setconf(8, &ifconf) != LGW_HAL_SUCCESS) {
        Serial.print("ERROR: failed to configure rxif for LoRa service channel\n");
        while(1);
        // return error
    }
}

static void lgw_print_rxpkt(const struct lgw_pkt_rx_s *rxpkt) {
                Serial.print("\n----- ");
                Serial.print((rxpkt->modulation == MOD_LORA) ? "LoRa" : "FSK");
                Serial.println(" packet -----");
                Serial.print("  count_us: ");
                Serial.println(rxpkt->count_us);
                Serial.print("  size:     ");
                Serial.println(rxpkt->size);
                Serial.print("  modem_id: ");
                Serial.println(rxpkt->modem_id);
                Serial.print("  chan:     ");
                Serial.println(rxpkt->if_chain);
                Serial.print("  status:   ");
                Serial.println(rxpkt->status);
                Serial.print("  datr:     ");
                Serial.println(rxpkt->datarate);
                Serial.print("  codr:     ");
                Serial.println(rxpkt->coderate);
                Serial.print("  bw:       ");
                Serial.println(rxpkt->bandwidth);
                Serial.print("  rf_chain  ");
                Serial.println(rxpkt->rf_chain);
                Serial.print("  freq_hz   ");
                Serial.println(rxpkt->freq_hz);
                Serial.print("  fr_offset ");
                Serial.println(rxpkt->freq_offset);
                Serial.print("  snr_avg:  ");
                Serial.println(rxpkt->snr);
                Serial.print("  rssi_chan:");
                Serial.println(rxpkt->rssic);
                Serial.print("  rssi_sig :");
                Serial.println(rxpkt->rssis);
                Serial.print("  crc:      ");
                Serial.println(rxpkt->crc);
                Serial.print("  status:   ");
                Serial.println(rxpkt->status);

                for (int j = 0; j < rxpkt->size; j++) {
                    Serial.print(rxpkt->payload[j],HEX);
                    Serial.print(" ");
                }
                Serial.println("");
}

static bool _lgw_status_listening = false;

void lgw_idle(void){
    _lgw_status_listening = false;
}

static void lgw_rxpkt_cb(const struct lgw_pkt_rx_s *rxpkt) {
  lgw_print_rxpkt(rxpkt);
  // TODO add LoRaWAN packet printing
  // TODO add MeshCore packet printing
  // TODO add Meshtastic packet printing
}

static struct lgw_pkt_rx_s rxpkt[MAX_RX_PKT];

void lgw_listen(void){

    unsigned long nb_pkt_crc_ok = 0, nb_loop = 0;

    /* Loop until we have enough packets with CRC OK */
    Serial.print("Waiting for packets...\n");

    _lgw_status_listening = true;

    while (_lgw_status_listening) {
        /* fetch N packets */
        int nb_pkt = lgw_receive(ARRAY_SIZE(rxpkt), rxpkt);

        if (nb_pkt == 0) {
            delay(10); // ms
        } else {
            for (int i = 0; i < nb_pkt; i++) {
                if (rxpkt[i].status == STAT_CRC_OK) {
                    nb_pkt_crc_ok += 1;
                }

                // TODO add RX callback here with parameter rxpkt + i
                lgw_rxpkt_cb(rxpkt + i);

                // cleaning
                memset(rxpkt + i, 0, sizeof(lgw_pkt_rx_s));
            }
        }

        // TODO show stats periodically
    }

    Serial.print("Stop listening packets\n");
}
