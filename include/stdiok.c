//the vga text buffer
volatile char* vga = (volatile char*) 0xB8000;

void clear() {
    // 80 columns * 25 rows = 2000 characters (4000 bytes total)
    for (int i = 0; i < 80 * 25; i++) {
        vga[i * 2] = ' ';       // Overwrite with a blank space
        vga[i * 2 + 1] = 0x0F;  // Keep the white-on-black color attribute
    }
}

void print(const char *msg) {
    //clear the screen   
    clear();

    //start the printing
    //set i to 0
    long i = 0;
    //while the next is not at \0 keep going
    while (msg[i] != '\0') {
        vga[i * 2] = msg[i]; //write the char
        vga[i * 2 + 1] = 0x0F; //write the color
        i++; //ad one to i
    }
}