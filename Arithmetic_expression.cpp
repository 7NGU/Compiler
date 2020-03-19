#include "Lexical.cpp"
#include <string>
#include <iostream>

using namespace std;


void collor(char *input);
void spaceless(std::string pch);
void loc(void);
int expr(void);
int rest5(int rest5_in);
int term(void);
int unary(void);
int rest6(int rest6_in);
int factor(void);
int spe[MAX_LINE];
string att[MAX_LINE];
int x, count, cnt = 0;
std::string output;
std::string res[MAX_LINE];

void collor(char *input){
    int length = strlen(input);
    opt output;
    cnt = 0;
    count = 0;
    for(i = 0; i < length; i++){
        output = analyze(input);
        spe[cnt] = output.spe;
        att[cnt] = output.att;
        cnt++;
        //printf("<%d, %s>\n", output.spe, output.att);
    }

    for(x = 0; x < cnt; x++){
        //printf("%d ", spe[j]);
        expr();
    }

    printf("\nDerivation Process:\n");
    printf("expr\t");
    for(int j = 0; j < count; j++){
        printf("     =>");
        spaceless(res[j]);
        if(j != count - 1){
            printf("\t");
        }
    }
    memset(spe, 0, MAX_LINE);
}

void spaceless(std::string pch){
    int l = pch.length();
    for(int j = 0; j < l; j++){
        if(pch[j] == ' ' && pch[j+1] == ' '){
            pch[j+1] = '\0';
        }
        else if(pch[j] == ' ' && pch[j+1] == ')'){
            pch[j] = '\0';
        }
    }
    std::cout<<pch<<std::endl;
}


int expr(void){
    output = "expr";
    int rest5_in, term_val, expr_val, rest5_val;
    output = output.replace(output.find("expr"), 4, "term rest5");
    res[count++] = output;
    term_val = term();
    rest5_in = term_val;
    rest5_val = rest5(rest5_in);
    expr_val = rest5_val;
    printf("expr_val:%d\n", expr_val);
    return expr_val;
}

int rest5(int rest5_in){
    int rest51_in, term_val, rest5_val, rest51_val;
    if(spe[x] == 41){
        output = output.replace(output.find("rest5"), 5, "+ term rest5");
        res[count++] = output;
        x++;
        term_val = term();
        rest51_in = rest5_in + term_val;
        rest51_val = rest5(rest51_in);
        rest5_val = rest51_val;
	}
    else if(spe[x] == 42){
        output = output.replace(output.find("rest5"), 5, "- term rest5");
        res[count++] = output;
        x++;
        term_val = term();
        rest51_in = rest5_in - term_val;
        rest51_val = rest5(rest51_in);
        rest5_val = rest51_val;
	}
	else{
        output = output.replace(output.find("rest5"), 5, "");
        res[count++] = output;
        rest5_val = rest5_in;
	}
    return rest5_val;
}
int term(void){
    int rest6_in, rest6_val, term_val;
    output = output.replace(output.find("term"), 4, "unary rest6");
    res[count++] = output;
    rest6_in = unary();
    rest6_val = rest6(rest6_in);
    term_val = rest6_val;
    return term_val;
}

int unary(void){
    int unary_val, factor_val;
    output = output.replace(output.find("unary"), 5, "factor");
    res[count++] = output;
    factor_val = factor();
    unary_val = factor_val;
    return unary_val;
}

int factor(void){
    int factor_val, expr_val, loc_val, num_val;
    if(spe[x] == 100){
        output = output.replace(output.find("factor"), 6, "num");
        res[count++] = output;
        // sscanf(att[x].c_str(), "%d", num_val);//字符串转换为整型
        num_val = atoi(att[x].c_str());
        x++;
        factor_val = num_val;
    }
    else if(spe[x] == 81){
        output = output.replace(output.find("factor"), 6, "(expr)");
        res[count++] = output;
        x++;
        expr_val = expr();
        factor_val = expr_val;
        x++;
    }
    else if(spe[x] == 111){
        output = output.replace(output.find("factor"), 6, "loc");
        res[count++] = output;
        loc_val = 0;
        factor_val = loc_val;
    }
    return factor_val;
}

int rest6(int rest6_in){
    int rest61_in, unary_val, rest6_val, rest61_val;
	if(spe[x] == 43){
        output = output.replace(output.find("rest6"), 5, "* unary rest6");
        res[count++] = output;
        x++;
        unary_val = unary();
        rest61_in = rest6_in * unary_val;
        rest61_val = rest6(rest61_in);
        rest6_val = rest61_val;
	}
	else if(spe[x] == 44){
        output = output.replace(output.find("rest6"), 5, "/ unary rest6");
        res[count++] = output;
        x++;
        unary_val = unary();
        rest61_in = rest6_in / unary_val;
        rest61_val = rest6(rest61_in);
        rest6_val = rest61_val;
	}
    else{
        output = output.replace(output.find("rest6"), 5, "");
        res[count++] = output;
        rest6_val = rest6_in;
	}
    return rest6_val;
}