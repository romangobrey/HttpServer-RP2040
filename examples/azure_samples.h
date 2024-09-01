
#ifndef _AZURE_SAMPLES_H_
#define _AZURE_SAMPLES_H_

#ifdef __cplusplus
extern "C"
{
#endif

extern const char pico_az_connectionString[];
extern const char pico_az_x509connectionString[];
extern const char pico_az_x509certificate[];
extern const char pico_az_x509privatekey[];
extern const char pico_az_id_scope[];
extern const char pico_az_COMMON_NAME[];
extern const char pico_az_CERTIFICATE[];
extern const char pico_az_PRIVATE_KEY[];

void iothub_ll_telemetry_sample(void);
void iothub_ll_c2d_sample(void);
void iothub_ll_client_x509_sample(void);
void prov_dev_client_ll_sample(void);

#ifdef __cplusplus
}
#endif

#endif /* _AZURE_SAMPLES_H_ */
