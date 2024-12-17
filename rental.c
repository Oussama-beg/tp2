#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "rental.h"
#include "customer.h"
#include "game.h"
#include "outils.h"

RentalR create_rentalR(Customer c, Game g, int id, Date rentaldate, Date returndate, float price){

    RentalR newr;

    newr.rentalid = id;
    newr.customer = c;
    newr.game = g;

    newr.rentalDate = rentaldate;
    newr.returnDate = returndate;
    
    newr.totalprice = price;

    return newr;

}

RentalD create_rentalD(RentalR rentale){

    RentalD rentald;

    rentald.rentalID = rentale.rentalid;
    rentald.cid = rentale.customer.customerid;
    rentald.gid = rentale.game.gameid;
    rentald.rentalDate = rentale.rentalDate;
    rentald.returnDate = rentale.returnDate;
    rentald.totalprice = rentale.totalprice;

    return rentald;

}

int read_blockr(TOF * tof ,blockr *bloc ,int nb){
    if(nb <= tof->header.nb)
    return -1;
    FILE *file = fopen(tof->file , "r+b");
    if(file == NULL){
        return -1;
    }

    fseek(file, sizeof(Header) + nb * sizeof(blockr) , SEEK_SET);

    int result = fread(bloc, sizeof(blockr) , 1 , file);
    fclose(file);
    return result;
}

void write_blockr(TOF *tof, blockr *bloc , int nb){
    FILE *file = fopen(tof->file,"r+b");
    fseek(file, sizeof(Header) + nb * sizeof(blockr) , SEEK_SET);
    fwrite(bloc, sizeof(blockr) , 1 , file);
    close(file);
}

int saverentaldisk(TOF *tof, RentalR rentalr){

    blockr bloc;
    int read = read_blockr(tof, &bloc, tof->header.nb);
    RentalD rental = create_rentalD(rentalr);

    if(read <= 0 || bloc.count == 10){

        blockr blocc;
        blocc.tab[0] = rental;
        blocc.count = 1;
        write_blockr(tof, &blocc, tof->header.nb);
        tof->header.nb++;
        write_entete(tof);
        return 1;

    }else{
        bloc.tab[bloc.count] = rental;
        bloc.count++;
        write_blockr(tof, &bloc, tof->header.nb -1);

        return 1;
    }
    return -1;
}


int search_rental(TOF *tof, int ID ,RentalR *rental){

    blockr bloc;

    for(int i = 0; i< tof->header.nb; i++){
        if(read_blockr(tof,&bloc, i) == -1){
            return -1;
        }

        for(int j = 0; j< bloc.count ; j++){
            if(bloc.tab[j].rentalID == ID){

                search_customer(tof, bloc.tab[j].cid, &(rental->customer));
                search_game(tof, bloc.tab[j].gid, &(rental->game));
                rental->rentalid = ID;
                rental->rentalDate;
                rental->returnDate;
                rental->totalprice;

                return 1;
            }
        }
    }
    return -1;
}

void displayAllrental(TOF* tof){
    RentalR r;
    blockr bloc;

    for(int i = 0 ; i < tof->header.nb ; i++){
        if(read_blockr(tof ,&bloc ,i) == -1){
            return;
        }
        for(int j = 0 ; j< bloc.count; j++){
            if(search_rental(tof, bloc.tab[j].rentalID, &r) == 1){
            
            printf("ID");


            }

        }
    }
}

