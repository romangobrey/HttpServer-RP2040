# HttpServer

## Description
HTTP Server implementation for some ethernet devices.
Check the list of supported hardware devices, using other hardware might have unpredictable results.
It supports HTTP only.

### Hardware requirements
- Waveshare RP2040-ETH (TCP/IP controller CH9120)
- Wiznet W5500-EVB-Pico (TCP/IP controller W5500)

## Dependencies
The library uses "arduino-libraries/Ethernet" when W5500 is used.