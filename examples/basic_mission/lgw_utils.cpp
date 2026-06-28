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
//#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#include "container.h"
#include "config.h"
#include "networks.h"
#include "endpoints.h"

uint8_t clocksource = 0;
lgw_radio_type_t radio_type = LGW_RADIO_TYPE_SX1250;  //LGW_RADIO_TYPE_SX1255, LGW_RADIO_TYPE_SX1257, LGW_RADIO_TYPE_SX1250
bool single_input_mode = false;
float rssi_offset = RSSI_OFFSET;
bool full_duplex = false;

struct lgw_conf_board_s boardconf;
struct lgw_conf_rxrf_s rfconf;
struct lgw_conf_rxif_s ifconf;

const int32_t channel_if_mode[9] = CHANNEL_IF_MODE;

const uint8_t channel_rfchain_mode[9] = CHANNEL_RFCHAIN_MODE;

// TODO add rx_cb flag
void lgw_config(const uint32_t SX1302_CS_Pin, const uint32_t SX1302_RESET_Pin, const bool rx_only) {

  SPI.beginTransaction(SPISettings(SPI_CLK_SPEED, MSBFIRST, SPI_MODE0));

  pinMode(SX1302_RESET_Pin, OUTPUT);
  pinMode(SX1302_CS_Pin, OUTPUT);

  digitalWrite(SX1302_RESET_Pin, LOW);
  digitalWrite(SX1302_CS_Pin, HIGH);

  Serial.print("SX1302 Reset\n");
  /* Board reset */
  digitalWrite(SX1302_RESET_Pin, HIGH);
  delay(100);
  digitalWrite(SX1302_RESET_Pin, LOW);
  delay(100);

  Serial.print("Configure SX1302/SX1303 concentrator\n");

  int i, j, x;
  /* Configure the gateway */
  memset(&boardconf, 0, sizeof boardconf);
  boardconf.lorawan_public = true;
  boardconf.cs = SX1302_CS_Pin;
  boardconf.clksrc = clocksource;
  boardconf.full_duplex = full_duplex;
  if (lgw_board_setconf(&boardconf) != LGW_HAL_SUCCESS) {
    Serial.print("ERROR: failed to configure board\n");
    while (1)
      ;
  }

  /* set configuration for RF chains */
  memset(&rfconf, 0, sizeof rfconf);
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
    while (1)
      ;
    // return error
  }

  memset(&rfconf, 0, sizeof rfconf);
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
    while (1)
      ;
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
      while (1)
        ;
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
    while (1)
      ;
    // return error
  }
}

static void lgw_print_rxpkt(const struct lgw_pkt_rx_s *rxpkt) {
  Serial.print("\n----- ");
  Serial.print((rxpkt->modulation == MOD_LORA) ? "LoRa" : "FSK");
  Serial.println(" packet -----");
  Serial.print("  count_us  : ");
  Serial.println(rxpkt->count_us);
  Serial.print("  modem_id  : ");
  Serial.println(rxpkt->modem_id);
  Serial.print("  chan      : ");
  Serial.println(rxpkt->if_chain);
  Serial.print("  status    : ");
  Serial.println(rxpkt->status);
  Serial.print("  datr      : ");
  Serial.println(rxpkt->datarate);
  Serial.print("  codr      : ");
  Serial.println(rxpkt->coderate);
  Serial.print("  bw        : ");
  Serial.println(rxpkt->bandwidth);
  Serial.print("  rf_chain  : ");
  Serial.println(rxpkt->rf_chain);
  Serial.print("  freq_hz   : ");
  Serial.println(rxpkt->freq_hz);
  Serial.print("  fr_offset : ");
  Serial.println(rxpkt->freq_offset);
  Serial.print("  snr_avg   : ");
  Serial.println(rxpkt->snr);
  Serial.print("  rssi_chan : ");
  Serial.println(rxpkt->rssic);
  Serial.print("  rssi_sig  : ");
  Serial.println(rxpkt->rssis);
  Serial.print("  crc       : ");
  Serial.println(rxpkt->crc, HEX);
  Serial.print("  status    : ");
  Serial.println(rxpkt->status, HEX);
  Serial.print("  size      : ");
  Serial.println(rxpkt->size);
  Serial.print("  payload   : ");

  for (int j = 0; j < rxpkt->size; j++) {
    uint8_t b = rxpkt->payload[j];
    if(b<0x10) {Serial.print("0");}
    Serial.print(b, HEX);
    Serial.print(" ");
  }
  Serial.println("");
}

static bool _lgw_status_listening = false;

void lgw_idle(void) {
  _lgw_status_listening = false;
}

// LGW Stats

typedef struct lgw_stats {
  uint32_t count_us_last;
  uint32_t rx_cnt;
  uint32_t rx_lora_cnt;
  uint32_t rx_fsk_cnt;
  uint32_t rx_crc_ok;
  uint32_t rx_bad_crc;
  uint32_t rx_no_crc;
  uint32_t ftime_cnt;
  uint32_t rx_size_cnt;
  float snr_lora_sum;
  float snr_min_lora_sum;
  float snr_max_lora_sum;
  float snr_lora_crc_ok_sum;
  float snr_lora_bad_crc_sum;
  float rssis_sum;
  float rssic_sum;

  // counters for LoRaWAN frames (type, dr, size)

  // mission
  uint32_t rx_downlink_cnt;
  uint32_t rx_friend_cnt;
  uint32_t rx_friend_replay_cnt;
  uint32_t rx_friend_badmic_cnt;

  uint32_t tx_cnt;
  uint32_t tx_repeat_cnt;

  // packet forwarder
  uint32_t rx_forward_cnt;  // UDP or MQTT if MCU has IP connection
} lgw_stats_t;

static lgw_stats_t _lgw_stats;
static uint32_t _lgw_stats_report_counter = 0;

static void lgw_stats_update(const struct lgw_pkt_rx_s *rxpkt) {
  _lgw_stats.count_us_last = rxpkt->count_us;
  _lgw_stats.rx_cnt++;
  _lgw_stats.rx_size_cnt += rxpkt->size;
  switch (rxpkt->modulation) {
    case MOD_LORA:
      _lgw_stats.rx_lora_cnt++;
      _lgw_stats.snr_lora_sum += rxpkt->snr;
      break;
    case MOD_FSK:
      _lgw_stats.rx_lora_cnt++;
      _lgw_stats.snr_lora_sum += rxpkt->snr;
      break;
    case MOD_CW:
    case MOD_UNDEFINED:
    default:
      break;
  }
  switch (rxpkt->status) {
    case STAT_CRC_BAD:
      _lgw_stats.rx_bad_crc++;
      _lgw_stats.snr_lora_bad_crc_sum += rxpkt->snr;
      break;
    case STAT_CRC_OK:
      _lgw_stats.rx_crc_ok++;
      _lgw_stats.snr_lora_crc_ok_sum += rxpkt->snr;
      break;
    case STAT_NO_CRC:
      _lgw_stats.rx_no_crc++;
      break;
    case STAT_UNDEFINED:
    default:
      break;
  }
  _lgw_stats.rssic_sum += rxpkt->rssic;
  _lgw_stats.rssis_sum += rxpkt->rssis;
  if (rxpkt->ftime_received) {
    _lgw_stats.ftime_cnt++;
  }
}

static void lgw_stats_print(const unsigned long ms) {
  // TODO add RTC time
  Serial.print(F("INFO: LGW stats #"));
  Serial.print(_lgw_stats_report_counter++);
  Serial.print(F(" ("));
  Serial.print(ms / 1000);
  Serial.println(F(")"));

  if (_lgw_stats.rx_cnt > 0) {
    Serial.print("count_us_last        : ");
    Serial.println(_lgw_stats.count_us_last);
  }
  Serial.print("rx_cnt               : ");
  Serial.println(_lgw_stats.rx_cnt);
  if (_lgw_stats.rx_cnt > 0) {
    Serial.print("rx_lora_cnt          : ");
    Serial.println(_lgw_stats.rx_lora_cnt);
    Serial.print("rx_fsk_cnt           : ");
    Serial.println(_lgw_stats.rx_fsk_cnt);
    Serial.print("rx_crc_ok            : ");
    Serial.println(_lgw_stats.rx_crc_ok);
    Serial.print("rx_bad_crc           : ");
    Serial.println(_lgw_stats.rx_bad_crc);
    Serial.print("rx_no_crc            : ");
    Serial.println(_lgw_stats.rx_no_crc);
    Serial.print("ftime_cnt            : ");
    Serial.println(_lgw_stats.ftime_cnt);
    Serial.print("rx_size_avg          : ");
    Serial.println(1.0 * _lgw_stats.rx_size_cnt / _lgw_stats.rx_cnt);
  }
  if (_lgw_stats.rx_lora_cnt > 0) {
    Serial.print("snr_lora_avg         : ");
    Serial.println(_lgw_stats.snr_lora_sum / _lgw_stats.rx_lora_cnt);
  }
  if (_lgw_stats.rx_crc_ok > 0) {
    Serial.print("snr_lora_crc_ok_avg  : ");
    Serial.println(_lgw_stats.snr_lora_crc_ok_sum / _lgw_stats.rx_crc_ok);
  }
  if (_lgw_stats.rx_bad_crc > 0) {
    Serial.print("snr_lora_bad_crc_avg : ");
    Serial.println(_lgw_stats.snr_lora_bad_crc_sum / _lgw_stats.rx_bad_crc);
  }
  if (_lgw_stats.rx_cnt > 0) {
    Serial.print("rssis_avg            : ");
    Serial.println(_lgw_stats.rssis_sum / _lgw_stats.rx_cnt);
    Serial.print("rssic_avg            : ");
    Serial.println(_lgw_stats.rssic_sum / _lgw_stats.rx_cnt);
  }
  Serial.print("tx_cnt               : ");
  Serial.println(_lgw_stats.tx_cnt);
  Serial.print("tx_repeat_cnt        : ");
  Serial.println(_lgw_stats.tx_repeat_cnt);
}

static void lgw_stats_reset(void) {
  // TODO fast reset
  memset(&_lgw_stats, 0, sizeof(_lgw_stats));
  _lgw_stats.snr_lora_sum = 0.0;
  _lgw_stats.snr_min_lora_sum = 0.0;
  _lgw_stats.snr_max_lora_sum = 0.0;
  _lgw_stats.rssis_sum = 0.0;
  _lgw_stats.rssic_sum = 0.0;
}

static void lgw_stats_setup(void) {
  lgw_stats_reset();
}


// LGW callback functions

static void lgw_rxpkt_cb(const struct lgw_pkt_rx_s *rxpkt) {
  lgw_print_rxpkt(rxpkt);

  lgw_stats_update(rxpkt);

  // TODO add LoRaWAN packet printing
  // TODO filter and repeat LoRaWAN packet
  // TODO filter and repeat Chirpstack mesh
  // TODO add MeshCore packet printing
  // TODO filter and repeat MeshCore packet
  // TODO add Meshtastic packet printing
  // TODO filter and repeat Meshtastic packet
}

static unsigned long lgw_period_cb_last_call_in_ms = 0;

static void lgw_period_cb(void) {

  const unsigned long ms = millis();
  if (ms > lgw_period_cb_last_call_in_ms + LGW_PERIOD_CB_PERIOD) {
    lgw_period_cb_last_call_in_ms = ms;

    lgw_stats_print(ms);
    lgw_stats_reset();

    // TODO execute periodic frame transmit according the mission
  }
}


static struct lgw_pkt_rx_s rxpkt[MAX_RX_PKT];

void lgw_listen(void) {

  unsigned long nb_pkt_crc_ok = 0, nb_loop = 0;

  /* Loop until we have enough packets with CRC OK */
  Serial.print("INFO: Waiting for packets...\n");

  _lgw_status_listening = true;

  while (_lgw_status_listening) {
    /* fetch N packets */
    int nb_pkt = lgw_receive(ARRAY_SIZE(rxpkt), rxpkt);

    if (nb_pkt == 0) {
      delay(10);  // ms
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

    lgw_period_cb();
  }

  Serial.print("INFO: Stop listening packets\n");
}
