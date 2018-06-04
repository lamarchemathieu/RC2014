
#ifndef _BDOS_H_
#define _BDOS_H_

#include <stdint.h>

#include "bdos.h"

#define BDOS_DIRECT_CONSOLE_IO_INPUTSTATUS 0xFF

void bdos_console_output(uint8_t c);
uint8_t bdos_console_input(void);
uint8_t bdos_reset(void);
uint16_t bdos_version(void);
uint8_t bdos_direct_console_io(uint8_t c);

#endif