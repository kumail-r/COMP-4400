// By Kumail Raza
// 105225432
// 11/2/2022

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wordNumber(FILE* fp, int crossward[100][100], int rows, int cols, int x, int y, int acrossWordIndex, int acrossWordNumber, int downWordNumber){
    int downWordIndex = 0;
    while(1){
        if (x - 1 < 0 || crossward[x - 1][y] == 0){
            break;
        }
        downWordIndex += 1;
        x -= 1;
    }
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (crossward[j][i] == 1 && j + 1 < rows && crossward[j + 1][i] == 1) {
                downWordNumber++;
                if (y == i && x == j){
                    fprintf(fp, "    intersection(W%d, W%d, %d, %d),\n", acrossWordNumber, downWordNumber,acrossWordIndex,downWordIndex);
                }
                while (crossward[j][i] == 1 && j < rows) {
                    j++;
                }
            }
        }
    }
    
}

void createStep2File(char wordList[100][100], int wordCount, int lengthList[100 * 100], int lengthListLength, int downCount,int crossward[100][100], int cwRow, int cwCol){
    FILE* fp = fopen("step2.pl", "w"); // open file pointer
    if(!fp) { // check if file loaded correctly
        printf("Error in opening step2.pl");
        exit(1); // if not, exit
    }
    printf("step2.pl created successfully.\n");
    fprintf(fp, "%% By Kumail Raza %%\n%% 105225432 %%\n\n");
    fprintf(fp, "%% WORDS %%\n"); // print comment in file
    for(int i = 0; i < wordCount; i++) { // iterate through all words
        // convert word to lower case in order to work properly in prolog
        char lower[strlen(wordList[i])]; // initialize lower case string
        strcpy(lower, wordList[i]); // copy word to lower case variable
        for(int k = 0; k < strlen(lower); k++) { 
            if ((lower[k] >= 'A') && (lower[k] <= 'Z')) {
                lower[k] = lower[k] + 32; // if upper case, convert to lower
            }
        }
        // print out word facts (example: word(word, [w,o,r,d], word_length)))
        fprintf(fp, "word(%s, [", lower); 
        for(int j = 0; j < strlen(lower); j++) {
            fprintf(fp, "%c", lower[j]);
            if (j+1 < strlen(lower)){
                fprintf(fp, ",");
            }
            else{
                fprintf(fp, "], %ld).\n", strlen(wordList[i]));
            }
        }
    }
    // print out "intersection"
    fprintf(fp, "\n%% WORD INTERSECTIONS %%\ndoes_exist(0, [C|_], C).\ndoes_exist(I, [_|T], C) :-\n    Y is I-1,\n    does_exist(Y, T, C).\nis_same([X|W], [X|Z]) :- is_same(W, Z).\n\nintersection(W1, W2, Index1, Index2):-\n    word(W1, List1, Length1),\n    word(W2, List2, Length2),\n    \\+is_same(List1, List2),\n    does_exist(Index1, List1, Letter),\n    Index1 < Length1,\n    does_exist(Index2, List2, Letter),\n    Index2 < Length2.\n");
	
    fprintf(fp, "\n%% CROSSWORD DATA %%\ncrossward(");
    // fprintf(fp, "W1,W2,W3,W4,W5,W6,W7,W8,W9,W10,W11");
    for(int i = 1; i < lengthListLength + 1; i++) {
        fprintf(fp, "W%d", i);
        if (i != lengthListLength) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "):-\n");
    
    int acrossCount = lengthListLength - downCount;
    // handle intersections
    int wordCounter = 0;
    int isWord = 0;
    for (int i = 0; i < cwRow; i++) {
        isWord = 0;
        for (int j = 0; j < cwCol; j++) {
            if (crossward[i][j] == 1 && j < cwCol - 1 && crossward[i][j + 1] == 1 && isWord == 0) {
                isWord = 1;
                wordCounter += 1;
                if (i > 0 && crossward[i - 1][j] == 1) {
                    // on top
                    wordNumber(fp, crossward, cwRow, cwCol, i, j, isWord - 1, wordCounter, acrossCount);
                    
                }
                else if (i < cwRow - 1 && crossward[i + 1][j] == 1) { 
                    // below
                    wordNumber(fp, crossward, cwRow, cwCol, i, j, isWord - 1, wordCounter, acrossCount);
                }
            }
            else if (crossward[i][j] == 1 && isWord > 0) {
                isWord += 1;
                if (i > 0 && crossward[i - 1][j] == 1) {
                    // on top
                    wordNumber(fp, crossward, cwRow, cwCol, i, j, isWord - 1, wordCounter, acrossCount);
                }
                else if (i < cwRow - 1 && crossward[i + 1][j] == 1) { 
                    // below
                    wordNumber(fp, crossward, cwRow, cwCol, i, j, isWord - 1, wordCounter, acrossCount);
                }
            }
            else if (crossward[i][j] == 0 && isWord > 0) {
                isWord = 0;
            }
        }
    }
    
    // handle word statements
    for (int i = 0; i < lengthListLength; i++) {
        fprintf(fp, "    word(W%d, _, %d)%c\n", (i + 1), lengthList[i], i + 1 == lengthListLength ? '.' : ',');
    }
    
    // for file i/o
    fprintf(fp, "\ncrossward:-\n    open(\'selectedwords.txt\', write, Stream),\n    crossward(W1");
    for (int i = 1; i < lengthListLength; i++){
        fprintf(fp, ", W%d", i + 1);
    }
    fprintf(fp, "),\n");
    for (int i = 0; i < lengthListLength; i++){
        fprintf(fp, "    write(Stream, W%d),\n    write(Stream,\'\\n\'),\n", i + 1);
    }
    fprintf(fp, "    close(Stream).");    

    fclose(fp);
}

int main() {
    FILE * fp;
    fp = fopen("words.txt", "r");
    if(!fp) {
        printf("Error in opening words.txt");
        exit(1);
    }
    printf("words.txt opened successfully.\n");
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
    wordCount--;
    for (int i = 0; i < wordCount; i++){
	printf("word:%s\n",wordList[i]);
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
    printf("binpattern.txt opened successfully.\n");
    ch = getc(fp);
    int cwRow = 0;
    int cwCol = 0;
    int tempRow = 0;
    int tempCol = 0;
    while(ch != EOF) {
        if (ch == '\n') {
	    tempRow = cwRow;
	    tempCol = cwCol;
            cwCol = 0;
            cwRow += 1;
        }
        else {
            crosswardMatrix[cwRow][cwCol] = ch - 48;
            cwCol += 1;
        }
        ch = getc(fp);
    }
    cwRow = tempRow + 1;
    cwCol = tempCol;
    printf("row:%d,col:%d\n\n",cwRow,cwCol);
    int wordLengthList[100 * 100] = { }; // initialize to all 0s 
    int wordLengthListCounter = 0;
    for (int i = 0; i < cwRow; i++) {
        for (int j = 0; j < cwCol; j++) {
            if (crosswardMatrix[i][j] == 1 && j + 1 < cwCol && crosswardMatrix[i][j + 1] == 1) {
                while (crosswardMatrix[i][j] == 1 && j < cwCol) {
                    wordLengthList[wordLengthListCounter]++;
                    j++;
                }
                wordLengthListCounter++;
            }
        }
    }
    int acrossCount = wordLengthListCounter;
    for (int i = 0; i < cwCol; i++) {
        for (int j = 0; j < cwRow; j++) {
            if (crosswardMatrix[j][i] == 1 && j + 1 < cwRow && crosswardMatrix[j + 1][i] == 1) {
                while (crosswardMatrix[j][i] == 1 && j < cwRow) {
                    wordLengthList[wordLengthListCounter]++;
                    j++;
                }
                wordLengthListCounter++;
            }
        }
    }
    int downCount = wordLengthListCounter - acrossCount;
    
    createStep2File(wordList, wordCount, wordLengthList, wordLengthListCounter, downCount,crosswardMatrix, cwRow, cwCol);
    return 0;
}
