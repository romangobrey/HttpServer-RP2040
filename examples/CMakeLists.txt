set(TARGET_NAME main)
set(TARGET_FILES
    custom_hsm_x509.c
    iothub_ll_c2d_sample.c
    iothub_ll_client_x509_sample.c
    iothub_ll_telemetry_sample.c    
    ${TARGET_NAME}.c
    prov_dev_client_ll_sample.c
    sample_certs.c
    )

add_executable(${TARGET_NAME} ${TARGET_FILES})

target_include_directories(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${TARGET_NAME} PRIVATE
        pico_stdlib
        hardware_spi
        ETHERNET_FILES
        IOLIBRARY_FILES
        DHCP_FILES
        DNS_FILES
        TIMER_FILES
        AZURE_SDK_PORT_FILES
        mbedcrypto
        mbedx509
        mbedtls
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${TARGET_NAME})
