//vga pointer
volatile char* vga = (volatile char*) 0xB8000;

//make a len function it has 0 because we also cound \0
long len(char *text) {
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
void ken_print(char *msg) {
    //the for loop we use len0 to get all of the chars and then write them
    for (long i = 0; i < len(msg); i++) {
        vga[i * 2] = msg[i];     //write the char
        vga[i * 2 + 1] = 0x2F; //make green background
    }
}

void kernel_main() {
    // Characters for "SUCCESS"
    char test_str[] = {'S', 'U', 'C', 'C', 'E', 'S', 'S', '\0'};
    
    //print it to the screen
    ken_print(test_str);
    // Hang the CPU safely
    while (1) {
        __asm__("hlt");
    }
}