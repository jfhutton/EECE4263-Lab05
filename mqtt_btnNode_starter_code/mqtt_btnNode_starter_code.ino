/*******************************************************************************
 *     Program name: mqtt_btnNode_starter_code.ino
 *          Version: 2.1
 *             Date: Oct 14, 2020
 *           Author: Greg Nordstrom
 *         Platform: NodeMCU 1.0 ESP8266.E12-based devkit board
 *    Additional HW: Two n/o pushbuttons connected to D5 ("On") and D6 ("Off")
 * Additional files: mqtt_btnNode_starter_code.h
 *  Req'd libraries: ESP8266WiFi, PubSubClient, ArduinoJson, Bounce2, Ticker
 *
 * Sends/receives MQTT messages to/from a remote LED node (ledNodeXX), turning
 * its LED on or off. Use mqtt_ledcontroller_starter_code.h to set this button
 * node's Client ID, as well as the remote LED node's Client ID and the MQTT
 * broker's connection information.
 * 
 * This node sends and receives the following MQTT messages, where btnNodeXX
 * is this node's Client ID and ledNodeXX is the remote LED node's Client ID:
 *
 *   Sends:
 *      Topic: "ledNodeXX/ledCommand"
 *      Usage: To instruct ledNodeXX to turn on/off its LED
 *    Payload: {"senderID":"btnNodeXX","cmd":"on" | "off"}
 *
 *   Receives:
 *      Topic: "btnNodeXX/ledStatus"
 *      Usage: Reports the current status of ledNodeXX's LED
 *    Payload: {"ledStatus":"on" | "off", "msg":"some message text"}
 *
 * This program also displays status messages on a serial terminal (115200N81)
 * along with the message text contained in a received ledStatus message.
 *
 * Finally, note that this node's functionality can be fully exercised using an 
 * MQTT message "sniffer" such as MQTT-Spy (available on GitHub). MQTT-Spy is a
 * Java program, which requires Java to be installed on the host machine.
 *
 * DEVELOPER NOTES:
 * This program uses the public domain PubSubClient library to perform MQTT
 * messaging functions, and all message payloads are encoded in JSON format.
 *  1. Default message size, including header, is only 128 bytes (rather small).
 *  2. Increase/decrease by changing MQTT_MAX_PACKET_SIZE inside PubSubClient.h.
 *  3. Recommended size is 512 bytes.
 *
 ******************************************************************************/
// included configuration file and support libraries
#include "mqtt_btnNode_starter_code.h"     // this project's .h file
#include <ESP8266WiFi.h>                   // wi-fi support
#include <PubSubClient.h>                  // MQTT client
#include <ArduinoJson.h>                   // MQTT payloads are in JSON format
#include <Bounce2.h>                       // pushbutton debouncer library
#include <Ticker.h>                        // allows timed callbacks

WiFiClient wfClient;                       // create a wifi client
PubSubClient psClient(wfClient);           // create a pub-sub object (must be
                                           // associated with a wifi client)

// char buffer to store incoming/outgoing messages
char json_msgBuffer[200];

// buffer to store sprintf formatted strings for printing
char sbuf[80];

// create a Ticker object to periodically check the debounced pushbutton
Ticker pbTimer;

// create a Bounce object for "On" and "Off" PB switches
Bounce ledOnPBDebouncer = Bounce();
Bounce ledOffPBDebouncer = Bounce();

/**********************************************************
 * Helper functions
 *********************************************************/
void connect_wifi()
{
  // in an attempt to remove the annoying garbled text on
  // startup, print a couple of blank lines (with delay)
  Serial.println();
  delay(100);
  Serial.println();
  delay(100);

  // attempt to connect to the WiFi network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print(" network");
  delay(10);
  #ifdef LIPSCOMB
    WiFi.begin(ssid);            // Lipscomb WiFi does NOT require a password
  #else
    WiFi.begin(ssid, password);  // For WiFi networks that DO require a password
  #endif

  // advance a "dot-dot-dot" indicator until connected to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  // report to console that WiFi is connected and print IP address
  Serial.print(" connected as ");
  Serial.println(WiFi.localIP());
}

void processMQTTMessage(char* topic, byte* json_payload, unsigned int length)
{
  // This code is called whenever a message previously registered for is
  // received from the broker. Incoming messages are selected by topic,
  // then the payload is parsed and appropriate action taken. (NB: If only
  // a single message type has been registered for, then there's no need to
  // select on a given message type. In practice this may be rare though...)

  // For info on sending MQTT messages inside the callback handler, see
  // https://github.com/bblanchon/ArduinoJson/wiki/Memory-model.

  // create space for the json object tree
  // NB: See https://github.com/bblanchon/ArduinoJson/wiki/Memory-model
  // for guidance on selecting proper jsonBuffer size

  ...
  
  // process messages by topic
  if(strcmp(topic, ... ) {
    ...
  }

}

void setup() {
  Serial.begin(115200);
  while(!Serial) {
    // wait for serial connection
    delay(1);
  }

  ...

  // finally, flash the on-board LED five times to let user know
  // that the NodeMCU board has been initialized and ready to go
  pinMode(D4, OUTPUT);
  for(int i=0; i<5; i++) {
    digitalWrite(D4, 0);  // active low
    delay(20);
    digitalWrite(D4, 1);
    delay(150);
  }
  Serial.println("Network initialization complete");
}

void loop()
{
  // This is largely a reactive program, and as such only uses
  // the main loop to maintain the MQTT broker connection and
  // periodically call the psClient.loop() code to ensure the
  // client stays active
  
  // reconnect to MQTT server if connection lost
  if (!psClient.connected()) {
    reconnect();
  }

  delay(10);
  psClient.loop();  // call periodically to keep client alive and well
}
