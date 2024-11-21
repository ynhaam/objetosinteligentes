### **Gestão Inteligente de Estoque com IoT**
Este projeto visa implementar uma solução prática e eficiente para monitorar níveis de estoque em tempo real, utilizando sensores IoT, microcontroladores (ESP32) e LEDs indicadores. A ideia é automatizar o processo de controle de estoque, facilitando a tomada de decisões e reduzindo desperdícios.

 **Funcionamento e uso:**
 
O sistema mede o nível de estoque utilizando um **sensor ultrassônico**, processa as informações com o **ESP32**, e notifica visualmente por meio de LEDs:  

🟢 Verde: Estoque em nível ideal.  
🟡 Amarelo: Estoque em metade da capacidade, sinalizando atenção.  
🔴 Vermelho: Estoque baixo, indicando necessidade de reposição imediata.  

Além da notificação local, os dados são transmitidos para um aplicativo remoto via MQTT, permitindo acompanhamento em tempo real e ações proativas.  

**Reproduzindo o Projeto:**

👉 Montagem: Conecte o sensor ao ESP32 conforme o diagrama de montagem no artigo fornecido no repositório. Ligue o LED semáforo a saídas digitais.

👉 Código: Faça o upload do código disponível neste repositório para a ESP32 via IDE Arduino, inclusive o Firmata. Personalize os valores de limite do sensor e as configurações MQTT.

👉 Testes: Verifique a funcionalidade do sensor e a correspondência dos LEDs com os níveis do estoque. Confirme a comunicação MQTT com o aplicativo.

**Descrição do Hardware:**
- ESP32: Microcontrolador responsável pelo processamento e comunicação.
- Sensor Ultrassônico HC-SR04: Mede a distância para determinar o nível do estoque.
- LED Semáforo: Três LEDs (vermelho, amarelo, verde) que indicam o estado do estoque.
- Protoboard e Jumpers: Para montagem.
- Resistores: Proteção dos LEDs.

**Observações Importantes:**

Não esqueça de ler o artigo, principalmente a bibliografia, pois lá consta todas as fontes que me ajudou a construir esse projeto, na qual tenho muito carinho!
