#include "string.h"
#include <stdint.h>

/**
 * @brief Converts a given number to its ascii representation and stores in 
 * it the passed char array.
 * 
 * @param n The number being converted
 * @param str The output char array
 */
void int_to_ascii(uint32_t n, char *str) {
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
 * @brief Converts an int into its ascii hex representation. Stores the
 * ascii string in the passed str pointer.
 * 
 * @param n - Integer being converted into ascii. Not tested with negatives yet.
 * @param str - char pointer that must have allocated enough space to store the
 * hex value already.
 */
void hex_to_ascii(int n, char* str) {
    append(str, '0');
    append(str, 'x');

    int32_t tmp;
    for (int i = 28; i >= 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp > 0xA) {
            append(str, tmp - 0xA + 'a');
        } else {
            append(str, tmp + '0');
        }
    }
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

/**
 * @brief Appends a char to the end of a string. String must have space for the
 * new char.
 * 
 * @param buf String to append to.
 * @param c The char being appended.
 */
void append(char* buf, char c) {
    int len = strlen(buf);
    buf[len] = c;
    buf[len + 1] = '\0';
}

/**
 * @brief Removes last char from a given string.
 */
void backspace(char* str) {
    int len = strlen(str);
    str[len - 1] = '\0';
}

/**
 * @brief Returns <0 if s1 < s2, 0 if s1 == s2, >0 if s1 > s2
 */
int strcmp(char* str1, char* str2) {
    int i;
    for (i = 0; str1[i] == str2[i]; i++) {
        if (str1[i] == '\0') {
            return 0;
        }
    }
    return str1[i] - str2[i];
}