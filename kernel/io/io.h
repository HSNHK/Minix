#ifndef IO_H
#define IO_H

#include "../types.h"

extern uint8 inb(uint16 port);
extern void outb(uint16, uint8);
extern void sleep(uint32);

#endif