#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

// A helper function to clear the input stream after a character read
void clear_input_stream() {
    int c;
    // Read and discard characters until we find a newline or end-of-file
    while ((c = getchar()) != '\n' && c != EOF);
}

#endif