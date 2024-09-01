# Ethernet
add_library(ETHERNET_FILES STATIC)

target_sources(ETHERNET_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet/socket.c
        ${WIZNET_DIR}/Ethernet/wizchip_conf.c
        )

if(${WIZNET_CHIP} STREQUAL W5100S)
target_include_directories(ETHERNET_FILES INTERFACE
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Ethernet/W5100S
        )

target_link_libraries(ETHERNET_FILES PUBLIC
        W5100S_FILES
        )
elseif(${WIZNET_CHIP} STREQUAL W5500)
target_include_directories(ETHERNET_FILES INTERFACE
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Ethernet/W5500
        )

target_link_libraries(ETHERNET_FILES PUBLIC
        W5500_FILES
        )
endif()

if(${WIZNET_CHIP} STREQUAL W5100S)
add_library(W5100S_FILES STATIC)

target_sources(W5100S_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet/W5100S/w5100s.c
        )

target_include_directories(W5100S_FILES INTERFACE
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Ethernet/W5100S
        )

target_link_libraries(W5100S_FILES PRIVATE
        ETHERNET_FILES
        )
elseif(${WIZNET_CHIP} STREQUAL W5500)
add_library(W5500_FILES STATIC)

target_sources(W5500_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet/W5500/w5500.c
        )

target_include_directories(W5500_FILES INTERFACE
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Ethernet/W5500
        )

target_link_libraries(W5500_FILES PRIVATE
        ETHERNET_FILES
        )
endif()

# Loopback
add_library(LOOPBACK_FILES STATIC)

target_sources(LOOPBACK_FILES PUBLIC
        ${WIZNET_DIR}/Application/loopback/loopback.c
        )

target_include_directories(LOOPBACK_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Application/loopback
        )

# DHCP
add_library(DHCP_FILES STATIC)

target_sources(DHCP_FILES PUBLIC
        ${WIZNET_DIR}/Internet/DHCP/dhcp.c
        )

target_include_directories(DHCP_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/DHCP
        )

# DNS
add_library(DNS_FILES STATIC)

target_sources(DNS_FILES PUBLIC
        ${WIZNET_DIR}/Internet/DNS/dns.c
        )

target_include_directories(DNS_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/DNS
        )

# FTP Client
add_library(FTPCLIENT_FILES STATIC)

target_sources(FTPCLIENT_FILES PUBLIC
        ${WIZNET_DIR}/Internet/FTPClient/ftpc.c
        )

target_include_directories(FTPCLIENT_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/FTPClient
        )

# FTP Server
add_library(FTPSERVER_FILES STATIC)

target_sources(FTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Internet/FTPServer/ftpd.c
        )

target_include_directories(FTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/FTPServer
        )

# HTTP Server
add_library(HTTPSERVER_FILES STATIC)

target_sources(HTTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Internet/httpServer/httpParser.c
        ${WIZNET_DIR}/Internet/httpServer/httpServer.c
        ${WIZNET_DIR}/Internet/httpServer/httpUtil.c
        )

target_include_directories(HTTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/httpServer
        )

# MQTT
add_library(MQTT_FILES STATIC)

target_sources(MQTT_FILES PUBLIC
        ${WIZNET_DIR}/Internet/MQTT/mqtt_interface.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTClient.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTFormat.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTPacket.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c
        )

target_include_directories(MQTT_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/MQTT
        ${WIZNET_DIR}/Internet/MQTTPacket/src
        ) 

# SNTP
add_library(SNTP_FILES STATIC)

target_sources(SNTP_FILES PUBLIC
        ${WIZNET_DIR}/Internet/SNTP/sntp.c
        )

target_include_directories(SNTP_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/SNTP
        )

target_link_libraries(SNTP_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )

# AZURE SDK
add_library(AZURE_SDK_FILES STATIC)

target_sources(AZURE_SDK_FILES PUBLIC
        ${AZURE_SDK_DIR}/c-utility/adapters/socketio_mbed.c
        ${AZURE_SDK_DIR}/c-utility/adapters/httpapi_compact.c
        ${AZURE_SDK_DIR}/certs/certs.c
        ${AZURE_SDK_DIR}/c-utility/pal/tlsio_options.c
        ${AZURE_SDK_DIR}/c-utility/src/xlogging.c
        ${AZURE_SDK_DIR}/c-utility/src/singlylinkedlist.c
        ${AZURE_SDK_DIR}/c-utility/src/buffer.c
        ${AZURE_SDK_DIR}/c-utility/src/consolelogger.c
        ${AZURE_SDK_DIR}/c-utility/src/constbuffer.c
        ${AZURE_SDK_DIR}/c-utility/src/constmap.c
        ${AZURE_SDK_DIR}/c-utility/src/crt_abstractions.c
        ${AZURE_SDK_DIR}/c-utility/src/doublylinkedlist.c
        ${AZURE_SDK_DIR}/c-utility/src/gballoc.c
        ${AZURE_SDK_DIR}/c-utility/src/gb_stdio.c
        ${AZURE_SDK_DIR}/c-utility/src/gb_time.c
        ${AZURE_SDK_DIR}/c-utility/src/hmac.c
        ${AZURE_SDK_DIR}/c-utility/src/hmacsha256.c
        ${AZURE_SDK_DIR}/c-utility/src/httpapiex.c
        ${AZURE_SDK_DIR}/c-utility/src/httpapiexsas.c
        ${AZURE_SDK_DIR}/c-utility/src/httpheaders.c
        ${AZURE_SDK_DIR}/c-utility/src/map.c
        ${AZURE_SDK_DIR}/c-utility/src/optionhandler.c
        ${AZURE_SDK_DIR}/c-utility/src/sastoken.c
        ${AZURE_SDK_DIR}/c-utility/src/sha1.c
        ${AZURE_SDK_DIR}/c-utility/src/sha224.c
        ${AZURE_SDK_DIR}/c-utility/src/sha384-512.c
        ${AZURE_SDK_DIR}/c-utility/src/strings.c
        ${AZURE_SDK_DIR}/c-utility/src/string_token.c
        ${AZURE_SDK_DIR}/c-utility/src/string_tokenizer.c
        ${AZURE_SDK_DIR}/c-utility/src/urlencode.c
        ${AZURE_SDK_DIR}/c-utility/src/usha.c
        ${AZURE_SDK_DIR}/c-utility/src/vector.c
        ${AZURE_SDK_DIR}/c-utility/src/xio.c
        ${AZURE_SDK_DIR}/c-utility/src/azure_base64.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothubtransport_mqtt_common.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_device_client_ll.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_client_ll.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_client_core_ll.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_client_ll_uploadtoblob.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_client_authorization.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_client_retry_control.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_client_diagnostic.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_message.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothubtransport.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothubtransportmqtt.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothubtransporthttp.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothubtransport_mqtt_common.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub_transport_ll_private.c
        ${AZURE_SDK_DIR}/iothub_client/src/version.c
        ${AZURE_SDK_DIR}/umqtt/src/mqtt_client.c
        ${AZURE_SDK_DIR}/umqtt/src/mqtt_codec.c
        ${AZURE_SDK_DIR}/umqtt/src/mqtt_message.c
        ${AZURE_SDK_DIR}/deps/parson/parson.c
        ${AZURE_SDK_DIR}/serializer/src/codefirst.c
        ${AZURE_SDK_DIR}/serializer/src/agenttypesystem.c
        ${AZURE_SDK_DIR}/serializer/src/commanddecoder.c
        ${AZURE_SDK_DIR}/serializer/src/datamarshaller.c
        ${AZURE_SDK_DIR}/serializer/src/datapublisher.c
        ${AZURE_SDK_DIR}/serializer/src/dataserializer.c
        ${AZURE_SDK_DIR}/serializer/src/iotdevice.c
        ${AZURE_SDK_DIR}/serializer/src/jsondecoder.c
        ${AZURE_SDK_DIR}/serializer/src/jsonencoder.c
        ${AZURE_SDK_DIR}/serializer/src/methodreturn.c
        ${AZURE_SDK_DIR}/serializer/src/multitree.c
        ${AZURE_SDK_DIR}/serializer/src/schema.c
        ${AZURE_SDK_DIR}/serializer/src/schemalib.c
        ${AZURE_SDK_DIR}/serializer/src/schemaserializer.c
        ${AZURE_SDK_DIR}/iothub_client/src/iothub.c
        ${AZURE_SDK_DIR}/c-utility/src/http_proxy_io.c
        ${AZURE_SDK_DIR}/c-utility/src/azure_base32.c
        ${AZURE_SDK_DIR}/provisioning_client/src/prov_device_client.c
        ${AZURE_SDK_DIR}/provisioning_client/src/prov_transport_mqtt_client.c
        ${AZURE_SDK_DIR}/provisioning_client/src/prov_transport_mqtt_common.c
        ${AZURE_SDK_DIR}/provisioning_client/src/prov_security_factory.c
        ${AZURE_SDK_DIR}/provisioning_client/src/prov_device_ll_client.c
        ${AZURE_SDK_DIR}/provisioning_client/src/iothub_security_factory.c
        ${AZURE_SDK_DIR}/provisioning_client/src/iothub_auth_client.c
        ${AZURE_SDK_DIR}/provisioning_client/src/prov_auth_client.c
        ${AZURE_SDK_DIR}/provisioning_client/adapters/hsm_client_data.c
        ${AZURE_SDK_DIR}/provisioning_client/deps/utpm/src/tpm_codec.c
        ${AZURE_SDK_DIR}/provisioning_client/deps/utpm/src/Marshal.c
        ${AZURE_SDK_DIR}/provisioning_client/deps/utpm/src/tpm_comm_emulator.c
        ${AZURE_SDK_DIR}/provisioning_client/deps/utpm/src/Memory.c
        )

target_include_directories(AZURE_SDK_FILES PUBLIC
        ${AZURE_SDK_DIR}/certs
        ${AZURE_SDK_DIR}/c-utility/inc
        ${AZURE_SDK_DIR}/c-utility/deps/azure-macro-utils-c/inc
        ${AZURE_SDK_DIR}/c-utility/deps/umock-c/inc
        ${AZURE_SDK_DIR}/c-utility/pal/inc
        ${AZURE_SDK_DIR}/c-utility/pal/freertos
        ${AZURE_SDK_DIR}/c-utility/pal/generic
        ${AZURE_SDK_DIR}/iothub_client/inc
        ${AZURE_SDK_DIR}/umqtt/inc
        ${AZURE_SDK_DIR}/umqtt/inc/azure_umqtt_c
        ${AZURE_SDK_DIR}/serializer/inc
        ${AZURE_SDK_DIR}/deps/azure-macro-utils-c/inc
        ${AZURE_SDK_DIR}/deps/parson
        ${AZURE_SDK_DIR}/deps/umock-c/inc
        ${AZURE_SDK_DIR}/provisioning_client/inc
        ${AZURE_SDK_DIR}/provisioning_client/adapters
        ${AZURE_SDK_DIR}/provisioning_client/deps/utpm/inc
        ${PORT_DIR}/azure-iot-sdk-c/inc
        )
