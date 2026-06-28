/*
 Thingsat Basic Mission
 Copyright (c) 2021-2026 UGA CSUG LIG

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

#include <stdint.h>
#include <stdbool.h>

#include "container.h"
#include "networks.h"

/*
 * Author : Didier Donsez, Université Grenoble Alpes
 */

typedef struct Network
{
	/*
	 * @brief DevAddr (if devaddr_subnet == NOT_ENDPOINT_ENTRY), the entry should not be used.
	 */
	uint32_t devaddr_subnet;

	/*
	 * @brief Mask of the DevAddr
	 */
	uint32_t devaddr_mask;
//
//	/*
//	 * @brief Repeat RX packets
//	 */
//	bool	 repeat;
//
//	/*
//	 * @brief Store RX packets into files for transfert to the ground segment
//	 */
//	bool	 store;
//
//	/*
//	 * @brief Name of the network (for debugging)
//	 */
//	char*	 name;
//

} Network_t;

static const Network_t networks[] = THINGSAT_PARTNERS_NETWORKS;

bool network_check_devaddr(const uint32_t devaddr) {

    for (uint8_t n = 0; n < ARRAY_SIZE(networks); n++) {
        const Network_t *network = networks + n;
        if (IS_BELONGING_TO_NETWORK(devaddr,network->devaddr_subnet, network->devaddr_mask)) {
            return true;
        }
    }
    return false;
}