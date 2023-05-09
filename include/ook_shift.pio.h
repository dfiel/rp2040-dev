// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// --------- //
// ook_shift //
// --------- //

#define ook_shift_wrap_target 0
#define ook_shift_wrap 9

#define ook_shift_offset_start 8u

static const uint16_t ook_shift_program_instructions[] = {
            //     .wrap_target
    0xc044, //  0: irq    clear 4                    
    0xc025, //  1: irq    wait 5                     
    0xbf42, //  2: nop                           [31]
    0x0508, //  3: jmp    8                      [5] 
    0xbf42, //  4: nop                           [31]
    0xa542, //  5: nop                           [5] 
    0xc044, //  6: irq    clear 4                    
    0xc025, //  7: irq    wait 5                     
    0x6021, //  8: out    x, 1                       
    0x0024, //  9: jmp    !x, 4                      
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program ook_shift_program = {
    .instructions = ook_shift_program_instructions,
    .length = 10,
    .origin = -1,
};

static inline pio_sm_config ook_shift_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + ook_shift_wrap_target, offset + ook_shift_wrap);
    return c;
}

static inline void ook_shift_program_init(PIO pio, uint sm, uint offset, float div) {
    pio_sm_config c = ook_shift_program_get_default_config(offset);
    sm_config_set_out_shift(&c, true, true, 8);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    sm_config_set_clkdiv(&c, div);
    pio_sm_init(pio, sm, offset + ook_shift_offset_start, &c);
    pio_sm_set_enabled(pio, sm, true);
}

#endif
