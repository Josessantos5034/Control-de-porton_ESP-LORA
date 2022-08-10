#include <esp_now.h>
#include <WiFi.h>

const int  buttonPin = 4;
const int buttonPin2 = 18;
const int ledPin = LED_BUILTIN;

int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

uint8_t broadcastAddress1[] = {0xE0, 0xE2, 0xE6, 0x01, 0x69, 0x82};

typedef struct test_struct {
  int a ; //x;
  int b;
} test_struct;

test_struct test;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {

  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);  //Cambiar el estado de la función de la placa
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent); //Enviar datos

 // El número de tableros utilizados en la sección de recepción
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {

  //Valores a enviar
  test.a = buttonState;
  test.b = buttonState;

  esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  primero (); 
  segundo ();
  
}
void primero (){
  buttonState = digitalRead(buttonPin); // Leer el estado básico del interruptor


  if (buttonState != lastButtonState) {

    if (buttonState == HIGH) {

      buttonPushCounter++; Agregando al valor de la variable después de cada clic
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {

      Serial.println("off");
    }

    //delay(50);
  }

  lastButtonState = buttonState;

  if (buttonPushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(1000);
}
void segundo (){
  buttonState = digitalRead(buttonPin2); // Leer el estado básico del interruptor


  if (buttonState != lastButtonState) {

    if (buttonState == HIGH) {

      buttonPushCounter++; Agregando al valor de la variable después de cada clic
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {

      Serial.println("off");
    }

    //delay(50);
  }

  lastButtonState = buttonState;

  if (buttonPushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(1000);
}
