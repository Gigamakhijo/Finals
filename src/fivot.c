#include "fivot.h"
#include "bit.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>

int filesize( const char  *filename){
    struct stat file_info;
    int sz_file;
    if ( 0 > stat( filename, &file_info)){
	    return -1; // file이 없거나 에러
    }
    return file_info.st_size;
}

uint8_t ** new_bitmap(int chunk_size){
     uint8_t ** bitmap = (uint8_t **)malloc(sizeof(uint8_t*) * 8);
    //초기화 과정
    for(int i=0;i<8;i++){
        bitmap[i] = (uint8_t *)malloc(sizeof(uint8_t) * chunk_size);
    }
    return bitmap;
}

uint8_t ** new_fivot_bitmap(int chunk_size){
     uint8_t ** bitmap = (uint8_t **)malloc(sizeof(uint8_t*) * chunk_size);
    //초기화 과정
    for(int i=0;i<chunk_size;i++){
        bitmap[i] = (uint8_t *)malloc(sizeof(uint8_t) * 8);
    }
    return bitmap;
}

void set_bitmap(uint8_t ** bitmap, int chunk_size, BITFILE * bf){
    for(int i=0;i<8;i++){
        for(int j=0;j<chunk_size;j++){
            bread(INT, bf, &bitmap[i][j], 1, 1);
        }
    }
}

void set_fivot_bitmap(uint8_t ** bitmap, int chunk_size, BITFILE * bf){
    for(int i=0;i<chunk_size;i++){
        for(int j=0;j<8;j++){
            bread(INT, bf, &bitmap[i][j], 1, 1);
        }
    }
}

void print_bitmap(uint8_t ** bitmap, int chunk_size){
    for(int i=0;i<8;i++){
        for(int j=0;j<chunk_size;j++){
            printf("%d ", bitmap[i][j]);
        }
        printf("\n");
    }
}

void print_fivot_bitmap(uint8_t ** bitmap, int chunk_size){
    for(int i=0;i<chunk_size;i++){
        for(int j=0;j<8;j++){
            printf("%d ", bitmap[i][j]);
        }
        printf("\n");
    }
}

void free_bitmap(uint8_t ** bitmap){
    for(int i=0;i<8;i++){
        free(bitmap[i]);
    }
    free(bitmap);
}

void free_fivot_bitmap(uint8_t ** bitmap, int chunk_size){
    for(int i=0;i<chunk_size;i++){
        free(bitmap[i]);
    }
    free(bitmap);
}

void convert_fivot(char * input, char * output){
    int chunk = filesize(input);
    uint8_t ** bitmap = new_bitmap(chunk);

    BITFILE *rbf, *wbf;
    rbf = bopen(input, "rb");
    wbf = bopen(output, "wb");
    
    set_bitmap(bitmap, chunk, rbf);

    for(int i=0;i<chunk;i++){
        for(int j=0;j<8;j++){
            bwrite(INT, wbf, &bitmap[j][i], 1, 1);
        }
    }

    free_bitmap(bitmap);
    bflush(wbf);
    bclose(wbf);
    bclose(rbf);
}

void revert_fivot(char * input, char * output){
    int chunk = filesize(input);
    uint8_t ** bitmap = new_fivot_bitmap(chunk);

    BITFILE *rbf, *wbf;
    rbf = bopen(input, "rb");
    wbf = bopen(output, "wb");
    
    set_fivot_bitmap(bitmap, chunk, rbf);

    for(int i=0;i<8;i++){
        for(int j=0;j<chunk;j++){
            bwrite(INT, wbf, &bitmap[j][i], 1, 1);
        }
    }

    free_fivot_bitmap(bitmap, chunk);
    bflush(wbf);
    bclose(wbf);
    bclose(rbf);
}
