#include <WiFiClientSecure.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <ERacerControl.h>
#include <ERacerCommandProcessor.h>
#include <eRacerVarSetup.h>
#include <string>

ERacerControl erc(MOTOR_1_SPEED_PIN, MOTOR_1_DIR_A_PIN, MOTOR_1_DIR_B_PIN,
								 MOTOR_2_SPEED_PIN,MOTOR_2_DIR_A_PIN, MOTOR_2_DIR_B_PIN);

ERacerCommandProcessor inputHandler;

//PubSubClient mqttClient(mqtt_server, mqtt_port, mqttCallback, espClient);

//PubSubClient* mqttClient; //declare a pointer to some memory space to hold a future mqttClient
PubSubClient *mqttClient;

/************  
	Receives data from the MQTT broker
	This expects to receive commands formatted such as:
		FWD:200:10
************/
void mqttCallback(char* topic, byte* payload, unsigned int length) {
	Serial.println("Command Received");

  char cmdToProcess[length+1]; // establish the byte array
	memcpy(cmdToProcess, payload, length); // copy the data
	cmdToProcess[length] = 0; // make sure it is null terminated;

/*
	char cmdToProcess[(sizeof payload) + 1];  // establish the byte array

	memcpy(cmdToProcess, payload, sizeof payload); // copy the data
	cmdToProcess[sizeof payload] = 0; // make sure it is null terminated;
*/
	// NOW we need to parse the command

	ERacerCommandDataType cmd = inputHandler.parseCommandLine(cmdToProcess);
	Serial.print("COMMAND: ");

	Serial.print(cmd.cmdName.c_str());
	Serial.print("  ");
	Serial.print(cmd.param1);
	Serial.print("  ");
	Serial.println(cmd.param2);

  erc.runCommand(cmd.cmdName, cmd.param1, cmd.param2);

  mqttClient->publish(mqtt_topicResponse, "Command Complete");
  Serial.println("Command Run Complete");
} // function::mqttCallback

/************  
	Connects to the MQTT broker
************/
void connectToMQTT() {
    while (!mqttClient->connected()) {

        Serial.printf("Connecting to MQTT Broker as %s...\n", client_id);
        if (mqttClient->connect(client_id, mqtt_username, mqtt_password)) {
            Serial.println("Connected to MQTT broker");
						// subscribe to a topic with the same name as the racer
            mqttClient->subscribe(mqtt_topicCommand);

						snprintf (msg, MSG_BUFFER_SIZE, "[%s] is ready", client_id);

            mqttClient->publish(mqtt_topicResponse, msg);  // Publish message upon connection
        } else {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(mqttClient->state());
            Serial.println(" Retrying in 5 seconds.");
            delay(5000);
        }
    }
} //function::connectToMQTT

/************  
	Connects to the MQTT broker
************/
void mqttInitialize() 
{
  //if you get here you have connected to the WiFi    
  Serial.print("Setting mqtt to ");
  Serial.println(mqtt_server);

  espClient.setCACert(ca_cert);  // for security, define which certificate to use to encrypt/decrypt messages

  mqttClient = new PubSubClient(mqtt_server, mqtt_port, mqttCallback, espClient);

//  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient->setKeepAlive(60);
  // I don't think the set Callback  should happen until after connect
  // mqttClient.setCallback(mqttCallback);  <-- this is what is killing everything.  

  connectToMQTT();
} // function::mqttInitialize

/************  
	Checks to see if Wifi reset button has been pushed.
************/
void checkWifiResetButton(){
  // check for button press
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
    // poor mans debounce/press-hold, code not ideal for production
    delay(50);
    if( digitalRead(TRIGGER_PIN) == LOW ){
      Serial.println("Wifi Reset Pressed");
      // still holding button for 3000 ms, reset settings, code not ideaa for production
      delay(3000); // reset delay hold
      if( digitalRead(TRIGGER_PIN) == LOW ){
        Serial.println("Wifi Reset Held");
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();
        ESP.restart();
      }
      
      // start portal w delay
      Serial.println("Starting config portal");
      wm.setConfigPortalTimeout(120);
      
      if (!wm.startConfigPortal(client_id)) {
        Serial.println("failed to connect or hit timeout");
        delay(3000);
        ESP.restart();
      } else {
        //if you get here you have connected to the WiFi
        Serial.println("connected.");
      }
    }
  }
} // function::checkWifiResetButton

/************  
	Initialize Wifi.  
************/
void wifiInitialize()
{
	// Wifi
  WiFi.mode(WIFI_STA); // explicitly set mode to STATION, esp defaults to STA+AP  

  delay(5000); // wait 5 seconds after setting up wifi to give it time to connect
 
  // wm.resetSettings(); // this wipes settings.  Only uncomment for testing purposes

  if(wm_nonblocking) 
	{
		wm.setConfigPortalBlocking(false);
	}

	// wifi manager menu settings
  std::vector<const char *> menu = {"wifi","info","param","sep","restart","exit"};
  wm.setMenu(menu);

  // set dark theme
  wm.setClass("invert");

  wm.setConfigPortalTimeout(180); // auto close configportal after 3 minutes

  bool res;
	res = wm.autoConnect(client_id); // password protected ap

  if(!res) {
    Serial.println("Failed to connect or hit timeout");
    ESP.restart(); // restart the device and try again
  } 
} // function::wifiInitialize
/************  
	initExternalAntenna
	Turns on the external antenna
************/

void initExternalAntenna() {
	//https://www.sigmdel.ca/michel/ha/xiao/xiao_esp32c6_intro_en.html#antenna_1
	//https://forum.seeedstudio.com/t/xiao-esp32c6-switching-between-builtin-and-external-antenna/276374/13
	digitalWrite(WIFI_ANT_CONFIG, HIGH); 
} // function::initExternalAntenna

/************  
	System Setup.  
	This runs exactly 1 time when the system is booting up.
************/
void setup() {

	// Turn on our Serial Output for debugging/logging purposes.
  Serial.begin(115200);
//  Serial.setDebugOutput(true);  

  Serial.println("=== Beginning To Run ===");

	// Pin initialize
  pinMode(TRIGGER_PIN, INPUT);  // wifi reset pin
  pinMode(STATUS_LED, OUTPUT);	// status LED pin

  digitalWrite(STATUS_LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("\n Starting");
  delay(5000);  // just wait 5 seconds

	Serial.println("Enable external antenna");
	initExternalAntenna();

  Serial.println("-- initi wifi");
	wifiInitialize();

  Serial.println("-- initi mqtt");
  mqttInitialize();  

  Serial.println("-- init eRacer control");

  erc.begin();

  Serial.println("Setup complete");

  digitalWrite(STATUS_LED, true); // turn on our LED, we are processing
}  // function::setup

/************  
	Looping control
	This runs until the system is disconnected from power.
	Main loop is to check to see if anything has been published to the MQTT broker.
	If so, grab that data and execute the command.
************/
void loop() {
  Serial.println("*************  Looping ******************");
  
  // 	checkWifiResetButton();  // figure this out when we actually have a button connected

  // now poll the mqtt 
  if (!mqttClient->connected()) {
    connectToMQTT();
  }
  mqttClient->loop();


  yield(); // this allows the other thread to pull data back

  // I feel like some delay or something needs to be here, but I'm not certain
  delay(3000); // remove this later.  I just need to see all the logs.

//  erc.moveForward(255, 2);

} // function::loop
