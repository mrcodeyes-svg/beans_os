#include "keyboard/keyboard.h"
#include "screen/screen.h"

//command type
typedef enum {
    none,
    clear
} command_type;


//the commands
char *command_list[] = {"clear screen"};
//the length of all the commands
int command_list_length = 1;
//the command buffer
char command_buffer[2048];
//the place we are at
int command_place = 0;
//our command pos
int command_pos = 0;
//break time
bool break_now = false;
//the command type
command_type local_command_type = none;
//make i
int pos = 0;

//get key cmd
unsigned char get_key_cmd(char key_main) {
    //the main key
    char key = get_key_main(key_main);
    //check for stuff like enter and then do stuff
    if (key == '\n') {
        //add a null term to the end
        command_buffer[command_place] = '\0';

        //check if we have a command
        while (command_list[command_pos][pos] != '\0' || command_buffer[pos] != '\0') {
            for (int j = 0; j < command_list_length; j++) {
                //check if the command
                if (command_list[command_pos][j] == command_buffer[j]) {
                    //if we get the clear command clear
                    if (command_pos == 0) {
                        //set command type to clear
                        local_command_type = clear;
                        full_clear(black);
                        break_now = true;
                        break;
                    }
                }
            }
            if (!break_now) {
                pos = 0;
                break_now = false;
                local_command_type = none;
                command_place = 0;
                pos = 0;
                command_pos++;
            } else {
                command_pos = 0;
                pos = 0;
                break;
            }

            if (command_pos > command_list_length) {
                //reset and give an error
                enter(false);
                print_str("Not vaild command please use help for list of commands", black);
                command_pos = 0;
                pos = 0;
                break;
            }
        }
        
        if (local_command_type != clear) {
            //go down and make sure it doesnt track
            enter(false);
        }
        //do it again
        admin_print("beans_os> ", black);

        //reset command buffer and command place
        command_pos = 0;
        pos = 0;
        break_now = false;
        local_command_type = none;
        command_place = 0;
        return 0;
    }
    //backspace
    else if (key == 8) {
        backspace(1, black);
        //take one away
        command_place--;
        return 0;
    }
    //add our key to the buffer
    command_buffer[command_place] = key;
    command_place++;
    return key;
}

//get the key
unsigned char get_key(char msg) {
    //the current char
    char cur_char = 0;

    //get the new key
    cur_char = get_key_main(msg);
    //check if the key main is backspace
    if (cur_char == 8) {
        backspace(1, black);
        return 0;
    } 
    else if (cur_char == '\n') {
        //if its 23 then enter
        enter(true);
        return 0;
    }
    else if (cur_char == '\t') {
        //for loop to press space 4 times
        for (int i = 0; i < 4; i++) {
            print_char(' ', black);
        }
        return 0;
    }
    return cur_char;
}

//the get key code main just normal now
unsigned char get_key_code() {
    return get_key_code_main();
}