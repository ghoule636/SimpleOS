#include "../drivers/ports.h"

void main() {
    // Create a pointer to the first text cell of video memory
    char* video_memory = (char*) 0xb8000;
    // Store the value X in video memory
    *video_memory = 'X';
}