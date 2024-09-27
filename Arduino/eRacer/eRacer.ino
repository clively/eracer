#include <WiFiClientSecure.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <string>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ERacerControl.h>
#include <ERacerCommandProcessor.h>
#include <eRacerVarSetup.h>


ERacerControl erc(MOTOR_1_SPEED_PIN, MOTOR_1_DIR_A_PIN, MOTOR_1_DIR_B_PIN,
								 MOTOR_2_SPEED_PIN,MOTOR_2_DIR_A_PIN, MOTOR_2_DIR_B_PIN);

ERacerCommandProcessor inputHandler;

//PubSubClient mqttClient(mqtt_server, mqtt_port, mqttCallback, espClient);

//PubSubClient* mqttClient; //declare a pointer to some memory space to hold a future mqttClient
PubSubClient *mqttClient;

/************  
	Display Setup
************/


void setupDisplay() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();

	display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_BLACK);
	display.display();
	
	display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

	// Show initial display buffer contents on the screen --
  // the library can initialize this with a splash screen.
  display.display();
	 // Clear the buffer
} // function::setupDisplay

void clearLine(int rowNo =2) {
		 display.fillRect(0, (rowNo*8), SCREEN_WIDTH, 8, SSD1306_BLACK);
		 display.display();
} // function::clearLine

void showMessage(std::string msg, int rowNo = 2) {
	/*
		Each "row" is 8 pixels tall; starts with zero.
		So row 1 is 0-7, row 2 is 8-15, row r = 16 - 23,etc
		Each row represents a single page of data in the display and has 128 (0-127) columns
	*/
	/* likely need to add something that will clear out this line */
	clearLine(rowNo);

	display.setCursor(0,(rowNo*8));

	display.println(F(msg.c_str()));
	display.display(); // copy it out there

	Serial.println(msg.c_str());
} //function::showMessage


/************  
	Receives data from the MQTT broker
	This expects to receive commands formatted such as:
		FWD:200:10
************/
void mqttCallback(char* topic, byte* payload, unsigned int length) {
	clearLine(2);
	clearLine(3);
	clearLine(4);

	showMessage("Command Received", 2);

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

	showMessage(cmdToProcess, 3);

  erc.runCommand(cmd.cmdName, cmd.param1, cmd.param2);

  mqttClient->publish(mqtt_topicResponse, "Command Complete");
  showMessage("Command Run Complete", 4);

	clearLine(2);
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
  showMessage("Setting mqtt.");
  //Serial.println(mqtt_server);

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
      showMessage("Config portal");
      wm.setConfigPortalTimeout(120);
      
      if (!wm.startConfigPortal(client_id)) {
        showMessage("wifi fail");
        delay(3000);
        ESP.restart();
      } else {
        //if you get here you have connected to the WiFi
        showMessage("connected.");
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
	WiFi.setTxPower((wifi_power_t)cpower);
  delay(3000); // wait 5 seconds after setting up wifi to give it time to connect
 
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
	showMessage("Portal Up");
	res = wm.autoConnect(client_id); // password protected ap

  if(!res) {
    Serial.println("Failed to connect or hit timeout");
    ESP.restart(); // restart the device and try again
  } 
	showMessage("Portal done.");
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
	pulse the internal LED	
************/

void pulse(void) {
	static unsigned long delaytime = 0;
	static int delta = PULSE_DELTA;
	static int fade = 0;

  if (millis() - delaytime > PULSE_DELAY) {
    fade += delta;
    if (fade <= 0) {
      fade = 0;
      delta = PULSE_DELTA;
    } else if (fade >= 255) {
      fade = 255;
      delta = - PULSE_DELTA;
    }
    analogWrite(STATUS_LED, fade);
    delaytime = millis();
  }
}


/************  
	System Setup.  
	This runs exactly 1 time when the system is booting up.
************/
void setup() {

	// Turn on our Serial Output for debugging/logging purposes.
  Serial.begin(115200);
	Serial.println("Setup display");
	setupDisplay();
	delay(2000);
//  Serial.setDebugOutput(true);  
  showMessage("Beginning");

	// Pin initialize
  pinMode(TRIGGER_PIN, INPUT);  // wifi reset pin
  pinMode(STATUS_LED, OUTPUT);	// status LED pin

  // turn it ON
  digitalWrite(STATUS_LED, HIGH);

  showMessage("Starting");
  delay(5000);  // just wait 5 seconds

	showMessage(" ext antenna");
	//initExternalAntenna();

  showMessage("initi wifi");
	wifiInitialize();

  showMessage("initi mqtt");
  mqttInitialize();  

  showMessage("init control");

  erc.begin();  // after this executes then it goes straight into the loop.

  showMessage("Ready"); // this was never sent.

	  // turn it OFF
  digitalWrite(STATUS_LED, 1-LOW);

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
	pulse();

  // I feel like some delay or something needs to be here, but I'm not certain
  delay(3000); // remove this later.  I just need to see all the logs.

//  erc.moveForward(255, 2);

} // function::loop
