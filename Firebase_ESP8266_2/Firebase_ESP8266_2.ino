//Tugas Akhir Saharudin

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DTH_Turbidity.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

#define WIFI_SSID "Kos Fatanah"
#define WIFI_PASSWORD "Kost***********"
#define FIREBASE_HOST "tugasakhir********************.com"
#define FIREBASE_AUTH "wsJTbQ7BPWx41vsWpJ*************************"

#define sensorPin A0
#define echoPin 0
#define trigPin 2
#define flowsensor 14 // Sensor Input
#define flowsensor1 12 // Sensor Input

// variabel Sensor Turbidity
   float kekeruhan;
   int sensorValue = 1;
   unsigned int maps;
   float volt = 0;

// variabel Sensor FlowMeter
   volatile int flow_frequency; 
   volatile int flow_frequency1;

   float vol = 0.0,l_minute;
   float vol1 = 0.0,N_minute;

   unsigned long currentTime;
   unsigned long cloopTime;

   unsigned long currentTime1;
   unsigned long cloopTime1;

// Batas2
   int batas_atas = 20;
   int batas_bawah = 40;
   int batas_tds = 30;

// Variabel Sensor Ultrasonik
   long duration; 
   int distance;

// variabel Relay & Valve
   const int valve_1 = 5;
   const int valve_2 = 4;

DTH_Turbidity turbSensor(sensorPin);

// Define NTP Client to get time
   WiFiUDP ntpUDP;
   //NTPClient timeClient(ntpUDP, "pool.ntp.org", 28860);
   NTPClient timeClient(ntpUDP, "pool.ntp.org", 28800);

// Variable to save current epoch time
   int timestamp;

// Function that gets current epoch time
   unsigned long getTime() {
   timeClient.update();
   unsigned long now = timeClient.getEpochTime();
   return now;
}

void flow () // Interrupt function to increment flow
{
   flow_frequency++;
}

void flow1 () // Interrupt function to increment flow
{
   flow_frequency1++;
}


void setup() {
  Serial.begin(9600);

  pinMode(valve_1, OUTPUT);
  pinMode(valve_2, OUTPUT);
  pinMode(kekeruhan, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(flowsensor, INPUT);
  pinMode(flowsensor1, INPUT);

  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
  attachInterrupt(digitalPinToInterrupt(flowsensor1), flow1, RISING); // Setup Interrupt

  currentTime = millis();
  cloopTime = currentTime;

  currentTime1 = millis();
  cloopTime1 = currentTime1;

  if(distance < 40){
  digitalWrite(valve_1, LOW); // buang air
  digitalWrite(valve_2, HIGH); // Mengisi air
  }

// connect to wifi.  
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP address: ");
  Serial.println(WiFi.localIP());

   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

// Inisialisasi NTP Client
  timeClient.begin();
}

void loop() {
//Sensor Turbidity
//mapping untuk threshold 0 sampai 30
  int sensorValue = analogRead(sensorPin);
//  int turbidity = map(sensorValue, 0, 2800, 50, 0);
  int turbidity = map(sensorValue, 0, 1000, 50, 0);

// Dapatkan waktu dari server NTP
  timeClient.update();

  //Ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration/58.2;

//Flowmeter 1
  currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0)
    {
       l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    }

   //Flowmeter 2
   currentTime1 = millis();
   // Every second, calculate and print litres/hour
   if(currentTime1 >= (cloopTime1 + 1000))
   {
    cloopTime1 = currentTime1; // Updates cloopTime
    if(flow_frequency1 != 0)
    {
       N_minute = (flow_frequency1 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    }


// Sensor Turbidity
   Serial.println(" " );
   Serial.print("Turbidity: ");
   Serial.println(turbidity);
   volt = turbSensor.getVoltage();
   Serial.print("Voltage: ");
   Serial.print(volt);
   Serial.println(" volt");
  
   Serial.println(" ");

// Get current timestamp
   timestamp = getTime();
   Serial.print ("time: ");
   Serial.println (timestamp);

// Sensor ultrasonic
   Serial.print("Jarak : ");
   Serial.print(distance);
   Serial.println(" cm");

   Serial.println(" ");

// Sensor Flowmeter 1
   Serial.print("Rate 1 : ");
   Serial.print(l_minute);
   Serial.println(" L/M");
   l_minute = l_minute/60;
   vol = vol +l_minute;
   Serial.print("Volume :");
   Serial.print(vol);
   Serial.println(" L");
   flow_frequency = 0; // Reset Counter

   Serial.println(" ");

// Sensor Flowmeter 2
   Serial.print("Rate 2 : ");
   Serial.print(N_minute);
   Serial.println(" L/M");
   N_minute = N_minute/60;
   vol1 = vol1 +N_minute;
   Serial.print("Volume :");
   Serial.print(vol1);
   Serial.println(" L");
   flow_frequency1 = 0; // Reset Counter
  }

  else {

  l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
  Serial.print("Rate 1 : ");
  Serial.print(l_minute);
  Serial.println(" L/M");
  l_minute = l_minute/60;
  vol = vol +l_minute;
  Serial.print("Volume :");
  Serial.print(vol);
  Serial.println(" L");

  Serial.println(" ");
  
  N_minute = (flow_frequency1 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
  Serial.print("Rate 2 : ");
  Serial.print(N_minute);
  Serial.println(" L/M");
  N_minute = N_minute/60;
  vol1 = vol1 +N_minute;
  Serial.print("Volume :");
  Serial.print(vol1);
  Serial.println(" L");

  Serial.println("  ");
  delay(1000);
}
  
//Perintah Relay to Valve
  if (turbidity > batas_tds){
  digitalWrite(valve_1, LOW); // buang air
  digitalWrite(valve_2, HIGH); // mengisi air
  delay(1000);
   }
 
  if (distance > batas_bawah) {
  digitalWrite(valve_1, HIGH);  // buang air  
  digitalWrite(valve_2, LOW); // mengisi air
  delay(1000);
 }   
  if (turbidity < batas_tds && distance <= batas_atas) {
    digitalWrite(valve_1, HIGH);
    digitalWrite(valve_2, HIGH);
    delay(1000);
  }

  String turbidityPart = String(turbidity) + String(" ntu"); 
  String voltPart = String(volt) + String(" v"); 
  String volPart = String(vol) + String(" L"); 
  String vol1Part = String(vol1) + String(" L");  
  String distancePart = String(distance) + String(" cm");    
  String timeClientPart = String(month(timestamp)) + "/" + String(day(timestamp)) + 
  "/" + String(year(timestamp))+ " - " + String(hour(timestamp)) + 
  ":" + String(minute(timestamp)) + ":" + String(second(timestamp));

// kirim data ke firebase
// Firebase.pushString("/Data Sensor/Turbidity", turbidityPart);
   Firebase.setString("/Data Sensor/Turbidity", turbidityPart);
   Firebase.setString("/Data Sensor/Volt", voltPart);
   Firebase.setString("/Data Sensor/FlowMeter1", volPart);
   Firebase.setString("/Data Sensor/FlowMeter2", vol1Part);
   Firebase.setString("/Data Sensor/Ultrasonic", distancePart);
   Firebase.setString("/Data Sensor/timestamp", timeClientPart);

}
  delay(1000);
}

//Tugas Akhir Saharudin
