/*
              **********************************************
                      PROJETO MINI GOL QUADRADO RC
                           VERSÃO BLUETOOTH
                      CANAL ARDUINO PARA MODELISMO
              **********************************************


  Para conferir as Vídeo Aulas Gratuítas desse projeto, acesse:
  https://www.youtube.com/ArduinoParaModelismo

  Aprenda Arduino para modelismo: https://www.arduinoparamodelismo.com

   Atenção Siga atentamente as instruções das vídeos aulas e e-book para a montagem do hardware
   
   Playlist com todos os vídeos deste projeto:https://www.youtube.com/playlist?list=PLcWVEPpBZCFrAGE-x5P0iJ3kxTMPvpj4V
   
  Desenvolvido por Aldeir de Souza Moreira - aldeirsm@gmail.com - https://www.youtube.com/ArduinoParaModelismo
  C 2024 - Todos os direitos reservados
*/

/* DÊ UM PASSO A MAIS...

🚀 Transforme suas miniaturas em Verdadeiras obras-primas com o Curso de Arduino para Modelismo 
Se Inscreva Aqui 👉 https://arduinoparamodelismo.com

✅ Aprenda a usar Arduino e ESP32 para dar Vida às suas Miniaturas,
Controlando tudo via controle remoto de uma forma simples e com baixo custo!

Você ainda vai contar com suporte via WhatsApp diretamente comigo, Aldeir Moreira!

💡 Realize seu sonho e ainda tenha a possibilidade de fazer uma renda extra, automatizando miniaturas por encomendas!  
Se Inscreva Aqui 👉 https://arduinoparamodelismo.com

*/


#include <Servo.h>  // Incluindo biblioteca Servo

Servo servo;  // Criando Objeto Servo, para controle do Servo Motor

uint32_t TempLuzFreio, TempPiscaAlerta, TempSetaDireita, TempSetaEsquerda, bip_tensao, temp;  // Variáveis necessárias para contagem de tempo em milis segundos (substitui a função delay) - (variáveis uint32_t são inteiros de 32 bits sem sinal)

int JoyAX = 255, JoyAY = 255;  // Variáveis Globais para receberem os valores dos eixo X e Y do JoyStick A
int JoyBX = 90, JoyBY = 90;    // Variáveis Globais para receberem os valores dos eixo X e Y do JoyStick B
// As variáveis JoyAX e JoyBY não serão utilizadas neste código

// Variáveis Globais para auxiliar na identificação de quando um botão foi pressionado no celular
boolean Farol_Ativo = 0;
boolean Pisca_Ativo = 0;
boolean SetaD_Ativo = 0;
boolean SetaE_Ativo = 0;
boolean LuzRe_Ativo = 0;
boolean LuzFreio_Ativo = 0;

float tensao = 0;

int Velocidade = 2;

// Variável Global para armazenar os caracteres que o arduino receber do celular via módulo bluetooth
char DadosRecebidos;

#define IN1 5
#define IN2 6
#define ENA 9


void setup() {

  Serial.begin(9600);  // Inicializando comunicação Serial Padrão nas portas 0 e 1 do arduino
  Serial.println("PROJETO FUSCA BLUETOOTH RC");
  servo.attach(2);  // Informando que o servo motor está conectado ao pino digital 7 do Arduino

  pinMode(3, OUTPUT);   // Leds - Farol
  pinMode(4, OUTPUT);   // Buzzer - Buzinha
  pinMode(5, OUTPUT);   // Ponte H
  pinMode(6, OUTPUT);   // Ponte H
  pinMode(7, OUTPUT);   // Led - Seta Esquerda Dianteira
  pinMode(8, OUTPUT);   // Led - Seta Direita Dianteira
  pinMode(9, OUTPUT);   // Led - Lanterna / Luz de Freio / Luz de Ré / Seta Direita Trazeira
  pinMode(10, OUTPUT);  // Led - Lanterna / Luz de Freio / Luz de Ré / Seta Esquerda Trazeira



  ///////////// Build panel in app

  // Serial.println("*.kwl");
  // Serial.println("clear_panel()");
  // Serial.println("set_grid_size(10,5)");
  // Serial.println("add_text(5,1,medium,L,Volts,255,0,0,)");
  // Serial.println("add_text(4,1,medium,R,4.20,255,0,0,T)");
  // Serial.println("add_text(3,2,large,L,PROJETO GOL RC,245,240,245,)");
  // Serial.println("add_text(4,3,large,C,            ARDUINO PARA MODELISMO,245,240,245,)");
  // Serial.println("add_text(3,4,small,L,       www.ArduinoParaModelismo.com,245,240,245,)");
  // Serial.println("add_button(2,4,11,G,g)");
  // Serial.println("add_button(0,0,4,I,i)");
  // Serial.println("add_button(9,0,5,H,h)");
  // Serial.println("add_button(9,4,16,E,e)");
  // Serial.println("add_switch(7,4,1,P,p,0,0)");
  // Serial.println("add_switch(0,4,1,F,f,0,0)");
  // Serial.println("add_free_pad(7,1,10,170,0,50,C,D)");
  // Serial.println("add_free_pad(0,1,0,510,0,50,A,B)");
  // Serial.println("add_gauge(2,0,4,0,100,100,Z,3.5v,4.2v,10,10)");
  // Serial.println("add_buzzer(6,1,1,S,a,false,100.00)");
  // Serial.println("add_led(3,1,1,L,0,255,0)");
  // Serial.println("set_panel_notes(,,,)");
  // Serial.println("run()");
  // Serial.println("*");

  Serial.println("*.kwl");
  Serial.println("clear_panel()");
  Serial.println("set_grid_size(10,5)");
  Serial.println("add_text(5,1,medium,L,Volts,255,0,0,)");
  Serial.println("add_text(4,1,medium,R,4.02,255,0,0,T)");
  Serial.println("add_text(3,2,large,L,PROJETO GOL RC,245,240,245,)");
  Serial.println("add_text(4,3,large,C,            ARDUINO PARA MODELISMO,245,240,245,)");
  Serial.println("add_text(3,4,small,L,       www.ArduinoParaModelismo.com,245,240,245,)");
  Serial.println("add_button(2,4,11,G,g)");
  Serial.println("add_button(9,0,5,H,h)");
  Serial.println("add_button(9,4,16,E,e)");
  Serial.println("add_button(8,0,4,I,i)");
  Serial.println("add_button(1,0,22,X,x)");
  Serial.println("add_button(0,0,21,Z,z)");
  Serial.println("add_switch(7,4,1,P,p,0,0)");
  Serial.println("add_switch(0,4,1,F,f,0,0)");
  Serial.println("add_free_pad(7,1,10,170,0,50,C,D)");
  Serial.println("add_free_pad(0,1,0,510,0,50,A,B)");
  Serial.println("add_gauge(2,0,4,0,100,75,Z,3.5v,4.2v,10,10)");
  Serial.println("add_buzzer(6,1,1,S,a,false,100.00)");
  Serial.println("add_led(3,1,1,L,0,255,0)");
  Serial.println("set_panel_notes(,,,)");
  Serial.println("run()");
  Serial.println("*");




  // Emite um bip ao ligar o Jeep
  tone(4, 1000, 100);
  delay(100);
  tone(4, 800, 100);
  delay(100);
  tone(4, 600, 100);
  delay(100);
  tone(4, 400, 100);
  delay(100);
  tone(4, 200, 100);
  delay(100);
}


/* DÊ UM PASSO A MAIS...

🚀 Transforme suas miniaturas em Verdadeiras obras-primas com o Curso de Arduino para Modelismo 
Se Inscreva Aqui 👉 https://arduinoparamodelismo.com

✅ Aprenda a usar Arduino e ESP32 para dar Vida às suas Miniaturas,
Controlando tudo via controle remoto de uma forma simples e com baixo custo!

Você ainda vai contar com suporte via WhatsApp diretamente comigo, Aldeir Moreira!

💡 Realize seu sonho e ainda tenha a possibilidade de fazer uma renda extra, automatizando miniaturas por encomendas!  
Se Inscreva Aqui 👉 https://arduinoparamodelismo.com

*/



void loop() {

DadosRecebidos = Serial.read();
  
  if (DadosRecebidos > 0) {}
  if (DadosRecebidos == 'A') {
    JoyAX = Serial.parseInt();
    while (DadosRecebidos != 'B') {
      if (Serial.available()) {
        DadosRecebidos = Serial.read();
        if (DadosRecebidos == 'Y') {
          JoyAY = Serial.parseInt();
        }
      }
    }
  }
  if (DadosRecebidos == 'C') {
    JoyBX = Serial.parseInt();
    while (DadosRecebidos != 'D') {
      if (Serial.available()) {
        DadosRecebidos = Serial.read();
        if (DadosRecebidos == 'Y') {
          JoyBY = Serial.parseInt();
        }
      }
    }
  }

  servo.write(JoyBX);

  int aux = 0;
  if (JoyAY <= 250) {
    if (Velocidade == 1) {
      aux = map(JoyAY, 250, 0, 20, 190);
    } else {
      aux = map(JoyAY, 250, 0, 20, 255);
    }
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, aux);
    digitalWrite(10, LOW);
  } else if (JoyAY >= 260) {
    if (Velocidade == 1) {
      aux = map(JoyAY, 260, 510, 20, 190);
    } else {
      aux = map(JoyAY, 260, 510, 20, 255);
    }
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, aux);
    digitalWrite(10, HIGH);
  } else {
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(10, LOW);
  }

  if (DadosRecebidos == 'Z') Velocidade = 1;
  if (DadosRecebidos == 'X') Velocidade = 2;



  // FAROL e LANTERNA
  if (DadosRecebidos == 'F') {
    // Se o caractere recebido for 'F':
    digitalWrite(3, HIGH);                       // Liga o farol
    Farol_Ativo = HIGH;                          // Atualiza o estado do farol para ativo
    Serial.println(" Botão Farol Pressionado");  // Imprime uma mensagem indicando que o botão do farol foi pressionado
  }

  if (DadosRecebidos == 'f') {
    // Se o caractere recebido for 'f':
    digitalWrite(3, LOW);  // Desliga o farol
    Farol_Ativo = LOW;     // Atualiza o estado do farol para inativo

    // Lanternas
    //  if ((Pisca_Ativo == LOW) && (SetaD_Ativo == LOW) && (SetaE_Ativo == LOW)) {
    // Se nenhum pisca ou seta estiver ativo:
    //  digitalWrite(9, LOW);   // Desliga a lanterna direita
    //}
    Serial.println(" Botão Farol Pressionado");  // Imprime uma mensagem indicando que o botão do farol foi pressionado
  }

  if (Farol_Ativo == HIGH) {
    // Se o farol estiver ativo e nenhum pisca ou seta estiver ativo:
    digitalWrite(9, HIGH);  // Liga a lanterna direita
  }
  ////////////////////
  if (Farol_Ativo == LOW) {
    // Se o farol estiver ativo e nenhum pisca ou seta estiver ativo:
    digitalWrite(9, LOW);  // Liga a lanterna direita
  }
  ////////////////////////
  // Pisca FAROL
  if (DadosRecebidos == 'G') {
    // Se o caractere recebido for 'G':
    digitalWrite(3, !Farol_Ativo);   // Inverte o estado do farol
    Serial.println(DadosRecebidos);  // Imprime o caractere recebido
  }

  if (DadosRecebidos == 'g') {
    // Se o caractere recebido for 'g':
    digitalWrite(3, Farol_Ativo);    // Mantém o estado atual do farol
    Serial.println(DadosRecebidos);  // Imprime o caractere recebido
  }



  // BUZINA
  if (DadosRecebidos == 'E') {  // Verifica se o caractere enviado do celular e recebido pelo módulo Bluetooth é igual a letra E maiúsculo
    tone(4, 400);               // Gera um tom com 400 Hz na porta  4 onde está ligado o Buzzer enquanto o botão estver sendo precionado
    Serial.println("Botão Buzina Pressionado");
  } else if (DadosRecebidos == 'e') {  // Verifica se o caractere enviado do celular e recebido pelo módulo Bluetooth é igual a letra e minúsculo
    tone(4, 400, 5);                   // Faz parar todos os tons gerados na porta  4 onde está ligado o Buzzer após 5 milissegundos
  }



  // PISCA-ALERTA
  if (DadosRecebidos == 'P') {
    // Se o caractere recebido for 'P':
    Pisca_Ativo = HIGH;              // Ativa o pisca-alerta
    ApagaSetas();                    // Desativa as setas
    PiscaAlerta();                   // Ativa o pisca-alerta
    Serial.println(DadosRecebidos);  // Imprime o caractere recebido
    TempPiscaAlerta = millis();      // Armazena o tempo atual para controle do pisca-alerta
  }

  if (DadosRecebidos == 'p') {
    // Se o caractere recebido for 'p':
    Pisca_Ativo = LOW;               // Desativa o pisca-alerta
    ApagaSetas();                    // Desativa as setas
    Serial.println(DadosRecebidos);  // Imprime o caractere recebido
    TempPiscaAlerta = millis();      // Armazena o tempo atual para controle do pisca-alerta
  }

  if (Pisca_Ativo) {
    // Se o pisca-alerta estiver ativo:
    SetaD_Ativo = LOW;                     // Desativa a seta direita
    SetaE_Ativo = LOW;                     // Desativa a seta esquerda
    PiscaAlerta();                         // Ativa o pisca-alerta
    Serial.println("PISCA ALERTA ATIVO");  // Imprime uma mensagem indicando que o pisca-alerta está ativo
  }

  if (DadosRecebidos == 'H') {
    // Se o caractere recebido for 'H':
    SetaD_Ativo = !SetaD_Ativo;      // Inverte o estado da seta direita
    ApagaSetas();                    // Desativa as setas
    Serial.println(DadosRecebidos);  // Imprime o caractere recebido
    TempSetaDireita = millis();      // Armazena o tempo atual para controle da seta direita
  }

  if (SetaD_Ativo) {
    // Se a seta direita estiver ativa:
    SetaE_Ativo = LOW;               // Desativa a seta esquerda
    SetaDireita();                   // Ativa a seta direita
    Serial.println("SETA D ATIVA");  // Imprime uma mensagem indicando que a seta direita está ativa
  }

  if (DadosRecebidos == 'I') {
    // Se o caractere recebido for 'I':
    SetaE_Ativo = !SetaE_Ativo;      // Inverte o estado da seta esquerda
    ApagaSetas();                    // Desativa as setas
    Serial.println(DadosRecebidos);  // Imprime o caractere recebido
    TempSetaEsquerda = millis();     // Armazena o tempo atual para controle da seta esquerda
  }

  if (SetaE_Ativo) {
    // Se a seta esquerda estiver ativa:
    SetaD_Ativo = LOW;               // Desativa a seta direita
    SetaEsquerda();                  // Ativa a seta esquerda
    Serial.println("SETA E ATIVA");  // Imprime uma mensagem indicando que a seta esquerda está ativa
  }



  // Envio de dados para o Celular
  if (millis() - temp > 5000) {
    // Se passaram mais de 5000 milissegundos desde a última execução:
    readVcc();                                  // Chama a função que lê a tensão da bateria
    Serial.print("*T" + String(tensao) + "*");  // Envia via Bluetooth para o celular a Tensão da Bateria em um formato adequado para o aplicativo.

    int bateria = map((tensao * 10), 34, 42, 0, 100);  // Converte a tensão da bateria em porcentagem (3 volts igual a 0%, 4.2 volts igual a 100%).
    Serial.print("*Z" + String(bateria) + "*");        // Envia via Bluetooth para o celular o valor útil em porcentagem da bateria.

    temp = millis();  // Atualiza a variável temp com o tempo atual

    if (tensao > 3.8) {
      Serial.print("*LR0G255B0*");  // Envia via Bluetooth para o celular a cor para o indicador de bateria (verde), formato adequado para o aplicativo.
    } else if (tensao < 3.6) {
      Serial.print("*LR255G0B0*");  // Envia via Bluetooth para o celular a cor para o indicador de bateria (vermelho), formato adequado para o aplicativo.
    } else {
      Serial.print("*LR255G255B0*");  // Envia via Bluetooth para o celular a cor para o indicador de bateria (amarelo), formato adequado para o aplicativo.
    }
  }

  if (tensao < 3.6) {                                      // Verifica se a tensão da bateria é menor que 3.6 volts
    if (millis() - bip_tensao > 10000) {                   // Se passaram mais de 10000 milissegundos desde o último bip de alerta:
      Serial.print("*W*");                                 // Envia via Bluetooth para o celular um comando de alerta
      Serial.println("Tensao baixa, carregue a bateria");  // Imprime uma mensagem indicando tensão baixa no console Serial
      tone(4, 500, 100);                                   // Emite um bip de alerta de tensão baixa
      delay(100);
      tone(4, 200, 200);
      delay(200);
      tone(4, 900, 100);
      bip_tensao = millis();  // Atualiza a variável bip_tensao com o tempo atual
    }
  }
}


/* DÊ UM PASSO A MAIS...

🚀 Transforme suas miniaturas em Verdadeiras obras-primas com o Curso de Arduino para Modelismo 
Se Inscreva Aqui 👉 https://arduinoparamodelismo.com

✅ Aprenda a usar Arduino e ESP32 para dar Vida às suas Miniaturas,
Controlando tudo via controle remoto de uma forma simples e com baixo custo!

Você ainda vai contar com suporte via WhatsApp diretamente comigo, Aldeir Moreira!

💡 Realize seu sonho e ainda tenha a possibilidade de fazer uma renda extra, automatizando miniaturas por encomendas!  
Se Inscreva Aqui 👉 https://arduinoparamodelismo.com

*/


// Função para ler a tensão da alimentação da Bateria
int readVcc() {
  // Configura o registrador ADMUX para medir a referência interna de 1.1V
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);

  delay(2);  // Aguarda 2 milissegundos (tempo de estabilização)

  ADCSRA |= _BV(ADSC);  // Inicia a conversão analógico-digital (AD)
  while (bit_is_set(ADCSRA, ADSC))
    ;  // Aguarda a conclusão da conversão

  uint8_t low = ADCL;   // Lê primeiro o registrador ADCL - trava ADCH
  uint8_t high = ADCH;  // Lê o registrador ADCH - destrava ADCH

  // Combina os valores lidos para obter o resultado da conversão
  tensao = (high << 8) | low;

  // Calcula a tensão em milivolts usando a fórmula: Vcc = 1125300 / tensao
  tensao = 1125300L / tensao;

  // Converte a tensão para volts dividindo por 1000
  tensao = tensao / 1000;

  // Limita a tensão máxima para 4.2V para evitar leituras incorretas
  if (tensao > 4.2) {
    tensao = 4.2;
  }

  // A leitura da tensão está disponível na variável global 'tensao'
  // Serial.println(tensao); // Ativação dessa linha imprimiria a tensão no console Serial (descomente se necessário)
}


// Função para acionar a seta direita
void SetaDireita() {
  // Verifica se passaram mais de 500 milissegundos desde a última execução
  if (millis() - TempSetaDireita > 500) {
    // Inverte o estado dos LEDs conectados aos pinos 7 e 9 (seta direita)
    digitalWrite(7, !digitalRead(7));
    // Emite um breve tom no buzzer
    tone(4, 30, 30);
    TempSetaDireita = millis();  // Atualiza a variável TempSetaDireita com o tempo atual
  }
}

// Função para acionar a seta esquerda
void SetaEsquerda() {
  // Verifica se passaram mais de 500 milissegundos desde a última execução
  if (millis() - TempSetaEsquerda > 500) {
    // Inverte o estado dos LEDs conectados aos pinos 8 e 10 (seta esquerda)
    digitalWrite(8, !digitalRead(8));
    // Emite um breve tom no buzzer
    tone(4, 30, 30);
    TempSetaEsquerda = millis();  // Atualiza a variável TempSetaEsquerda com o tempo atual
  }
}

// Função para acionar o pisca-alerta
void PiscaAlerta() {
  // Verifica se passaram mais de 500 milissegundos desde a última execução
  if (millis() - TempPiscaAlerta > 500) {
    // Inverte o estado dos LEDs conectados aos pinos 7, 9, 8 e 10 (pisca-alerta)
    digitalWrite(7, !digitalRead(7));
    digitalWrite(8, !digitalRead(8));
    // Emite um breve tom no buzzer
    tone(4, 30, 30);
    TempPiscaAlerta = millis();  // Atualiza a variável TempPiscaAlerta com o tempo atual
  }
}

// Função para apagar todas as setas
void ApagaSetas() {
  // Desliga os LEDs conectados aos pinos 7, 9, 8 e 10 (todas as setas)
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

// FIM DO CÓDIGO

/* DÊ UM PASSO A MAIS...

🚀 Transforme suas miniaturas em Verdadeiras obras-primas com o Curso de Arduino para Modelismo 
Se Inscreva Aqui 👉 https://arduinoparamodelismo.com

✅ Aprenda a usar Arduino e ESP32 para dar Vida às suas Miniaturas,
Controlando tudo via controle remoto de uma forma simples e com baixo custo!

Você ainda vai contar com suporte via WhatsApp diretamente comigo, Aldeir Moreira!

💡 Realize seu sonho e ainda tenha a possibilidade de fazer uma renda extra, automatizando miniaturas por encomendas!  
Se Inscreva Aqui 👉 https://arduinoparamodelismo.com

*/
