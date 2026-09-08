#include "keyboard.h"

//this was made by ai
// Inline assembly functions for I/O port communication
static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

//this was human and ai
//get code and char
unsigned char get_key() {
    //if it has nothing then we return 0
    if ((inb(key_stat) & 0x01) == 0) {
        return 0;
    }
    //else return the char
    else {
        return inb(key_data);
    }
}