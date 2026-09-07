#include "screen/screen.h"

//a welcome
void welcome() {
    //clear the screen
    clear(black);
    //hi
    char *welcome = "Hi and welcome to beans OS have a great time =)";

    //print it to the screen
    print_str(welcome, black);
}

void kernel_main() {
    //say hi
    welcome();

    //print 0x01
    print_char('0x30', black);

    // Hang the CPU safely
    while (1) {
        __asm__("hlt");
    }
}