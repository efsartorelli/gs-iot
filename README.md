🟦🟩 Monitoramento de Sonolência (Global Solution IoT) 🟩🟦
==================================================================

📌 Sobre o Projeto
------------------
Este projeto faz parte da **Global Solution de IoT**, com foco em 
**segurança e bem-estar no ambiente de trabalho**.  
A solução implementa um **monitor de sonolência** usando ESP32, LEDs,
botão, buzzer e comunicação MQTT para enviar o estado do colaborador
em tempo real para a nuvem.  

Quando o trabalhador começa a sentir sono ou fadiga, ele aperta um botão.
O sistema:
- 🔴 Acende LED vermelho  
- 🔊 Ativa buzzer (alerta sonoro local)  
- ☁️ Envia mensagem “SONO” para o broker MQTT

Quando ele está bem:
- 🟢 LED verde ligado  
- 🔇 Buzzer desligado  
- ☁️ Publica mensagem “OK”

Isso permite integração com dashboards, apps e sistemas do RH para
detecção precoce de risco, prevenção de acidentes e aumento de produtividade.

------------------------------------------------------------------

⚙️ Hardware Utilizado
----------------------
- 🧠 **ESP32** — microcontrolador Wi-Fi
- 🔘 **Botão (GPIO 14)** — colaborador indicando estado
- 🟢 **LED Verde (GPIO 26)** — estado OK
- 🔴 **LED Vermelho (GPIO 25)** — estado SONO
- 🔊 **Buzzer (GPIO 27)** — alerta sonoro
- 🔌 Jumpers e protoboard ou simulação no Wokwi

O botão está configurado em **INPUT_PULLUP**:
- Solto (HIGH) → OK  
- Apertado (LOW) → SONO  

------------------------------------------------------------------

🧩 Funcionamento da Lógica
--------------------------
O ESP32 conecta no Wi-Fi e no broker MQTT público:

🔗 Broker: `broker.hivemq.com`  
📡 Tópico usado: `gs/sono/estado`

As funções principais do sistema:

### 🟢 estadoOk()
- LED verde ON  
- LED vermelho OFF  
- Buzzer OFF  
- Publica "OK" no MQTT

### 🔴 estadoSono()
- LED vermelho ON  
- LED verde OFF  
- Buzzer ON  
- Publica "SONO" no MQTT

### 🔁 Loop principal
- Lê o botão  
- Detecta mudança de estado  
- Atualiza LEDs, buzzer e MQTT  
- Evita publicações repetidas usando `estadoAtual`

------------------------------------------------------------------

📡 Comunicação MQTT
-------------------
A cada mudança no botão, o ESP32 publica no tópico:

- `"OK"`  
- `"SONO"`

Essas mensagens podem ser lidas por:
- 🖥️ Dashboards  
- 📱 Aplicativos  
- 🧩 Sistemas de monitoramento  
- 📊 Painéis do RH

Possíveis integrações:
- Monitoramento de operadores de máquinas  
- Motoristas noturnos  
- Equipes em turnos da madrugada  
- Home office com pedal de acionamento  

------------------------------------------------------------------

▶️ Como Executar o Projeto
--------------------------
1) Abra o código no Wokwi ou IDE (Arduino / PlatformIO).  
2) Configure seu Wi-Fi:
const char* ssid = "SEU_WIFI";
const char* password = "SENHA";
3) Conecte o ESP32.  
4) Suba o código.  
5) Abra o Serial Monitor (115200 baud).  
6) Acesse o cliente MQTT:
- https://www.hivemq.com/demos/websocket-client/
- Conecte em `broker.hivemq.com:1883`
- Assine `gs/sono/estado`
7) Teste:
- Botão solto → 🟢 LED verde + “OK” no MQTT  
- Botão apertado → 🔴 LED vermelho + 🔊 buzzer + “SONO” no MQTT

------------------------------------------------------------------

🎥 Roteiro Resumido (para o vídeo)
----------------------------------
- Explicar objetivo: detectar sonolência e enviar para MQTT  
- Mostrar hardware: ESP32, LEDs, buzzer e botão  
- Mostrar código: Wi-Fi, MQTT, estados  
- Demonstrar botão → LED vermelho + buzzer + mensagem SONO  
- Voltar para estado OK  
- Encerrar mostrando aplicabilidade no mundo real  

------------------------------------------------------------------

🚀 Tecnologias Utilizadas
--------------------------
- ESP32  
- Arduino Framework  
- MQTT  
- HiveMQ  
- Comunicação em tempo real  
- Sensores e atuadores básicos  

------------------------------------------------------------------

👨‍💻 Desenvolvido por
----------------------
RM94618 - Enzo Vazquez Sartorelli
RM94524 - Eduardo de Oliveira Nistal
Global Solution – IoT  
FIAP – Engenharia de Software  

