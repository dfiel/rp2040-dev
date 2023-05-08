#include <Arduino.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "manchester.pio.h"

static const float pio_freq = 125000 * 2;

void setup() {
  // put your setup code here, to run once:
      // Choose which PIO instance to use (there are two instances)
    PIO pio = pio0;

    // Our assembled program needs to be loaded into this PIO's instruction
    // memory. This SDK function will find a location (offset) in the
    // instruction memory where there is enough space for our program. We need
    // to remember this location!
    uint offset = pio_add_program(pio, &manchester_program);

    // Find a free state machine on our chosen PIO (erroring if there are
    // none). Configure it to run our program, and start it, using the
    // helper function we included in our .pio file.
    uint sm = pio_claim_unused_sm(pio, true);

    float div = (float)clock_get_hz(clk_sys) / pio_freq;

    manchester_program_init(pio, sm, offset, 0, div);

    pio_sm_set_enabled(pio, sm, false);
    pio_sm_put_blocking(pio, sm, 0b11011);
    pio_sm_put_blocking(pio, sm, 0b00110);
    pio_sm_set_enabled(pio, sm, true);
}

void loop() {
  // put your main code here, to run repeatedly:
}