#include<bits/stdc++.h>
#define _KEY_WORD_END "key word end"
#define INF 10000
#define MAX_LINE 255
using namespace std;
struct Word {
	int  spe;
	string att;
} id[MAX_LINE],ConstNum[MAX_LINE];
int m=0,n=0;
char ch=' ';
char InputCode[MAX_LINE];
char strToken[MAX_LINE]="";
int  next_input=0;
int  next_token=0;

void GetChar();
void GetBC();
void Concat();
bool IsLetter();
bool IsDigit();
int  Reserve();
void Retract();
void InsertId();
void InsertConst();
void output();
char* key[]= {"while","if","int","else",_KEY_WORD_END};
int  key_value[]= {20,17,5,15,INF};
int ID=111;
int Const=100;
void StrTOChar(string str);
void Trans(Word *w,int value,char a[]="-");
Word LEX();

// int main() {
// 	Word  word ;
// 	fstream f("code.txt");
// 	string line;
// 	while(getline(f,line)) {
// 		next_input=0;
// 		int tag=1;
// 		StrTOChar(line);
// 		printf("Your code:%s\n",InputCode);
// 		while(next_input<line.length()) {
// 			word = LEX();
// 		//	tag=word.spe;
// 		//	if(tag!=999)
// 				cout<<"<"<<word.spe<<","<<word.att<<">"<<endl;
// 		}
// 	}
// }

Word LEX() {
	Word CodeWord ;
	GetChar();
	GetBC();
	next_token=0;
	if(IsLetter()) {
		//cout<<"Letter"<<endl;
		while(IsLetter() || IsDigit()) {
			Concat();
			GetChar();
		}
		Retract();
		int code=Reserve();
		if(code==0) {
			//cout<<0<<endl;
			Trans(&CodeWord,ID,strToken);
			InsertId();
		} else {
			Trans(&CodeWord,code,"-");
		}
		return CodeWord;
	} else if(IsDigit()) {
		while(IsDigit()) {
			Concat();
			GetChar();
		}
		Retract();
		Trans(&CodeWord,Const,strToken);
		InsertConst();
		return CodeWord;
	} else if(ch =='=') {
		GetChar();
		if(ch =='=') {
			Trans(&CodeWord,51,"-");
			return CodeWord;
		}
		Retract();
		Trans(&CodeWord,46,"-");
		return CodeWord;
	} else if(ch=='+') {
		GetChar();
		if(ch=='+') {
			Trans(&CodeWord,56,"-");
			return CodeWord;
		}
		Retract();
		Trans(&CodeWord,41,"-");
		return CodeWord;
	} else if(ch=='-') {
		GetChar();
		if(ch=='-') {
			Trans(&CodeWord,57,"-");
			return CodeWord;
		}
		Retract();
		Trans(&CodeWord,42,"-");
		return CodeWord;
	} else if(ch=='*') {
		Trans(&CodeWord,43,"-");
		return CodeWord;
	} else if(ch=='/') {
		Trans(&CodeWord,44,"-");
		return CodeWord;
	} else if(ch=='(') {
		Trans(&CodeWord,58,"-");
		return CodeWord;
	} else if(ch==')') {
		Trans(&CodeWord,59,"-");
		return CodeWord;
	} else if(ch==',') {
		Trans(&CodeWord,60,"-");
		return CodeWord;
	} else if(ch=='[') {
		Trans(&CodeWord,61,"-");
		return CodeWord;
	} else if(ch==']') {
		Trans(&CodeWord,62,"-");
		return CodeWord;
	} else if(ch=='#') {
		Trans(&CodeWord,1000,"-");
		return CodeWord;
	} 
	else if(ch=='%') {
		Trans(&CodeWord,45,"-");
		return CodeWord;
	} else if(ch=='>') {
		GetChar();
		if(ch=='=') {
			Trans(&CodeWord,48,"-");
			return CodeWord;
		}
		Retract();
		Trans(&CodeWord,47,"-");
		return CodeWord;
	} else if(ch=='<') {
		GetChar();
		if(ch=='=') {
			Trans(&CodeWord,50,"-");
			return CodeWord;
		}
		Retract();
		Trans(&CodeWord,49,"-");
		return CodeWord;
	} else if(ch=='!') {
		GetChar();
		if(ch=='=') {
			Trans(&CodeWord,52,"-");
			return CodeWord;
		}
		Retract();
		Trans(&CodeWord,55,"-");
		return CodeWord;
	} else if(ch=='&') {
		GetChar();
		if(ch=='&') {
			Trans(&CodeWord,53,"-");
			return CodeWord;
		}
	} else if(ch=='|') {
		GetChar();
		if(ch=='|') {
			Trans(&CodeWord,54,"-");
			return CodeWord;
		}
	} else if(ch==';') {
		Trans(&CodeWord,999,"-");
		return CodeWord;
	} else {
		cout<<"Error"<<endl;
	}
}
void GetChar() {
	ch = InputCode[next_input];
	next_input++;
}
void GetBC() {
	while(ch==' ') {
		GetChar();
	}
}
void Concat() {
	strToken[next_token] = ch;
	next_token++;
	strToken[next_token]='\0';
}
void Retract() {
	next_input--;
	ch=' ';
}
int Reserve() {
	int i=0;
	while(strcmp(key[i],_KEY_WORD_END)) {
		if(!strcmp(key[i],strToken)) {
			return key_value[i];
		}
		i++;
	}
	return 0;
}
bool IsLetter() {
	if(ch>='a'&&ch<='z' || ch>='A'&&ch<='Z')
		return true;
	return false;
}
bool IsDigit() {
	if(ch>='0'&&ch<='9')
		return true;
	return false;
}
void Trans(Word *w,int value,char a[]) {
	 //cout<<a<<endl;
	w->spe=value;
	string s=a;
	//cout<<s<<endl;
	//cout<<1<<endl;
	w->att=s;
}
void StrTOChar(string str) {
	int length = str.length();
	//cout<<length<<endl;
	for(int i=0; i<length; i++) {
		InputCode[i]=str[i];
	}
	InputCode[length]='\0';
}
void InsertId() {
	id[m].spe=ID;
	id[m].att=*strToken;
	m++;
}
void InsertConst() {
	ConstNum[n].spe=Const;
	ConstNum[n].att=*strToken;
	n++;
}
void output() {
	cout<<"-------------------------"<<endl;
	for(int i=0; i<m; i++) {
		cout<<"<"<<id[i].spe<<","<<id[i].att<<">"<<endl;
	}
	cout<<"-------------------------"<<endl;
	for(int i=0; i<n; i++) {
		cout<<"<"<<ConstNum[i].spe<<","<<ConstNum[i].att<<">"<<endl;
	}
}
