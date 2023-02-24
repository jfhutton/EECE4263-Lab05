// This .h file accompanies the mqtt_ledNode.ino v2.1 program.

// system defines
#define LED   D1  // active high LED w/ current limiting resistor
#define ON     1
#define OFF    0

// uncomment for Lipscomb broker, comment out for "brokerX"
#define LIPSCOMB

// Network and MQTT broker credentials
#ifdef LIPSCOMB
  const char* mqttBroker = "10.51.97.101";  // ECE mosquitto server (wlan0)
  const char* ssid = "LipscombGuest";       // no PW needed for Lipscomb guest wifi
#else
  const char* mqttBroker = "1.1.1.1";       // address of brokerX
  const char* ssid = "ssid";                // ssid of brokerX's network
  const char* password = "password";        // password for brokerX's network
#endif  	

int mqttPort = 1883;

const char* clientID = "ledNodeXX";         // Change XX to your ID number
