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
#define IN3 3
#define IN4 4
#define ENA 9


void setup() {

  Serial.begin(9600);  // Inicializando comunicação Serial Padrão nas portas 0 e 1 do arduino
  Serial.println("PROJETO FUSCA BLUETOOTH RC");
  servo.attach(7);  // Informando que o servo motor está conectado ao pino digital 7 do Arduino

  pinMode(3, OUTPUT);   // Leds - Farol
  pinMode(4, OUTPUT);   // Buzzer - Buzinha
  pinMode(5, OUTPUT);   // Ponte H
  pinMode(6, OUTPUT);   // Ponte H
  pinMode(7, OUTPUT);   // Led - Seta Esquerda Dianteira
  pinMode(8, OUTPUT);   // Led - Seta Direita Dianteira
  pinMode(9, OUTPUT);   // Led - Lanterna / Luz de Freio / Luz de Ré / Seta Direita Trazeira
  pinMode(10, OUTPUT);  // Led - Lanterna / Luz de Freio / Luz de Ré / Seta Esquerda Trazeira
  pinMode(11, INPUT);


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

  int aux = 0;  // variável para auxiliar na converasão dos valores do joystick para o padrão PWM de 0 a 255

  if (JoyAY <= 250) {  // FRENTE - quando o bastão do joystick virtual é empurado para cima (posição central é = 255, todo para cima = 0)

    if (Velocidade == 1) {
      aux = map(JoyAY, 260, 510, 20, 190);  // Velocidade 01 - LENTA
    } else {
      aux = map(JoyAY, 260, 510, 20, 255); // Velocidade 02 - RÁPIDA
    }
    // Controle da Ponte H
    digitalWrite(8, LOW);            // ativa pino ponte H com valor LOW para que o veículo se movimente para frente
    digitalWrite(9, HIGH);            // ativa pino ponte H com o valor da variável Pot (controle de aceleração)
    analogWrite(10, aux);
    Serial.print(" Frente PWM: ");  // Mostra no Monitor Serial
    Serial.println(aux);            // Mostra no Monitor Serial os valores de aux
    TempLuzFreio = millis();        // variável TempSetaDireita recebe o tempo atual
                                    // Luz de Ré
  

  } 

  else if (JoyAY >= 260) {  // RÉ - quando o bastão do joystick virtual é empurado para baixo (posição central é = 255, todo para baixo = 510)
    if (Velocidade == 1) {
      aux = map(JoyAY, 260, 510, 20, 190);
    } else {
      aux= map(JoyAY, 260, 510, 20, 255);
    }
    // Controle da Ponte H
  
    digitalWrite(8, HIGH);  // ativa pino ponte H com o valor da variável Pot (controle de aceleração)
    digitalWrite(9, LOW);  // ativa pino ponte H com valor LOW para que o veículo se movimente para trás
    analogWrite(10, aux);
    Serial.print(" Trás PWM: ");  // Mostra no Monitor Serial
    Serial.println(aux);

    //Serial.print(" Re PWM: "); // Mostra no Monitor Serial
    //Serial.println(aux); // Mostra no Monitor Serial os valores de aux

    // Luz de Ré
    

    TempLuzFreio = millis();  // variável TempSetaDireita recebe o tempo atual
  }

  else {                  // MOTOR PARADO
    
    analogWrite(8, LOW);  // desativa as duas portas da ponte h
    analogWrite(9, LOW);  // desativa as duas portas da ponte h

    // Luz de Ré
  
    // GERENCIA CONTROLE DA LUZ DE FREIO, SETAS, LENTERNA E PISCA ALERTA DO FUSCA
    // if ((Pisca_Ativo == LOW) && (SetaD_Ativo == LOW) && (SetaE_Ativo == LOW)) {
    // Verifica se as variáveis indicando atividade do pisca, seta direita e seta esquerda estão todas desativadas.
    if (millis() - TempLuzFreio < 50) {
      // Se o tempo decorrido desde a última atualização da luz de freio for menor que 150 milissegundos:
      // digitalWrite(9, LOW);
      //  Serial.println(" luz freio apagado - 150");
      // Apaga os LEDs conectados aos pinos 9 e 10 e imprime uma mensagem indicando a condição.
    } else if ((millis() - TempLuzFreio > 50) && (millis() - TempLuzFreio < 650)) {
      // Se o tempo decorrido estiver entre 300 e 1000 milissegundos:
      
     
    // }
    }
  }
   if (DadosRecebidos == 'Z') {
    Velocidade = 1;
    tone(4, 400, 100);
  }
  if (DadosRecebidos == 'X') {
    Velocidade = 2;
    tone(4, 400, 100);
    delay(100);
    tone(4, 200, 100);
  }
}


