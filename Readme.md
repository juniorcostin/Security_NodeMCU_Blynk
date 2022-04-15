**System Security with NodeMCU and Blynk**
---

Basicamente é um software que se resume em realizar o monitoramento de uma residência utilizando apenas alguns componentes básicos como um microcontrolador NodeMCU, um módulo rele para Arduino, alguns sensores de presença e por fim uma sirene.

A base do projeto roda em torno da versão free do software Blynk, para realizar a conexão entre o NodeMCU e a internet, para que seja possível realizar o controle de qualquer lugar, e também trabalhar com o envio de notificações caso algo de errado ocorra.

**Análise do código 👨‍💻 e passos para a utilização**

Inicialmente devemos analisar as variáveis necessárias para o funcionamento do Blynk, que são:

**BLYNK_TEMPLATE_ID**
Essa definição é seu template criado dentro do Blynk lembrando que ele deve ser criado selecionando uma placa NodeMCU:
```
#define BLYNK_TEMPLATE_ID  "**********" 
````

**Variáveis para o Blynk**
Essas são as variáveis necessárias para que o Blynk possa iniciar corretamente, denominadas auth, ssid e pass.
Que basicamente são, seu token Blynk que está vinculado ao seu dispositivo, o nome da sua rede wi-fi e a senha da sua rede wi-fi.
````
char auth[] = "***********"; //Token para comunicação com o Blynk
char ssid[] = "***********"; //Nome da rede que o NODEMCU deve se conectar
char pass[] = "***********"; //Senha da rede que o NODEMCU deve se conectar
````

**Variável: alarme**
Essa variável é incrementada toda vez em que o botão dentro do Blynk for acionado, para que fosse possível ligar e desligar o alarme, pois sem a existência dela ele ficaria ligado o tempo todo.
```
int alarme = 0; //Variável para tratamento de erro
```

**Descrição de Pinagem**
Basicamente define os pinos D4, para a leitura do sensor de presença, D1 para o acionamento de um Relé onde se encontra a sirene e o D2 para acionar outro relé que realizara o controle de uma luz.
```
#define PIN_SENSOR D4  //Pino D4 como Pino para o Sensor de Presença
#define PIN_ALARME D1 //Pino D1 Para acionar a Sirene
#define PIN_LUZ D2 //Pino D2 para acionar uma luz no momento em que a Sirene for disparada
```

**Função Timer para Reconhcimento do Blynk**
Essa função realiza todo o processamento dos dados enviados pelo sensor de presença, e realiza esse envio ao Blynk fazendo uma tradução dos dados para uma String que facilita o uso no aplicativo.
```
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
  Blynk.virtualWrite(V0, traducao);  //Pino Virtual 0 está definido no Blynk para coletar os dados do Ultrasônico
  Serial.println(traducao); //print da variável no monitor serial com delay de 2s
  delay(2000);  
}
```

**Configuração dos Pinos Virtuais Criados no Blynk**
È aqui que incrementamos a variável alarme para que seja possível realizar o acionamento do alarme. 
Também configuramos o botão com alguns estados de HIGH e LOW para que fosse possível realizar um som caracteristico de alarmes no momento em que ele fosse ligado ou desligado.
```
BLYNK_WRITE(V1){ //Parametro da biblioteca Blynk para iniciar o Pino Virtual 0 previamente configurado na paltaforma dentro do Template
  int ValorDoPino0 = param.asInt();//variável da biblioteca Blynk para a leitura dos botões
  if(ValorDoPino0 == 1){  //IF para no momento em que o botão de alarme for apertado popular a variável alarme com 1 e realizar um som caracteristico de alarme junto com a sirene
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
  if(ValorDoPino0 == 0){  //IF para no momento em que o botão de alarme for apertado popular a variável alarme com 0 e realizar um som caracteristico de alarme junto com a sirene
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
```

**Void Setup**
Basicamente definimos os pinos como INPUT e OUTPUT, para entrada ou saida dos dados. 
Realizamos o inicio do Blynk com o Blynk.begin lendo as varáveis criadas com Token, nome e senha da rede wi-fi.
E também como uma característica interna do próprio microcontrolador iniciamos a chamada para o ESP.WDTDisable(), que está informando o uso do WatchDog.
```
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
```

**Void Loop**
Já iniciamos o loop alimentando o WatchDog para que ele continue monitorando o ESP, inicializamos o Blynk, e após isso inicializamos o timer que foi criado para enviar as informações para dentro do aplicativo Blynk.
```
void loop(){
  ESP.wdtFeed();//Alimenta o WatchDog
  Blynk.run();//Inicializa o Blynk
  TimerSensorPresenca.run();//Inicializa o Timer
}
```


