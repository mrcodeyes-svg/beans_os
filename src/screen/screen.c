#include "keyboard\base_functions\base_functions.h"

//vga pointer
volatile char* vga = (volatile char*) 0xB8000;
//where we are on the screen
static long screen_pos = 0;


//make a len function it has 0 because we also cound \0
long len(const char *text) {
    //make i
    long i = 0;
    //the while loop
    while (text[i] != '\0') {
        //add one to i
        i++;
    }
    //return i
    return i;
}

//make a print function its called ken_print because it means kernel print
void print_str(const char *msg, const int back_color) {
    //the for loop we use len0 to get all of the chars and then write them
    for (long i = screen_pos; i < len(msg); i++) {
        vga[i * 2] = msg[i];     //write the char
        /*
        colors
        0x0F is black
        0x1F is blue
        0x2F is green
        0x3F is cyan
        0x4F is red
        0x5F is purple
        0x6F is orange
        0x7F is gray
        */
        vga[i * 2 + 1] = back_color; //make dyamic background
        //add one to screen pos
        screen_pos++;
    }
}

//a clear function to clear the screen
void clear(const int color) {
    //a loop to do it easier
    for (int i = 0; i < 80 * 25; i++) {
        vga[i * 2] = ' ';
        vga[i * 2 + 1] = color;
        screen_pos = 0; //set to 0 
    }
}

//a function to print a char
void print_char(char msg, int color) {
    //set the msg
    vga[screen_pos * 2] = msg;
    //set the color
    vga[screen_pos * 2 + 1] = color;
    //increase screen pos
    screen_pos++;
}

//this was made by ai too im just lazy
void print_hex(unsigned int num, unsigned char color) {
    char buffer[32];
    itoa(num, buffer, 16);
    print_str("0x", color);
    print_str(buffer, color);
}