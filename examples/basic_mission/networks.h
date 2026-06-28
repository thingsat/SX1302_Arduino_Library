/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 UGA CSUG LIG

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

/*
 * Author : Didier Donsez, Université Grenoble Alpes
 */

 /*
 * LoRaWAN Networks constants for the Thingsat LoRa experiments
 *
 * Used for the configuration of Network_t.
 * See https://www.thethingsnetwork.org/docs/lorawan/prefix-assignments/
 */


#ifndef _BASIC_MISSION_NETWORKS_H_
#define _BASIC_MISSION_NETWORKS_H_

// DevAddr mask = (top address XOR top address) XOR 0xFFFFFFFF

#define DEVADDR_MASK_UNASSIGNED							(0xFFFFFFFF)
#define DEVADDR_MASK_ALL								(0x00000000)
#define DEVADDR_MASK_NETID1								(0xFE000000)
#define DEVADDR_MASK_NETID3								(0xFFFE0000)
#define DEVADDR_MASK_NETID6								(0xFFFFFC00)

// DevAddr base address

#define DEVADDR_BASE_UNASSIGNED							(0xFFFFFFFF)
#define DEVADDR_BASE_ALL								(0x00000000)
// CampusIoT NetId 6 (FC00AC00 - FC00AFFF)
#define DEVADDR_BASE_CAMPUSIOT							(0xFC00AC00)
// TTN NetID 1 (26000000 - 27FFFFFF)
#define DEVADDR_BASE_TTN								(0x26000000)
// Helium NetID 1 (48000000 - 49FFFFFF) // TO BE CONFIRMED
#define DEVADDR_BASE_HELIUM								(0x48000000)
// Actility NetID 1 (04000000 - 05FFFFFF)
#define DEVADDR_BASE_ACTILITY							(0x04000000)
// Orange NetID 1 (1E000000 - 1FFFFFFF)
#define DEVADDR_BASE_ORANGE								(0x1E000000)
// Bouygues Telecom NetID 1 (0E000000 - 0FFFFFFF)
#define DEVADDR_BASE_BOUYGUES_TELECOM					(0x0E000000)
// Requea NetId 6 (FC006800 - FC006BFF)
#define DEVADDR_BASE_REQUEA								(0xFC006800)

// TODO add Netmore

// Swisscom NetID 1 (08000000 - 09FFFFFF)
#define DEVADDR_BASE_SWISSCOM							(0x08000000)
// KPN NetID 1 (2A000000 - 2BFFFFFF)
#define DEVADDR_BASE_KPN								(0x2A000000)
// Digita NetID 3 (E0020000 - E003FFFF)
#define DEVADDR_BASE_DIGITA								(0xE0020000)

// TATA Communication NetID 1(22000000 - 23FFFFFF)
#define DEVADDR_BASE_TATA_COMMUNICATIONS				(0x22000000)

// Lacuna NetId 6 (FC00A000 - FC00A3FF)
#define DEVADDR_BASE_LACUNA								(0xFC00A000)
// Hiber NetId 6 (FC008400 - FC0087FF)
#define DEVADDR_BASE_HIBER								(0xFC008400)

// Multitech NetID 1 (2E000000 - 2FFFFFFF)
#define DEVADDR_BASE_MULTITECH							(0x2E000000)
// Schneider Electric NetID 3 (E02E0000 - E02FFFFF)
#define DEVADDR_BASE_SCHNEIDER_ELECTRIC					(0xE02E0000)
// Kerlink NetID 1 (24000000 - 25FFFFFF)
#define DEVADDR_BASE_KERLINK							(0x24000000)


#define	ALL_NETWORKS { \
						{ DEVADDR_BASE_ALL, DEVADDR_MASK_ALL}, \
				}


// Field 1 = base address
// Field 2 = devaddr mask = (top address XOR top address) XOR 0xFFFFFFFF
#define	THINGSAT_PARTNERS_NETWORKS			{ \
						{ DEVADDR_BASE_CAMPUSIOT, DEVADDR_MASK_NETID6}, \
						{ DEVADDR_BASE_TTN, DEVADDR_MASK_NETID1}, \
						{ DEVADDR_BASE_HELIUM, DEVADDR_MASK_NETID1}, \
 \
						{ DEVADDR_BASE_ACTILITY, DEVADDR_MASK_NETID1}, \
						{ DEVADDR_BASE_ORANGE, DEVADDR_MASK_NETID1}, \
						{ DEVADDR_BASE_BOUYGUES_TELECOM, DEVADDR_MASK_NETID1}, \
						{ DEVADDR_BASE_REQUEA, DEVADDR_MASK_NETID6}, \
 \
						{ DEVADDR_BASE_SWISSCOM, DEVADDR_MASK_NETID1}, \
						{ DEVADDR_BASE_KPN, DEVADDR_MASK_NETID1}, \
						{ DEVADDR_BASE_LACUNA, DEVADDR_MASK_NETID6}, \
						{ DEVADDR_BASE_HIBER, DEVADDR_MASK_NETID6}, \
 \
						{ DEVADDR_BASE_TATA_COMMUNICATIONS, DEVADDR_MASK_NETID1}, \
						{ DEVADDR_BASE_MULTITECH, DEVADDR_MASK_NETID1}, \
						{ DEVADDR_BASE_SCHNEIDER_ELECTRIC, DEVADDR_MASK_NETID3}, \
						{ DEVADDR_BASE_KERLINK, DEVADDR_MASK_NETID1}, \
				}


/**
 * @brief Macro for check if a DevAddr is into a network
 * A special case is devaddr_subnet=0x00000000 and devaddr_mask=0x00000000, all ground networks are monitored
 * A special case is devaddr_subnet=0xFFFFFFFF and devaddr_mask=0xFFFFFFFF, non ground networks are monitored
 */
#define IS_BELONGING_TO_NETWORK(devaddr,devaddr_subnet,devaddr_mask) ( devaddr_subnet == ( devaddr & devaddr_mask ))

bool network_check_devaddr(const uint32_t devaddr);

#endif
