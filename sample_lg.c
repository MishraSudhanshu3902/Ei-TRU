#include "sample.h"
#include "rng.h"

void sample_fixed_type_lg(int *r, const unsigned char u[N3_SAMPLE_BYTES]){

    int32_t s[N3-1];
    int i;

    for (i = 0; i < (N3 - 1)/8; i++)
    {
        s[8*i+0] =                              (u[29*i+ 0] << 3) + (u[29*i+ 1] << 11) + (u[29*i+ 2] << 19) + ((uint32_t) u[29*i+ 3] << 27);
        s[8*i+1] = ((u[29*i+ 3] & 0xe0) >> 2) + (u[29*i+ 4] << 6) + (u[29*i+ 5] << 14) + (u[29*i+ 6] << 22) + ((uint32_t) u[29*i+ 7] << 30);
        s[8*i+2] = ((u[29*i+ 7] & 0xfc) << 1) + (u[29*i+ 8] << 9) + (u[29*i+ 9] << 17) + ((uint32_t)u[29*i+10] << 25);
        s[8*i+3] = ((u[29*i+10] & 0x80) >> 4) + (u[29*i+11] << 4) + (u[29*i+12] << 12) + (u[29*i+13] << 20) + ((uint32_t) u[29*i+14] << 28);
        s[8*i+4] =  ((u[29*i+14] & 0xf0) >> 1)+ (u[29*i+ 15] << 7) + (u[29*i+ 16] << 15) + (u[29*i+ 17] << 23) + ((uint32_t) u[29*i+ 18] << 31);
        s[8*i+5] = ((u[29*i+ 18] & 0xfe) <<2) + (u[29*i+ 19] << 10) + (u[29*i+ 20] << 18) + ((uint32_t) u[29*i+ 21] << 26);
        s[8*i+6] = ((u[29*i+ 21] & 0xc0) >> 3) + (u[29*i+ 22] << 5) + (u[29*i+ 23] << 13) + (u[29*i+24] << 21) + ((uint32_t) u[29*i+25] << 29);
        s[8*i+7] = ((u[29*i+25] & 0xf8)) + (u[29*i+26] << 8) + (u[29*i+27] << 16) + (u[29*i+28] << 24);
    }

    int leftOut = (N3  - 1) - ((N3  - 1) / 8) * 8;

    i = (N3 - 1)/8;

    switch(leftOut){

        case 2:
        s[8*i+0] =                              (u[29*i+ 0] << 3) + (u[29*i+ 1] << 11) + (u[29*i+ 2] << 19) + ((uint32_t) u[29*i+ 3] << 27);
        s[8*i+1] = ((u[29*i+ 3] & 0xe0) >> 2) + (u[29*i+ 4] << 6) + (u[29*i+ 5] << 14) + (u[29*i+ 6] << 22) + ((uint32_t) u[29*i+ 7] << 30);
        break;

        case 4:
        s[8*i+0] =                              (u[29*i+ 0] << 3) + (u[29*i+ 1] << 11) + (u[29*i+ 2] << 19) + ((uint32_t) u[29*i+ 3] << 27);
        s[8*i+1] = ((u[29*i+ 3] & 0xe0) >> 2) + (u[29*i+ 4] << 6) + (u[29*i+ 5] << 14) + (u[29*i+ 6] << 22) + ((uint32_t) u[29*i+ 7] << 30);
        s[8*i+2] = ((u[29*i+ 7] & 0xfc) << 1) + (u[29*i+ 8] << 9) + (u[29*i+ 9] << 17) + ((uint32_t)u[29*i+10] << 25);
        s[8*i+3] = ((u[29*i+10] & 0x80) >> 4) + (u[29*i+11] << 4) + (u[29*i+12] << 12) + (u[29*i+13] << 20) + ((uint32_t) u[29*i+14] << 28);
        break;

        case 6:
        s[8*i+0] =                              (u[29*i+ 0] << 3) + (u[29*i+ 1] << 11) + (u[29*i+ 2] << 19) + ((uint32_t) u[29*i+ 3] << 27);
        s[8*i+1] = ((u[29*i+ 3] & 0xe0) >> 2) + (u[29*i+ 4] << 6) + (u[29*i+ 5] << 14) + (u[29*i+ 6] << 22) + ((uint32_t) u[29*i+ 7] << 30);
        s[8*i+2] = ((u[29*i+ 7] & 0xfc) << 1) + (u[29*i+ 8] << 9) + (u[29*i+ 9] << 17) + ((uint32_t)u[29*i+10] << 25);
        s[8*i+3] = ((u[29*i+10] & 0x80) >> 4) + (u[29*i+11] << 4) + (u[29*i+12] << 12) + (u[29*i+13] << 20) + ((uint32_t) u[29*i+14] << 28);
        s[8*i+4] =  ((u[29*i+14] & 0xf0) >> 1)+ (u[29*i+ 15] << 7) + (u[29*i+ 16] << 15) + (u[29*i+ 17] << 23) + ((uint32_t) u[29*i+ 18] << 31);
        s[8*i+5] = ((u[29*i+ 18] & 0xfe) <<2) + (u[29*i+ 19] << 10) + (u[29*i+ 20] << 18) + ((uint32_t) u[29*i+ 21] << 26);
        break;

        default:break;
    }

    int S = (t)/3 * 3;

    for(int i = 0;i<S;i = i + 3){

        unsigned char randomval_seed[4];

        randombytes(randomval_seed,4);

        int randomValue = (u[0]) + (u[1]<<8) + (u[2]<<16) + (u[3]<<24);

        int set = randomValue & 1;

        int start = (set==0)?1:4;

        for(int j = 0;j<3;j++){
            s[i+j] |= (start++);
        }    
    }

    crypto_sort_int32(s,N3-1);

    for(int i = 0;i<N3-1;i++){
        r[i] = (s[i] & 7);
    }

    r[N3 - 1] = 0;
}

void sample_lg(Term* r,const unsigned char u[N3_SAMPLE_BYTES]){

    int arr[N3];

    sample_fixed_type_lg(arr,u);

    int map[7][2] = {{0,0},{1,0},{0,1},{-1,-1},{-1,0},{0,-1},{1,1}};

    int cnt = 0;

    for(int i = 0;i<N3;i++){
        r[i].a = map[arr[i]][0];
        r[i].b = map[arr[i]][1];

        if(r[i].a!=0 || r[i].b!=0){
            cnt++;
        }
    }

}

