#include <iostream>

using namespace std;

// Os tokens da linguagem são definidos em um 'enum':
enum tokenum {
    ID=0, INT, ATRIB, LPAR, RPAR, MAIS, NUM, DIV, PEV, CHAR, LCHAVES, RCHAVES, MOD, MAIOR, MENOR, MAISMAIS, IGUALIGUAL, FOR, IF, ELSE, LETRA
};

// Define um par <token, texto>

struct token {
    tokenum token;
    string texto;
};

// Vetor de tokens (o que o analisador lexico gera)
// (sim, voce vai querer deixar ele global)
token v[1024];
int n = 0;

// funções auxiliares
bool minusculo(char c) { return 'a' <= c and c <= 'z'; }
bool maiusculo(char c) { return 'A' <= c and c<='Z';}
bool dig(char c) { return '0' <= c and c <= '9'; }

// verifica se uma string é um token ID
bool id(string s) {
    if ( !(minusculo(s[0]) or s[0]=='_') ) return false;
    for (int i=1;i<s.size();i++)
        if ( !(minusculo(s[i]) or s[i]=='_' or dig(s[i])) )
            return false;
    return true;
}	

// verifica se uma string é um token NUM
bool num(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (i == 0 && s[i] == '-') {   // verifica se o primeiro caractere for '-'
            return true;
        } else if (!dig(s[i])) {
            // Se o caractere atual não for um dígito, a string não é um número
            return false;
        }
    }
    return true;
}
// verifica se uma string é um token LETRA
bool letra(string s) {
    if (((s[0]=='\'') and (((minusculo(s[1])) or (maiusculo(s[1]))) and  (s[2]=='\'')))) return true;
    else 
    return  false;
}

int main() {

   // laco principal
    string s;
    while (cin >> s) {
        // para cada string lida, verifica qual eh seu token e o coloca no vetor de tokens.
        if (s == "=") v[n++] = {ATRIB,s};
        else if (s=="int") v[n++] = {INT,s};
        else if (s=="}") v[n++] = {RCHAVES,s};
        else if (s=="%") v[n++] = {MOD,s};
        else if (s==">") v[n++] = {MAIOR,s};
        else if (s=="<") v[n++] = {MENOR,s};
        else if (s=="++") v[n++] = {MAISMAIS,s};
        else if (s=="==") v[n++] = {IGUALIGUAL,s};
        else if (s=="if") v[n++] = {IF,s};
        else if (s=="else") v[n++] = {ELSE,s};
        else if (s=="(") v[n++] = {LPAR,s};
        else if (s==")") v[n++] = {RPAR,s};
        else if (s=="+") v[n++] = {MAIS,s};
        else if (s=="/") v[n++] = {DIV,s};
        else if (s==";") v[n++] = {PEV,s};
	else if (s=="char") v[n++] = {CHAR,s};
        else if (s=="{") v[n++] = {LCHAVES,s};
        else if (letra(s)) v[n++] = {LETRA,s};
        else if (num(s)) v[n++] = {NUM,s};
        //else if (numNeg(s)) v[n++] = {NUM,s};
        else if (id(s)) v[n++] = {ID, s};
        else {

            // um erro lexico ocorre se nenhuma string pode ser reconhecida
            cout << "Erro lexico " << s << " nao reconhecido" << endl;
            return 1;
        }
    }

    // Imprime a sequencia de tokens obtida
    for (int i = 0; i < n; i++) {
    // Nome do token através da enum
    string nomeToken;
    switch (v[i].token) {
        case ID:
            nomeToken = "ID";
            break;
        case INT:
            nomeToken = "INT";
            break;
        case LPAR:
            nomeToken = "LPAR";
            break;
        case RPAR:
            nomeToken = "RPAR";
            break;
        case LCHAVES:
            nomeToken = "LCHAVES";
            break;
        case RCHAVES:
            nomeToken = "RCHAVES";
            break;
        case ATRIB:
            nomeToken = "ATRIB";
            break;
        case NUM:
            nomeToken = "NUM";
            break;
        case PEV:
            nomeToken = "PEV";
            break;
        case CHAR:
            nomeToken = "CHAR";
            break;
        case FOR:
            nomeToken = "FOR";
            break;
        case MENOR:
            nomeToken = "MENOR";
            break;
        case MAIS:
            nomeToken = "MAIS";
            break;
        case MAISMAIS:
            nomeToken = "MAISMAIS";
            break;
        case IF:
            nomeToken = "IF";
            break;
        case MOD:
            nomeToken = "MOD";
            break;
        case IGUALIGUAL:
            nomeToken = "IGUALIGUAL";
            break;
        case LETRA:
            nomeToken = "LETRA";
            break;
        case ELSE:
            nomeToken = "ELSE";
            break;
    }

    // Imprime o nome do token
    cout << "<" << nomeToken;

    // Se for um token relevante, imprime também seu texto original
       if (v[i].token == ID || v[i].token == NUM || v[i].token == LETRA) {
            cout << ",\"" << v[i].texto << "\"";
        }
        cout << "> ";
    }
     return 0;
}
