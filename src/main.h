#include "Arduino.h"
#include "HX711.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
#define f32 float
#define f64 double

#define FPSerial softSerial

void setup();
void loop();
void play_audio(i32 weight, DFRobotDFPlayerMini pla);
void tare_reset();
void train();
void printDetail(u8 type, i32 value);
