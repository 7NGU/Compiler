#include "Lexical_Analyzer.cpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

void collor(char *input);
void spaceless(std::string pch);
void stmts(void);
void stmt(void);
void rest0(void);
string loc(void);
string resta(string resta_inArray);
void elist(void);
void rest1(void);
void bool_x(void);
void equality(void);
void rel(void);
void rest4(void);
void rop_expr(void);
string expr(void);
string rest5(string rest5_in);
string term(void);
string unary(void);
string rest6(string rest6_in);
string factor(void);
void emit(string out);
string newtemp();
int spe[MAX_LINE];
std::string att[MAX_LINE];
int x, count, cnt = 0;
std::string output;
string out;
string temp = "1";
std::string res[MAX_LINE];

void emit(string out){
    cout<<out<<endl;
}

string newtemp(){
    string s ="T"+temp;
    int t=atoi(temp.c_str())+1;
    stringstream sx;
    sx<<t;
    temp=sx.str();
    return s;
}

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
        stmts();
    }

    printf("\nDerivation Process:\n");
    printf("stmts\t");
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

void stmts(void){
    output = "stmt rest0";
    res[count++] = output;
    stmt();
    rest0();
}

void rest0(void){
    
    if(x >= cnt){
        output = output.replace(output.find("rest0"), 5, "");
        res[count++] = output;
    }
    else{
        output = output.replace(output.find("rest0"), 5, "stmt rest0");
        res[count++] = output;
        x++;
        stmt();
        rest0();
    }
}

void stmt(){
    string loc_place, expr_place;
    if(spe[x] == 111){
        output = output.replace(output.find("stmt"), 4, "loc = expr;");
        res[count++] = output;
        loc_place = loc();
        if(spe[x++] != 46){
            printf("Error! loc after need '='\n");
        }
        else{
            expr_place = expr();
            if(spe[x] != 84){
                printf("Error! Need ';'\n");
            }
            else{
                out = loc_place+"="+expr_place;
                emit(out);
                x++;
            }
        }

    }
    else if(spe[x] == 17){
        output = output.replace(output.find("stmt"), 4, "if(bool)stmt else stmt");
        res[count++] = output;
        if(spe[++x] != 81){
            printf("Error! if don't have '('\n");
        }
        else{
            x++;
            bool_x();
            if(spe[x++] != 82){
                printf("Error! if don't have')\n");
            }
            else{
                stmt();
                if(spe[x] != 15){
                    printf("Error! if after need else\n");
                }
                else{
                    x++;
                    stmt();
                }
            }
        }
    }
    else if(spe[x] == 20){
        output = output.replace(output.find("stmt"), 4, "while(bool)stmt");
        res[count++] = output;
        if(spe[++x] != 81){
            printf("Error! while don't have '('\n");
        }
        else{
            x++;
            bool_x();
            if(spe[x++] != 82){
                printf("Error! while don't have')'\n");
            }
            else{
                stmt();
            }
        }
    }
    else{
        printf("Error! Wrong assignment\n");
        x = cnt;
    }
}

string loc(void){
    string resta_inArray, id_place, loc_place, resta_place;
    output = output.replace(output.find("loc"), 3, "ID resta");
    res[count++] = output;
    id_place = att[x];
    resta_inArray = id_place;
    x++;
    resta_place = resta(resta_inArray);
    loc_place = resta_place;
    return loc_place;
}
string resta(string resta_inArray){
    string resta_place;
    if(spe[x] == 88){
        output = output.replace(output.find("resta"), 5, "[elist]");
        res[count++] = output;
        if(spe[x] != 88){
            printf("Error! Don't have '['\n");
        }
        else{
            x++;
            elist();
            if(spe[x] != 89){
                printf("Error! Don't have ']'\n");
            }
            else{
                x++;
            }
        }
    }
    else{
        output = output.replace(output.find("resta"), 5, "");
        res[count++] = output;
        resta_place = resta_inArray;
    }
    return resta_place;
}

void elist(void){
    output = output.replace(output.find("elist"), 5, "expr rest1");
    res[count++] = output;
    expr();
    rest1();
}

void rest1(void){
    if(spe[x] == 90){
        output = output.replace(output.find("rest1"), 5, ", expr rest1");
        res[count++] = output;
        x++;
        expr();
        rest1();
    }
    else{
        output = output.replace(output.find("rest1"), 5, "");
        res[count++] = output;
    }
}


void bool_x(void){
    output = output.replace(output.find("bool"), 4, "equality");
    res[count++] = output;
    equality();
}

void equality(void){
    output = output.replace(output.find("equality"), 8, "rel rest4");
    res[count++] = output;
    rel();
    rest4();
}

void rel(void){
    output = output.replace(output.find("rel"), 3, "expr rop_expr");
    res[count++] = output;
    expr();
    rop_expr();
}

void rop_expr(void){
    if(spe[x] == 49){
        output = output.replace(output.find("rop_expr"), 8, "< expr");
        res[count++] = output;
        x++;
        expr();
    }
    else if(spe[x] == 50){
        output = output.replace(output.find("rop_expr"), 8, "<= expr");
        res[count++] = output;
        x++;
        expr();
    }
    else if(spe[x] == 47){
        output = output.replace(output.find("rop_expr"), 8, "> expr");
        res[count++] = output;
        x++;
        expr();
    }
    else if(spe[x] == 48){
        output = output.replace(output.find("rop_expr"), 8, ">= expr");
        res[count++] = output;
        x++;
        expr();
    }
    else{
        output = output.replace(output.find("rop_expr"), 8, "");
        res[count++] = output;
    }   
}


void rest4(void){
    if(spe[x] == 51){
        output = output.replace(output.find("rest4"), 5, "== rel rest4");
        res[count++] = output;
        x++;
        rel();
        rest4();
	}
    else if(spe[x] == 52){
        output = output.replace(output.find("rest4"), 5, "!= rel rest4");
        res[count++] = output;
        x++;
        rel();
        rest4();
	}
	else{
        output = output.replace(output.find("rest4"), 5, "");
        res[count++] = output;
	}
}

string expr(void){
    string rest5_in, term_place, expr_place, rest5_place;
    output = output.replace(output.find("expr"), 4, "term rest5");
    res[count++] = output;
    term_place = term();
    rest5_in = term_place;
    rest5_place = rest5(rest5_in);
    expr_place = rest5_place;
    return expr_place;
}

string rest5(string rest5_in){
    string rest51_in, rest51_place, rest5_place, term_place;
    if(spe[x] == 41){
        output = output.replace(output.find("rest5"), 5, "+ term rest5");
        res[count++] = output;
        x++;
        term_place = term();
        rest51_in = newtemp();
        out = rest51_in + "=" + rest5_in + "+" + term_place;
        emit(out);
        rest51_place = rest5(rest51_in);
        rest5_place = rest51_place;
	}
    else if(spe[x] == 42){
        output = output.replace(output.find("rest5"), 5, "- term rest5");
        res[count++] = output;
        x++;
        term_place = term();
        rest51_in = newtemp();
        out = rest51_in + "=" + rest5_in + "-" + term_place;
        emit(out);
        rest51_place = rest5(rest51_in);
        rest5_place = rest51_place;
	}
	else{
        output = output.replace(output.find("rest5"), 5, "");
        res[count++] = output;
        rest5_place = rest5_in;
	}
    return rest5_place;
}

string term(void){
    string unary_place, rest6_in, term_place, rest6_place;
    output = output.replace(output.find("term"), 4, "unary rest6");
    res[count++] = output;
    unary_place = unary();
    rest6_in = unary_place;
    rest6_place = rest6(rest6_in);
    term_place = rest6_place;
    return term_place;
}

string unary(void){
    string unary_place, factor_place;
    output = output.replace(output.find("unary"), 5, "factor");
    res[count++] = output;
    factor_place = factor();
    unary_place = factor_place;
    return unary_place;
}

string factor(void){
    string factor_place, expr_place, loc_place, num_value;
    if(spe[x] == 100){
        output = output.replace(output.find("factor"), 6, "num");
        res[count++] = output;
        num_value = att[x];
        x++;
        factor_place = num_value;
    }
    else if(spe[x] == 81){
        output = output.replace(output.find("factor"), 6, "(expr)");
        res[count++] = output;
        x++;
        expr_place = expr();
        factor_place = expr_place;
        x++;
    }
    else if(spe[x] == 111){
        output = output.replace(output.find("factor"), 6, "loc");
        res[count++] = output;
        loc_place = loc();
        factor_place = loc_place;
    }
    return factor_place;
}

string rest6(string rest6_in){
    string rest61_in, rest61_place, rest6_place, unary_place;
	if(spe[x] == 43){
        output = output.replace(output.find("rest6"), 5, "* unary rest6");
        res[count++] = output;
        x++;
        rest61_in = newtemp();
        unary_place = unary();
        out = rest61_in + "=" + rest6_in + "*" + unary_place;
        emit(out);
        rest61_place = rest6(rest61_in);
        rest6_place = rest61_place;
	}
	else if(spe[x] == 44){
        output = output.replace(output.find("rest6"), 5, "/ unary rest6");
        res[count++] = output;
        x++;
        rest61_in = newtemp();
        unary_place = unary();
        out = rest61_in + "=" + rest6_in + "/" + unary_place;
        emit(out);
        rest61_place = rest6(rest61_in);
        rest6_place = rest61_place;
	}
    else{
        output = output.replace(output.find("rest6"), 5, "");
        res[count++] = output;
        rest6_place = rest6_in;
	}
    return rest6_place;
}