
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "struct.h"
void insert_customer(TOF *,Customer );
int search_customer(TOF *,int,Customer * );
int read_blockc(TOF *, blockc *,int);
void write_blockc(TOF*, blockc *,int);
void displayAllcustomer(TOF *);

#endif