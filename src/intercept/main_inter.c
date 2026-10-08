#include "keyboard/keyboard.h"
#include "screen/screen.h"

//the current char
char cur_char = 0;

//get the key
unsigned char get_key(char msg) {
    //get the new key
    cur_char = get_key_main(msg);
    //check if the key main is backspace
    if (cur_char == 8) {
        backspace(1, black);
        return 0;
    } 
    else if (cur_char == '\n') {
        //if its 23 then enter
        enter();
        return 0;
    }
    else {
        return cur_char;
    }
}

//the get key code main just normal now
unsigned char get_key_code() {
    return get_key_code_main();
}