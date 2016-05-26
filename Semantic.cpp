#include <iostream>
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <math.h>
#define MAXBIEN 10
#define MAXCT 20
#define PI 3.14159265
using namespace std;

typedef char BIEN[10];
typedef char CONGTHUC[50];
BIEN bien[MAXBIEN];
int soBien;
CONGTHUC congthuc[MAXCT];
int soCongThuc;
int quanHe[MAXBIEN][MAXCT];
double giaTriBien[MAXBIEN];

void docFile(char *fn);
void khoiTaoGiaTriBien();
void hienThiBienVaCongThuc();
void kichHoatBien(int iBien);
int demSoBienChuaKichHoat(int kCongThuc);
int timCongThucSanSangKichHoat();
int timBienChuaKichHoat(int kCongThuc);
void tinhVaLuuGiaTriBienTheoCTR0(int iBien);
void tinhVaLuuGiaTriBienTheoCTR1(int iBien);
void tinhVaLuuGiaTriBienTheoCTR2(int iBien);
void tinhVaLuuGiaTriBienTheoCTR3(int iBien);
void tinhVaLuuGiaTriBienTheoCTR4(int iBien);
void tinhVaLuuGiaTriBienTheoCTR5(int iBien);
void nhapVaKichHoatCacBienBanDau();
void nhapChiSoBienCanTinh(int &iBienCanTinh);
void giaiTamGiac();

int main()
{
    docFile("data.txt");
    hienThiBienVaCongThuc();
    khoiTaoGiaTriBien();
    cout<<"\nGiai tam giac\n";
    giaiTamGiac();

    return 0;
}

void docFile(char *fn){
    FILE *f;
    f = fopen(fn,"rt");
    if(f==NULL){
        printf("Khong mo duoc file %s",fn);
        getch();
        exit(1);
    }

    fscanf(f,"%d\n",&soBien);
    fscanf(f,"%d\n",&soCongThuc);

    for(int i=0;i<soBien;i++){
        fscanf(f,"%s\n",&bien[i]);
    }
    for(int i=0;i<soCongThuc;i++){
        fscanf(f,"%s\n",&congthuc[i]);
    }
    for(int i=0;i<soBien;i++){
        for(int j=0;j<soCongThuc;j++){
            fscanf(f,"%d\t",&quanHe[i][j]);
        }
    }
    fclose(f);
}

void khoiTaoGiaTriBien(){
    for(int i;i<soBien;i++){
        giaTriBien[i]=0;
    }
}

void hienThiBienVaCongThuc(){
    int i,j;
    printf("So bien: %d\n",soBien);
    printf("So CT: %d\n",soCongThuc);
    for(i=0;i<soBien;i++){
        printf("%s\n",bien[i]);
    }
    for(i=0;i<soCongThuc;i++){
        printf("%s\n",congthuc[i]);
    }
    for(i=0;i<soBien;i++){
        for(j=0;j<soCongThuc;j++){
                if(quanHe[i][j]==-1){
                    printf("%d\t",quanHe[i][j]);
                }else{
                    printf(" %d\t",quanHe[i][j]);
                }
        }
        printf("\n");
    }
}

///Kích hoạt biến là tìm 1 dòng of i biến nếu có -1 thì bật lên 1
///1 là đã kích hoạt, -1 là biến có liên hệ và chưa kích hoạt
void kichHoatBien(int iBien){
    for(int j=0;j<soCongThuc;j++){
        if(quanHe[iBien][j]==-1)
            quanHe[iBien][j]=1;
    }
}

///Duyệt qua 1 cột kCông thức qua các biến nếu =-1 thì kq++;
///return kết quả
int demSoBienChuaKichHoat(int kCongThuc){
    int kq = 0;
    for(int i=0;i<soBien;i++){
        if(quanHe[i][kCongThuc]==-1)
            kq++;
    }
    return kq;
}


///Duyệt qua các công thức và tìm số công thức nào có số biến chưa kích hoạt bằng 1 thì sẳn sàng kích hoạt
int timCongThucSanSangKichHoat(){
    for(int j=0;j<soCongThuc;j++){
        if(demSoBienChuaKichHoat(j)==1)
            return j;
    }
    return -1;
}

///Tìm 1 cột kCongThuc nếu có 1 biến chua kích hoạt thì return ra giá trị biến chưa kích hoạt
///Giá trị đó tìm thấy đầu tiên
int timBienChuaKichHoat(int kCongThuc){
    for(int i=0;i<soBien;i++){
        if(quanHe[i][kCongThuc]==-1)
            return i;
    }
    return -1;
}

void tinhVaLuuGiaTriBienTheoCTR0(int iBien){
    switch(iBien){
        case 0:giaTriBien[0] = PI-giaTriBien[1]-giaTriBien[2];
            break;
        case 1:giaTriBien[1] = PI-giaTriBien[0]-giaTriBien[2];
            break;
        case 2:giaTriBien[2] = PI-giaTriBien[0]-giaTriBien[1];
            break;
    }
}

void tinhVaLuuGiaTriBienTheoCTR1(int iBien){
    switch(iBien){
        case 0:giaTriBien[0] = asin(giaTriBien[3]*sin(giaTriBien[1])/giaTriBien[4]);
            break;
        case 1:giaTriBien[1] = asin(sin(giaTriBien[0]*giaTriBien[4]/giaTriBien[3]));
            break;
        case 3:giaTriBien[3] = sin(giaTriBien[0])*giaTriBien[4]/sin(giaTriBien[1]);
            break;
        case 4:giaTriBien[4] = giaTriBien[3]*sin(giaTriBien[1])/sin(giaTriBien[0]);
            break;
    }
}

void tinhVaLuuGiaTriBienTheoCTR2(int iBien){
    switch(iBien){
        case 4:giaTriBien[4] = giaTriBien[5]*sin(giaTriBien[1])/sin(giaTriBien[2]);
            break;
        case 5:giaTriBien[5] = giaTriBien[4]*sin(giaTriBien[2])/sin(giaTriBien[1]);
            break;
        case 2:giaTriBien[2] = asin(giaTriBien[5]*sin(giaTriBien[1])/giaTriBien[4]);
            break;
        case 1:giaTriBien[1] = asin(giaTriBien[4]*sin(giaTriBien[2])/giaTriBien[5]);
            break;
    }
}

void tinhVaLuuGiaTriBienTheoCTR3(int iBien){
    switch(iBien){
        case 3:giaTriBien[3] = giaTriBien[7]-giaTriBien[4]-giaTriBien[5];
            break;
        case 4:giaTriBien[4] = giaTriBien[7]-giaTriBien[3]-giaTriBien[5];
            break;
        case 5:giaTriBien[5] = giaTriBien[7]-giaTriBien[3]-giaTriBien[4];
            break;
        case 7:giaTriBien[7] = giaTriBien[3]+giaTriBien[4]+giaTriBien[5];
            break;
    }
}

void tinhVaLuuGiaTriBienTheoCTR4(int iBien){
    switch(iBien){
        case 6:giaTriBien[6] = giaTriBien[4]*sin(giaTriBien[0]);
            break;
        case 4:giaTriBien[4] = giaTriBien[6]/sin(giaTriBien[0]);
            break;
        case 0:giaTriBien[0] = asin(giaTriBien[6]/giaTriBien[4]);
            break;
    }
}

void tinhVaLuuGiaTriBienTheoCTR5(int iBien){
    switch(iBien){
        case 8:giaTriBien[8] = giaTriBien[6]*giaTriBien[5]/2;
            break;
        case 6:giaTriBien[6] = giaTriBien[8]*2/giaTriBien[5];
            break;
        case 5:giaTriBien[5] = 2*giaTriBien[8]/giaTriBien[6];
            break;

    }
}

void nhapVaKichHoatCacBienBanDau(){
    int iBien,soBienBanDau;
    printf("Nhap so bien ban dau de xac dinh tam giac: ");
    scanf("%d",&soBienBanDau);
    printf("\nNhap chi so cac bien\n");
    printf("0:anpha\t1:beta\t2:gama\t3:a\t4:b\t5:c\t6:hc\t7:p\t8:s\n");
    for(int i=0;i<soBienBanDau;i++){
        printf("Chi so cua bien thu %d: ",i+1);
        scanf("%d",&iBien);
        kichHoatBien(iBien);
        printf("\t%s: ",bien[iBien]);
        scanf("%lf",&giaTriBien[iBien]);
    }
}

void nhapChiSoBienCanTinh(int &iBienCanTinh){
    printf("Nhap chi so bien can tinh:");
    scanf("%d",&iBienCanTinh);
}

///B1: Nhập và kích hoạt các đỉnh ban đầu
///B2:Nhâp biến cần tính
///B3:Tim công thức sẵn sàng kích hoạt
///Khi công thức sẳn sàng kích hoạt tồn tại (!=-1) thì
///B4:Tìm biến chưa kích hoạt
///b5: kích hoạt biến đó
///B6:In biến và giá trị biến và tìm công thức chưa sẳn sàng kích hoạt lặp lại đến khi ko tìm thấy công thức sẳn sàng kích hoạt
///B6:In ra công thức cuối, biến và giá trị

void giaiTamGiac(){
    nhapVaKichHoatCacBienBanDau();
    int iBienCanTinh;
    nhapChiSoBienCanTinh(iBienCanTinh);

    int iBienChuaKichHoat;
    int jCongThucSanSangKichHoat = timCongThucSanSangKichHoat();
    printf("\n==Cac cong thuc duoc kich hoat==\n");
    while(jCongThucSanSangKichHoat>-1){
        iBienChuaKichHoat = timBienChuaKichHoat(jCongThucSanSangKichHoat);
        switch(jCongThucSanSangKichHoat){
            case 0:tinhVaLuuGiaTriBienTheoCTR0(iBienChuaKichHoat);break;
            case 1:tinhVaLuuGiaTriBienTheoCTR1(iBienChuaKichHoat);break;
            case 2:tinhVaLuuGiaTriBienTheoCTR2(iBienChuaKichHoat);break;
            case 3:tinhVaLuuGiaTriBienTheoCTR3(iBienChuaKichHoat);break;
            case 4:tinhVaLuuGiaTriBienTheoCTR4(iBienChuaKichHoat);break;
            case 5:tinhVaLuuGiaTriBienTheoCTR5(iBienChuaKichHoat);break;
        }
        kichHoatBien(iBienChuaKichHoat);
        printf("   %s => ",congthuc[jCongThucSanSangKichHoat]);
        printf("bien %s : %g\n",bien[iBienChuaKichHoat],giaTriBien[iBienChuaKichHoat]);
        jCongThucSanSangKichHoat = timCongThucSanSangKichHoat();
    }
    printf("ket qua bien %s = %g",bien[iBienCanTinh],giaTriBien[iBienCanTinh]);
}
