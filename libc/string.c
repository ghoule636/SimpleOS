#include "string.h"
#include "../cpu/types.h"

/**
 * @brief Converts a given number to its ascii representation and stores in 
 * it the passed char array.
 * 
 * @param n The number being converted
 * @param str The output char array
 */
void int_to_ascii(u32int n, char *str) {
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
int ascii_to_int(char *str) {
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
void reverseStr(char *s) {
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
int strlen(char *s) {
    int i = 0;
    while (s[i] != 0) ++i;
    return i;
}