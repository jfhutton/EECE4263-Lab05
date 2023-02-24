// This file accompanies the mqtt_btnNode_starter_code.ino v2.1 program

// system defines
#define DEBOUNCE_INTERVAL    5  // 5mS works well for circuit-mount PBs
#define PB_UPDATE_TIME       8  // number of mS between button status checks
#define PB_ON               D5  // pin connected to led "on" switch
#define PB_OFF              D6  // pin connected to led "off" switch

// Network and MQTT broker credentials
const char* mqttBroker = "10.51.97.101";  // ECE mosquitto server (wlan0)
const char* ssid = "LipscombGuest";       // no PW needed for Lipscomb

int mqttPort = 1883;

// Client ID of this LED controller
const char* clientID = "btnNodeXX";       // Change XX to your two-digit ID

// Client ID of the remote LED node
const String ledClientID = "ledNodeXX";   // Change XX to your two-digit ID
