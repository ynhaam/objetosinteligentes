#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "CLARO_2G113C30";
const char* password = "5A113C30";
const char* mqtt_server = "192.168.0.3";

WiFiClient espClient;
PubSubClient client(espClient);

String my_topic;
String my_payload;

const int PINO_TRIG = 4;
const int PINO_ECHO = 2;
const int PINO_LED_VERMELHO = 5;
const int PINO_LED_AMARELO = 18;
const int PINO_LED_VERDE = 19;

int Valor;

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String conc_payload;
  for (int i = 0; i < length; i++) {
    conc_payload += ((char)payload[i]);
  }
  my_topic = topic;
  my_payload = conc_payload;
}

void reconnect() {

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("espClient")) {
      Serial.println("connected");
      client.subscribe("ESP32_RECEBE");
    } else {
      Serial.print("failed");
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(PINO_TRIG, OUTPUT);  
  pinMode(PINO_ECHO, INPUT);   
  pinMode(PINO_LED_VERMELHO, OUTPUT);   
  pinMode(PINO_LED_AMARELO, OUTPUT);   
  pinMode(PINO_LED_VERDE, OUTPUT);   

}
void loop() {
  reconnect();
  client.loop();

  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);
  
  long duracao = pulseIn(PINO_ECHO, HIGH); 
  float distancia = (duracao * 0.0343) / 2;

  float distanciamaxima = 30.0;
  float porcentageminversa = distancia / distanciamaxima;
  float nivel = (1 - porcentageminversa) * 100;
  
  if (nivel <0) 
  { 
    nivel = 0;
  } else if (nivel >100) {
    nivel = 100;
  }
  
  if (nivel <=20) 
  {
    digitalWrite(PINO_LED_VERMELHO, HIGH); 
    digitalWrite(PINO_LED_AMARELO, LOW); 
    digitalWrite(PINO_LED_VERDE, LOW);   
  } else if (nivel >= 50) {
    digitalWrite(PINO_LED_VERMELHO, LOW); 
    digitalWrite(PINO_LED_AMARELO, LOW); 
    digitalWrite(PINO_LED_VERDE, HIGH);   
  } else {
    digitalWrite(PINO_LED_VERMELHO, LOW); 
    digitalWrite(PINO_LED_AMARELO, HIGH); 
    digitalWrite(PINO_LED_VERDE, LOW);  
  }

  client.publish("projeto/nivel", String(nivel).c_str());

  
  delay(1000); 
}
