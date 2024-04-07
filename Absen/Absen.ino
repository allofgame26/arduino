#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
// RFID
#include <SPI.h>
#include <MFRC522.h>

// network SSID nama wifi
const char* ssid = "wifiku";
const char* password = "password";

// Pengenalan host (server) = IP address komputer server
const char* host = "192.168.0.27";

// tombol
#define button 5
// lampu
#define LED 15

// variabel RFID
#define SDA 2
#define RST 0

MFRC522 rfid(SDA,RST);

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // setting koneksi wifi
  WiFi.hostname("NodeMCU");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //cek koneksi
  while(WiFi.status() != WL_CONNECTED){
    //Progress sedang mencari wifi
    delay(1000);
    Serial.print(".");
  }  
  Serial.println("Wifi Connected");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());

  pinMode(LED,OUTPUT);
  pinMode(button,OUTPUT);

  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Dekatkan Kartu Anda!!!");
  Serial.println("");
}

void loop() {
  // baca status button
  if(digitalRead(button) == 1){
    // menyalakan lampu LED
    digitalWrite(LED,HIGH);
    while(digitalRead(button) == 1);
    // ubah mode absensi
    String getdata, Link;
    HTTPClient http;
    //Get Data
    Link = "http://192.168.0.27/rfid/ubahmode.php";
    if(http.begin(client,Link)){
      int httpCode = http.GET();
      String payload = http.getString(); // umpan balik jika berhasil / gagal

      Serial.println(payload);
      http.end();
    } else {
      Serial.println("Failed to Connect to make HTTP Request");
    }
  }
  // matikan lampu
  digitalWrite(LED,LOW);

  if(! rfid.PICC_IsNewCardPresent() || ! rfid.PICC_ReadCardSerial()){
    return;
  }
    String id = "";
    for(byte i = 0; i < rfid.uid.size;i++){
      id += rfid.uid.uidByte[i];
      Serial.println(id);
    }

    // menyalakan lampu
    digitalWrite(LED,HIGH);

    // kirim data
    const int httpPort = 80;
    if(!client.connect(host, httpPort)){
      Serial.println("Connecttion Failed");
      return;
    }

    String link;
    HTTPClient http;
    link = "http://192.168.0.27/rfid/kirimkartu.php?nokartu=" + id ;
    if(http.begin(client,link)){
      int httpCode = http.GET();
      String payload = http.getString(); // umpan balik jika berhasil / gagal

      Serial.println(payload);
      http.end();
      delay(2000);
    } else {
      Serial.println("Failed to Connect to make HTTP Request");
    }
}
