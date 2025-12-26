#include <stdio.h>
#include <string.h>

// SÖZDE KODLARI ADIM ADIM KODLARIN ARASINA YAZILMIÞTIR.

struct Musteri {
    char adSoyad[50];
    char favoriKahve[30];
};

struct Musteri veritabani[100];
int kayitliKisiSayisi = 0;

int main() {
    char girilenIsim[50];
    char secilenKahve[30];
    int kisiBulunduMu = 0; 
    int secim, i;

    FILE *dosyaOku = fopen("kisiler.txt", "r");
    if (dosyaOku != NULL) {


        while (fscanf(dosyaOku, " %[^\n]s", veritabani[kayitliKisiSayisi].adSoyad) != EOF) {

            fscanf(dosyaOku, " %[^\n]s", veritabani[kayitliKisiSayisi].favoriKahve);
            
            kayitliKisiSayisi++;
            if (kayitliKisiSayisi >= 100) break;
        }
        fclose(dosyaOku);
    }
    // -------------------------------------------------------

    while(1) {
        // ADIM 1: BAÞLA
        printf("\n====================================\n");
        printf("       KAHVE OTOMASYONU BASLADI\n");
        printf("====================================\n");
        
        // ADIM 2: Ýsim Soyisim Giriniz
        printf("Lutfen Isim Soyisim giriniz (Cikmak icin 'x'): ");
    
        scanf(" %[^\n]s", girilenIsim); // boþluklu isimleri alabÝLMEK ÝÇÝN

        if(strcmp(girilenIsim, "x") == 0) break; 

        // ADIM 3: Giden kiþi kayýtlý mý?
        
        kisiBulunduMu = 0; 
        
        for(i = 0; i < kayitliKisiSayisi; i++) {
            if(strcmp(veritabani[i].adSoyad, girilenIsim) == 0) {
                // EVET ise:
                kisiBulunduMu = 1;
                strcpy(secilenKahve, veritabani[i].favoriKahve); // Kayýtlý kahveyi al
                printf("\n> Hos geldiniz %s! Kaydiniz bulundu.\n", girilenIsim);
                printf("> Sizin icin hemen bir %s hazirliyorum.\n", secilenKahve);
                // "Adým 9"a (Servis) atlamak için buradaki if bloðundan çýkýp aþaðýya gideceðiz.
                break;
            }
        }

        // HAYIR ise: "Adým 4"e git (Yani seçim yapma kýsmý)
        if (kisiBulunduMu == 0) {
            printf("\n> Kaydiniz bulunamadi. Lutfen secim yapiniz.\n");

            // ADIM 4: Kahve verilecek durum veya zaman seçilir
            printf("\nSecim Modu:\n1. Ruh Hali\n2. Gun Saati\n3. Manuel Secim\nSeciminiz: ");
            int modSecimi;
            scanf("%d", &modSecimi);

            if (modSecimi == 1) { 
                // ADIM 5: Ruh Haline Göre
                printf("Ruh Haliniz (1: Mutlu, 2: Uzgun, 3: Kizgin): ");
                scanf("%d", &secim);
                if (secim == 1) strcpy(secilenKahve, "Mocha");
                else if (secim == 2) strcpy(secilenKahve, "Latte");
                else if (secim == 3) strcpy(secilenKahve, "Cappucino");
                else strcpy(secilenKahve, "HATALI SEÇÝM"); // Hatalý seçim
            } 
            else if (modSecimi == 2) { 
                // ADIM 6: Gün Saatine Göre
                printf("Gun Saati (1: Sabah, 2: Ogle, 3: Aksam): ");
                scanf("%d", &secim);
                if (secim == 1) strcpy(secilenKahve, "Espresso");
                else if (secim == 2) strcpy(secilenKahve, "Mocha");
                else if (secim == 3) strcpy(secilenKahve, "Cappucino");
                else strcpy(secilenKahve, "HATALI SEÇÝM");
            } 
            else { 
                // ADIM 7: Manuel
                printf("Kahve Secin (1: Latte, 2: Mocha, 3: Cappucino, 4: Macchiato): ");
                scanf("%d", &secim);
                if (secim == 1) strcpy(secilenKahve, "Latte");
                else if (secim == 2) strcpy(secilenKahve, "Mocha");
                else if (secim == 3) strcpy(secilenKahve, "Cappucino");
                else if (secim == 4) strcpy(secilenKahve, "Macchiato");
                else {
                    printf("Gecersiz secim, basa donuluyor.\n");
                    continue; // Döngü baþýna dön
                }
            }
            
            // Kahve hazýrlandý mesajý (Adým 8 öncesi hazýrlýk)
            printf("\n> %s hazirlaniyor...\n", secilenKahve);

            // ADIM 8: Alýnan kahve kayýt edilsin mi?
            printf("Bu secimi isminize kaydetmek ister misiniz? (1: Evet, 2: Hayir): ");
            
            int kayitSecimi;
            
            scanf("%d", &kayitSecimi);

            if (kayitSecimi == 1) {
                if (kayitliKisiSayisi < 100) {
                	
                    strcpy(veritabani[kayitliKisiSayisi].adSoyad, girilenIsim);
                    strcpy(veritabani[kayitliKisiSayisi].favoriKahve, secilenKahve);
                    kayitliKisiSayisi++;
                    
             
                    FILE *dosyaYaz = fopen("kisiler.txt", "a");
                    
                    if (dosyaYaz != NULL) {
                        fprintf(dosyaYaz, "%s\n%s\n", girilenIsim, secilenKahve);
                        
                        fclose(dosyaYaz);
                        
                        printf("> Veri 'kisiler.txt' dosyasina yazildi.\n");
                    } else {
                        printf("> Dosya hatasi! Kalici kayit yapilamadi.\n");
                    }


                    printf("> Basariyla kaydedildi!\n");
                } else {
                    printf("> Hafiza dolu, kayit yapilamadi!\n");
                }
            }
        }

        // ADIM 9: Kahveyi servis et
        printf("\n*********************************\n");
        printf(" BUYURUN, %s HAZIR! AFIYET OLSUN.\n", secilenKahve); 
        printf("*********************************\n");

        // ADIM 10: BÝTÝR (Döngü olduðu için baþa sarar, ancak listeyi görelim)
        
        // --- EKSTRA: Kayýtlý Kiþileri Listeleme ---
        printf("\n--- Guncel Kayitli Musteri Listesi ---\n");
        for(i=0; i < kayitliKisiSayisi; i++) {
            printf("%d. %s (Favori: %s)\n", i+1, veritabani[i].adSoyad, veritabani[i].favoriKahve);
        }
        printf("--------------------------------------\n");
    }
    return 0;
}
