#include "screen\screen.h"
#include "screen\keyboard\keyboard.h"

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

    //print 0x30
    print_char('\n', black);
    print_char('0x30', black);

    //make a var for the key
    char key = 0;

    // Hang the CPU safely
    while (1) {
        //get the key
        key = get_key_code();
        //check if the key is not zero 
        //if (key != 0) {
            //print it
            print_hex(key, black);
        //}
        // __asm__("hlt");
    }
}