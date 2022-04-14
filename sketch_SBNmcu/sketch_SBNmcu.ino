//Inicialização do Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID  "**********" //Template criado dentro da plataforma Blink

//Bibliotecas
#include <ESP8266WiFi.h> //Bibliote do ESP8266
#include <BlynkSimpleEsp8266.h> //Biblioteca do Blynk para ESP8266

//Valriáveis
char auth[] = "***********"; //Token para comunicação com o Blynk
char ssid[] = "***********"; //Nome da rede que o NODEMCU deve se conectar
char pass[] = "***********"; //Senha da rede que o NODEMCU deve se conectar
int alarme = 0; //Variável para tratamento de erro

//Definições
#define PIN_SENSOR D4  //Pino D4 como Pino para o Sensor de Presença
#define PIN_ALARME D1 //Pino D1 Para acionar a Sirene
#define PIN_LUZ D2 //Pino D2 para acionar uma luz no momento em que a Sirene for disparada

// Timer Blynk para leitura do sensor de presença
BlynkTimer TimerSensorPresenca;
void LerSensorPresenca(){
  int sinal = digitalRead(PIN_SENSOR); //variável interna para a leitura do sensor de presença
  String traducao = ""; //variável que faz a conversão dos dados enviados pelo sensor para uma String
    if (alarme == 1){
      if (sinal == HIGH){
        digitalWrite(PIN_ALARME, HIGH);
        digitalWrite(PIN_LUZ, HIGH);
        traducao = "Com movimentação no Momento"; //traduz o valor 1 enviado pelo sensor como uma string informando que há presença no momento
      }
      if (sinal == LOW){
        digitalWrite(PIN_ALARME, LOW);
        digitalWrite(PIN_LUZ, LOW);
        traducao = "Sem Movimentação no Momento"; //traduz o valor 0 enviado pelo sensor como uma string informando que não há presença no momento
      }
    }
    else{
      digitalWrite(PIN_ALARME, LOW);
      digitalWrite(PIN_LUZ, LOW);
      traducao = "Alarme Desligado";  
    }
  Blynk.virtualWrite(V0, traducao);  //Pino Virtual 0 está definido no Blynk para coletar os dados do Ultrasônico
  Serial.println(traducao); //print da variável no monitor serial com delay de 2s 
  delay(2000);  
}

BLYNK_WRITE(V1){ //Parametro da biblioteca Blynk para iniciar o Pino Virtual 0 previamente configurado na paltaforma dentro do Template
  int ValorDoPino0 = param.asInt();//variável da biblioteca Blynk para a leitura dos botões
  if(ValorDoPino0 == 1){  //IF para no momento em que o botão de alarme for apertado popular a variável alarme com 1 e realizar um som caracteristico de alarme junto com a sirene
    alarme = 1;
    digitalWrite(PIN_ALARME, HIGH);
    delay(100);
    digitalWrite(PIN_ALARME, LOW);
    delay(100);
    digitalWrite(PIN_ALARME, HIGH);
    delay(100);
    digitalWrite(PIN_ALARME, LOW);
  } 
  else {
  }
  if(ValorDoPino0 == 0){  //IF para no momento em que o botão de alarme for apertado popular a variável alarme com 0 e realizar um som caracteristico de alarme junto com a sirene
    alarme = 0;
    digitalWrite(PIN_ALARME, HIGH);
    delay(100);
    digitalWrite(PIN_ALARME, LOW);
    delay(100);
    digitalWrite(PIN_ALARME, HIGH);
    delay(100);
    digitalWrite(PIN_ALARME, LOW);
  } 
  else {
  }
}

void setup(){
  //Definição dos Pinos como Saida e Entrada de Dados
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_ALARME, OUTPUT);
  pinMode(PIN_LUZ, OUTPUT);
  
  Serial.begin(9600); //Inicia o monitor Serial
  Blynk.begin(auth, ssid, pass);//Inicia o blynk utilizando as variáveis AUTH, SSID, PASS
  TimerSensorPresenca.setInterval(2000L, LerSensorPresenca);//Inicia o Timer Blynk com tempo de envio de 2000 milisegundos
  ESP.wdtDisable(); //Inicia a função de WatchDog fisica dentro do ESP8266  
}

void loop(){
  ESP.wdtFeed();//Alimenta o WatchDog
  Blynk.run();//Inicializa o Blynk
  TimerSensorPresenca.run();//Inicializa o Timer 
  
}
