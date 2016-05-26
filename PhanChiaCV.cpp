#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#define MAX_CV 20
#define MAX_MAY 5

using namespace std;

struct CONGVIEC{
    int chiso;
    int time;
    int may;
};

void DocFile(char *fn,int &tongSoMay,int &tongSoCV,CONGVIEC cv[MAX_CV]);
void KhoiTao(int tongSoMay,int tongSoCV,CONGVIEC cv[MAX_CV],int thoiGianMay[MAX_MAY]);
void HoanVi(CONGVIEC &cv1,CONGVIEC &cv2);
void SapXepCongViec(int tongSoMay,int tongSoCV,CONGVIEC cv[MAX_CV]);
void PhanChiaCongViec(int tongSoMay,int tongSoCV,CONGVIEC cv[MAX_CV],int thoiGianMay[MAX_MAY]);
int TimMayRanhNhat(int tongSoMay,int thoiGianMay[MAX_MAY]);
void HienThi(int tongSoMay,int tongSoCV,CONGVIEC cv[MAX_CV],int thoiGianMay[MAX_MAY]);
int main()
{
    int tongSoMay,tongSoCV;
    CONGVIEC cv[MAX_CV];
    int thoiGianMay[MAX_MAY];
    DocFile("PCCV.txt",tongSoMay,tongSoCV,cv);
    KhoiTao(tongSoMay,tongSoCV,cv,thoiGianMay);
    SapXepCongViec(tongSoMay,tongSoCV,cv);
    PhanChiaCongViec(tongSoMay,tongSoCV,cv,thoiGianMay);
    HienThi(tongSoMay,tongSoCV,cv,thoiGianMay);
    return 0;
}

void DocFile(char *fn,int &tongSoMay,int &tongSoCV,CONGVIEC cv[MAX_CV]){
    FILE *f;
    f=fopen(fn,"rt");
    if(f==NULL){
        printf("Khong mo dc file");
        exit(1);
    }
    fscanf(f,"%d\n",&tongSoMay);
    fscanf(f,"%d\n",&tongSoCV);
    for(int i=0;i<tongSoCV;i++){
        fscanf(f,"%d",&cv[i].time);
    }
    fclose(f);
}

void KhoiTao(int tongSoMay,int tongSoCV,CONGVIEC cv[MAX_CV],int thoiGianMay[MAX_MAY]){
    for(int i=0;i<tongSoCV;i++){
        cv[i].chiso=i;
        cv[i].may=-1;
    }
    for(int i=0;i<tongSoMay;i++){
        thoiGianMay[i] = 0;
    }
}

void HoanVi(CONGVIEC &cv1,CONGVIEC &cv2){
    CONGVIEC temp;
    temp=cv1;
    cv1=cv2;
    cv2=temp;
}

void SapXepCongViec(int tongSoMay,int tongSoCV,CONGVIEC cv[MAX_CV]){
    for(int i=0;i<tongSoCV-1;i++){
        for(int j=i+1;j<tongSoCV;j++){
            if(cv[i].time>cv[j].time)
                HoanVi(cv[i],cv[j]);
        }
    }
}

int TimMayRanhNhat(int tongSoMay,int thoiGianMay[MAX_MAY]){

    int cs = 0;
    int time= thoiGianMay[cs];
    for(int i=1;i<tongSoMay;i++){
        if(thoiGianMay[i]<time){
            cs=i;
            time = thoiGianMay[i];
        }
    }
    return cs;
}

void PhanChiaCongViec(int tongSoMay,int tongSoCV,CONGVIEC cv[MAX_CV],int thoiGianMay[MAX_MAY]){

    for(int i=0;i<tongSoCV;i++){
        int may = TimMayRanhNhat(tongSoMay,thoiGianMay);
        cv[i].may = may;
        thoiGianMay[may] += cv[i].time;
    }
}

void HienThi(int tongSoMay,int tongSoCV,CONGVIEC cv[MAX_CV],int thoiGianMay[MAX_MAY]){
     printf("Tong so CV: %d\n",tongSoCV);

     printf("CV\t|ThoiGian\t| May");
     printf("\n------------------------------\n");
     for(int i=0;i<tongSoCV;i++){
             printf("%d\t",cv[i].chiso+1);
             printf("| %d\t\t",cv[i].time);
             printf("| %d\t",cv[i].may+1);
             printf("\n------------------------------\n");
     }

     int _max = thoiGianMay[0];
     for(int i=1;i<tongSoMay;i++){
             if(thoiGianMay[i] >_max){
                     _max = thoiGianMay[i];
             }
     }
     printf("Thoi gian thuc hien thap nhat: %d\n",_max);

}

