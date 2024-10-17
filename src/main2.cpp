// #include "main.h"

// SoftwareSerial softSerial(/*rx =*/10, /*tx =*/11);

// DFRobotDFPlayerMini myDFPlayer;
// HX711 scale;
// // LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
// LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// float tare_scale = 124;
// u8 i = 30;

// void setup()
// {
//   FPSerial.begin(9600);
//   Serial.begin(9600);
//   pinMode(2, INPUT_PULLUP);
//   pinMode(3, INPUT_PULLUP);
//   pinMode(4, INPUT_PULLUP);

//   pinMode(12, OUTPUT);
//   pinMode(11, OUTPUT);
//   pinMode(10, OUTPUT);
//   pinMode(9, OUTPUT);
//   pinMode(8, OUTPUT);
//   pinMode(7, OUTPUT);

//   lcd.begin(16, 2);
//   lcd.setCursor(3, 0);
//   lcd.print("Bem vindo!");
//   Serial.println("Welcome!");
//   delay(1000);

//   lcd.setCursor(2, 2);
//   String message = "Balanca Tech";
//   for (byte i = 0; i < message.length(); i++)
//   {
//     lcd.print(message[i]);
//     Serial.print(message[i]);
//     delay(100);
//   }
//   Serial.println();
//   delay(500);

//   // Serial.println();
//   // Serial.println(F("DFRobot DFPlayer Mini Demo"));
//   // Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

//   // if (!myDFPlayer.begin(FPSerial, /*isACK = */ true, /*doReset = */ true))
//   // { // Use serial to communicate with mp3.
//   //   Serial.println(F("Unable to begin:"));
//   //   Serial.println(F("1.Please recheck the connection!"));
//   //   Serial.println(F("2.Please insert the SD card!"));
//   //   while (true)
//   //   {
//   //     delay(0); // Code to compatible with ESP8266 watch dog.
//   //   }
//   // }
//   // myDFPlayer.waitAvailable();
//   // Serial.println(F("DFPlayer Mini online."));

//   // myDFPlayer.volume(30); // Set volume value. From 0 to 30
//   // myDFPlayer.play(9999); // Play the first mp3

//   // scale.begin(A1, A0);
//   // scale.set_gain(64);
//   // scale.tare();
// }

// void loop() {}

// void loop_()
// {
//   if (i--)
//   {
//     scale.set_scale(tare_scale);
//     float measurement = scale.get_units(10);
//     String weight = String(measurement, 1) + "g";
//     lcd.clear();
//     lcd.setCursor(3, 0);
//     lcd.print("Peso atual");
//     lcd.setCursor((16 - weight.length()) / 2, 1);
//     lcd.print(weight);
//     Serial.println("Weight: " + String(measurement, 1) + "g" + " (Tare reset in " + String(i) + "s)");
//     Serial.println();
//     delay(1000);
//     // static unsigned long timer = millis();

//     // if (millis() - timer > 3000)
//     // {
//     //   timer = millis();
//     //   play_audio(211); // Play next mp3 every 3 second.
//     // }

//     // if (myDFPlayer.available())
//     // {
//     //   printDetail(myDFPlayer.readType(), myDFPlayer.read()); // Print the detail message from DFPlayer to handle different errors and states.
//     // }
//   }
//   else
//   {
//     tare_reset();

//     i = 30;
//   }

//   delay(10);
// }

// void tare_reset()
// {
//   lcd.clear();
//   lcd.setCursor(6, 0);
//   lcd.print("Tara");
//   lcd.setCursor(2, 1);
//   lcd.print("programatica");
//   delay(3000);
//   Serial.println("Resetting tare, remove any object on the scale");
//   Serial.print("Resetting tare scale in: ");
//   for (int i = 6; i > 0; i--)
//   {
//     lcd.clear();
//     lcd.setCursor(4, 0);
//     lcd.print("Tara  em");
//     lcd.setCursor(3, 1);
//     lcd.print(String(i) + " segundos");
//     Serial.print(String(i) + "s... ");
//     delay(1000);
//   }
//   Serial.println();

//   scale.tare();
//   lcd.clear();
//   lcd.setCursor(6, 0);
//   lcd.print("Tara");
//   lcd.setCursor(4, 1);
//   lcd.print("resetada");
//   Serial.println("Tare reset");
//   Serial.println("You can put stuff on the scale again");
//   delay(3000);
//   Serial.println();
// }

// void train()
// {
//   scale.tare();
//   Serial.println("Ready");

//   Serial.println("Put the weight on the scale");
//   delay(5000);
//   Serial.println("Starting tare scale");
//   bool scale_found = false;

//   float start_tare = -1;
//   float end_tare = -1;
//   float s_tare = -1;
//   float e_tare = -1;

//   float resolution = 256;
//   const float weight = 1064;

//   while (!scale_found)
//   {

//     Serial.print("Testing for " + String(tare_scale) + " (Resolution: " + String(resolution) + ")");

//     Serial.print(".");
//     scale.set_scale(tare_scale);
//     Serial.print(".");
//     float measurement = scale.get_units(100);
//     Serial.println(". Measurement: " + String(measurement, 1));
//     Serial.println();

//     if (start_tare == -1 && measurement <= (weight - 0.5))
//     {
//       start_tare = tare_scale;
//     }
//     if (end_tare == -1 || measurement >= (weight + 0.5))
//     {
//       end_tare = tare_scale;
//     }

//     if (start_tare != -1 && end_tare != -1)
//     {
//       Serial.println("Tare scale is between " + String(end_tare) + " and " + String(start_tare));
//       Serial.println();

//       s_tare = start_tare;
//       e_tare = end_tare;
//       start_tare = -1;
//       end_tare = -1;

//       if (resolution <= 0.1)
//       {
//         Serial.println();
//         Serial.println();
//         Serial.println("Process finished, tare scale is " + String((s_tare + e_tare) / 2));
//         Serial.println();
//         Serial.println();
//         scale_found = true;
//         scale.set_scale((s_tare + e_tare) / 2);
//         return;
//       }

//       tare_scale = e_tare;
//       resolution /= 2;
//       tare_reset();
//     }
//     else
//     {
//       tare_scale += resolution;
//     }
//   }
// }

// void printDetail(u8 type, i32 value)
// {
//   switch (type)
//   {
//   case TimeOut:
//     Serial.println(F("Time Out!"));
//     break;
//   case WrongStack:
//     Serial.println(F("Stack Wrong!"));
//     break;
//   case DFPlayerCardInserted:
//     Serial.println(F("Card Inserted!"));
//     break;
//   case DFPlayerCardRemoved:
//     Serial.println(F("Card Removed!"));
//     break;
//   case DFPlayerCardOnline:
//     Serial.println(F("Card Online!"));
//     break;
//   case DFPlayerUSBInserted:
//     Serial.println("USB Inserted!");
//     break;
//   case DFPlayerUSBRemoved:
//     Serial.println("USB Removed!");
//     break;
//   case DFPlayerPlayFinished:
//     Serial.print(F("Number:"));
//     Serial.print(value);
//     Serial.println(F(" Play Finished!"));
//     break;
//   case DFPlayerError:
//     Serial.print(F("DFPlayerError:"));
//     switch (value)
//     {
//     case Busy:
//       Serial.println(F("Card not found"));
//       break;
//     case Sleeping:
//       Serial.println(F("Sleeping"));
//       break;
//     case SerialWrongStack:
//       Serial.println(F("Get Wrong Stack"));
//       break;
//     case CheckSumNotMatch:
//       Serial.println(F("Check Sum Not Match"));
//       break;
//     case FileIndexOut:
//       Serial.println(F("File Index Out of Bound"));
//       break;
//     case FileMismatch:
//       Serial.println(F("Cannot Find File"));
//       break;
//     case Advertise:
//       Serial.println(F("In Advertise"));
//       break;
//     default:
//       break;
//     }
//     break;
//   default:
//     break;
//   }
// }
// enum Audios
// {
//   Um = 1,
//   Dois = 2,
//   Tres = 3,
//   Quatro = 4,
//   Cinco = 5,
//   Seis = 6,
//   Sete = 7,
//   Oito = 8,
//   Nove = 9,
//   Dez = 10,
//   Onze = 11,
//   Doze = 12,
//   Treze = 13,
//   Quatorze = 14,
//   Quinze = 15,
//   Dezesseis = 16,
//   Dezessete = 17,
//   Dezoito = 18,
//   Dezenove = 19,
//   Vinte = 20,
//   Vinte_E = 21,
//   Trinta = 22,
//   Trinta_E = 23,
//   Quarenta = 24,
//   Quarenta_E = 25,
//   Cinquenta = 26,
//   Cinquenta_E = 27,
//   Sessenta = 28,
//   Sessenta_E = 29,
//   Setenta = 30,
//   Setenta_E = 31,
//   Oitenta = 32,
//   Oitenta_E = 33,
//   Noventa = 34,
//   Noventa_E = 35,
//   Cem = 36,
//   Cento_E = 37,
//   Duzentos = 38,
//   Duzentos_E = 39,
//   Trezentos = 40,
//   Trezentos_E = 41,
//   Quatrocentos = 42,
//   Quatrocentos_E = 43,
//   Quinhentos = 44,
//   Quinhentos_E = 45,
//   Seiscentos = 46,
//   Seiscentos_E = 47,
//   Setecentos = 48,
//   Setecentos_E = 49,
//   Oitocentos = 50,
//   Oitocentos_E = 51,
//   Novecentos = 52,
//   Novecentos_E = 53,
//   Desligar = 54,
//   Gramas = 55,
//   Ligar = 56,
//   Quilos = 57,
//   Tara = 58,
// };

// void play_audio(i32 weight, DFRobotDFPlayerMini player)
// {
//   i32 unidade_audio = Gramas;

//   if (weight >= 1000)
//   {
//     // quilos
//     i32 quilos = weight / 1000;
//     weight %= 1000;
//     unidade_audio = Quilos;

//     const Audios unidades_audios[] = {
//         Um,
//         Dois,
//         Tres,
//         Quatro,
//         Cinco,
//         Seis,
//         Sete,
//         Oito,
//         Nove,
//     };

//     player.play(unidades_audios[quilos - 1]);
//     player.waitAvailable();
//   }
//   i32 centenas = weight / 100;
//   i32 dezenas = (weight % 100) / 10;
//   i32 unidades = weight % 10;

//   if (centenas > 0)
//   {
//     if (dezenas == 0 && unidades == 0)
//     {
//       const Audios centenas_audios[] = {
//           Cem,
//           Duzentos,
//           Trezentos,
//           Quatrocentos,
//           Quinhentos,
//           Seiscentos,
//           Setecentos,
//           Oitocentos,
//           Novecentos,
//       };

//       player.play(centenas_audios[centenas - 1]);
//       player.waitAvailable();
//     }
//     else
//     {
//       const Audios centenas_audios[] = {
//           Cento_E,
//           Duzentos_E,
//           Trezentos_E,
//           Quatrocentos_E,
//           Quinhentos_E,
//           Seiscentos_E,
//           Setecentos_E,
//           Oitocentos_E,
//           Novecentos_E,
//       };

//       player.play(centenas_audios[centenas - 1]);
//       player.waitAvailable();

//       if (dezenas > 0)
//       {
//         if (dezenas == 1)
//         {
//           const Audios dezenas_audios[] = {
//               Dez,
//               Onze,
//               Doze,
//               Treze,
//               Quatorze,
//               Quinze,
//               Dezesseis,
//               Dezessete,
//               Dezoito,
//               Dezenove,
//           };

//           player.play(dezenas_audios[unidades]);
//           player.waitAvailable();
//         }
//         else
//         {
//           if (unidades == 0)
//           {
//             const Audios dezenas_audios[] = {
//                 Vinte,
//                 Trinta,
//                 Quarenta,
//                 Cinquenta,
//                 Sessenta,
//                 Setenta,
//                 Oitenta,
//                 Noventa,
//             };

//             player.play(dezenas_audios[dezenas - 2]);
//             player.waitAvailable();
//           }
//           else
//           {
//             const Audios dezenas_audios[] = {
//                 Vinte_E,
//                 Trinta_E,
//                 Quarenta_E,
//                 Cinquenta_E,
//                 Sessenta_E,
//                 Setenta_E,
//                 Oitenta_E,
//                 Noventa_E,
//             };

//             player.play(dezenas_audios[dezenas - 2]);
//             player.waitAvailable();

//             const Audios unidades_audios[] = {
//                 Um,
//                 Dois,
//                 Tres,
//                 Quatro,
//                 Cinco,
//                 Seis,
//                 Sete,
//                 Oito,
//                 Nove,
//             };

//             player.play(unidades_audios[unidades - 1]);
//             player.waitAvailable();
//           }
//         }
//       }
//     }
//   }

//   player.play(unidade_audio);
//   player.waitAvailable();
// }