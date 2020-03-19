#include "Lexical_Analyzer.cpp"
#include <string>
#include <iostream>

void collor(char *input);
void spaceless(std::string pch);
void stmts(void);
void stmt(void);
void rest0(void);
void loc(void);
void resta(void);
void elist(void);
void rest1(void);
void bool_x(void);
void equality(void);
void rel(void);
void rest4(void);
void rop_expr(void);
void expr(void);
void rest5(void);
void term(void);
void unary(void);
void rest6(void);
void factor(void);
int spe[MAX_LINE];
int x, count, cnt = 0;
std::string output;
std::string res[MAX_LINE];

void collor(char *input){
    int length = strlen(input);
    opt output;
    cnt = 0;
    count = 0;
    printf("Production Process:\n");
    for(i = 0; i < length; i++){
        output = analyze(input);
        spe[cnt++] = output.spe;
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
    printf("stmts->stmt rest0\n");
    output = "stmt rest0";
    res[count++] = output;
    stmt();
    rest0();
}

void rest0(void){
    
    if(x >= cnt){
        printf("rest0->ℇ\n");
        output = output.replace(output.find("rest0"), 5, "");
        res[count++] = output;
    }
    else{
        printf("rest0->stmt rest0\n");
        output = output.replace(output.find("rest0"), 5, "stmt rest0");
        res[count++] = output;
        x++;
        stmt();
        rest0();
    }
}

void stmt(){
    if(spe[x] == 111){
        printf("stmt->loc = expr;\n");
        output = output.replace(output.find("stmt"), 4, "loc = expr;");
        res[count++] = output;
        loc();
        if(spe[x++] != 46){
            printf("Error! loc after need '='\n");
        }
        else{
            expr();
            if(spe[x] != 84){
                printf("Error! Need ';'\n");
            }
            else{
                x++;
            }
        }

    }
    else if(spe[x] == 17){
        printf("stmt->if(bool)stmt else stmt\n");
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
        printf("stmt->while(bool)stmt\n");
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

void loc(void){
    printf("loc->ID resta\n");
    output = output.replace(output.find("loc"), 3, "ID resta");
    res[count++] = output;
    x++;
    resta();
}

void resta(){
    if(spe[x] == 88){
        printf("resta->[elist]\n");
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
        printf("resta->ℇ\n");
        output = output.replace(output.find("resta"), 5, "");
        res[count++] = output;
    }
}

void elist(void){
    printf("elist->expr rest1\n");
    output = output.replace(output.find("elist"), 5, "expr rest1");
    res[count++] = output;
    expr();
    rest1();
}

void rest1(void){
    if(spe[x] == 90){
        printf("rest1->,expr rest1\n");
        output = output.replace(output.find("rest1"), 5, ", expr rest1");
        res[count++] = output;
        x++;
        expr();
        rest1();
    }
    else{
        printf("rest1->ℇ\n");
        output = output.replace(output.find("rest1"), 5, "");
        res[count++] = output;
    }
}


void bool_x(void){
    printf("bool->equality\n");
    output = output.replace(output.find("bool"), 4, "equality");
    res[count++] = output;
    equality();
}

void equality(void){
    printf("equality->rel rest4\n");
    output = output.replace(output.find("equality"), 8, "rel rest4");
    res[count++] = output;
    rel();
    rest4();
}

void rel(void){
    printf("rel->expr rop_expr\n");
    output = output.replace(output.find("rel"), 3, "expr rop_expr");
    res[count++] = output;
    expr();
    rop_expr();
}

void rop_expr(void){
    if(spe[x] == 49){
        printf("rop_expr-><expr\n");
        output = output.replace(output.find("rop_expr"), 8, "< expr");
        res[count++] = output;
        x++;
        expr();
    }
    else if(spe[x] == 50){
        printf("rop_expr-><=expr\n");
        output = output.replace(output.find("rop_expr"), 8, "<= expr");
        res[count++] = output;
        x++;
        expr();
    }
    else if(spe[x] == 47){
        printf("rop_expr->>expr\n");
        output = output.replace(output.find("rop_expr"), 8, "> expr");
        res[count++] = output;
        x++;
        expr();
    }
    else if(spe[x] == 48){
        printf("rop_expr->>=expr\n");
        output = output.replace(output.find("rop_expr"), 8, ">= expr");
        res[count++] = output;
        x++;
        expr();
    }
    else{
        printf("rop_expr->ℇ\n");
        output = output.replace(output.find("rop_expr"), 8, "");
        res[count++] = output;
    }   
}


void rest4(void){
    if(spe[x] == 51){
		printf("rest4->==rel rest4\n");
        output = output.replace(output.find("rest4"), 5, "== rel rest4");
        res[count++] = output;
        x++;
        rel();
        rest4();
	}
    else if(spe[x] == 52){
		printf("rest4->!=rel rest4\n");
        output = output.replace(output.find("rest4"), 5, "!= rel rest4");
        res[count++] = output;
        x++;
        rel();
        rest4();
	}
	else{
        printf("rest4->ℇ\n");
        output = output.replace(output.find("rest4"), 5, "");
        res[count++] = output;
	}
}

void expr(void){
    printf("expr->term rest5\n");
    output = output.replace(output.find("expr"), 4, "term rest5");
    res[count++] = output;
    term();
    rest5();
}

void rest5(void){
    if(spe[x] == 41){
		printf("rest5->+term rest5\n");
        output = output.replace(output.find("rest5"), 5, "+ term rest5");
        res[count++] = output;
        x++;
        term();
        rest5();
	}
    else if(spe[x] == 42){
		printf("rest5->-term rest5\n");
        output = output.replace(output.find("rest5"), 5, "- term rest5");
        res[count++] = output;
        x++;
        term();
        rest5();
	}
	else{
        printf("rest5->ℇ\n");
        output = output.replace(output.find("rest5"), 5, "");
        res[count++] = output;
	}
}

void term(void){
    printf("term->unary rest6\n");
    output = output.replace(output.find("term"), 4, "unary rest6");
    res[count++] = output;
    unary();
    rest6();
}

void unary(void){
    printf("unary->factor\n");
    output = output.replace(output.find("unary"), 5, "factor");
    res[count++] = output;
    factor();
}

void factor(void){
    if(spe[x] == 100){
        printf("factor->num\n");
        output = output.replace(output.find("factor"), 6, "num");
        res[count++] = output;
        x++;
    }
    else if(spe[x] == 81){
        printf("factor->(expr)\n");
        output = output.replace(output.find("factor"), 6, "(expr)");
        res[count++] = output;
        x++;
        expr();
        x++;
    }
    else if(spe[x] == 111){
        printf("factor->loc\n");
        output = output.replace(output.find("factor"), 6, "loc");
        res[count++] = output;
        loc();
    }
}

void rest6(void){
	if(spe[x] == 43){
		printf("rest6->*unary rest6\n");
        output = output.replace(output.find("rest6"), 5, "* unary rest6");
        res[count++] = output;
        x++;
        unary();
        rest6();
	}
	else if(spe[x] == 44){
		printf("rest6->/unary rest6\n");
        output = output.replace(output.find("rest6"), 5, "/ unary rest6");
        res[count++] = output;
        x++;
        unary();
        rest6();
	}
    else{
		printf("rest6->ℇ\n");
        output = output.replace(output.find("rest6"), 5, "");
        res[count++] = output;
	}
}