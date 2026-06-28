/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 GINP UGA CSUG LIG

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

 #ifndef _BASIC_MISSION_CONFIG_H_
 #define _BASIC_MISSION_CONFIG_H_


// TODO Add conditional module : For Thingsat INISAT and Thingsat ProtoSEED with Nucleo L432KC

// SX1302/3 SPI module

#ifndef SPI_CLK_SPEED
#define SPI_CLK_SPEED 5000000
#endif

#ifndef SX1302_RESET
#define SX1302_RESET    D3
#endif

#ifndef SX1302_CS
#define SX1302_CS       D6
#endif

// Radio frontends (SX125x)

#define ENABLE_SX1250

#ifdef ENABLE_SX1250
#define RSSI_OFFSET         (-215.4)
#define RSSI_TCOMP_COEFF_A  (0)
#define RSSI_TCOMP_COEFF_B  (0)
#define RSSI_TCOMP_COEFF_C  (20.41)
#define RSSI_TCOMP_COEFF_D  (2162.56)
#define RSSI_TCOMP_COEFF_E  (0)
#endif

// Frequency plan for EU868

#define FREQ_A_EU868  (867500000u)
#define FREQ_B_EU868  (868500000u)

#define CHANNEL_IF_MODE {\
    -400000,\
    -200000,\
    0,\
    -400000,\
    -200000,\
    0,\
    200000,\
    400000,\
    -200000\
}\

#define CHANNEL_RFCHAIN_MODE { 1, 1, 1, 0, 0, 0, 0, 0, 1 }\

// Listen

#ifndef MAX_RX_PKT
#define MAX_RX_PKT  4
#endif

#ifndef LGW_PERIOD_CB_PERIOD
#define LGW_PERIOD_CB_PERIOD (60000U)
#endif

#endif