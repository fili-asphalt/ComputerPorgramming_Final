#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
------------------------------------
Process :

1. read all data (m, sigma(d))
2. convert all d to 0 or 1
    if can't, show "bad code"
3. Turn the barcode to the front
4. Decode
    if can't, show "bad code"
5. Check c and k
    if can't, show "bad c" or "bad k"
6. Show it
------------------------------------
*/

//------------------------------------
// custom defines
#define BAD_C "bad C\n"
#define BAD_K "bad K\n"
#define BAD_CODE "bad code\n"
#define FILE_NAME "testData.txt"
//------------------------------------
// custom function
void reverse(char* bin);                                  // Done by ortter
void swap_char(char* a, char* b);                         // Done by ortter
char bits6_to_char(char* bin);                            // Done by ortter
int data_to_bin(int data[], int size, char* bin);         // Done by fili
int checkCandK(char* decodeData, int size, char* anser);  // Done by fili
int char_to_scoore(char* character);                      // Done by fili
//------------------------------------

int main() {
    //------------------------------------
    // variable declare
    int dataSize;          // how many data input.
    int data[160];         // store data.
    char binary[160];      // translate data into binary
    int charSize;          // how long are anser should have.
    char anser[30];        // store anser.
    int correct_char = 1;  // check every binary can be decode to char
    int caseNumber = 1;    // current case
    FILE* inputFile = fopen(FILE_NAME, "r");  // data file
    //------------------------------------

    // while ((scanf("%d",&dataSize)) && dataSize != 0){
    while ((fscanf(inputFile, "%d", &dataSize)) && dataSize != 0) {
        // check input effectiveness, dataSize should >= 23 and combine with 6
        // data per char(except the last char)
        if (dataSize < 23 || (dataSize + 1) % 6 != 0) {
            printf("Case %d: ", caseNumber);
            printf(BAD_CODE);
        } else {
            charSize = (dataSize + 1) / 6;
            for (int i = 0; i < dataSize; i++) {
                fscanf(inputFile, "%d", data + i);
                // scanf("%d",data+i);
            }
            if (data_to_bin(data, dataSize, binary)) {
                if (*(binary + 1) == '1') {
                    reverse(binary);
                }
                // decode to char
                binary[dataSize] = '0';
                for (int i = 0; i < charSize; i++) {
                    *(anser + i) = bits6_to_char(binary + (i * 6));
                    // some one can't decode
                    if (*(anser + i) == 'n') {
                        correct_char = 0;
                        break;
                    }
                }
                // check start and end
                if (!(*(anser) == 'B' && *(anser + charSize - 1) == 'B')) {
                    correct_char = 0;
                }

                if (correct_char) {
                    // anser : "B...CKB", charSize : sizeof(anser)
                    if (checkCandK(anser + 1, charSize - 2, anser)) {
                        printf("Case %d: ", caseNumber);
                        printf("%s", anser);
                        printf("\n");
                    } else {
                        printf("Case %d: ", caseNumber);
                        printf("%s", anser);
                    }
                } else {
                    printf("Case %d: ", caseNumber);
                    printf(BAD_CODE);
                }
            } else {
                printf("Case %d: ", caseNumber);
                printf(BAD_CODE);
            }

            caseNumber++;
            correct_char = 1;
        }

        // fflush(stdin);
    }
}

// ensure barcode can be postive
void reverse(char* bin) {
    int len = strlen(bin);

    for (size_t i = 0; i < len / 2; i++) {
        swap_char(bin + i, bin + (len - 1 - i));
    }
}

// change two char
void swap_char(char* a, char* b) {
    if (*a != *b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

// change 6 data into a char
char bits6_to_char(char* bin) {
    if (bin[5] == '0') {
        bin[5] = '\0';

        /*UAa data
        if (!strcmp(bin, "00001"))
            return '0';
        else if (!strcmp(bin, "10001"))
            return '1';
        else if (!strcmp(bin, "01001"))
            return '2';
        else if (!strcmp(bin, "11000"))
            return '3';
        else if (!strcmp(bin, "00101"))
            return '4';
        else if (!strcmp(bin, "10100"))
            return '5';
        else if (!strcmp(bin, "01100"))
            return '6';
        else if (!strcmp(bin, "00011"))
            return '7';
        else if (!strcmp(bin, "10010"))
            return '8';
        else if (!strcmp(bin, "10000"))
            return '9';
        else if (!strcmp(bin, "00100"))
            return '-';
        else if (!strcmp(bin, "00110"))
            return 'B';
        else return 'n';
        */
        if (!strcmp(bin, "00011"))
            return '0';
        else if (!strcmp(bin, "01001"))
            return '1';
        else if (!strcmp(bin, "10000"))
            return '2';
        else if (!strcmp(bin, "10100"))
            return '3';
        else if (!strcmp(bin, "11000"))
            return '4';
        else if (!strcmp(bin, "00101"))
            return '5';
        else if (!strcmp(bin, "01100"))
            return '6';
        else if (!strcmp(bin, "00001"))
            return '7';
        else if (!strcmp(bin, "10010"))
            return '8';
        else if (!strcmp(bin, "10001"))
            return '9';
        else if (!strcmp(bin, "00100"))
            return '-';
        else if (!strcmp(bin, "00110"))
            return 'B';
        else
            return 'n';
    } else {
        return 'n';
    }
}

// change cahr into score for count C and K
int char_to_scoore(char* character) {
    switch (*character) {
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
        case '-':
            return 10;
            break;
        default:
            return -1;
            break;
    }
}

// check C and K
int checkCandK(char* decodeData, int size, char* anser) {
    int scoreC = 0;
    int scoreK = 0;
    int checkSize = size - 2;
    // check C
    for (int i = 0; i < checkSize; i++) {
        if (char_to_scoore(decodeData + i) < 0) {
            return 0;
        }
        scoreC +=
            ((checkSize - i - 1) % 10 + 1) * char_to_scoore(decodeData + i);
    }
    scoreC %= 11;
    //--------
    if (scoreC == char_to_scoore(decodeData + size - 2)) {
        // check K
        checkSize++;
        for (int i = 0; i < checkSize; i++) {
            scoreK +=
                ((checkSize - i - 1) % 9 + 1) * char_to_scoore(decodeData + i);
        }
        scoreK %= 11;
        //----------
        if (scoreK == char_to_scoore(decodeData + size - 1)) {
            *(decodeData + size - 2) = '\0';
            *(decodeData + size - 1) = '\0';
            sprintf(anser, "%s", decodeData);
            return 1;
        } else {
            sprintf(anser, BAD_K);
            return 0;
        }
    } else {
        sprintf(anser, BAD_C);
        return 0;
    }
}

// check data whether are effective(±5%) or not and change data into binary
int data_to_bin(int data[], int size, char* bin) {
    int max = 0;
    int min = 2000;
    float boundary;

    // find maximum and minimum
    for (int i = 0; i < size; i++) {
        if (data[i] > max) {
            max = data[i];
        } else {
            if (data[i] < min) {
                min = data[i];
            }
        }
    }
    boundary = (float)(max + min) / 2;
    min *= 2;
    // let small numbers, which should convert to 0 shift to large number and
    // find maximum and minimum again
    for (int i = 0; i < size; i++) {
        if (data[i] < boundary) {
            data[i] <<= 1;
            if (data[i] > max) {
                max = data[i];
            }
            data[i] >>= 1;
        } else {
            if (data[i] < min) {
                min = data[i];
            }
        }
    }

    // check data whether are effective(±5%) or not
    if ((95 * max) > (105 * min)) {
        return 0;
    } else {
        for (int i = 0; i < size; i++) {
            if (data[i] < boundary) {
                *(bin + i) = '0';
            } else {
                *(bin + i) = '1';
            }
        }
        *(bin + size) = '\0';
        return 1;
    }
}