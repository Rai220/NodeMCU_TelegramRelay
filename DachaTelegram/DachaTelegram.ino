/*******************************************************************
 *  this is a basic example how to program a Telegram Bot          *
 *  using TelegramBOT library on Arduino Zero and WiFiSchield101   *
 *                                                                 *
 *  Open a conversation with the bot, it will echo your messages   *
 *                                                                 *
 *  written by Giacarlo Bacchio                                    *
 *******************************************************************/

#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
#include <ESPTelegramBot.h>


// Initialize Wifi connection to the router
const char *ssid = "DachaSecurity3";   // cannot be longer than 32 characters!
const char *pass = "xxx";   //                              // your network key
const int RELAY_1 = 14;
const int RELAY_2 = 12;
const int RELAY_3 = 13;
const int RELAY_4 = 15;
int status = WL_IDLE_STATUS;


// Initialize Telegram BOT
#define BOTtoken "249572387:xxx"  //token of TestBOT
#define BOTname "xxx"
#define BOTusername "xxx"
TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
String action = "";
String object = "";
String message = "";
String answer = "";
int gpioToUse = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(RELAY_3, HIGH);
  digitalWrite(RELAY_4, HIGH);

  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  bot.begin();      // launch Bot functionalities
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
    Bot_EchoMessages();   // reply to message with Echo
    Bot_lasttime = millis();
  }
}

void Bot_EchoMessages() {
  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++) {
    action = "";
    object = "";
    message = bot.message[i][5];

    if (message.indexOf("open garage") >= 0) {
      object = "relay 1";
      gpioToUse = RELAY_1;
      action = "blink";
    }

    if (message.indexOf("close garage") >= 0) {
      object = "relay 2";
      gpioToUse = RELAY_2;
      action = "blink";
    }
    

    if (message.indexOf("relay 1") >= 0) {
      object = "relay 1";
      gpioToUse = RELAY_1;
    }
    if (message.indexOf("relay 2") >= 0) {
      object = "relay 2";
      gpioToUse = RELAY_2;
    }
    if (message.indexOf("relay 3") >= 0) {
      object = "relay 3";
      gpioToUse = RELAY_3;
    }
    if (message.indexOf("relay 4") >= 0) {
      object = "relay 4";
      gpioToUse = RELAY_4;
    }
    if (message.indexOf("led") >= 0) {
      object = "led";
      gpioToUse = LED_BUILTIN;
    }

    if (message.indexOf("turn on") >= 0) {
      action = "turn on";
    }
    if (message.indexOf("turn off") >= 0) {
      action = "turn off";
    }
    if (message.indexOf("blink") >= 0) {
      action = "blink";
    }

    if (action != "" && object != "") {
      answer = "Action: " + action + ", object: " + object + ", GPIO: " + gpioToUse;
      if (action == "turn on") {
        digitalWrite(gpioToUse, LOW);
      } else if (action == "turn off") {
        digitalWrite(gpioToUse, HIGH);
      } else if (action == "blink") {
        digitalWrite(gpioToUse, LOW);
        delay(500);
        digitalWrite(gpioToUse, HIGH);
      }
      
    } else {
      answer = "Unknown command!";
    }
    
    bot.sendMessage(bot.message[i][4], answer, "");
  }
  bot.message[0][0] = "";   // All messages have been replied - reset new messages
}
