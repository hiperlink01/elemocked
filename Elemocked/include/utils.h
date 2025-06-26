#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdio.h>

//helper function to clear the input stream after read character(s)
void Clear_Input_Stream() {
    int c;
    //discard characters until newline or end-of-file
    do { c = getchar(); }
    while ( c != '\n' && c != EOF );
}

void Gui_Clear(){

    printf("\e[1;1H\e[2J");
    
}

//helper function to count how many occurrences of a character appear in a string
int strcnt(char* str, char to_count){

    int count = 0;
    
    for (int i = 0; i < strlen(str) && str[i] != '\0'; i++)
    { if (str[i] == to_count) { count++; } }

    return count;
}

#endif