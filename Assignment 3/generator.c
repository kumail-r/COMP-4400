#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE * fp;
    fp = fopen("words.txt", "r");
    if(!fp) {
        printf("Error in opening the file..!!");
        exit(1);
    }
    char ch = getc(fp);
    char word[100];
    memset(word,0,strlen(word)); 
    char wordList[100][100];
    int wordCount = 0;
    while(ch != EOF) {
        if (ch == '\n') {
            strcat(wordList[wordCount], word);
            wordCount = wordCount + 1;
            memset(word,0,strlen(word));
        }
        else{
            strncat(word, &ch, 1);
        }
        ch = getc(fp);
        if (ch == EOF){
            strcat(wordList[wordCount], word);
            wordCount = wordCount + 1;
            memset(word, 0, strlen(word));
        }
    }
    fclose(fp);
    int crosswardMatrix[100][100];
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            crosswardMatrix[i][j] = -1;
        }
    }
    fp = fopen("binpattern.txt", "r");
    if(!fp) {
        printf("Error in opening the file..!!");
        exit(1);
    }
    ch = getc(fp);
    int cwRow = 0;
    int cwCol = 0;
    while(ch != EOF) {
        if (ch == '\n') {
            cwCol = 0;
            cwRow += 1;
        }
        else {
            crosswardMatrix[cwRow][cwCol] = ch - 48;
            cwCol += 1;
        }
        ch = getc(fp);
    }
    for (int i = 0; i < cwRow + 1; i++){
        for (int j = 0; j < cwCol; j++){
            printf("%d", crosswardMatrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
