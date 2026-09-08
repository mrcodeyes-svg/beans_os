#ifndef screen_h
#define screen_h

//define all of the colors
#define black 0x0F
#define blue 0x1F
#define green 0x2F
#define cyan 0x3F
#define red 0x4F
#define purple 0x5F
#define orange 0x6F
#define gray 0x7F

//our funcions
void print_str(const char *msg, const int back_color);
void clear(const int color);
long len(const char *text);
void print_char(char msg, int color);

#endif