#include <bits/stdc++.h>
#include "Lexical_Analyzer.cpp"
#include <string>

using namespace std;

struct QUA{
	string array;
	string place;
	string offset;
	string truelist;
	string falselist;
};


QUA equality();
QUA rest4(string rest4_inTruelist, string rest4_inFalselist);
QUA rel();
QUA Bool();
QUA rop_expr(string rop_expr_inPlace);
void advance();
void Error();
string makelist(string nextq);
string Emit[MAX_LINE][4];
void backpatch(string b1, string b2);
string merge(string m1, string m2);
string M();
string N();
string term();
string unary();
string rest6(string rest6_in);
string factor();
string expr();
string rest5(string rest5_in);
bool IsDigit(char ch);
int CheckKey();
int Iskey(string s);
string stmts();
string rest0(string rest0_inNextlist);
string stmt();
QUA loc();
QUA resta(string resta_inArry);
QUA elist(string elist_inArray);
QUA rest1(string rest1_inNdim, string rest1_inPlace, string rest1_inArray);
void emit(string a,string b,string c,string d);
string limit(string array, string j);
void emitOut(int i);
string newtemp();
vector<int>link[MAX_LINE];
string Res[MAX_LINE];
void out1(string str);
void out2(string str1, int length, string str2);
Word AWord;
string input, nextquad = "0";
int cnt=0, tag = 0, temp = 1, len = 0;

void out1(string str){
	Res[tag] = str;
	tag++;
	Res[tag] = Res[tag - 1];
}

void out2(string str1, int length, string str2){
	Res[tag] = Res[tag].replace(Res[tag].find(str1), length, str2);
	tag++;
	Res[tag] = Res[tag - 1];
}

string stmts(){
	out1("=>stmt rest0");
	string rest0_inNextlist, rest0_nextlist, stmt_nextlist, stmts_nextlist;
	stmt_nextlist = stmt();
	rest0_inNextlist = stmt_nextlist;
	rest0_nextlist = rest0(rest0_inNextlist);
	stmts_nextlist=rest0_nextlist;
	return stmts_nextlist;
}
string M(){
	out2("m",1," ");
	string m_quad;
	m_quad = nextquad;
	return m_quad;
}
string N(){
	out2("n",1," ");
	string n_nextlist;
	n_nextlist = makelist(nextquad);
	emit("j","-","-","0");
	return n_nextlist;
}
void backpatch(string b1, string b2){
		int k=atoi(b1.c_str());
		for(auto i:link[k]){
			Emit[i][3]=b2;
		}
}
string merge(string m1,string m2){
	int k1=atoi(m1.c_str());
	int k2=atoi(m2.c_str());
	for(auto i:link[k1]){
		link[cnt].push_back(i);
	}
	for(auto i:link[k2]){
		link[cnt].push_back(i);
	}
	stringstream lin;
	lin<<cnt;
	return lin.str();
}
string stmt(){
	QUA element;
	string m1_quad, m2_quad, n_nextlist, stmt_nextlist, stmt1_nextlist, stmt2_nextlist;
	string loc_place, expr_place, loc_offset;
	if(AWord.spe == 17){
		out2("stmt", 4, "if( bool ) m stmt n else m stmt");
		advance();
		if(AWord.spe == 58){
			advance();
			element = Bool();
			if(AWord.spe == 59){
				advance();
				m1_quad = M();
				stmt1_nextlist = stmt();
				n_nextlist = N();
				if(AWord.spe == 15){
					advance();
					m2_quad = M();
					stmt2_nextlist = stmt();
					backpatch(element.truelist, m1_quad);
					backpatch(element.falselist, m2_quad);
					stmt_nextlist = merge(stmt1_nextlist ,stmt2_nextlist);
					stmt_nextlist=merge(stmt_nextlist,n_nextlist);
				} 
				else{
					Error();
				}
			}
			else{
				Error();
			}
		}
		else{
			Error();
		}
	}
	else if(AWord.spe == 20){
		out2("stmt", 4, "while ( m bool ) m stmt");
		advance();
		if(AWord.spe == 58){
			advance();
			m1_quad = M();
			element = Bool();
			if(AWord.spe == 59){
				advance();
				m2_quad = M();
				stmt1_nextlist = stmt();
				backpatch(stmt1_nextlist, m1_quad);
				backpatch(element.truelist, m2_quad);
				stmt_nextlist = element.falselist;
				emit("j","-","-", m1_quad);
			}
			else{
				Error();
			}
		}
		else{
			Error();
		}
	}
	else{
		out2("stmt", 4, "loc = expr;");
		QUA element;
		element = loc();
		loc_place = element.place;
		loc_offset = element.offset;
		if(AWord.spe == 46){
			advance();
			expr_place = expr();
			if(AWord.spe == 999){
				advance();
				if(loc_offset == "null"){
					emit("=", expr_place , "-" , loc_place);
				}
				else{
					emit("[]=" , expr_place ,"-" , loc_place + "[" + loc_offset + "]");
				}
				stmt_nextlist = makelist(nextquad);
			}
			else{
				Error();
			}
		}
		else{
			Error();
		}
	}
	return stmt_nextlist;
}
string rest0(string rest0_inNextlist){
	string m_quad,rest01_inNextlist,stmt_nextlist,rest01_nextlist,rest0_nextlist;
	if(AWord.spe != 1000){
		out2("rest0", 5, "m stmt rest0");
		m_quad=M();
		backpatch(rest0_inNextlist,m_quad);
		stmt_nextlist=stmt();
		rest01_inNextlist=stmt_nextlist;
		rest01_nextlist=rest0(rest01_inNextlist);
		rest0_nextlist=rest01_nextlist;
	}
	else{
		out2("rest0", 5, " ");
		rest0_nextlist=rest0_inNextlist;
	}
	return rest0_nextlist;
}
QUA loc(){
	string resta_inArray, id_place, loc_place, resta_place, loc_offset;
	out2("loc", 3, "id resta");
	QUA element;
	if(AWord.spe == 111){
		id_place = AWord.att;
		resta_inArray = id_place;
		advance();
		element = resta(resta_inArray);
		loc_place = element.place;
		loc_offset = element.offset;
		return element;
	}
	else{
		Error();
	}
}
QUA resta(string resta_inArray){
	string resta_place, resta_offset, elist_array, elist_offset, elist_inArray;
	QUA element, element_1;
	if(AWord.spe == 61){
		out2("resta", 5, "[ elist ]");
		elist_inArray = resta_inArray;
		advance();
		element = elist(elist_inArray);
		elist_array = element.array;
		elist_offset = element.offset;
		resta_place = newtemp();
		emit("-" , elist_array ,"C," , resta_place);
		resta_offset = newtemp();
		emit("*" ,"w", elist_offset  ,resta_offset);
		if(AWord.spe == 62){
			advance();
		}
		else{
			Error();
		}
	}
	else{
		out2("resta", 5, " ");
		resta_place = resta_inArray;
		resta_offset = "null";
	}
	element_1.place = resta_place;
	element_1.offset = resta_offset;
	return element_1;
}
QUA elist(string elist_inArray){
	out2("elist", 5, "expr rest1");
	string rest1_inArray, rest1_inPlace, expr_place, elist_array, elist_offset;
	string rest1_inNdim;
	rest1_inArray = elist_inArray;
	rest1_inNdim = "1";
	rest1_inPlace = expr();
	QUA element;
	element = rest1(rest1_inNdim, rest1_inPlace, rest1_inArray);
	elist_array = element.array;
	elist_offset = element.offset;
	return element;
}

QUA rest1(string rest1_inNdim, string rest1_inPlace, string rest1_inArray){
	string t, m, rest11_inArray, rest11_inNdim, rest11_inNplace, expr_place, rest11_array, rest11_offset, rest1_array, rest1_offset;
	QUA element;
	if(AWord.spe == 60){
		out2("rest1", 5, ",expr rest1");
		advance();
		t = newtemp();
		int add = atoi(rest1_inNdim.c_str()) + 1;
		stringstream ss;
		ss << add;
		m = ss.str();
		string li = limit(rest1_inArray, m);
		expr_place = expr();
		emit("*" , rest1_inPlace , li ,  t);
		emit("+" , t ,  expr_place  , t);
		rest11_inArray = rest1_inArray;
		rest11_inNdim = m;
		rest11_inNplace = t;
		element = rest1(rest11_inNdim, rest11_inNplace, rest11_inArray);
		rest1_array = element.array;
		rest1_offset = element.offset;
	}
	else{
		element.array = rest1_inArray;
		element.offset = rest1_inPlace;
		out2("rest1", 5, " ");
	}
	return element;
}

QUA Bool(){
	out2("bool", 4, "equality");
	string bool_truelist, bool_falselist;
	QUA element;
	element = equality();
	bool_truelist = element.truelist;
	bool_falselist = element.falselist;
	return element;
}
QUA equality(){
	out2("equality", 8, "rel rest4");
	string rest4_inTruelist, rest4_inFalselist, equality_truelist, equality_falselist;
	QUA element_1, element_2;
	element_1 = rel();
	rest4_inTruelist = element_1.truelist;
	rest4_inFalselist = element_1.falselist;
	element_2 = rest4(rest4_inTruelist, rest4_inFalselist);
	equality_truelist = element_2.truelist;
	equality_falselist = element_2.falselist;
	return element_2;
}

QUA rest4(string rest4_inTruelist, string rest4_inFalselist){
	string rest4_truelist, rest4_falselist;
	QUA element;
	if(AWord.spe == 51){
		out2("rest4", 5, "== rel rest4");
		advance();
		rel();
	}
	else if(AWord.spe == 52){
		out2("rest4", 5, "!= rel rest4");
		advance();
		rel();
	}
	else{
		out2("rest4", 5, " ");
		element.truelist = rest4_inTruelist;
		element.falselist = rest4_inFalselist;
	}
	return element;
}

QUA rel(){
	string rop_expr_inPlace, expr_place, rel_truelist, rel_falselist;
	out2("rel", 3, "expr rop_expr");
	QUA element;
	expr_place = expr();
	rop_expr_inPlace = expr_place;
	element = rop_expr(rop_expr_inPlace);
	rel_truelist = element.truelist;
	rel_falselist = element.falselist;
	return element;
}

QUA rop_expr(string rop_expr_inPlace){
	string rop_expr_truelist, rop_expr_falselist, expr_place;
	QUA element;
	if(AWord.spe == 50){
		out2("rop_expr", 8, "<= expr");
		advance();
		rop_expr_truelist = makelist(nextquad);
		int quad = atoi(nextquad.c_str()) + 1;
		stringstream ss;
		ss << quad;
		rop_expr_falselist = makelist(ss.str());
		expr_place = expr();
		emit("j<=" , rop_expr_inPlace ,  expr_place , "-");
		emit("j","-","-","-");
	}
	else if(AWord.spe == 49){
		out2("rop_expr", 8, "< expr");
		advance();
		rop_expr_truelist = makelist(nextquad);
		int quad = atoi(nextquad.c_str()) + 1;
		stringstream ss;
		ss << quad;
		rop_expr_falselist = makelist(ss.str());
		expr_place = expr();
		emit("j<" , rop_expr_inPlace ,expr_place, "-");
		emit("j","-","-","-");
	}
	else if(AWord.spe == 48){
		out2("rop_expr", 8, ">= expr");
		advance();
		rop_expr_truelist = makelist(nextquad);
		int quad = atoi(nextquad.c_str()) + 1;
		stringstream ss;
		ss << quad;
		rop_expr_falselist = makelist(ss.str());
		expr_place = expr();
		emit("j>=" , rop_expr_inPlace , expr_place , "-");
		emit("j","-","-","-");
	}
	else if(AWord.spe == 47){
		out2("rop_expr", 8, "> expr");
		advance();
		rop_expr_truelist = makelist(nextquad);
		int quad = atoi(nextquad.c_str()) + 1;
		stringstream ss;
		ss << quad;
		rop_expr_falselist = makelist(ss.str());
		expr_place = expr();
		emit("j>" , rop_expr_inPlace , expr_place , "-");
		emit("j","-","-","-");
	}
	else{
		out2("rop_expr", 8, "");
		rop_expr_truelist = makelist(nextquad);
		int quad = atoi(nextquad.c_str()) + 1;
		stringstream ss;
		ss << quad;
		rop_expr_falselist = makelist(ss.str());
		emit("jnz" , rop_expr_inPlace ,"-","-");
		emit("j","-","-","-");
	}
	element.truelist = rop_expr_truelist;
	element.falselist = rop_expr_falselist;
	return element;
}

string expr(){
	out2("expr", 4, "term rest5");
	string term_place, rest5_in, expr_place, rest5_place;
	term_place = term();
	rest5_in = term_place;
	rest5_place = rest5(rest5_in);
	expr_place = rest5_place;
	return expr_place;
}
string term(){
	string rest6_in, unary_place, term_place, rest6_place;
	out2("term", 4, "unary rest6");
	unary_place = unary();
	rest6_in = unary_place;
	rest6_place = rest6(rest6_in);
	term_place = rest6_place;
	return term_place;
}
string unary(){
	out2("unary", 5, "factor");
	string unary_place, factor_place;
	factor_place = factor();
	unary_place = factor_place;
	return unary_place;
}
string rest5(string rest5_in){
	string rest51_in, term_place, rest5_place, rest51_place;
	if(AWord.spe == 41){
		out2("rest5", 5, "+ term rest5");
		advance();
		term_place = term();
		rest51_in = newtemp();
		emit("+" , rest5_in , term_place, rest51_in);
		rest51_place = rest5(rest51_in);
		rest5_place = rest51_place;
	}
	else if(AWord.spe == 42){
		out2("rest5", 5, "- term rest5");
		advance();
		term_place = term();
		rest51_in = newtemp();
		emit("-" , rest5_in , term_place , rest51_in);
		rest51_place = rest5(rest51_in);
		rest5_place = rest51_place;
	}
	else{
		out2("rest5", 5, " ");
		rest5_place = rest5_in;
	}
	return rest5_place;
}
string rest6(string rest6_in){
	string rest61_in, rest61_place, rest6_place, unary_place;
	if(AWord.spe == 43){
		out2("rest6", 5, "* unary rest6");
		advance();
		unary_place = unary();
		rest61_in = newtemp();
		emit("*," , rest6_in , unary_place , rest61_in);
		rest6_place = rest6(rest61_in);
	}
	else if(AWord.spe == 44){
		out2("rest6", 5, "/ unary rest6");
		advance();
		unary_place = unary();
		rest61_in = newtemp();
		emit("/" , rest6_in , unary_place , rest61_in);
		rest6_place = rest6(rest61_in);
	}
	else{
		out2("rest6", 5, " ");
		rest6_place = rest6_in;
	}
	return rest6_place;
}
string factor(){
	string expr_place, factor_place, loc_place, loc_offset;
	QUA element;
	if(AWord.spe == 100){
		out2("factor", 6, "num");
		factor_place = AWord.att;
		advance();
	}
	else if(AWord.spe == 58){
		out2("factor", 6, "( expr )");
		advance();
		expr_place = expr();
		if(AWord.spe == 59){
			factor_place = expr_place;
			advance();
		}
	}
	else{
		out2("factor", 6, "loc");
		element = loc();
		loc_place = element.place;
		loc_offset = element.offset;
		if(loc_offset == "null")
			factor_place = loc_place;
		else{
			factor_place = newtemp();
			emit("=[]" , loc_place + "[" + loc_offset + "]" , "-" , factor_place);
		}
	}
	return factor_place;
}

void advance(){
	Word word = LEX();
	AWord.att = word.att;
	AWord.spe = word.spe;
}

void Error(){
	cout << "Error! Please input again." << endl;
}

void emit(string a,string b,string c,string d){
	int q=atoi(nextquad.c_str());
	Emit[q][0]=a;
	Emit[q][1]=b;
	Emit[q][2]=c;
	Emit[q][3]=d;
	q=q+1;
	stringstream ss;
	ss << q;
	nextquad = ss.str();
}
string newtemp(){
	stringstream ss;
	string s;
	ss << temp;
	s = "t" + ss.str();
	temp++;
	return s;
}
string limit(string array, string j){
	return "n" + j;
}
string makelist(string i){
	int a=atoi(i.c_str());
	link[cnt].push_back(a);
	stringstream lin;
	lin<<cnt;
	++cnt;
	return lin.str();
}
void emitOut(int n)
{
    cout<<Emit[n][0]<<", "<<Emit[n][1]<<", "<<Emit[n][2]<<", "<<Emit[n][3]<<" \n";
}

