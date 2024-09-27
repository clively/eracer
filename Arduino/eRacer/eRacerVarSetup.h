#ifndef ERacerVarSetup_h
#define ERacerVarSetup_h

#include <Adafruit_SSD1306.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <string>

/*******  PIN Definitions  *******/ 
const int TRIGGER_PIN = D0;  // Connect D0 to a button to support WIFI memory reset.
const int STATUS_LED = LED_BUILTIN;		// 

#define DEVICEADDR_PCF 0x20
// Pin expander PIN reference
#define X_P0	0
#define X_P1	1
#define X_P2	2
#define X_P3	3
#define X_P4	4
#define X_P5	5
#define X_P6	6
#define X_P7	7
#define X_P8	0   // DOES NOT EXIST
#define X_P9	0   // DOES NOT EXIST
#define X_P10	8
#define X_P11	9
#define X_P12	10
#define X_P13	11
#define X_P14	12
#define X_P15	13

const int MOTOR_1_SPEED_PIN = D7;  // Requires an ANALOG pin.  Digital Expanders don't have that.
const int MOTOR_1_DIR_A_PIN = X_P11;
const int MOTOR_1_DIR_B_PIN = X_P12;

const int MOTOR_2_SPEED_PIN = D8;   // Requires an ANALOG pin.  Digital Expanders don't have that.
const int MOTOR_2_DIR_A_PIN = X_P6;
const int MOTOR_2_DIR_B_PIN = X_P5;

/*******  LED Blinking  *******/ 
#define PULSE_DELTA 10
#define PULSE_DELAY 50

/******* MQTT Broker Connection Details *******/
const char* mqtt_server = "yde4f5d3.ala.us-east-1.emqxsl.com";
const char* mqtt_username = "LCTempSensor";
const char* mqtt_password = "loved5555";
const char* mqtt_topicCommand = "eRacer0001"; // Command Topic is same name as car.  = "eRaceCmd";
const char* mqtt_topicResponse = "eRaceRsp";
const int mqtt_port =8883; // ssl

const char* client_id = "eRacer0001";  // Device Name used when connecting to the MQTT broker.

// mqtt messages
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

// wifi setup
bool wm_nonblocking = false; // change to true to use non blocking

WiFiManager wm; // global wm instance
WiFiClientSecure espClient;

// Load DigiCert Global Root CA ca_cert, which is used by EMQX Serverless Deployment

static const char ca_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
-----END CERTIFICATE-----
)EOF";

// Display screen setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet of screen for Address; 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#endif






