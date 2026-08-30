#include "include/stdiok.h"

void kernel_main() {
    //set the bool to false nil means nothing
    int nil = 0;
    //the msg
    char *msg = "hi";
    //print hi
    print(msg);
    //set nothing to true
    nil = 1;
    //and hlt so the cpu does not crash
    while (nil) {__asm__("hlt");}
}