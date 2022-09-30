#include "util.h"

/**
 * @brief Copies the data from the from address to the to address.
 * 
 * @param to_address Destination address
 * @param from_address Copy from address
 * @param size Size of data to be copied.
 */
void mem_cpy(char *to_address, char *from_address, int size) {
    for (int i = 0; i < size; i++) {
        to_address[i] = from_address[i];
    }
}

/**
 * @brief Converts a given number to its ascii representation and stores in 
 * it the passed char array.
 * 
 * @param n The number being converted
 * @param str The output char array
 */
void int_to_ascii(int n, char str[]) {
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
}