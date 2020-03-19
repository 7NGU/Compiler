#include <bits/stdc++.h>
#include "Lexical_Analyzer.cpp"
#include "Senmantic_Analyzer.cpp"
#include <string>

using namespace std;

int main(){
	while(getline(cin, input)){
		input += '#';
		next_input = 0;
		StrTOChar(input);
		advance();
		stmts();
		printf("Quaternion:\n");
		int q=atoi(nextquad.c_str());
		for(int i = 0; i < q; ++i){
			printf("%d: ", i);
			emitOut(i);
		}
		printf("\nDerivation Process:\n");
		for (int j = 0; j < tag; j++){
			int len = Res[j].length();
			for (int i = 0; i < len;){
				if(Res[j][i] != ' '){
					if(i == 0 && j == 0){
						cout << "stmts " << Res[j][i];
					}
					else if(i == 0)
						cout << "      " << Res[j][i];
					else
						cout << Res[j][i];
					i++;
				}
				else{
					cout << Res[j][i];
					i++;
					while (Res[j][i] == ' '){
						i++;
					}
				}
			}
			printf("\n");
		}
		printf("\n");
	}
}

//a=6/b+5*c-d;
//x=A[i]; x=A[i,j];
//if(c) x=y+z; else x=y-z;
//while(a<b) if(c) x=y+Z; else x=y-z; a=y;