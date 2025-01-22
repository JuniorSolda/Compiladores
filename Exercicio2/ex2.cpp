/*

GRAMATICA JÁ FATORADA:

   A → i = E$
   E → DE’
   E’→ eDE’ | ε
   D→ LD`
   D’→oLD’  | ε
   L → i | nF | (E)
   F → i | (E)


*/

#include <iostream>

using namespace std;

string s;
int spos=0;

void match(char c) {
    if (c=='\0') { return; }

    if (spos == s.size() or s[spos] != c) {
        cout << "Erro sintatico" << endl;
        exit(1);
    }
    spos++;
}

void A(), E(), EL(), D(), DL(), L(), F();

void A() {
    match('i');
    match('=');
    E();
    match('$');
}

void E() {
    D();
    EL();
}

void EL() {
    if (s[spos]=='e') {
        match('e');
        D();
        EL();
    } else
        match('\0');
}

void D() {
    L();
    DL();
}

void DL() {
    if (s[spos]=='o') {
        match('o');
        L();
        DL();
    } else
        match('\0');
}

void L() {
    if (s[spos]=='i') {
        match('i');
    } else if(s[spos]=='n'){
    	match('n');
    	F();
    } else if(s[spos]=='('){
    	match('(');
    	E();
    	if(s[spos]==')'){
    		match(')');
    	}
    }
}

void F(){
	 if (s[spos]=='i') {
        match('i');
    } else if(s[spos]=='('){
    	match('(');
    	E();
    	if(s[spos]==')'){
    		match(')');
    	}
    }
}
int main() {

    cin >> s;
    s = s + "$";
    A();
    cout << "entrada valida" << endl;

    return 0;
}
