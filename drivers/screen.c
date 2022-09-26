#include "screen.h"
#include "ports.h"

// private functions
int get_cursor();
void set_cursor(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

/**
 * @brief Prints a given string at the given location. If col or row are negative will print at 
 * cursor position.
 * 
 * @param message String being printed must terminate in a null char.
 * @param col col of print location
 * @param row row of print location
 */
void print_at(char *message, int col, int row) {
    int offset;
    if (col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor();
        row = get_offset_row(offset);
        col = get_offset_column(offset);
    }

    int i = 0;
    while(message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_column(offset);
    }
}

/**
 * @brief Simple function that calls print_at and prints at current cursor location.
 * 
 * @param message String to be printed.
 */
void print(char *message) {
    print_at(message, -1, -1);
}

/**
 * @brief prints a single char at the given col and row. If -1 is passed for col and row then cursor 
 * will be used as the location to print. Function updates cursor position and returns the offset of the
 * next char location.
 * 
 * @param c char to be printed
 * @param col column of the char to be printed
 * @param row row of the char to be printed
 * @param attr style of char to be printed ex. 0x0f = white text on black background
 * @return int - the next char location
 */
int print_char(char c, int col, int row, char attr) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (col >= MAX_COLUMNS || row >= MAX_ROWS) {
        vidmem[2 * MAX_COLUMNS * MAX_ROWS - 2] = 'E';
        vidmem[2 * MAX_COLUMNS * MAX_ROWS - 1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    } else {
        vidmem[offset] = c;
        vidmem[offset + 1] = attr;
        offset +=  2;
    }
    set_cursor(offset);
    return offset;
}

int get_cursor() {
    /* Screen cursor position: ask VGA control register (0x3d4) for bytes
    * 14 = high byte of cursor and 15 = low byte of cursor. */
    port_byte_out(REG_SCREEN_CTRL, 14); /* Requesting byte 14: high byte of cursor pos */
    /* Data is returned in VGA data register (0x3d5) */
    int position = port_byte_in(REG_SCREEN_DATA);
    position = position << 8; /* high byte */

    port_byte_out(REG_SCREEN_CTRL, 15); /* requesting low byte */
    position += port_byte_in(REG_SCREEN_DATA);
    // VGA 'cells' consist of the character and its control data
    // so this means we have to multiply the position by two so we offset
    // the data and the control data.
    return position * 2;
}

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(0x3d4, 15);
    port_byte_out(0x3d5, offset);
    port_byte_out(0x3d4, 14);
    offset = offset >> 8;
    port_byte_out(0x3d5, offset);
}

void clear_screen() {
    int screen_size = MAX_COLUMNS * MAX_ROWS;
    char *screen = VIDEO_ADDRESS;

    for (int i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor(0);
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLUMNS + col);
}
int get_offset_row(int offset) {
    return offset / (2 * MAX_COLUMNS);
}
/*
 * Calculates the column by getting the row then translating that into the offset of start of the
 * row by multiplying by MAX_COLUMNS and by 2 then subtracting the offset which gives us our column 
 * and then we divide by 2 to compensate for the VGA char format.
 */
int get_offset_column(int offset) {
    return (offset - (get_offset_row(offset) * 2 * MAX_COLUMNS)) / 2;
}