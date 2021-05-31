#include <stdio.h>
#include <stdlib.h>

#define B5 988
#define A5 880
#define C6 1047
#define D6 1174
#define E6 1318
#define F6 1397
#define G6 1568
#define A6 1760


#define NOTES_COUNT 38

int current_note_index = 0;
int notes[38] = {E6, B5, C6, D6, C6, B5, A5, A5, C6, E6, D6, C6, B5, B5, C6, D6, E6, C6, A5, A5, D6, F6, A6, G6, F6, E6, C6, E6, D6, C6, B5, B5, C6, D6, E6, C6, A5, A5};
int delays[38] = {400, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 400, 400, 400, 400, 600, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 400, 400, 200, 600};

int get_next_note();
int get_next_delay();

int get_next_note() {
    int note = notes[current_note_index];
    current_note_index = (current_note_index + 1) % NOTES_COUNT;
    return note;
}

int get_next_delay() {
    return delays[current_note_index];
}
