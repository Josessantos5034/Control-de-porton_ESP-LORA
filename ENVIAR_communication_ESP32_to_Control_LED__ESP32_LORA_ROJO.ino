#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------

//----------------------------------------Defines PIN Button and PIN LED.
/*#define LED1_Pin   4
#define LED1_Pin   17
#define LED1_Pin   16
*/
#define BTN1_Pin   5
#define BTN2_Pin   15
#define BTN3_Pin   2 
//----------------------------------------

int BTN1_State; //--> Variable to hold the button state.
int BTN2_State;
int BTN3_State;

uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x1A, 0xD6, 0x88}; //--> esp32 thing

int LED_State_Send = 0; //--> Variable to hold the data to be transmitted to control the LEDs on the paired ESP32.

// int LED_State_Receive; //--> Variable to receive data to control the LEDs on the ESP32 running this code.

String success; //--> Variable to store if sending data was successful

//----------------------------------------Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int led;
} struct_message_send;

struct_message send_Data; // Create a struct_message to send data.

//struct_message receive_Data; // Create a struct_message to receive data.
//----------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
  Serial.println(">>>>>");
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is received
/*void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  Serial.println();
  Serial.println("<<<<< Receive Data:");
  Serial.print("Bytes received: ");
  Serial.println(len);
  LED_State_Receive = receive_Data.led;
  Serial.print("Receive Data: ");
  Serial.println(LED_State_Receive);
  Serial.println("<<<<<");

  digitalWrite(LED_Pin, LED_State_Receive);
} */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
void setup() {
  Serial.begin(115200);

  //pinMode(LED_Pin, OUTPUT);
  pinMode(BTN1_Pin, INPUT);
  pinMode(BTN2_Pin, INPUT);
  pinMode(BTN3_Pin, INPUT);
  
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station

  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------
  
  //----------------------------------------Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  //----------------------------------------
  
  //----------------------------------------Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  //----------------------------------------
  
  //----------------------------------------Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //----------------------------------------
  
  // esp_now_register_recv_cb(OnDataRecv); //--> Register for a callback function that will be called when data is received
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop() {
  BTN1_State = digitalRead(BTN1_Pin); //--> Reads and holds button states.
  BTN2_State = digitalRead(BTN2_Pin);
  BTN3_State = digitalRead(BTN3_Pin);
  //----------------------------------------When the button is pressed it will send data to control the LED on the ESP32 Target.
 
 boton_1 ();
 boton_2 ();
 boton_3 ();

}
void boton_1 (){
   if(BTN1_State == 1) {
    LED_State_Send = !LED_State_Send;
    send_Data.led = LED_State_Send;

    Serial.println();
    Serial.print(">>>>> ");
    Serial.println("Send data");
  
    //----------------------------------------Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
     
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
    //----------------------------------------
    
    //----------------------------------------Wait for the button to be released. Release the button first to send the next data.
    while(BTN1_State == 1) {
      BTN1_State = digitalRead(BTN1_Pin);
      delay(10);
    }
  }
}

void boton_2 (){
   if(BTN2_State == 1) {
    LED_State_Send = !LED_State_Send;
    send_Data.led = LED_State_Send;

    Serial.println();
    Serial.print(">>>>> ");
    Serial.println("Send data");
  
    //----------------------------------------Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
     
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
    //----------------------------------------
    
    //----------------------------------------Wait for the button to be released. Release the button first to send the next data.
    while(BTN2_State == 1) {
      BTN2_State = digitalRead(BTN2_Pin);
      delay(10);
    }
  }
}
void boton_3 (){
   if(BTN3_State == 1) {
    LED_State_Send = !LED_State_Send;
    send_Data.led = LED_State_Send;

    Serial.println();
    Serial.print(">>>>> ");
    Serial.println("Send data");
  
    //----------------------------------------Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
     
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
    //----------------------------------------
    
    //----------------------------------------Wait for the button to be released. Release the button first to send the next data.
    while(BTN3_State == 1) {
      BTN3_State = digitalRead(BTN3_Pin);
      delay(10);
    }
  }
}
