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
    char tmpWord[100] = {'\0'};
    while(ch != EOF) {
        if (ch == '\n') {
            strncat(solvedWords[solvedMax],"\0",1);
	    solvedMax++;
	}
	else if (ch >= 'a' && ch <= 'z'){
	    strncat(solvedWords[solvedMax],&ch,1);
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
    int tmpRow = 0;
    int tmpCol = 0;
    while (ch != EOF) {
        if (ch != '\n'){
            crossward[cwRow][cwCol] = ch;
            cwCol++;
        }
        else{
	    tmpRow = cwRow;
	    tmpCol = cwCol;
            cwCol = 0;
            cwRow++;
        }
        ch = getc(fp);
    }
    cwCol = tmpCol;
    cwRow = tmpRow;
    cwRow++;
    char crosswardCopy[100][100] = {'\0'}; // create copy to be used for downs
    for (int i = 0; i < cwRow; i++){
        strcpy(crosswardCopy[i], crossward[i]);
    }
    int wordCounter = 0;
    for (int i = 0; i < cwRow; i++) { // place all acrosses into crossward
        for (int j = 0; j < cwCol; j++) {
            if (crossward[i][j] == '1' && j + 1 < cwCol && crossward[i][j + 1] == '1') {
                int tempWordLength = 0;
                while (crossward[i][j] != '0' && j < cwCol) {
                    crossward[i][j] = solvedWords[wordCounter][tempWordLength];
                    tempWordLength++;
                    j++;
                }
                wordCounter++;
            }
        }
    }
    
    for (int i = 0; i < cwCol; i++) { // place downs into crosswardCopy
        for (int j = 0; j < cwRow; j++) {
            if (crosswardCopy[j][i] == '1' && j + 1 < cwRow && crosswardCopy[j + 1][i] == '1') {
                int tempWordLength = 0;
                while (crosswardCopy[j][i] != '0' && j < cwRow) {
                    crosswardCopy[j][i] = solvedWords[wordCounter][tempWordLength];
                    tempWordLength++;
                    j++;
                }
                wordCounter++;
            }
        }
    }
    
    for (int i = 0; i < cwRow; i++) { // get filled in array and print
        for (int j = 0; j < cwCol; j++) {
            if (crossward[i][j] == '1') {
                crossward[i][j] = crosswardCopy[i][j];
            }
        }
    }
    // initialize output array with empty spaces
    char output[100 * 2 + 1][100 * 4 + 1] = {[0 ... (100 * 2)][0 ... (100 * 4)] = ' '};
    for (int i = 0; i < cwRow; i++) {
        for (int j = 0; j < cwCol; j++) {
            if (crossward[i][j] != '0') {
                int letterXIndex = j * 4 + 2;
                int letterYIndex = i * 2 + 1;
                output[letterYIndex][letterXIndex] = crossward[i][j];
                output[letterYIndex][letterXIndex - 2] = '|';
                output[letterYIndex][letterXIndex + 2] = '|';
                output[letterYIndex - 1][letterXIndex] = '-';
                output[letterYIndex - 1][letterXIndex - 1] = '-';
                output[letterYIndex - 1][letterXIndex - 2] = '-';
                output[letterYIndex - 1][letterXIndex + 1] = '-';
                output[letterYIndex - 1][letterXIndex + 2] = '-';
                output[letterYIndex + 1][letterXIndex] = '-';
                output[letterYIndex + 1][letterXIndex + 1] = '-';
                output[letterYIndex + 1][letterXIndex + 2] = '-';
                output[letterYIndex + 1][letterXIndex - 1] = '-';
                output[letterYIndex + 1][letterXIndex - 2] = '-';
            }
        }
    }
    
    for (int i = 0; i < cwRow * 2 + 1; i++) { 
        for (int j = 0; j < cwCol * 4 + 1; j++) {
            printf("%c", output[i][j]);
        }
        printf("\n");
    }
    return 0;
}
