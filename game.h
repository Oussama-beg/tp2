#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "struct.h"
void insert_game(TOF*,Game );
int search_game(TOF*, int , Game* );
int read_blockg(TOF*, blockg*,int);
void write_blockg(TOF*, blockg*,int);
void displayAllgame(TOF*);

#endif