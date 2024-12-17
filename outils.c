#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

TOF *open_file(char *path, char mode)
{
    FILE *f;
    TOF *tof = (TOF *)malloc(sizeof(TOF));
    strcpy(tof->file, path);
    switch (mode)
    {
    
    case 'A':
        read_entete(tof);
        return tof;

    case 'N':
        f = fopen(path, "w");
        fclose(f);
        tof->header.nb = 0;
        write_entete(tof);
        return tof;
    }
}

void write_entete(TOF *tof){
    FILE *file = fopen(tof->file , "r+b");
    fwrite(&(tof->header), sizeof(Header), 1, file);
    fclose(file);
}

void read_entete(TOF *tof){
    FILE *file = fopen(tof->file , "rb");
    fread(&(tof->header), sizeof(Header), 1, file);
    fclose(file);
}



void close(TOF *tof){
    if(tof != NULL){
        free(tof->file);
        free(tof);
    }
}


