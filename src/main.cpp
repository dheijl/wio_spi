#include <Arduino.h>

#include <SPI.h>

#include "debug.h"
#include <tft_functions.h>
#include <battery.h>
#include "buttons.h"

// for documentation
const auto spi_ss = PIN_SPI_SS;     // (50ul) = BCM24 = pin 24 on wio breakout
const auto spi_mosi = PIN_SPI_MOSI; // (48ul) = BCM10 = pin 19 on wio breakout
const auto spi_miso = PIN_SPI_MISO; // (47ul) = BCM9  = pin 21 on wio breakout
const auto spi_sck = PIN_SPI_SCK;   // (49ul) = BCM11 = pin 23 on wio breakout

const auto PIN_SDATA_RDY = D0; // (0ul)  = BCM27 = pin 13 on wio breakout

const char *tqbf = "the quick brown fox jumps over the lazy dog!the quick brown fox jumps over the lazy dog\r\n!";

// local function declarations here:
static void setup_debug();
static void setup_spi();
static void print_hex(uint8_t x);
static void wait_sdata();

// static void wait_btn();

void setup()
{
  setup_debug();
  // buttons
  init_buttons();
  // initialize tft
  init_tft();
  tft_clear();
  // initialize battery
  init_battery();
  printBatteryStats();
  // initialize spi
  setup_spi();
}

static unsigned char txbuf[128];
// static unsigned char rxbuf[128];

void loop()
{
  // wait for data ready from slave
  wait_sdata();
  tft_clear();

  // memset(rxbuf, 0xff, sizeof(rxbuf));
  memset(txbuf, 0xff, sizeof(txbuf));
  size_t count = strlen(tqbf);
  memcpy(txbuf, tqbf, count);
  wait_sdata();
#ifdef DEBUG
  Serial.print("TX: ");
  for (size_t i = 0; i < count; i++)
  {
    print_hex(txbuf[i]);
  }
  Serial.println();
#endif
  tft_println("Start SPI");
  // 24MHz transmit is OK, but receive is max 12 Mhz
  SPI.beginTransaction(SPISettings((int)12000000, MSBFIRST, (uint8_t)SPI_MODE1));
  // TXBUF != NULL => write and read simultaneously
  // TXBUF == NULL => read only
  // SPI.transfer(txbuf, rxbuf, count, false);
  // SPI.waitForTransfer();
  digitalWrite(PIN_SPI_SS, LOW);
  auto st = micros();
  SPI.transfer(txbuf, count);
  auto et = micros();
  digitalWrite(PIN_SPI_SS, HIGH);
  SPI.endTransaction();
  tft_println("SPI complete");
#ifdef DEBUG
  Serial.print("RX: ");
  for (size_t i = 0; i < count; i++)
  {
    print_hex(txbuf[i]);
    if (txbuf[i] != 0xff && txbuf[i] != 0x00)
    {
      tft_print(String((char)txbuf[i]));
    }
  }
  Serial.println();
  auto tt = et - st;
  auto pc = (float)tt / (float)count;
  Serial.println("Elapsed: " + String(tt) + "µs, per char: " + String(pc) + "µs");
#endif
}

static void print_hex(uint8_t x)
{
  if (x < 16)
  {
    Serial.print('0');
  }
  Serial.print(x, HEX);
}

static void setup_debug()
{
#ifdef DEBUG
  Serial.begin(115200);
  int n = 250;
  while (!Serial && n-- > 0)
  {
    delay(1);
  }
  delay(100);
#endif
}

static void setup_spi()
{
  tft_println("SPI setup");
  pinMode(D0, INPUT);
  pinMode(PIN_SPI_SS, OUTPUT);
  digitalWrite(PIN_SPI_SS, HIGH);
  SPI.begin();
  /*
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(1);
  */
  tft_println("SPI initialised");
}

// wait for slave data ready pin (D0)
static void wait_sdata()
{
  while (digitalRead(PIN_SDATA_RDY) == LOW)
  {
    delay(1);
  }
}

/*
// wait for middle button
static void wait_btn()
{
  while (digitalRead(BUTTON_2) == HIGH)
  {
    delay(1);
  }
  while (digitalRead(BUTTON_2) == LOW)
  {
    delay(1);
  }
}
*/