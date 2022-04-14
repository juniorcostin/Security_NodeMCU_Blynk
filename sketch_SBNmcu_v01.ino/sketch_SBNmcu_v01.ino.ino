//Inicialização do Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID  "TMPLlZOW2hdU"

//Bibliotecas
#include <ESP8266WiFi.h> //ESP8266
#include <BlynkSimpleEsp8266.h> //Blynk ESP8266


//Valriáveis
char auth[] = "ktrkh6mRvRSxIw5Uewyt3KwD04mLbzTn"; //Token para comunicação com o Blynk
char ssid[] = "Costin 2.4G"; //Nome da rede que deve se conectar
char pass[] = "63021922"; //Senha da rede que deve se conectar
int alarme = 0;


//Definições
#define PIN_SENSOR D4  //Pino D4 como Pino para o Sensor de Presença
#define PIN_ALARME D1 //Pino D1 Para acionar a Sirene




// Timer Blynk para leitura do sensor ultrasônico
BlynkTimer TimerSensorPresenca;
  void LerSensorPresenca(){
    int sinal = digitalRead(PIN_SENSOR);
    String traducao = "";
       if (alarme == 1){
        if (sinal == HIGH){
          digitalWrite(PIN_ALARME, HIGH);
          traducao = "Com movimentação no Momento";
        }
        if (sinal == LOW){
          digitalWrite(PIN_ALARME, LOW);
          traducao = "Sem Movimentação no Momento";
        }
       }
       else{
        traducao = "Alarme Desligado";
        digitalWrite(PIN_ALARME, LOW);
       }
    Blynk.virtualWrite(V0, traducao);  //Pino Virtual 0 está definido no Blynk para coletar os dados do Ultrasônico
    Serial.println(traducao);
    delay(2000);  
  }

  BLYNK_WRITE(V1){ //Parametro da biblioteca Blynk para iniciar o Pino Virtual 0 previamente configurado na paltaforma dentro do Template
  int ValorDoPino0 = param.asInt();//variável da biblioteca Blynk para a leitura dos botões
  if(ValorDoPino0 == 1){  //IF para caso o valor da variável ValorDoPino0 for igual a 1 deixa-lo em estado HIGH
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
  if(ValorDoPino0 == 0){  //IF para caso o valor da variável ValorDoPino0 for igual a 0 deixa-lo em estado LOW
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
  //Definição dos Pinos como Saida de Dados
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_ALARME, OUTPUT);
  
  Serial.begin(9600); //Inicia o monitor Serial
  Blynk.begin(auth, ssid, pass);//Inicia o blynk utilizando as variáveis AUTH, SSID, PASS
  TimerSensorPresenca.setInterval(2000L, LerSensorPresenca);//Inicia o Timer com tempo de envio de 2000 milisegundos
  ESP.wdtDisable();
  
  
}
void loop(){
  ESP.wdtFeed();//Alimenta o HW WDT.
  Blynk.run();//Inicializa o Blynk;
  TimerSensorPresenca.run();//Inicializa o Timer 
  
}
