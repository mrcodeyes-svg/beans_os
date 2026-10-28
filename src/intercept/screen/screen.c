//vga pointer
volatile char* vga = (volatile char*) 0xB8000;
//where we are on the screen
static long screen_pos = 0;

//the before enter locs too
int before_enter[1024];
//the before
int before_time_append = 0;
//enter locations
int enter_locs[1024];
//the amount of times we have appended
int time_append = 0;
//the last pos print_admin was used
int last_admin_print = 0;

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
    //the for loop we use len to get all of the chars and then write them
    for (long i = 0; i < len(msg); i++) {
        vga[screen_pos * 2] = msg[i];     //write the char
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
        vga[screen_pos * 2 + 1] = back_color; //make dyamic background
        //add one to screen pos
        screen_pos++;
    }
}

//a clear function to clear the screen
void full_clear(const int color) {
    //a loop to do it easier
    for (int i = 0; i < 80 * 25; i++) {
        vga[i * 2] = ' ';
        vga[i * 2 + 1] = color;
    }
    screen_pos = 0; //set to 0
    last_admin_print = 0; //also set to 0
}
//a function to print a char
void print_char(const char msg, const int color) {
    //set the msg
    vga[screen_pos * 2] = msg;
    //set the color
    vga[screen_pos * 2 + 1] = color;
    //increase screen pos
    screen_pos++;
}

//a function to make a backspace happen
void backspace(const int back, const int color) {
    //checks
    //take one away and do what we normally do and also check
    if (screen_pos > 0 && !(last_admin_print >= screen_pos - back)) {
        //check if we are going back a lot
        if (enter_locs[time_append -1] == screen_pos) {
            //set screen pos
            screen_pos = before_enter[before_time_append - 1];
            //subtract
            time_append--;
            before_time_append--;
            return;
        }
        screen_pos -= back;
        vga[screen_pos * 2] = ' ';
        vga[screen_pos * 2 + 1] = color;
    }
}

//a enter function
void enter(int track) {
    if (track) {
        //append to the before
        before_enter[before_time_append] = screen_pos;
    }
    //add this and also move
    screen_pos += 80 - (screen_pos % 80);
    //check if we get it
    if (track) {
        //add the screen pos to the thing and increase time append by 1 and the before time append
        enter_locs[time_append] = screen_pos;
        time_append++;
        before_time_append++;
    }
}

//a put pixel function
void put_pixel(int x, int y, int color) {
    //make pos x
    int pos = x * 2;
    //for loop to get y right
    for (int i = 0; i < y; i++) {
        pos += 80;
    }
    //put the pixel
    vga[pos + 1] = color;
}

//to print something but make sure it cant get removed
void admin_print(const char *msg, const int color) {
    //print it then we set last admin print to screen pos
    print_str(msg, color);
    last_admin_print = screen_pos-1;
}