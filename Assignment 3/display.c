#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char solvedWords[100][100]; // array of words from selectedworks.txt
    FILE *fp;
    fp = fopen("selectedwords.txt", "r");
    if(!fp) { // exit if selectedwords.txt can't be opened
        printf("Error opening selectedwords.txt");
        exit(1);
    }
    char ch = getc(fp);
    int solvedMax = 0; // number of words in solvedWords
    
    while(ch != EOF) {
        if(ch == 'W') {
            ch = getc(fp);
            int num = 0;
            while(ch != ' ') {
                num = num * 10;
                num = num + (ch - 48);
                ch = getc(fp);
            }
            solvedMax = num > solvedMax ? num : solvedMax;
            ch = getc(fp);
            ch = getc(fp);
            ch = getc(fp);
            char word[100] = {'\0'};
            while(ch != ',' && ch != EOF) {
                strncat(word, &ch, 1);
                ch = getc(fp);
            }
            strcpy(solvedWords[num - 1], word); 
        }
        ch = getc(fp);
    }
    fclose(fp);
    
    fp = fopen("binpattern.txt", "r");
    if(!fp) { // exit if binpattern.txt can't be opened
        printf("Error opening binpattern.txt");
        exit(1);
    }
    ch = getc(fp);
    char crossward[100][100] = {'\0'};
    int cwRow = 0;
    int cwCol = 0;
    while (ch != EOF) {
        if (ch != '\n'){
            crossward[cwRow][cwCol] = ch;
            cwCol++;
        }
        else{
            cwCol = 0;
            cwRow++;
        }
        ch = getc(fp);
    }
    cwRow++;
    printf("col:%d, row:%d\n", cwCol, cwRow);
    int wordCounter = 0;
    for (int i = 0; i < cwRow; i++){
        for (int j = 0; j < cwCol; j++){
            if (crossward[i][j] == '1' && j + 1 < cwCol && crossward[i][j + 1] == '1'){
                int tempWordLength = 0;
                while (crossward[i][j] != '0' && j < cwCol){
                    crossward[i][j] = solvedWords[wordCounter][tempWordLength];
                    printf("%c", crossward[i][j]);
                    tempWordLength++;
                    j++;
                }
                wordCounter++;
            }
            printf("%c", crossward[i][j]);
        }
        printf("\n");
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}
