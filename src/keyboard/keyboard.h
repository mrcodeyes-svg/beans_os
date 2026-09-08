#ifndef keyboard_h
#define keyboard_h

//the data port and status port
#define key_data 0x60
#define key_stat 0x64

//our functions
unsigned char get_key();
static inline unsigned char inb(unsigned short port);

#endif