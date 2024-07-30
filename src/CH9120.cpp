#include "CH9120.h"

UCHAR CH9120_MODE = TCP_SERVER;                   // Optional:TCP_SERVER、TCP_CLIENT、UDP_SERVER、UDP_CLIENT
UCHAR CH9120_LOCAL_IP[4] = {192, 168, 1, 2};      // LOCAL IP
UCHAR CH9120_GATEWAY[4] = {192, 168, 1, 1};       // GATEWAY
UCHAR CH9120_SUBNET_MASK[4] = {255, 255, 255, 0}; // SUBNET MASK
UCHAR CH9120_TARGET_IP[4] = {192, 168, 88, 254};  // TARGET_IP
UWORD CH9120_LOCAL_PORT = 80;                     // LOCAL PORT1
UWORD CH9120_TARGET_PORT = 8888;                  // TARGET PORT
UDOUBLE CH9120_BAUD_RATE = 115200;                // BAUD RATE
UBYTE CH9120_DHCP = 1;                            // DHCP (0 - Disabled, 1 - Enabled)

UCHAR tx[8] = {0x57, 0xAB};

/**
 * Sends four bytes to CH9120 (Set mode, enable port, clear serial port, switch DHCP, switch port 2)
 *
 * @param data data to transmit
 * @param command command to transmit
 * @return void
 */
void CH9120_Tx4Bytes(UCHAR data, int command)
{
  for (int i = 2; i < 4; i++)
  {
    if (i == 2)
      tx[i] = command;
    else
      tx[i] = data;
  }
  delay(10);
  for (int o = 0; o < 4; o++)
    UART_ID1.write(tx[o]);
  delay(10);
  for (int i = 2; i < 4; i++)
    tx[i] = 0;
}

/**
 * Sends five bytes to CH9120 (Set the local port and target port)
 *
 * @param data data to transmit
 * @param command command to transmit
 * @return void
 */
void CH9120_Tx5Bytes(UWORD data, int command)
{
  UCHAR Port[2];
  Port[0] = data & 0xff;
  Port[1] = data >> 8;
  for (int i = 2; i < 5; i++)
  {
    if (i == 2)
      tx[i] = command;
    else
      tx[i] = Port[i - 3];
  }
  delay(10);
  for (int o = 0; o < 5; o++)
    UART_ID1.write(tx[o]);
  delay(10);
  for (int i = 2; i < 5; i++)
    tx[i] = 0;
}

/**
 * Sends seven bytes to CH9120 (Set the IP address, subnet mask, gateway)
 *
 * @param data data to transmit
 * @param command command to transmit
 * @return void
 */
void CH9120_Tx7Bytes(UCHAR data[], int command)
{
  for (int i = 2; i < 7; i++)
  {
    if (i == 2)
      tx[i] = command;
    else
      tx[i] = data[i - 3];
  }
  delay(10);
  for (int o = 0; o < 7; o++)
    UART_ID1.write(tx[o]);
  delay(10);
  for (int i = 2; i < 7; i++)
    tx[i] = 0;
}

/**
 * Sends data to CH9120 (Set baud rate)
 *
 * @param data data to transmit
 * @param command command to transmit
 * @return void
 */
void CH9120_TxBaud(UDOUBLE data, int command)
{
  UCHAR Port[4];
  Port[0] = (data & 0xff);
  Port[1] = (data >> 8) & 0xff;
  Port[2] = (data >> 16) & 0xff;
  Port[3] = data >> 24;

  for (int i = 2; i < 7; i++)
  {
    if (i == 2)
      tx[i] = command;
    else
      tx[i] = Port[i - 3];
  }
  delay(10);
  for (int o = 0; o < 7; o++)
    UART_ID1.write(tx[o]);
  delay(10);
  for (int i = 2; i < 7; i++)
    tx[i] = 0;
}

/**
 * Starts receiving configuration parameters
 *
 * @return void
 */
void CH9120_StartConfig()
{
  digitalWrite(CFG_PIN, 0);
  digitalWrite(RES_PIN, 1);
  delay(500);
}

/**
 * Ends receiving configuration parameters
 *
 * @return void
 */
void CH9120_EndConfig()
{
  tx[2] = 0x0d;
  for (int o = 0; o < 3; o++)
    UART_ID1.write(tx[o]);
  delay(200);
  tx[2] = 0x0e;
  for (int o = 0; o < 3; o++)
    UART_ID1.write(tx[o]);
  delay(200);
  tx[2] = 0x5e;
  for (int o = 0; o < 3; o++)
    UART_ID1.write(tx[o]);
  delay(500);
  gpio_put(CFG_PIN, 1);
}

/**
 * Sets CH9120 mode (is set internally, will be sent to CH9120 on init)
 *
 * @param mode
 * @return void
 */
void CH9120_SetMode(ModeType mode)
{
  CH9120_Tx4Bytes(CH9120_MODE, MODE1);
  delay(100);

  switch (mode)
  {
  case TcpServerMode:
    CH9120_MODE = TCP_SERVER;
    break;
  case TcpClientMode:
    CH9120_MODE = TCP_CLIENT;
    break;
  case UdpServerMode:
    CH9120_MODE = UDP_SERVER;
    break;
  case UdpClientMode:
    CH9120_MODE = UDP_CLIENT;
    break;
  default:
    CH9120_MODE = TCP_SERVER;
    break;
  }
}

/**
 * Sets local ip (is set internally, will be sent to CH9120 on init)
 *
 * @param value
 * @return void
 */
void CH9120_SetLocalIp(UCHAR value[4])
{
  CH9120_LOCAL_IP[0] = value[0];
  CH9120_LOCAL_IP[1] = value[1];
  CH9120_LOCAL_IP[2] = value[2];
  CH9120_LOCAL_IP[3] = value[3];
}

/**
 * Sets subnet mask (is set internally, will be sent to CH9120 on init)
 *
 * @param value
 * @return void
 */
void CH9120_SetSubnetMask(UCHAR value[4])
{
  CH9120_SUBNET_MASK[0] = value[0];
  CH9120_SUBNET_MASK[1] = value[1];
  CH9120_SUBNET_MASK[2] = value[2];
  CH9120_SUBNET_MASK[3] = value[3];
}

/**
 * Sets gateway (is set internally, will be sent to CH9120 on init)
 *
 * @param value
 * @return void
 */
void CH9120_SetGateway(UCHAR value[4])
{
  CH9120_GATEWAY[0] = value[0];
  CH9120_GATEWAY[1] = value[1];
  CH9120_GATEWAY[2] = value[2];
  CH9120_GATEWAY[3] = value[3];
}

/**
 * Sets target ip (is set internally, will be sent to CH9120 on init)
 *
 * @param value
 * @return void
 */
void CH9120_SetTargetIp(UCHAR value[4])
{
  CH9120_TARGET_IP[0] = value[0];
  CH9120_TARGET_IP[1] = value[1];
  CH9120_TARGET_IP[2] = value[2];
  CH9120_TARGET_IP[3] = value[3];
}

/**
 * Sets local port (is set internally, will be sent to CH9120 on init)
 *
 * @param value
 * @return void
 */
void CH9120_SetLocalPort(UWORD value)
{
  CH9120_LOCAL_PORT = value;
}

/**
 * Sets target port (is set internally, will be sent to CH9120 on init)
 *
 * @param value
 * @return void
 */
void CH9120_SetTargetPort(UWORD value)
{
  CH9120_TARGET_PORT = value;
}

/**
 * Sets baud rate (is set internally, will be sent to CH9120 on init)
 *
 * @param value
 * @return void
 */
void CH9120_SetBaudRate(UDOUBLE value)
{
  CH9120_BAUD_RATE = value;
}

/**
 * Sets DHCP mode (is set internally, will be sent to CH9120 on init)
 *
 * @param value
 * @return void
 */
void CH9120_SetDhcpMode(UBYTE value)
{
  CH9120_DHCP = value;
}

/**
 * Sends mode to CH9120 (was set internally or default, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxMode()
{
  CH9120_Tx4Bytes(CH9120_MODE, MODE1);
  delay(100);
}

/**
 * Sends local ip to CH9120 (was set internally or default, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxLocalIp()
{
  CH9120_Tx7Bytes(CH9120_LOCAL_IP, LOCAL_IP);
  delay(100);
}

/**
 * Sends subnet mask to CH9120 (was set internally or default, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxSubnetMask()
{
  CH9120_Tx7Bytes(CH9120_SUBNET_MASK, SUBNET_MASK);
  delay(100);
}

/**
 * Sends gateway to CH9120 (was set internally or default, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxGateway()
{
  CH9120_Tx7Bytes(CH9120_GATEWAY, GATEWAY);
  delay(100);
}

/**
 * Sends target ip to CH9120 (was set internally or default, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxTargetIp()
{
  CH9120_Tx7Bytes(CH9120_TARGET_IP, TARGET_IP1);
  delay(100);
}

/**
 * Sends local port to CH9120 (was set internally, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxLocalPort()
{
  CH9120_Tx5Bytes(CH9120_LOCAL_PORT, LOCAL_PORT1); // Local port
  delay(100);
}

/**
 * Sends target port to CH9120 (was set internally, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxTargetPort()
{
  CH9120_Tx5Bytes(CH9120_TARGET_PORT, TARGET_PORT1);
  delay(100);
}

/**
 * Sends baud rate to CH9120 (was set internally, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxBaudRate()
{
  CH9120_TxBaud(CH9120_BAUD_RATE, UART1_BAUD1);
  delay(100);
}

/**
 * Sends DHCP mode to CH9120 (was set internally, is sent to CH9120 now)
 *
 * @return void
 */
void CH9120_TxDhcpMode()
{
  CH9120_Tx4Bytes(CH9120_DHCP, ALLOWDHCP);
  delay(100);
}

/**
 * Initialize CH9120
 *
 * @return void
 */
void CH9120_Init()
{
  delay(1000);

  UART_ID1.setTX(UART_TX_PIN1);
  UART_ID1.setRX(UART_RX_PIN1);
  UART_ID1.begin(INTI_BAUD_RATE);

  pinMode(CFG_PIN, OUTPUT);
  pinMode(RES_PIN, OUTPUT);

  CH9120_StartConfig();
  CH9120_TxMode();
  CH9120_TxLocalIp();
  CH9120_TxGateway();
  CH9120_TxSubnetMask();
  CH9120_TxLocalPort();
  CH9120_TxBaudRate();
  CH9120_TxTargetIp();
  CH9120_TxTargetPort();
  CH9120_TxDhcpMode();
  CH9120_EndConfig();

  UART_ID1.begin(TRANSPORT_BAUD_RATE);
  UART_ID1.setTimeout(5);
}
