#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_ITEMS 100
#define MAX_LENGTH 500

typedef struct {
    char aciklama[MAX_LENGTH];
    bool kontrol_edildimi; // 0 No, 1 Yes
} Madde;

typedef struct {
    float voltaj;
    int durum; //0 Average, 1 Good
} Akuler;

void MaddeEkle(Madde Liste[], int *sayi) {
    if (*sayi >= MAX_ITEMS) {
        printf("You cannot enter more items.\n");
    } else {
        printf("\nEnter the item you want to add: ");
        getchar(); 
        fgets(Liste[*sayi].aciklama, MAX_LENGTH, stdin);
        Liste[*sayi].aciklama[strcspn(Liste[*sayi].aciklama, "\n")] = 0; 
        Liste[*sayi].kontrol_edildimi = false;
        printf("\nItem Added\n");
        (*sayi)++;
    }
}

void Kontrol(Madde Liste[], int sayi) {
    for (int i = 0; i < sayi; i++) {
        int temp;
        if (Liste[i].kontrol_edildimi == true)
        {
            continue;
        }
        do {
            printf("%s (1 Yes 0 No): ", Liste[i].aciklama);
            scanf("%d", &temp);
            if (temp == 1) {
                Liste[i].kontrol_edildimi = true;
            } else if (temp == 0) {
                Liste[i].kontrol_edildimi = false;
            } else {
                printf("Invalid input! Please enter 0 or 1.\n");
            }
        } while (temp != 0 && temp != 1);
    }
}

void AkuEkle(Akuler AkuList[], int AkuSayisi) {
    for (int i = 0; i < AkuSayisi; i++) {
        printf("\nEnter the voltage of Aku %d: ", i + 1);
        scanf("%f", &AkuList[i].voltaj);
        printf("Enter the state of Aku %d (0: Average, 1: Good): ", i + 1);
        scanf("%d", &AkuList[i].durum);
    }
}

Akuler EnIyiAku(Akuler AkuList[], int AkuSayisi) {
    Akuler BestAku = AkuList[0];
    for (int i = 1; i < AkuSayisi; i++) {
        if (fabs(13 - AkuList[i].voltaj) < fabs(13 - BestAku.voltaj)) {
            BestAku = AkuList[i];
        } else if (fabs(13 - AkuList[i].voltaj) == fabs(13 - BestAku.voltaj)) {
            if (AkuList[i].durum == 1 && BestAku.durum == 0) {
                BestAku = AkuList[i]; 
            }
        }
    }
    return BestAku;
}

int main() {
    int sayi = 0;
    Madde Liste[MAX_ITEMS];
    int AkuSayisi;
    Akuler Akulist[MAX_ITEMS];
    int secim;

    while (true) {
        printf("\nWhat do you want to do?\n 1: Add Item \n 2: Check List \n 3: Add Aku \n 4: Result and Exit \n 5: Exit\n");
        printf("Select your choice: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                MaddeEkle(Liste, &sayi);
                break;
            case 2:
                if (sayi == 0) {
                    printf("You should add items first.\n");
                } else {
                    Kontrol(Liste, sayi);
                }
                break;
            case 3:
                printf("\nEnter the number of Akus: ");
                scanf("%d", &AkuSayisi);
                AkuEkle(Akulist, AkuSayisi);
                break;
            case 4:
                bool AllDone = true;
                printf("\n************************************************************");
                printf("\n************************************************************");
                printf("\nThe best Aku: Voltage = %.2f, State = %d (0 = Average, 1 = Good)\n", EnIyiAku(Akulist, AkuSayisi).voltaj, EnIyiAku(Akulist, AkuSayisi).durum);
                for (int i = 0; i < sayi; i++) {
                    if (Liste[i].kontrol_edildimi == false) {
                        printf("\nPlease complete the following task: %s\n", Liste[i].aciklama);
                        AllDone = false;
                    }
                }
                if (AllDone == false)
                {
                    printf("\n************************************************************");
                    printf("\n************************************************************");
                }
                if (AllDone == true)
                {
                    printf("\nCongratulations, everything is ready! Good luck!");
                    printf("\n************************************************************");
                    printf("\n************************************************************");
                    return 0;
                }
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }
    return 0;
}
