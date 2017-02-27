#include <stdio.h>
#include <conio.h>
#include <windows.h>

void SetColor(short color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int ApaKabisat(int bulan, int tahun){
    if (bulan == 2 && ((tahun % 4 == 0 && tahun % 100 != 0) || tahun % 400 == 0))
        return 1;
    return 0;
}
int ApaSetelahKabisat(int bulan, int tahun){
    if (bulan > 2 && ((tahun % 4 == 0 && tahun % 100 != 0) || tahun % 400 == 0))
        return 1;
    return 0;
}

int OffsetBulan(int bulan, int offset){
    int b = bulan + offset;
    if (b < 1)
        b += 12;
    if (b > 12)
        b -= 12;
    return b;
}

int ApaTanggalMerah(int tanggal, int bulan){
    if (tanggal == 1 && bulan == 1)
        return 1;
    if (tanggal == 17 && bulan == 8)
        return 1;
    return 0;
}

int main(){
    int tanggal, bulan, tahun;
    char t;
    int hariPerBulanNonKabisat[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int jumlahHariNonKabisatSebelumBulanIni[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    char stringBulan[12][9] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    /*int jumlahHariNonKabisatSebelumBulanIni[12];
    int a, b;
    for (a = 0; a < 12; a++){
        jumlahHariNonKabisatSebelumBulanIni[a] = 0;
        for (b = 0; b < a; b++){
            jumlahHariNonKabisatSebelumBulanIni[a] += hariPerBulanNonKabisat[b];
        }
        printf("\n%d", jumlahHariNonKabisatSebelumBulanIni[a]);
    }*/
    while(1){

    while (1){
        printf("Masukkan tanggal dalam format hh/bb/tttt : ");
        if (scanf(" %d / %d / %d%c", &tanggal, &bulan, &tahun, &t) == 4
            && tanggal > 0 && bulan > 0 && tahun > 0 && t == '\n'
            && bulan < 13 && tanggal < (hariPerBulanNonKabisat[bulan] + ApaKabisat(bulan, tahun)))
            break;
        printf("Invalid input\n\n");
        getchar();
    }


    int tahunSebelumnya = tahun - 1;
    int bulanSebelumnya = OffsetBulan(bulan, -1);
    int bulanSetelahnya = OffsetBulan(bulan, 1);

    unsigned long long totalHariHinggaAwalBulan = tahunSebelumnya * 365 + tahunSebelumnya/4 - tahunSebelumnya /100 + tahunSebelumnya / 400;
    if (bulan > 1)
        totalHariHinggaAwalBulan += jumlahHariNonKabisatSebelumBulanIni[bulan - 1] + ApaSetelahKabisat(bulan, tahun);
    printf("\nTotalharihinggaawalbulan %lld\n\n", totalHariHinggaAwalBulan);

    int offset = 1;

    int tanggal1Min1 = (totalHariHinggaAwalBulan + offset) % 7 - 1;
    int x, y;
    int tanggalan = 1;

    int limitBulan = hariPerBulanNonKabisat[bulan - 1] + ApaKabisat(bulan, tahun);
    int con = hariPerBulanNonKabisat[bulanSebelumnya - 1] + ApaKabisat(bulanSebelumnya, tahun) - tanggal1Min1;
    int phase = tanggal1Min1 < 0 ? 1 : 0;
    printf("|--------------------------------------------------------------|\n");
    printf("|                       %9s %4d                         |\n", stringBulan[bulan-1], tahun);
    printf("|--------------------------------------------------------------|\n");
    printf("| ");
    SetColor(12);
    printf("Minggu");
    SetColor (7);
    printf(" | Senin  | Selasa |  Rabu  | Kamis  | Jumat  | Sabtu  |\n");
    for (y = 0; y < 6; y++){
        for (x = 0; x < 7; x++){
            SetColor(7);
            printf("|");
            if (phase == 0){
                int tgl = con + x;
                if (x == 0 || ApaTanggalMerah(tgl, bulanSebelumnya))
                    SetColor(4);
                else
                    SetColor(8);
                printf("   %d   ", tgl);
                if (x == tanggal1Min1)
                    phase = 1;
            }else if (phase == 1){
                printf("  ");

                if (x == 0 || ApaTanggalMerah(tanggalan, bulan))
                    SetColor(12);
                else
                    SetColor(7);
                if (tanggalan == tanggal){
                    printf("[%2d]  ", tanggalan);
                }else{
                    printf(" %2d   ", tanggalan);
                }
                tanggalan++;
                if (tanggalan > limitBulan){
                    tanggalan = 1;
                    phase = 2;
                }
            }else{
                if (x == 0 || ApaTanggalMerah(tanggalan, bulanSetelahnya))
                    SetColor(4);
                else
                    SetColor(8);
                printf("   %2d   ", tanggalan);
                tanggalan++;
            }
        }
        SetColor(7);
        printf("|\n");
    }
    printf("|--------------------------------------------------------------|\n");
    if (kbhit())
    getchar();
    printf("Tekan Enter untuk mengulangi");
    getchar();
    system("cls");
}
}
