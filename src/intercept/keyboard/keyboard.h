#ifndef keyboard_h
#define keyboard_h

//the data port and status port
#define key_data 0x60
#define key_stat 0x64

//our functions
unsigned char get_key_code_main();
void itoa(int num, char *str, int base);
unsigned char get_key_main(char msg);

#endif