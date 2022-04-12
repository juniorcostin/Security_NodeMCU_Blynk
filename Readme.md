**System Security with NodeMCU and Blynk**
--
**🚧Software ainda em Desenvolvimento🚧**


Um básico sistema de segurança para a utilzação residencial desenvolvido com um NodeMCU, sensores de presença, Sirene e alguns relés.

Também consiste em aplicar novas funcionalidades como automatização de luzes e integração com Amazon Alexa.

Para utilizar basta apenas realizar a alteração das variáveis:

```
#define BLYNK_TEMPLATE_ID  "ID DO SEU TEMPLATE BLYNK"

char auth[] = "SEU TOKEN BLYNK"; //Token para comunicação com o Blynk
char ssid[] = "NOME DA REDE WI-FI"; //Nome da rede que deve se conectar
char pass[] = "SENHA DA REDE WIFI"; //Senha da rede que deve se conectar

```

Validar também os pinos utilizados pelo NodeMCU

```
#define PIN_SENSOR D4  //Pino D4 para o Sensor de Presença
#define PIN_LED D1 //Pino D1 para a Sirene
```

E também os Pinos virtuiais riados dentro do blynk

```
 Blynk.virtualWrite(V0, traducao);  //Pino Virtual 0 está definido no Blynk para coletar os dados sensor de movimento
```
