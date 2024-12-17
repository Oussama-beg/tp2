#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "game.h"
#include "rental.h"

int read_blockg(TOF * tof ,blockg *bloc ,int nb){
    if(nb <= tof->header.nb)
    return -1;
    FILE *file = fopen(tof->file , "r+b");
    if(file == NULL){
        return -1;
    }

    fseek(file, sizeof(Header) + nb * sizeof(blockg) , SEEK_SET);

    int result = fread(bloc, sizeof(blockg) , 1 , file);
    fclose(file);
    return result;
}

void write_blockg(TOF *tof, blockg *bloc , int nb){
    FILE *file = fopen(tof->file,"r+b");
    fseek(file, sizeof(Header) + nb * sizeof(blockg) , SEEK_SET);
    fwrite(bloc, sizeof(blockg) , 1 , file);
    close(file);
}

void insert_game(TOF* tof , Game user){

    blockg bloc;
    int read = read_blockg(tof ,&bloc,tof->header.nb -1);

    if(read <= 0 || bloc.count == SIZE){
        blockg blocc;
        blocc.tab[0] = user;
        blocc.count = 1;
        write_blockg(tof ,&blocc ,tof->header.nb);
        tof->header.nb++;
        write_entete(tof);
    }else{
        bloc.tab[bloc.count]= user;
        bloc.count++;

    write_blockg(tof , &bloc ,tof->header.nb-1);
    }

}

int search_game(TOF* tof , int id , Game* user){
    blockg bloc;

    for(int i = 0; i<= tof->header.nb ;i++){
        if(read_blockg(tof, &bloc ,i)== -1){
            return -1;
        }

        for(int j = 0 ; j<= bloc.count ; j++){
            if(bloc.tab[j].gameid == id ) {
                *user = bloc.tab[j];
                return 1;
            }
        }
    }
    return -1;
}


void displayAllgame(TOF* tof){
    blockg bloc;

    for(int i = 0 ; i < tof->header.nb ; i++){
        if(read_blockg(tof ,&bloc ,i) == -1){
            return ;
        }
        for(int j = 0 ; j< bloc.count; j++){
            Game c = bloc.tab[j];
            printf("ID :%d, Title: %s ,RentalPrice: %f\n",c.gameid,c.title,c.rentalPrice);

        }
    }
}