int JoyAX = 255, JoyAY = 255;  // Variáveis Globais para receberem os valores dos eixo X e Y do JoyStick A
int JoyBX = 90, JoyBY = 90;    // Variáveis Globais para receberem os valores dos eixo X e Y do JoyStick B
// As variáveis JoyAX e JoyBY não serão utilizadas neste código


// Variável Global para armazenar os caracteres que o arduino receber do celular via módulo bluetooth
char DadosRecebidos;
char F = 'f';
char R = 'r';

void setup() {

  Serial.begin(9600);  // Inicializando comunicação Serial Padrão nas portas 0 e 1 do arduino
  Serial.println("TransitApp");  

  pinMode(8, OUTPUT);   // Led - Seta Direita Dianteira
  pinMode(9, OUTPUT);   // Led - Lanterna / Luz de Freio / Luz de Ré / Seta Direita Trazeira
 
  // Configuração inicial do painel do aplicativo TransitApp
  Serial.println("*.kwl");
  Serial.println("clear_panel()");
  Serial.println("set_grid_size(10,5)");
  Serial.println("add_text(4,2,large,C,TransitApp,245,240,245)");
  Serial.println("add_switch(7,4,1,P,p,0,0)");
  Serial.println("add_switch(0,4,1,F,f,0,0)");
  Serial.println("add_free_pad(7,1,10,170,0,50,C,D)");
  Serial.println("add_free_pad(0,1,0,510,0,50,A,B)");
  Serial.println("run()");
  Serial.println("*");
 
}





void loop() {


DadosRecebidos = Serial.read();
Serial.println(F);
Serial.println(R);
Serial.println(DadosRecebidos);
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

  if (JoyAY <= 250 || F == 'F') {  // FRENTE - quando o bastão do joystick virtual é empurado para cima (posição central é = 255, todo para cima = 0)

    // Controle da Ponte H
    digitalWrite(8, HIGH);            // ativa pino ponte H com valor LOW para que o veículo se movimente para frente
    digitalWrite(9, LOW);            // ativa pino ponte H com o valor da variável Pot (controle de aceleração)       
  } 

  else if (JoyAY >= 260 || R == 'R') {  // RÉ - quando o bastão do joystick virtual é empurado para baixo (posição central é = 255, todo para baixo = 510)
    // Controle da Ponte H
  
    digitalWrite(8, LOW);  // ativa pino ponte H com o valor da variável Pot (controle de aceleração)
    digitalWrite(9, HIGH);  // ativa pino ponte H com valor LOW para que o veículo se movimente para trás
    
  }

  else {                  // MOTOR PARADO
    
    analogWrite(8, LOW);  // desativa as duas portas da ponte h
    analogWrite(9, LOW);  // desativa as duas portas da ponte h

  }

  if (DadosRecebidos == 'P') {
    F = 'F';
  }
  else if (DadosRecebidos =='p') {
    F ='f';
  }
  if (DadosRecebidos == 'F') {
    R = 'R';
  }
  else if (DadosRecebidos == 'f') {
    R = 'r';
  }
   
}