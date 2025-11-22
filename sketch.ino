#include <WiFi.h>
#include <PubSubClient.h>

/////// CONFIG WiFi ///////
const char* ssid     = "Wokwi-GUEST";      // coloque o WiFi do Wokwi ou da sua rede
const char* password = "";

/////// CONFIG MQTT ///////
const char* mqtt_server = "broker.hivemq.com";   // pode usar outro
const int   mqtt_port   = 1883;
const char* mqtt_topic  = "gs/sono/estado";

WiFiClient espClient;
PubSubClient client(espClient);

/////// PINOS ///////
const int LED_VERDE    = 26;
const int LED_VERMELHO = 25;
const int BUZZER       = 27;
const int BTN_SONO     = 14;   // botão ligado em INPUT_PULLUP

String estadoAtual = "OK";

void conectaWiFi() {
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void conectaMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    String clientId = "esp32Sono-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println(" conectado!");
    } else {
      Serial.print(" falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando de novo em 2s");
      delay(2000);
    }
  }
}

void publicaEstado(const char* estado) {
  if (!client.connected()) {
    conectaMQTT();
  }
  client.publish(mqtt_topic, estado);
  Serial.print("MQTT publicado: ");
  Serial.println(estado);
}

void estadoSono() {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(BUZZER, HIGH);   // buzzer liga
  publicaEstado("SONO");
  estadoAtual = "SONO";
}

void estadoOk() {
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(BUZZER, LOW);    // buzzer desliga
  publicaEstado("OK");
  estadoAtual = "OK";
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BTN_SONO, INPUT_PULLUP); // botão para GND

  // Estado inicial
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(BUZZER, LOW);

  conectaWiFi();
  client.setServer(mqtt_server, mqtt_port);
  conectaMQTT();
}

void loop() {
  client.loop();  // mantém conexão MQTT

  int leituraBotao = digitalRead(BTN_SONO);

  // Como usamos INPUT_PULLUP:
  // HIGH = sem sono (botão solto)
  // LOW  = sono detectado (botão apertado)
  if (leituraBotao == LOW && estadoAtual != "SONO") {
    // Transição para estado de sono
    estadoSono();
  } else if (leituraBotao == HIGH && estadoAtual != "OK") {
    // Volta para estado OK
    estadoOk();
  }

  delay(50); // pequeno debounce
}
