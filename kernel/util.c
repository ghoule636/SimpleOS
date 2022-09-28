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

