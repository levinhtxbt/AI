#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#define FILE_NAME "GTS.txt"
#define MAX_DINH 10
using namespace std;

struct DOTHI{
    int sodinh;
    int chiphi[MAX_DINH][MAX_DINH];
};

struct CHUTRINH{
    DOTHI dothi;
    int duongdi[MAX_DINH];
    int tongChiPhi;
};

void DocFile(DOTHI &dothi);
void KhoiTao(CHUTRINH &tour);
int LaChuaTham(int dinh,CHUTRINH tour);
int TimDinhChuaThamGanNhat(int dinhHienTai,CHUTRINH tour);
CHUTRINH GTS1(DOTHI dothi,int dinhBatDau);
CHUTRINH GTS2(DOTHI dothi);
void HienThiChuTrinh(CHUTRINH tour);
void HienThiDoThi(DOTHI dothi);
int main()
{
    DOTHI dothi;
    CHUTRINH chutrinh;
    DocFile(dothi);
    HienThiDoThi(dothi);
    chutrinh = GTS2(dothi);
    HienThiChuTrinh(chutrinh);
    return 0;
}
void DocFile(DOTHI &dothi){
    FILE *f;
    f = fopen(FILE_NAME,"rt");
    if(f==NULL){
        printf("Can not open file %s",FILE_NAME);
        exit(1);
    }
    fscanf(f,"%d\n",&dothi.sodinh);
    for(int i=0;i<dothi.sodinh;i++){
        for(int j=0;j<dothi.sodinh;j++){
            fscanf(f,"%d",&dothi.chiphi[i][j]);
        }
    }
    fclose(f);
}

void HienThiDoThi(DOTHI dothi){
    printf("Tong so dinh: %d\n",dothi.sodinh);
    for(int i=0;i<dothi.sodinh;i++){
        for(int j=0;j<dothi.sodinh;j++){
            printf("%d\t",dothi.chiphi[i][j]);
        }
        printf("\n");
    }
}

void HienThiChuTrinh(CHUTRINH tour){
    printf("Tour: ");
    for(int i=0;i<=tour.dothi.sodinh;i++){
        printf("%d",tour.duongdi[i]+1);
        if(tour.duongdi[i+1]!=-1)
            printf(" -> ");
    }
    printf("\nCost: %d",tour.tongChiPhi);
}

void KhoiTao(CHUTRINH &tour){
    tour.tongChiPhi=0;
    for(int i=0;i<MAX_DINH;i++){
        tour.duongdi[i]=-1;
    }
}

int LaChuaTham(int dinh,CHUTRINH tour){
    for(int i=0;i<MAX_DINH;i++){
        if(tour.duongdi[i]==dinh)
            return 0;
    }
    return 1;
}

int TimDinhChuaThamGanNhat(int dinhHienTai,CHUTRINH tour){
    int costMin = 9999;
    int cs = -1;
    for(int i=0;i<tour.dothi.sodinh;i++){
        if(dinhHienTai!=i && LaChuaTham(i,tour)){
            if(tour.dothi.chiphi[dinhHienTai][i]<costMin){
                costMin  = tour.dothi.chiphi[dinhHienTai][i];
                cs = i;
            }
        }
    }
    return cs;
}

CHUTRINH GTS1(DOTHI dothi,int dinh){
    CHUTRINH tour;
    KhoiTao(tour);
    tour.dothi = dothi;
    int N = dothi.sodinh;
    tour.duongdi[0] = dinh;
    int dinhHienTai = dinh;
    int dinhTiepTheo = -1;
    for(int i=1;i<MAX_DINH;i++){
        dinhTiepTheo = TimDinhChuaThamGanNhat(dinhHienTai,tour);
        if(dinhTiepTheo!=-1){
            tour.duongdi[i] = dinhTiepTheo;
            tour.tongChiPhi += dothi.chiphi[dinhHienTai][dinhTiepTheo];
            dinhHienTai = dinhTiepTheo;
        }
    }
    tour.duongdi[N] = dinh;
    tour.tongChiPhi += dothi.chiphi[dinhHienTai][dinh];
    return tour;


}

CHUTRINH GTS2(DOTHI dothi){
    CHUTRINH temp = GTS1(dothi,0);

    for(int i=1;i<dothi.sodinh;i++){
        CHUTRINH iChuTrinh = GTS1(dothi,i);
        if(iChuTrinh.tongChiPhi<temp.tongChiPhi){
            temp = iChuTrinh;
        }
    }
    return temp;
}
