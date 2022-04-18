// This file contains your configuration used to connect to Cloud IoT Core

// Wifi network details.
const char *ssid = "Pathan";
const char *password = "Cityview@18";

// Cloud iot details.
const char *project_id = "websysiot";
const char *location = "us-central1";
const char *registry_id = "websysreg";
const char *device_id = "websysdevice";

// Configuration for NTP
const char* ntp_primary = "pool.ntp.org";
const char* ntp_secondary = "time.nist.gov";

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif


const char *private_key_str =
    "Replace your Private Key";

// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 60*20; // Maximum 24H (3600*24)


const char *root_cert =
"Place your root certificate here\n";

// In case we ever need extra topics
const int ex_num_topics = 0;
const char* ex_topics[ex_num_topics];
