//Inicialização do Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID  "*******"

//Bibliotecas
#include <ESP8266WiFi.h> //ESP8266
#include <BlynkSimpleEsp8266.h> //Blynk ESP8266


//Valriáveis
char auth[] = "******"; //Token para comunicação com o Blynk
char ssid[] = "******"; //Nome da rede que deve se conectar
char pass[] = "******"; //Senha da rede que deve se conectar


//Definições
#define PIN_SENSOR D4  //Pino D4 como Pino para o Sensor de Presença
#define PIN_LED D1 //Pino D1 como Echo para o Sensor Ultrasonico


// Timer Blynk para leitura do sensor ultrasônico
BlynkTimer TimerSensorPresenca;
  void LerSensorPresenca(){
    int sinal = digitalRead(PIN_SENSOR);
    String traducao = "";
    if (sinal == HIGH){
      digitalWrite(PIN_LED, HIGH);
    }
    else{
      digitalWrite(PIN_LED, LOW);
    }
    if (sinal == 1){
      traducao = "Com movimentação no Momento";
    }
    else{
      traducao = "Sem Movimentação no Momento";
    }
    
    Blynk.virtualWrite(V0, traducao);  //Pino Virtual 0 está definido no Blynk para coletar os dados do Ultrasônico
    Serial.println(traducao);
    delay(2000);
  }

/******** INICIANDO LEITURA DOS RELES *************/
/*PINO NODEMCU D0
BLYNK_WRITE(V1){ //Parametro da biblioteca Blynk para iniciar o Pino Virtual 0 previamente configurado na paltaforma dentro do Template
  int ValorDoPino0 = param.asInt();//variável da biblioteca Blynk para a leitura dos botões
  if(ValorDoPino0 == 1){  //IF para caso o valor da variável ValorDoPino0 for igual a 1 deixa-lo em estado HIGH
    digitalWrite(D0, HIGH);
  } else {
    }
  if(ValorDoPino0 == 0){  //IF para caso o valor da variável ValorDoPino0 for igual a 0 deixa-lo em estado LOW
    digitalWrite(D0, LOW);
  } else {
    }
}*/


void setup()
{
  //Definição dos Pinos como Saida de Dados
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_LED, OUTPUT);
  
  Serial.begin(9600); //Inicia o monitor Serial
  Blynk.begin(auth, ssid, pass);//Inicia o blynk utilizando as variáveis AUTH, SSID, PASS
  TimerSensorPresenca.setInterval(2000L, LerSensorPresenca);//Inicia o Timer com tempo de envio de 2000 milisegundos
}
void loop()
{
  Blynk.run();//Inicializa o Blynk;
  TimerSensorPresenca.run();//Inicializa o Timer 
}
