/*
Alperen Akgül 2110206030

Harflerin frekansına göre deşifreleme yapan program

şifrelemek ve deşirelemek istediğiniz metni normal.txt içerisine tamamı küçük harf olacak şekilde atınız.

İngilizce harf frekans tablosu: https://commons.wikimedia.org/wiki/File:English_letter_frequency_%28frequency%29.svg

*/

#include <stdio.h>

int main(){
    int harfSayici[26] = {0};
    char alfabe[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};                     
    char sifrelemeAlfabesi[26] = {'r', 'u', 't', 'a', 'g', 'v', 'c', 'e', 't', 'y', 'o', 'f', 'b', 'h', 'd', 'x', 'i', 'w', 'q', 'k', 's', 'l', 'z', 'm', 'n', 'p'};
    char frekansAlfabesi[26] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};
    char buyuktenKucuge[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};  
    
    float frekans[26];
    
    FILE *normal = fopen("normal.txt", "r");
    FILE *sifreli = fopen("sifreli.txt", "w");
    FILE *desifreli = fopen("desifreli.txt", "w");
    int i, j, sayici = 0;

    //orjinal metni sifreli hale getirme
    char karakter = fgetc(normal);
    while(karakter != EOF){
        for(i = 0; i < 26; i++){
            if(alfabe[i] == karakter){
                karakter = sifrelemeAlfabesi[i];
                harfSayici[i] += 1;
                break;
            }
        }
        fputc(karakter, sifreli);
        sayici++;
        karakter = fgetc(normal);
    }
    fclose(normal);
    fclose(sifreli);

    //Sifreliyken dogruluk oranini bulma
    sifreli = fopen("sifreli.txt", "r");
    normal = fopen("normal.txt", "r");
    int sifreliDogru = 0;

    char sifreliKarakter = fgetc(sifreli);
    karakter = fgetc(normal);

    while(sifreliKarakter != EOF){
        if(karakter == sifreliKarakter){
            sifreliDogru++;
        }
        sifreliKarakter = fgetc(sifreli);
        karakter = fgetc(normal);
    }

    printf("Desifrelemeden once dogruluk Orani: %% %.2f\n", ((float)sifreliDogru/(float)sayici)*100);

    fclose(normal);
    fclose(sifreli);

    //harflerin metindeki frekansini hesaplama
    for(i = 0; i < 26; i++){
        frekans[i] = ((float)harfSayici[i] / (float)sayici);
    }

    //harfleri frekanslarina gore buyukten kucuge sıralama
    float gecici;
    char geciciChar;
    for(i = 0; i < 26; i++){
        for(j = i + 1; j < 26; j++){
            if(frekans[i] < frekans[j]){
                gecici = frekans[i];
                frekans[i] = frekans[j];
                frekans[j] = gecici;

                geciciChar = buyuktenKucuge[i];
                buyuktenKucuge[i] = buyuktenKucuge[j];
                buyuktenKucuge[j] = geciciChar;
            }
        }   
    }

    //metindeki hafleri Turkce'deki frekans tablosuna gore desifre etme
    sifreli = fopen("sifreli.txt", "r");

    sifreliKarakter = fgetc(sifreli);
    while(sifreliKarakter != EOF){
        for(i = 0; i < 26; i++){
            if(buyuktenKucuge[i] == sifreliKarakter){
                sifreliKarakter = frekansAlfabesi[i];
                break;
            }
        }
        fputc(sifreliKarakter, desifreli);
        sifreliKarakter = fgetc(sifreli);
    }
    fclose(desifreli);

    //Desifreliyken dogruluk oranini bulma
    desifreli = fopen("desifreli.txt", "r");
    normal = fopen("normal.txt", "r");
    int desifreliDogru = 0;

    char desifreliKarakter = fgetc(desifreli);
    karakter = fgetc(normal);

    while(desifreliKarakter != EOF){
        if(karakter == desifreliKarakter){
            desifreliDogru++;
        }
        desifreliKarakter = fgetc(desifreli);
        karakter = fgetc(normal);
    }

    printf("Desifrelemeden sonra dogruluk Orani: %% %.2f", ((float)desifreliDogru/(float)sayici)*100);

    fclose(normal);
    fclose(sifreli);
    fclose(desifreli);
}
