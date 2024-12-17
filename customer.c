#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "customer.h"
#include "rental.h"

int read_blockc(TOF * tof ,blockc *bloc ,int nb){
    if(nb <= tof->header.nb)
    return -1;
    FILE *file = fopen(tof->file , "r+b");
    if(file == NULL){
        return -1;
    }

    fseek(file, sizeof(Header) + nb * sizeof(blockc) , SEEK_SET);

    int result = fread(bloc, sizeof(blockc) , 1 , file);
    fclose(file);
    return result;
}


void write_blockc(TOF *tof, blockc *bloc , int nb){
    FILE *file = fopen(tof->file,"r+b");
    fseek(file, sizeof(Header) + nb * sizeof(blockc) , SEEK_SET);
    fwrite(bloc, sizeof(blockc) , 1 , file);
    close(file);
}

void insert_customer(TOF* tof , Customer user){

    blockc bloc;
    int read = read_blockc(tof ,&bloc,tof->header.nb -1);

    if(read <= 0 || bloc.count == SIZE){
        blockc blocc;
        blocc.tab[0] = user;
        blocc.count = 1;
        write_blockc(tof ,&blocc ,tof->header.nb);
        tof->header.nb++;
        write_entete(tof);
    }else{
        bloc.tab[bloc.count]= user;
        bloc.count++;

    write_blockc(tof , &bloc ,tof->header.nb-1);
    }

}

int search_customer(TOF* tof , int id , Customer* user){
    blockc bloc;

    for(int i = 0; i<= tof->header.nb ;i++){
        if(read_blockc(tof, &bloc ,i)== -1){
            return -1;
        }

        for(int j = 0 ; j<= bloc.count ; j++){
            if(bloc.tab[j].customerid == id ) {
                *user = bloc.tab[j];
                return 1;
            }
        }
    }
    return -1;
}


void displayAllcustomer(TOF* tof){
    blockc bloc;

    for(int i = 0 ; i < tof->header.nb ; i++){
        if(read_blockc(tof ,&bloc ,i) == -1){
            return ;
        }
        for(int j = 0 ; j< bloc.count; j++){
            Customer c = bloc.tab[j];
            printf("ID :%d, First name: %s, Last name: %s ,ContactInfo: %s\n",c.customerid,c.firstName,c.lastName,c.contactInfo);

        }
    }
}

