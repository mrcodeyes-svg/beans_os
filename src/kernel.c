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

//a char to char * converter
void str(char string, char* buffer) {
    //this is it simple because char can only be something like "i"
    buffer[0] = string;
    //well we also add the null term
    buffer[1] = '\0';
}

void kernel_main() {
    //say hi
    welcome();

    //the buffer
    char string_buffer[2];

    //make a var for the key
    char key = 0;

    while (1) {
        //get the key
        key = get_key_code();
        //check if the key is not zero 
        if (key != 0) {
            //get input then make it a char *
            str(key, string_buffer);

            //print it
            print_str(string_buffer, black);
            print_char(key, black);
            //set it back to 0
            key = 0;
        }
    }
}