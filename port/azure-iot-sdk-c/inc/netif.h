// Copyright (c) WIZnet. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// CAVEAT: This sample is to demonstrate azure IoT client concepts only and is not a guide design principles or style
// Checking of return codes and error values shall be omitted for brevity.  Please practice sound engineering practices
// when writing production code.

/**
 * ----------------------------------------------------------------------------------------------------
 * Includes
 * ----------------------------------------------------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

#include "wizchip_conf.h"
#include "socket.h"

/**
 * ----------------------------------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------------------------------
 */

/**
 * ----------------------------------------------------------------------------------------------------
 * Functions
 * ----------------------------------------------------------------------------------------------------
 */
/* Network */
int8_t wizchip_network_initialize(bool bDHCP, wiz_NetInfo *netinfo);

/* DHCP */
uint8_t wizchip_dhcp_run(void);
void wizchip_dhcp_time_handler(void);

/* DNS */
uint8_t wizchip_gethostbyname(const char *host, uint8_t *ip);

/* SNTP */
void wizchip_sntp_init(void);
time_t wizchip_sntp_get_current_timestamp(void);
