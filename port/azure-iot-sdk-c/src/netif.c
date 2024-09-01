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
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#include "pico/stdlib.h"

#include "netif.h"

#include "dhcp.h"
#include "dns.h"
#include "sntp.h"

/**
 * ----------------------------------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------------------------------
 */
/* Buffer */
#define ETHERNET_BUF_MAX_SIZE (1024 * 2)

/* Socket */
#define SOCKET_DHCP 2
#define SOCKET_DNS 3

/* SNTP */
#define SNTP_SERVER_ADDRESS "pool.ntp.org"
#define TIMEZONE 40 // Korea

/* Retry count */
#define DHCP_RETRY_COUNT 5

/**
 * ----------------------------------------------------------------------------------------------------
 * Variables
 * ----------------------------------------------------------------------------------------------------
 */
/* Network */
static uint8_t g_ethernet_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
}; // common buffer
static wiz_NetInfo *g_net_info;

/* DHCP */
static uint8_t g_dhcp_get_ip_flag = 0;

/* SNTP */
static uint8_t g_sntp_server_ip[4] = {
    0,
};

/**
 * ----------------------------------------------------------------------------------------------------
 * Functions
 * ----------------------------------------------------------------------------------------------------
 */
//--------------------------------------------------
// Static functions
//--------------------------------------------------
static void print_network_information(void);
static void wizchip_dhcp_init(void);
static void wizchip_dhcp_cb_assign(void);
static void wizchip_dhcp_cb_conflict(void);

/* Network */
int8_t wizchip_network_initialize(bool bDHCP, wiz_NetInfo *netinfo)
{
    int8_t ret = -1;
    g_net_info = netinfo;

    if (bDHCP) // DHCP
    {
        g_net_info->dhcp = NETINFO_DHCP;

        wizchip_dhcp_init();

        ret = wizchip_dhcp_run();
    }
    else // static
    {
        g_net_info->dhcp = NETINFO_STATIC;

        /* Network initialize */
        ctlnetwork(CN_SET_NETINFO, (void *)g_net_info);

        /* Get network information */
        print_network_information();

        ret = 1;
    }

    return ret;
}

/* DHCP */
uint8_t wizchip_dhcp_run(void)
{
    uint8_t retval = 0;
    uint8_t dhcp_retry = 0;

    while (1)
    {
        retval = DHCP_run();

        if (retval == DHCP_IP_LEASED)
        {
            if (g_dhcp_get_ip_flag == 0)
            {
                printf(" DHCP success\n");

                g_dhcp_get_ip_flag = 1;
            }

            close(SOCKET_DHCP);

            break;
        }
        else if (retval == DHCP_FAILED)
        {
            dhcp_retry++;

            if (dhcp_retry <= DHCP_RETRY_COUNT)
            {
                printf(" DHCP timeout occurred and retry %d\n", dhcp_retry);
            }
        }

        if (dhcp_retry > DHCP_RETRY_COUNT)
        {
            printf(" DHCP failed. Need to restart DHCP client.\n");

            DHCP_stop();

            g_dhcp_get_ip_flag = 0;
            retval = -1;

            break;
        }

        sleep_ms(1000); // wait for 1 second
    }

    return retval;
}

void wizchip_dhcp_time_handler(void)
{
    DHCP_time_handler();
}

/* DNS */
uint8_t wizchip_gethostbyname(const char *host, uint8_t *ip)
{
    uint8_t ret = 0;

    if (host[0] == '\0')
    {
        ret = -1;
    }
    else
    {
        DNS_init(SOCKET_DNS, g_ethernet_buf);
        ret = DNS_run(g_net_info->dns, (uint8_t *)host, ip);
        //  * @return  -1 : failed. @ref MAX_DOMIN_NAME is too small \n
        //  *           0 : failed  (Timeout or Parse error)\n
        //  *           1 : success

        if (ret)
        {
            printf(" DNS success\n");
            printf(" DNS target domain : %s\n", host);
            printf(" DNS IP of target domain : %d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
        }
        else
        {
            printf(" DNS failed\n");
        }
    }

    return ret;
}

/* SNTP */
void wizchip_sntp_init(void)
{
    printf(" Initializing SNTP\n");

    int rc = 0;

    rc = wizchip_gethostbyname(SNTP_SERVER_ADDRESS, g_sntp_server_ip);

    if (rc)
    {
        printf(" Getting SNTP server pool.ntp.org ip: %d.%d.%d.%d\n", g_sntp_server_ip[0], g_sntp_server_ip[1], g_sntp_server_ip[2], g_sntp_server_ip[3]);
    }
    else
    {
        printf(" Fail to getting SNTP server, set the time.google.com 216.239.35.8\n");

        // temporary assign - time.google.com
        g_sntp_server_ip[0] = 216;
        g_sntp_server_ip[1] = 239;
        g_sntp_server_ip[2] = 35;
        g_sntp_server_ip[3] = 8;
    }

    SNTP_init(SOCKET_DNS, g_sntp_server_ip, TIMEZONE, g_ethernet_buf);
/*
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
*/
}

// #define TIMEZONE 40 // Korea
// static uint8_t g_sntp_server_ip[4] = {216, 239, 35, 8}; // time.google.com
time_t wizchip_sntp_get_current_timestamp(void)
{
    uint32_t retval = 0;
    uint8_t loopcnt = 0;

    /* Get time */
    do
    {
        retval = SNTP_get_current_timestamp();

        sleep_ms(100);

        loopcnt++;
    } while (retval == 0 && loopcnt < 20);

    return (time_t)retval;
}

//--------------------------------------------------
// Static functions
//--------------------------------------------------
/* Network */
static void print_network_information(void)
{
    uint8_t tmp_str[8] = {
        0,
    };

    ctlnetwork(CN_GET_NETINFO, (void *)g_net_info);
    ctlwizchip(CW_GET_ID, (void *)tmp_str);

    printf("====================================================================================================\n");
    if (g_net_info->dhcp == NETINFO_DHCP)
    {
        printf(" %s network configuration : DHCP\n\n", (char *)tmp_str);
    }
    else
    {
        printf(" %s network configuration : static\n\n", (char *)tmp_str);
    }
    printf(" MAC         : %02X:%02X:%02X:%02X:%02X:%02X\n", g_net_info->mac[0], g_net_info->mac[1], g_net_info->mac[2], g_net_info->mac[3], g_net_info->mac[4], g_net_info->mac[5]);
    printf(" IP          : %d.%d.%d.%d\n", g_net_info->ip[0], g_net_info->ip[1], g_net_info->ip[2], g_net_info->ip[3]);
    printf(" Subnet Mask : %d.%d.%d.%d\n", g_net_info->sn[0], g_net_info->sn[1], g_net_info->sn[2], g_net_info->sn[3]);
    printf(" Gateway     : %d.%d.%d.%d\n", g_net_info->gw[0], g_net_info->gw[1], g_net_info->gw[2], g_net_info->gw[3]);
    printf(" DNS         : %d.%d.%d.%d\n", g_net_info->dns[0], g_net_info->dns[1], g_net_info->dns[2], g_net_info->dns[3]);
    printf("====================================================================================================\n\n");
}
/* DHCP */
static void wizchip_dhcp_init(void)
{
    printf(" DHCP client running\n");

    DHCP_init(SOCKET_DHCP, g_ethernet_buf);

    reg_dhcp_cbfunc(wizchip_dhcp_cb_assign, wizchip_dhcp_cb_assign, wizchip_dhcp_cb_conflict);
}

static void wizchip_dhcp_cb_assign(void)
{
    getIPfromDHCP(g_net_info->ip);
    getGWfromDHCP(g_net_info->gw);
    getSNfromDHCP(g_net_info->sn);
    getDNSfromDHCP(g_net_info->dns);

    g_net_info->dhcp = NETINFO_DHCP;

    /* Network initialize */
    ctlnetwork(CN_SET_NETINFO, (void *)g_net_info);

    print_network_information();
    printf(" DHCP leased time : %ld seconds\n", getDHCPLeasetime());
}

static void wizchip_dhcp_cb_conflict(void)
{
    printf(" Conflict IP from DHCP. Need to restart DHCP client.\n");
}
