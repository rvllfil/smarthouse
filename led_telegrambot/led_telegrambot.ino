#include "CTBot.h"
CTBot myBot;

String ssid = "CAMPERNIQUE";                                           // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "nusaputrahjanda";                                       // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "800937311:AAHd6mpC4JQrrIiR62O7vNZZyA_RE8MnyGs"; // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
uint32_t chat_id = 358016920;

// Relay
uint8_t led1 = 16; //D0                                 
uint8_t led2 = 5;  //D1                            
uint8_t led3 = 4;  //D2                                          
uint8_t led4 = 0;  //D3

// PIR
uint8_t pir = 14;  // D5
int statusPIR = 0; // status logical
int data = 0; // variabel temporary utk menampung data PIR

// LED
int led_wifi = 12;
int led_pir = 15;

void setup() {

  // set the pin connected to the LED to act as output pin
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led_wifi, OUTPUT);
  pinMode(led_pir, OUTPUT);
  
  
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led_wifi, HIGH);
  digitalWrite(led_pir, HIGH);
  
  
  pinMode(pir, INPUT); // set pin 2 sbg input
  
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection()) {
    Serial.println("\nWiFi Connected");
    digitalWrite(led_wifi, LOW);
  }
  else 
    Serial.println("\nWiFi Not Connected");


}

void sendTelegramMessage() 
{
  Serial.println("Kirim pesan ke Telegram");
  delay(200);
  String message = "Sensor mendeteksi objek ....";
  
  message.concat("\n");
  message.concat("WASPADA !!!"); 
  message.concat("\n");
  if(myBot.sendMessage(chat_id, message)){
    Serial.println("Pesan telah dikirim ke TELEGRAM");
    delay(1000);
  }
  else Serial.println("gagal kirim.."); 
  }


void loop() {
  // SENSOR PIR

    data = digitalRead(pir); // baca input dr Vout
    if (data == HIGH) { // cek jika ada pergerakan
      Serial.println("Sensor PIR Aktif");  
      sendTelegramMessage(); // nyalakan led indikator di board Arduino
      Serial.println("Motion detected!"); //buat monitor ke laptop
      digitalWrite(led_pir, LOW);
      delay(1000);
      digitalWrite(led_pir, HIGH);
      delay(1000);
    }
    else {
      digitalWrite(led_pir, HIGH);
    }
    
//     statusPIR = HIGH; //diset high spy tdk mendeteksi terus
//    } else {
//      if ((data == LOW) && (statusPIR == HIGH)){
//       Serial.println("Motion ended!"); //buat monitor ke laptop
//       statusPIR = LOW;
//       }
//     }
 
      // KONTROL LAMPU
      // a variable to store telegram message data
      TBMessage msg;
      
      // if there is an incoming message...
      if (myBot.getNewMessage(msg)) {
        
        // LED 1
        if (msg.text.equalsIgnoreCase("l1 on")) {              // if the received message is "l1 on"...
          digitalWrite(led1, LOW);                            // turn on the LED 
          myBot.sendMessage(msg.sender.id, "Lampu 1 Menyala"); // notify the sender
        }
        else if (msg.text.equalsIgnoreCase("l1 off")) {        // if the received message is "l1 off"...
          digitalWrite(led1, HIGH);                             // turn off the led 
          myBot.sendMessage(msg.sender.id, "Lampu 1 Mati");    // notify the sender
        }
    
        // LED 2
        else if (msg.text.equalsIgnoreCase("l2 on")) {              // if the received message is "l2 on"...
          digitalWrite(led2, LOW);                            // turn on the LED 
          myBot.sendMessage(msg.sender.id, "Lampu 2 Menyala"); // notify the sender
        }
        else if (msg.text.equalsIgnoreCase("l2 off")) {        // if the received message is "l2 off"...
          digitalWrite(led2, HIGH);                             // turn off the led 
          myBot.sendMessage(msg.sender.id, "Lampu 2 Mati");    // notify the sender
        }
    
        // LED 3
        else if (msg.text.equalsIgnoreCase("l3 on")) {         // if the received message is "l3 on"...
          digitalWrite(led3, LOW);                            // turn on the LED 
          myBot.sendMessage(msg.sender.id, "Lampu 3 Menyala"); // notify the sender
        }
        else if (msg.text.equalsIgnoreCase("l3 off")) {        // if the received message is "l3 off"...
          digitalWrite(led3, HIGH);                             // turn off the led 
          myBot.sendMessage(msg.sender.id, "Lampu 3 Mati");    // notify the sender
        }
    
        // LED 4
        else if (msg.text.equalsIgnoreCase("l4 on")) {         // if the received message is "l4 on"...
          digitalWrite(led4, LOW);                            // turn on the LED 
          myBot.sendMessage(msg.sender.id, "Lampu 4 Menyala"); // notify the sender
        }
        else if (msg.text.equalsIgnoreCase("l4 off")) {        // if the received message is "l4 off"...
          digitalWrite(led4, HIGH);                             // turn off the led 
          myBot.sendMessage(msg.sender.id, "Lampu 4 Mati");    // notify the sender
        }
    
        // ALL LED 4
        else if (msg.text.equalsIgnoreCase("all on")) {         // if the received message is "l4 on"...
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);                            // turn on the LED 
          myBot.sendMessage(msg.sender.id, "Semua Lampu Menyala"); // notify the sender
        }
        else if (msg.text.equalsIgnoreCase("all off")) {        // if the received message is "l4 off"...
          digitalWrite(led1, HIGH);
          digitalWrite(led2, HIGH);
          digitalWrite(led3, HIGH);
          digitalWrite(led4, HIGH);                             // turn off the led 
          myBot.sendMessage(msg.sender.id, "Semua Lampu Mati");    // notify the sender
        }
    
        else {                                                    // otherwise...
          // generate the message for the sender
          String reply;
          reply = (String)"Welcome " + msg.sender.username + (String)". Try l1 on or l1 off.";
          myBot.sendMessage(msg.sender.id, reply);             // and send it
        }
      }
      // wait 500 milliseconds
      delay(500);
}
