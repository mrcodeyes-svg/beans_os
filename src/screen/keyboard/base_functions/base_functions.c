//this was made by ai

//this was made by ai too 
void itoa(int num, char *str, int base) {
    int i = 0;
    int is_negative = 0;

    // Handle 0 explicitly
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Handle negative numbers for decimal base
    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 9) + 'a' - 1 : rem + '0';
        num = num / base;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Null terminator

    // Reverse the string in place
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}