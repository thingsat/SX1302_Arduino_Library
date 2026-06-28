/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 UGA CSUG LIG

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */


#ifndef _LGW_UTILS_H_
#define _LGW_UTILS_H_

#include "loragw_hal.h"

// TODO add rx_cb flag
void lgw_config(const uint32_t SX1302_CS_Pin, const uint32_t SX1302_RESET_Pin, const bool rx_only);

static void lgw_print_rxpkt(const struct lgw_pkt_rx_s *rxpkt);

void lgw_idle(void);

static void lgw_rxpkt_cb(const struct lgw_pkt_rx_s *rxpkt);

static void lgw_period_cb(void);

void lgw_listen(void);

#endif /* _LGW_UTILS_H_ */
