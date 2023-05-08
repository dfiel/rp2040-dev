// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ---------- //
// manchester //
// ---------- //

#define manchester_wrap_target 0
#define manchester_wrap 5

#define manchester_offset_start 4u

static const uint16_t manchester_program_instructions[] = {
            //     .wrap_target
    0xb542, //  0: nop                    side 0 [5] 
    0x1b04, //  1: jmp    4               side 1 [3] 
    0xbd42, //  2: nop                    side 1 [5] 
    0xb342, //  3: nop                    side 0 [3] 
    0x6021, //  4: out    x, 1                       
    0x0022, //  5: jmp    !x, 2                      
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program manchester_program = {
    .instructions = manchester_program_instructions,
    .length = 6,
    .origin = -1,
};

static inline pio_sm_config manchester_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + manchester_wrap_target, offset + manchester_wrap);
    sm_config_set_sideset(&c, 2, true, false);
    return c;
}

static inline void manchester_program_init(PIO pio, uint sm, uint offset, uint pin, float div) {
    pio_sm_set_pins_with_mask(pio, sm, 0, 1u << pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
    pio_gpio_init(pio, pin);
    pio_sm_config c = manchester_program_get_default_config(offset);
    sm_config_set_sideset_pins(&c, pin);
    sm_config_set_out_shift(&c, true, true, 32);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    sm_config_set_clkdiv(&c, div);
    pio_sm_init(pio, sm, offset + manchester_offset_start, &c);
    pio_sm_set_enabled(pio, sm, true);
}

#endif
