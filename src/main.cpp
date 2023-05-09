#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ook_gen_freq.pio.h"
#include "ook_shift.pio.h"

static const float pio_freq = 125000 * 2;

void setup()
{
  Serial.begin();
  Serial.println("Starting!");
  // put your setup code here, to run once:
  // Choose which PIO instance to use (there are two instances)
  PIO pio = pio0;

  // Our assembled program needs to be loaded into this PIO's instruction
  // memory. This SDK function will find a location (offset) in the
  // instruction memory where there is enough space for our program. We need
  // to remember this location!
  uint freq_offset = pio_add_program(pio, &ook_gen_freq_program);
  Serial.println("added freq prog");
  uint shift_offset = pio_add_program(pio, &ook_shift_program);
  Serial.println("added shift prog");

  // Find a free state machine on our chosen PIO (erroring if there are
  // none). Configure it to run our program, and start it, using the
  // helper function we included in our .pio file.
  uint freq_sm = pio_claim_unused_sm(pio, true);
  Serial.print("got freq sm: ");
  Serial.println(freq_sm);
  uint shift_sm = pio_claim_unused_sm(pio, true);
  Serial.print("got shift sm: ");
  Serial.println(shift_sm);

  float div = (float)clock_get_hz(clk_sys) / pio_freq;

  ook_gen_freq_program_init(pio, freq_sm, freq_offset, 0, div);
  Serial.println("init freq");
  ook_shift_program_init(pio, shift_sm, shift_offset, div);
  Serial.println("init shift");

  pio_sm_set_enabled(pio, shift_sm, false);
  pio_sm_put_blocking(pio, shift_sm, 0b11011);
  // pio_sm_put_blocking(pio, freq_sm, 0b00110);
  pio_sm_set_enabled(pio, shift_sm, true);
}

void loop()
{
  // put your main code here, to run repeatedly:
}