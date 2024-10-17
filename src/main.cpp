/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>

 ***************************************************
 This example shows the basic function of library for DFPlayer.

 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)

 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "HX711.h"

enum Audios
{
  Um = 1,
  Dois = 2,
  Tres = 3,
  Quatro = 4,
  Cinco = 5,
  Seis = 6,
  Sete = 7,
  Oito = 8,
  Nove = 9,
  Dez = 10,
  Onze = 11,
  Doze = 12,
  Treze = 13,
  Quatorze = 14,
  Quinze = 15,
  Dezesseis = 16,
  Dezessete = 17,
  Dezoito = 18,
  Dezenove = 19,
  Vinte = 20,
  Vinte_E = 21,
  Trinta = 22,
  Trinta_E = 23,
  Quarenta = 24,
  Quarenta_E = 25,
  Cinquenta = 26,
  Cinquenta_E = 27,
  Sessenta = 28,
  Sessenta_E = 29,
  Setenta = 30,
  Setenta_E = 31,
  Oitenta = 32,
  Oitenta_E = 33,
  Noventa = 34,
  Noventa_E = 35,
  Cem = 36,
  Cento_E = 37,
  Duzentos = 38,
  Duzentos_E = 39,
  Trezentos = 40,
  Trezentos_E = 41,
  Quatrocentos = 42,
  Quatrocentos_E = 43,
  Quinhentos = 44,
  Quinhentos_E = 45,
  Seiscentos = 46,
  Seiscentos_E = 47,
  Setecentos = 48,
  Setecentos_E = 49,
  Oitocentos = 50,
  Oitocentos_E = 51,
  Novecentos = 52,
  Novecentos_E = 53,
  Desligar = 54,
  Gramas = 55,
  Ligar = 56,
  Quilos = 57,
  Tara = 58,
  Virgula = 59,
};

#define i32 int32_t

#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266)) // Using a soft serial port
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/10, /*tx =*/11);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif

DFRobotDFPlayerMini player;
HX711 scale;
void printDetail();
void play_audio(i32 weight);
void waitAvailable();
void play(i32 n);

void setup()
{
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
#else
  FPSerial.begin(9600);
#endif

  Serial.begin(9600);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!player.begin(FPSerial, /*isACK = */ true, /*doReset = */ true))
  { // Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
    {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  player.volume(30); // Set volume value. From 0 to 30

  scale.begin(A1, A0);
  scale.set_gain(64);
  scale.set_scale(124);
  scale.tare();
  waitAvailable();
  play(Ligar);

  pinMode(A2, INPUT_PULLUP);
  delay(2000);
}

bool is_on = true;
u8 loop_count = 0;

void loop()
{
  Serial.print("Btn1: ");
  if (digitalRead(A2) == LOW)
    Serial.print("Pressed");
  else
    Serial.print("Not Pressed");
  Serial.println();

  if (digitalRead(A2) == LOW)
  {

    if (loop_count++ > 10)
    {
      is_on = !is_on;
      loop_count = 0;

      if (is_on)
      {
        scale.tare();
        play(Ligar);
      }
      else
        play(Desligar);
    }
  }
  else if (is_on)
  {
    if (loop_count <= 10 && loop_count > 0)
    {
      loop_count = 0;
      scale.tare();
      Serial.println("Tara");
      play(Tara);
    }
    else
    {
      float measurement = scale.get_units(10);
      Serial.println("Weight: " + String(measurement, 1) + "g");
      Serial.println();
      if (measurement >= 1)
        play_audio(measurement);
    }
  }
  else
  {
    loop_count = 0;
  }
  delay(50);
}

void wait_for_audio(i32 n)
{
  switch (n)
  {
  case Virgula:
  case Dois:
    return delay(2000);
  default:
    return delay(1300);
  }
}

void waitAvailable()
{
  Serial.println("Waiting to be available");
  player.waitAvailable();
}

String audio(i32 n)
{
  switch (n)
  {
  case 1:
    return "Um";
  case 2:
    return "Dois";
  case 3:
    return "Tres";
  case 4:
    return "Quatro";
  case 5:
    return "Cinco";
  case 6:
    return "Seis";
  case 7:
    return "Sete";
  case 8:
    return "Oito";
  case 9:
    return "Nove";
  case 10:
    return "Dez";
  case 11:
    return "Onze";
  case 12:
    return "Doze";
  case 13:
    return "Treze";
  case 14:
    return "Quatorze";
  case 15:
    return "Quinze";
  case 16:
    return "Dezesseis";
  case 17:
    return "Dezessete";
  case 18:
    return "Dezoito";
  case 19:
    return "Dezenove";
  case 20:
    return "Vinte";
  case 21:
    return "Vinte_E";
  case 22:
    return "Trinta";
  case 23:
    return "Trinta_E";
  case 24:
    return "Quarenta";
  case 25:
    return "Quarenta_E";
  case 26:
    return "Cinquenta";
  case 27:
    return "Cinquenta_E";
  case 28:
    return "Sessenta";
  case 29:
    return "Sessenta_E";
  case 30:
    return "Setenta";
  case 31:
    return "Setenta_E";
  case 32:
    return "Oitenta";
  case 33:
    return "Oitenta_E";
  case 34:
    return "Noventa";
  case 35:
    return "Noventa_E";
  case 36:
    return "Cem";
  case 37:
    return "Cento_E";
  case 38:
    return "Duzentos";
  case 39:
    return "Duzentos_E";
  case 40:
    return "Trezentos";
  case 41:
    return "Trezentos_E";
  case 42:
    return "Quatrocentos";
  case 43:
    return "Quatrocentos_E";
  case 44:
    return "Quinhentos";
  case 45:
    return "Quinhentos_E";
  case 46:
    return "Seiscentos";
  case 47:
    return "Seiscentos_E";
  case 48:
    return "Setecentos";
  case 49:
    return "Setecentos_E";
  case 50:
    return "Oitocentos";
  case 51:
    return "Oitocentos_E";
  case 52:
    return "Novecentos";
  case 53:
    return "Novecentos_E";
  case 54:
    return "Desligar";
  case 55:
    return "Gramas";
  case 56:
    return "Ligar";
  case 57:
    return "Quilos";
  case 58:
    return "Tara";
  case 59:
    return "Virgula";
  default:
    return "Desconhecido";
  }
}

void play(i32 n)
{
  Serial.println("Playing: " + audio(n));
  player.play(n);
  wait_for_audio(n);
  waitAvailable();
}

void printDetail()
{
  uint8_t type = player.readType();
  int value = player.read();
  switch (type)
  {
  case TimeOut:
    Serial.println(F("Time Out!"));
    break;
  case WrongStack:
    Serial.println(F("Stack Wrong!"));
    break;
  case DFPlayerCardInserted:
    Serial.println(F("Card Inserted!"));
    break;
  case DFPlayerCardRemoved:
    Serial.println(F("Card Removed!"));
    break;
  case DFPlayerCardOnline:
    Serial.println(F("Card Online!"));
    break;
  case DFPlayerUSBInserted:
    Serial.println("USB Inserted!");
    break;
  case DFPlayerUSBRemoved:
    Serial.println("USB Removed!");
    break;
  case DFPlayerPlayFinished:
    Serial.print(F("Number:"));
    Serial.print(value);
    Serial.println(F(" Play Finished!"));
    break;
  case DFPlayerError:
    Serial.print(F("DFPlayerError:"));
    switch (value)
    {
    case Busy:
      Serial.println(F("Card not found"));
      break;
    case Sleeping:
      Serial.println(F("Sleeping"));
      break;
    case SerialWrongStack:
      Serial.println(F("Get Wrong Stack"));
      break;
    case CheckSumNotMatch:
      Serial.println(F("Check Sum Not Match"));
      break;
    case FileIndexOut:
      Serial.println(F("File Index Out of Bound"));
      break;
    case FileMismatch:
      Serial.println(F("Cannot Find File"));
      break;
    case Advertise:
      Serial.println(F("In Advertise"));
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

void play_audio(i32 weight)
{
  if (weight < 1 || weight > 5000)
    return;
  waitAvailable();
  Serial.println("Lendo: " + String(weight));
  i32 unidade_audio = Gramas;

  if (weight >= 1000)
  {
    // quilos
    i32 quilos = weight / 1000;
    weight %= 1000;
    unidade_audio = Quilos;

    const Audios unidades_audios[] = {
        Um,
        Dois,
        Tres,
        Quatro,
        Cinco,
        Seis,
        Sete,
        Oito,
        Nove,
    };

    play(unidades_audios[quilos - 1]);
    if (weight > 0)
    {
      play(Virgula);
    }
  }
  i32 centenas = weight / 100;
  i32 dezenas = (weight % 100) / 10;
  i32 unidades = weight % 10;

  if (centenas > 0)
  {
    if (dezenas == 0 && unidades == 0)
    {
      const Audios centenas_audios[] = {
          Cem,
          Duzentos,
          Trezentos,
          Quatrocentos,
          Quinhentos,
          Seiscentos,
          Setecentos,
          Oitocentos,
          Novecentos,
      };

      play(centenas_audios[centenas - 1]);
    }
    else
    {
      const Audios centenas_audios[] = {
          Cento_E,
          Duzentos_E,
          Trezentos_E,
          Quatrocentos_E,
          Quinhentos_E,
          Seiscentos_E,
          Setecentos_E,
          Oitocentos_E,
          Novecentos_E,
      };

      play(centenas_audios[centenas - 1]);
    }
  }
  if (dezenas > 0)
  {
    if (dezenas == 1)
    {
      const Audios dezenas_audios[] = {
          Dez,
          Onze,
          Doze,
          Treze,
          Quatorze,
          Quinze,
          Dezesseis,
          Dezessete,
          Dezoito,
          Dezenove,
      };

      play(dezenas_audios[unidades]);
    }
    else
    {
      if (unidades == 0)
      {
        const Audios dezenas_audios[] = {
            Vinte,
            Trinta,
            Quarenta,
            Cinquenta,
            Sessenta,
            Setenta,
            Oitenta,
            Noventa,
        };

        play(dezenas_audios[dezenas - 2]);
      }
      else
      {
        const Audios dezenas_audios[] = {
            Vinte_E,
            Trinta_E,
            Quarenta_E,
            Cinquenta_E,
            Sessenta_E,
            Setenta_E,
            Oitenta_E,
            Noventa_E,
        };

        play(dezenas_audios[dezenas - 2]);
      }
    }
  }

  if (unidades > 0 && dezenas != 1)
  {
    const Audios unidades_audios[] = {
        Um,
        Dois,
        Tres,
        Quatro,
        Cinco,
        Seis,
        Sete,
        Oito,
        Nove,
    };

    play(unidades_audios[unidades - 1]);
  }

  play(unidade_audio);
}