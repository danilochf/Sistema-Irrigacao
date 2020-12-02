//definição dos pinos do modulo de umidade, um para a leitura analógica e outro para a leitura digital
#define pino_sinal_analogico A0
#define sensor_Umidade_Digital 8

//declaração das variaveis das portas de cada Relê
int porta_rele1 = 9;
int porta_rele2 = 12;
int porta_rele3 = 13;

//declaração das variaveis de leitura para o modulo de umidade
int valor_analogico;
int valor_Digital;

//declaração da variavel botão, somente para um controle manual
int botao = 10;

//Incluindo a biblioteca Servo
#include <Servo.h>
Servo myservo;  //Criando objeto Servo


int pos = 0;    //variavel para armazenar a posição do servo motor


//Inicio Modulo RTC


#include <virtuabotixRTC.h> //biblioteca para o RTC DS1302
// definições dos pinos do modulo RTC
#define   clk   5
#define   dat   6
#define   rst   7

// definições das variveis auxiliares, será utilizada somente uma vez com a data e horário atual
#define   segN       06
#define   minN       45
#define   horN       22
#define   dsemN      5
#define   dmesN     03
#define   mesN        9
#define   anoN     2020

virtuabotixRTC   myRTC(clk, dat, rst); //declara objeto para o RTC

//Fim Modulo RTC

void setup() {

  myservo.attach(11);
  myservo.write(0);
  Serial.begin(9600);
  
  pinMode(pino_sinal_analogico, INPUT);  //define o pino analógico do sensor de umidade como entrada
  pinMode(sensor_Umidade_Digital, INPUT); //define o pino digital do sensor de umidade como entrada

  pinMode(botao, INPUT_PULLUP); // define o pino do botao como entrada "INPUT"

  //Define os pinos para dos relês como saida e inicializa os como desligados
  pinMode(porta_rele1, OUTPUT);
  digitalWrite(porta_rele1, HIGH);

  pinMode(porta_rele2, OUTPUT);
  digitalWrite(porta_rele2, HIGH);

  pinMode(porta_rele3, OUTPUT);
  digitalWrite(porta_rele3, HIGH);

  
  //Envie o código uma vez ao Arduino para carregar os dados no RTC. Depois comente a linha abaixo e envie novamente. 
  //myRTC.setDS1302Time(segN, minN, horN, dsemN, dmesN, mesN, anoN);
  //Depois disso o módulo assume a data e horário e com ajuda da bateria o mantém atualizado.

}

void loop() {
  
  //========== Controle Manual de irrigação ===============
  if(digitalRead(botao) == LOW) // Se o botão for pressionado
  {
    if(digitalRead(porta_rele1) == LOW)
    {
      digitalWrite(porta_rele1, HIGH); //Desliga rele 1
      delay(2000);
      for (pos = 0; pos <= 90; pos += 1) {        
        myservo.write(pos); //liga Servo, fechando assim o registro      
        delay(200);                       
      }      
    }
    else
    {
      digitalWrite(porta_rele1, LOW); //Liga rele 1
      for (pos = 90; pos >= 0; pos -= 1) { 
        myservo.write(pos); //liga Servo, abrindo assim o registro
        delay(200);                       
      }
    }           
  }
  //========== Fim do Controle Manual de irrigação ===============  

  //======= Inicio Controle de Irrigação Automatica ===============
  //Le o valor do pino Analógico e do pino digital do sensor de Umidade
  valor_analogico = analogRead(pino_sinal_analogico);
  valor_Digital = digitalRead(sensor_Umidade_Digital); //Somente faço a leitura, não estou usando

  //Mostra o valor da porta analogica e digital no serial monitor
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);

  Serial.print("Porta Digital: ");
  Serial.print(valor_Digital);  

  if(myRTC.hours == 6 || myRTC.hours == 18) //Programado para regar duas vezes ao dia com duração de uma hora
  {       
    //Solo umido
    if (valor_analogico > 0 && valor_analogico < 400)
    {
      Serial.println(" Status: Solo umido");
      digitalWrite(porta_rele1, HIGH); //Desliga rele 1
      digitalWrite(porta_rele2, HIGH); //Desliga rele 2
      digitalWrite(porta_rele3, HIGH); //Desliga rele 3   
      
    }
 
    //Solo com umidade moderada 1
    if (valor_analogico > 400 && valor_analogico < 600)
    {
      Serial.println(" Status: Umidade moderada");
      while (myRTC.hours == 6 || myRTC.hours == 18)
      {
        digitalWrite(porta_rele1, HIGH); //Desliga rele 1
        digitalWrite(porta_rele2, LOW); //Liga rele 2
        digitalWrite(porta_rele3, HIGH); //Desliga rele 3
        DS1302(); //chama o método para atualizar a hora que vem RTC  
      }
      digitalWrite(porta_rele1, HIGH); //Desliga rele 1
      digitalWrite(porta_rele2, HIGH); //Desliga rele 2
      digitalWrite(porta_rele3, HIGH); //Desliga rele 3
      delay(2000);
      
    }

    //Solo com umidade moderada 2
    if (valor_analogico > 600 && valor_analogico < 800)
    {
      Serial.println(" Status: Umidade moderada");
      while (myRTC.hours == 6 || myRTC.hours == 18)
      {
        digitalWrite(porta_rele1, LOW); //Liga rele 1
        digitalWrite(porta_rele2, LOW); //Liga rele 2
        digitalWrite(porta_rele3, LOW); //Liga rele 3
        DS1302(); //chama o método para atualizar a hora que vem RTC        
      }
      digitalWrite(porta_rele1, HIGH); //Desliga rele 1
      digitalWrite(porta_rele2, HIGH); //Desliga rele 2
      digitalWrite(porta_rele3, HIGH); //Desliga rele 3
      delay(2000);
      
    }
 
    //Solo seco
    if (valor_analogico > 800 && valor_analogico < 1024)
    {
      Serial.println(" Status: Solo seco");
      while (myRTC.hours == 6 || myRTC.hours == 18)
      {
        digitalWrite(porta_rele1, LOW); //Liga rele 1
        digitalWrite(porta_rele2, LOW); //Liga rele 2
        digitalWrite(porta_rele3, LOW); //Liga rele 3
        DS1302(); //chama o método para atualizar a hora que vem RTC       
      }
      digitalWrite(porta_rele1, HIGH); //Desliga rele 1
      digitalWrite(porta_rele2, HIGH); //Desliga rele 2
      digitalWrite(porta_rele3, HIGH); //Desliga rele 3
      delay(2000);
    }
    
              
  }
  //======= FIM Controle de Irrigação Automatica ===============
  
  DS1302(); //chama o método para atualizar a hora que vem RTC 

}

void DS1302()
{
  myRTC.updateTime(); //faz leitura do DS1302

  // Imprime informações
  Serial.print(" -> ");
  week(myRTC.dayofweek); 
  Serial.print(" | ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" | ");  
  Serial.print(myRTC.hours);
  Serial.print(":");  
  Serial.print(myRTC.minutes);
  Serial.print(":");  
  Serial.println(myRTC.seconds);
  delay(2000);  
}

void week(int dayW)
{
  
  switch(dayW)
  {
    case 1: Serial.print("Dom"); break;
    case 2: Serial.print("Seg"); break;
    case 3: Serial.print("Ter"); break;
    case 4: Serial.print("Qua"); break;
    case 5: Serial.print("Qui"); break;
    case 6: Serial.print("Sex"); break;
    case 7: Serial.print("Sab"); break;
   
  } 
  
}
