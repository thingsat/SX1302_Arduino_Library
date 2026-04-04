/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 UGA CSUG LIG

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

#ifndef LGW_UTILS_H
#define LGW_UTILS_H

// TODO return error
// TODO add rx_cb flag
void lgw_config(const uint32_t SX1302_CS_Pin, const uint32_t SX1302_RESET_Pin, const bool rx_only); 

void lgw_listen(void);

void lgw_idle(void);

// TODO lgw_freq_plan
// TODO lgw_eui
// TODO lgw_stats

#endif