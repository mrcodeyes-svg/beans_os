#include <stdio.h>

char *command = "hi";
char *command_list[] = {"hi", "clear"};
int command_list_length = 2;

int main() {
    for (int i = 0; i < command_list_length; i++) {
        if (command == command_list[i]) {
            printf("got it");
        }
    }
}