#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
//#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27,20,4);
int ledazul = 6; // ledazul no pino 6
int ledvermelho = 5; // ledvermelho no pino 5
int rele = 8; // rele no pino 8
const int buzzer = 7; // buzzer no pino 7


void setup(){
  pinMode(10, OUTPUT);
  pinMode(rele, OUTPUT);

  Serial.begin(9600); // Inicia a serial
  SPI.begin(); // Inicia SPI bus
  mfrc522.PCD_Init(); // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor..."); 
  Serial.println();
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print(" Aproxime o seu");// Mensagem inicial no lcd
  lcd.setCursor(0,1);
  lcd.print("cartao ao leitor");// Mensagem inicial no lcd
  digitalWrite(rele, LOW); //Inicia o rele em modo LOW
  pinMode(ledazul,OUTPUT); //Define o ledazul como OUTPUT
  digitalWrite(ledazul, LOW); //Inicia o ledazul em modo LOW
  pinMode(ledvermelho,OUTPUT); //Define o ledvermelho como OUTPUT

}

      void loop()
      {
      // mostrar novos cartoes 
      if ( ! mfrc522.PICC_IsNewCardPresent())
      {
      return;
      }

      // Coloque o cartao no leitor
      if ( ! mfrc522.PICC_ReadCardSerial())
      {
      return;
      }
      //Mostra UID na serial
      Serial.print("UID da tag ");
      String conteudo= " ";
      byte letra;
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0 " : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        conteudo.concat(String(mfrc522.uid.uidByte[i]< 0x10 ? " 0 " : " "));
        conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
        
      }
      Serial.println();
      Serial.print("Mensagem......: ");


      if (conteudo.substring(1).equals(" 90 ac 82 20")  ) //ID de cartão autorizado
      {
        
        Serial.println("Ola guilherme ");// mensagem de boas vindas
        Serial.println();
        tone(buzzer,100);
        digitalWrite(ledazul, HIGH); // Muda o estado do ledazul
        delay(250);
        noTone(buzzer);
        delay(100);
        tone(buzzer,100); // Buzzer vai dar um som após o cartao ser detectado
        delay(250);
        noTone(buzzer);
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Ola guilherme "); //mensagem de boas vindas
        lcd.setCursor(0,1);
        lcd.print("Bem Vindo");
        //delay(3000);
        digitalWrite(ledazul, LOW); // Muda o estado do ledazul
        digitalWrite(rele, HIGH); // Muda o estado do rele 
        delay(1800); 
        digitalWrite(ledazul, LOW); // muda o estado do ledazul
        delay(600);
      
        mensageminicial();
      }


        if (conteudo.substring(1) == " 83 0 6 1e a0") //Coloque o ID do cartão não autorizado
        {
          Serial.println("Acesso negado ");
          Serial.println();
          tone(buzzer,500);
          digitalWrite(ledvermelho, HIGH); // Muda o estado do ledvermelho
          delay(250);
          noTone(buzzer);
          delay(100);
          tone(buzzer,300);// Buzzer vai dar um som após o cartao não ser autorizado 
          noTone(buzzer);
          delay(250);
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print(" Cartao nao "); 
          lcd.setCursor(3,1);
          lcd.print(" AUTORIZADO ");
          digitalWrite(ledvermelho, HIGH); // Muda o estado do ledvermelho
          digitalWrite(rele, LOW); // Muda o estado do rele 
          delay(1000); 
          digitalWrite(ledvermelho, LOW); // muda o estado do ledvermelho
          delay(600);
          mensageminicial();
        }
        }

void mensageminicial()

{
lcd.clear();
lcd.print(" Aproxime o seu "); // Mensagem de loop
lcd.setCursor(0,1);
lcd.print(" cartao ao leitor ");
}