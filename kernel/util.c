#include "util.h"

/**
 * @brief Copies the data from the from address to the to address.
 * 
 * @param to_address Destination address
 * @param from_address Copy from address
 * @param size Size of data to be copied.
 */
void mem_cpy(u8int *to_address, u8int *from_address, u32int size) {
    for (int i = 0; i < size; i++) {
        to_address[i] = from_address[i];
    }
}

/**
 * @brief Fills an area of memory of given size with the given value.
 * 
 * @param dest Starting location of memory to fill.
 * @param val Value to fill memory with.
 * @param size Size of memory area to fill.
 */
void mem_set(u8int* dest, u8int val, u32int size) {
    u8int* temp = dest;
    for (u32int i = 0; i < size; i++) {
        *temp = val;
        temp++;
    }
}

/**
 * @brief Converts a given number to its ascii representation and stores in 
 * it the passed char array.
 * 
 * @param n The number being converted
 * @param str The output char array
 */
void int_to_ascii(u32int n, u8int str[]) {
    int i, sign;
    sign = n;
    if (sign < 0) n = -n;
    i = 0;
    do {
        str[i] = n % 10 + '0';
        i++;
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
    reverseStr(str);
}

/**
 * @brief Converts a given string into its integer equivalent.
 * 
 * @param str String terminating with a null char.
 * @return int The integer value of the passed string.
 */
int ascii_to_int(u8int str[]) {
    int result = 0;
    int negative = 1;
    int i = 0;
    if (str[0] == '-') {
        negative = -1;
        i = 1;
    }
    while (str[i] != 0) {
        int temp = str[i] - '0';
        if (i) {
            if (negative == -1 && i > 1) {
                temp *= 10 * (i - 1);
            } else {
                temp *= 10 * i;
            }
        }
        result += temp;
        i++;
    }
    result *= negative;
    return result;
}

/**
 * @brief Reverses the given string.
 */
void reverseStr(char s[]) {
    int temp, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

/**
 * @brief Returns length of a string. 
 * 
 * @param s - String that must terminate in a '\0' char.
 * @return int Length of the string.
 */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != 0) ++i;
    return i;
}