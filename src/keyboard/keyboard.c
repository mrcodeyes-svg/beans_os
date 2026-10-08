#include "keyboard.h"

// Inline assembly functions for I/O port communication
static inline unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

//this was human and ai
//get code and char
unsigned char get_key_code() {
    //if it has nothing then we return 0
    if ((inb(key_stat) & 0x01) == 0) {
        return 0;
    }
    //else return the char
    else {
        return inb(key_data);
    }
}

//all the right codes non s means non shift
char nons_list_chars[] = {
    1, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 
    '-', '=', 14, 15, 'q', 'w', 'e', 'r', 't', 
    'y', 'u', 'i', 'o', 'p', '[', ']', 28, 29, 
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 
    'l', ';', '\'', '`', 42, '\\', 'z', 'x', 'c', 
    'v', 'b', 'n', 'm', ',', '.', '/', 54, 55, 
    56, ' ', 58, 59, 60, 61, 62, 63, 64, 
    65, 66, 67, 68
};

//the scancode thing
unsigned char get_key(char msg) {
    //check
    if (msg > 68) {
        return 0;
    } else {
        //get the char - 1 because of c it starts its lists at 0
        return nons_list_chars[msg - 1];
    }
}