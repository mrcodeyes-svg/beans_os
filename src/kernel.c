#include "screen\screen.h"
#include "keyboard\keyboard.h"

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

    //the buffer
    char string_buffer[2];

    //make a var for the key code
    char key_code = 0;
    //the key
    char key = 0;

    while (1) {
        //get the key
        key_code = get_key_code();
        //check if the key is not zero 
        if (key_code != 0) {
            //the key
            key = get_key(key_code);
            //check if key is 0
            if (key != 0) {
                //print key
                print_char(key, black);
                //set it back to 0
                key_code = 0;
            }
        }
    }
}