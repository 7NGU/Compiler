#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 255
#define Key "KETWORD_END"

struct opt{
    char att[MAX_LINE];
    int spe;
};

opt analyze(char *input);
void pop(char *str, int x);
void push();
int isDigit(char x);
int isLetter(char x);
int isCharacter(char x);
int isSpace(char x);
char word[MAX_LINE];
int n, i;


static char Reserved[][15]={"while", "if", "else", "int", Key};
static int Reserves_num[] = {20, 17, 15, 5};
static char Character[][15] = {"+", "-", "*", "/", "%", "=", ">", "<", "!", "(", ")", ";", "{", "}", "[", "]", ",",Key};
static int Character_num[] = {41, 42, 43, 44, 45, 46, 47, 49, 55, 81, 82, 84, 86, 87, 88, 89, 90};
static char Character_double[][15] = {">=", "<=", "==", "!=", "&&", "||", "++", "--", Key};
static int Character_double_num[] = {48, 50, 51, 52, 53, 54, 56, 57};



int isSpace(char x){
    if(x == 32){
        return 1;
    }
    else{
        return 0;
    }
}

int isLetter(char x){
    if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')){
        return 1;
    }
    else{
        return 0;
    }
}

int isCharacter(char x){
    if((x >= '0' && x <= '9') || (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || x < 33 || x == 127){
        return 0;
    }
    else{
        return 1;
    }
}

int isDigit(char x){
    if(x >= '0' && x <= '9'){
        return 1;
    }
    else{
        return 0;
    }
}

void pop(char *str, int x){
    word[n++] = str[x];
}

void push(){
    word[--n] = '\0';
}

struct opt analyze(char *input){
    //puts(input);
    struct opt res;
    //unsigned long length_s = strlen(input);
    //for(int i = 0; i < length_s; i++){
    if(isLetter(input[i])){
        n = 0;
        do{
            pop(input, i);
            i++;
        }while((isLetter(input[i]) || isDigit(input[i])) && !isSpace(input[i]));
        //判断是否为保留字符
        int num = 0;
        while(strcmp(Reserved[num], Key)){
            if(!strcmp(Reserved[num], word)){
                //printf("<%d, ->\n", Reserves_num[num]);
                res.spe = Reserves_num[num];
                strcpy(res.att, "-");
                i--;
                memset(word, '\0', MAX_LINE);
                return res;
            }
            else{
                num++;
            }
        }
        {
            //printf("<111, %s>\n", word);
            res.spe = 111;
            strcpy(res.att, word);
            i--;
            memset(word, '\0', MAX_LINE);
            return res;
        }
    }
    else if(isDigit(input[i])){
        n = 0;
        do{
            pop(input, i);
            i++;
        }while(isDigit(input[i]));
        //printf("<100, %s>\n", word);
        res.spe = 100;
        strcpy(res.att, word);
        i--;
        memset(word, '\0', MAX_LINE);
        return res;
    }
    else if(isCharacter(input[i])){
        n = 0;
        int num = 0;
        pop(input, i);
        if(!isCharacter(input[i+1])){
            while(1){
                if(!strcmp(Character[num], word)){
                    //printf("<%d, ->\n", Character_num[num]);
                    res.spe = Character_num[num];
                    strcpy(res.att, "-");
                    memset(word, '\0', MAX_LINE);
                    return res;
                }
                else{
                    num++;
                }
            }
        }
        else{
            pop(input, i+1);
            while(strcmp(Character_double[num], Key)){
                if(!strcmp(Character_double[num], word)){
                    //printf("<%d, ->\n", Character_double_num[num]);
                    res.spe = Character_double_num[num];
                    strcpy(res.att, "-");
                    i++;
                    memset(word, '\0', MAX_LINE);
                    return res;
                }
                else{
                    num++;
                }
            }
            {
                push();
                num = 0;
                while(1){
                    if(!strcmp(Character[num], word)){
                        //printf("<%d, ->\n", Character_num[num]);
                        res.spe = Character_num[num];
                        strcpy(res.att, "-");
                        memset(word, '\0', MAX_LINE);
                        return res;
                    }
                    else{
                        num++;
                    }
                }
                //printf("<%d, ->\n", Character_num[num]);
            }
        }
    }
    else {
        i++;
        res = analyze(input);
    }
    return res;
    //}
}
