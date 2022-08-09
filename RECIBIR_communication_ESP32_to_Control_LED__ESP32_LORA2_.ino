#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------

//----------------------------------------Defines PIN Button and PIN LED.
#define LED1_Pin   4
#define LED1_Pin   17
#define LED1_Pin   16
//----------------------------------------

// int BTN_State; //--> Variable to hold the button state.

uint8_t broadcastAddress[] = {0xE0, 0xE2, 0xE6, 0x01, 0x63, 0xA0}; //--> esp32 LORA

//int LED_State_Send = 0; //--> Variable to hold the data to be transmitted to control the LEDs on the paired ESP32.

int LED1_State_Receive; //--> Variable to receive data to control the LEDs on the ESP32 running this code.
int LED2_State_Receive;
int LED3_State_Receive;
// String success; //--> Variable to store if sending data was successful

//----------------------------------------Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int led;
} struct_message;
//struct_message_send;

//struct_message send_Data; // Create a struct_message to send data.

struct_message receive_Data; // Create a struct_message to receive data.
//----------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is sent
/* void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
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

*/ 
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
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
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
void setup() {
  Serial.begin(115200);

   pinMode(LED1_Pin, OUTPUT);
   pinMode(LED2_Pin, OUTPUT);
   pinMode(LED3_Pin, OUTPUT);
   //pinMode(BTN_Pin, INPUT);
  
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station

  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------
  
  //----------------------------------------Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  //esp_now_register_send_cb(OnDataSent);
  //----------------------------------------
  
  //----------------------------------------Register peer
  /* esp_now_peer_info_t peerInfo;
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
  */
  esp_now_register_recv_cb(OnDataRecv); //--> Register for a callback function that will be called when data is received
}
void loop() {
  
}
