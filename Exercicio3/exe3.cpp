/*
(1) S' -> E$
(2) S -> +
(3) E -> ESS
(4) E -> n

*/
/*  
 O automato LR(0) resulta na seguinte tabela
 
  | acao  |   goto    |
  +------------+------+
  | + | n | $ | E | S |
  +---+---+---+---+---+
0 |   |S2 |  | 1 |    |
1 |  |s2 |acc| 3 |    |
2 |r4|r4 |r4 |   |    |
3 |s4|s2 |   |   | 5  |
4 |r2|r2 |r2 | 3 |    |
5 |r3|r3 |r3 |   |    |
--+---+---+---+---+---+

*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

string s;
int spos=0;
stack<int> est;
stack<char> simb;

typedef pair<char, int> ci;
ci acao[6][256];        // tabela acao
int got[6][256];        // tabela goto

void init() {
    // inicializa as tabelas acao/goto
    for (int i=0;i<8;i++)
        for (int j=0;j<256;j++)
            acao[i][j] = ci('\0',0);

    // preenche as tabelas acao/goto
    got[0]['E'] = 1;
    got[1]['E'] = 3;
    got[3]['S'] = 5;
    got[3]['E'] = 3;
    acao[0]['n'] = ci('s',2);
    acao[1]['n'] = ci('s',2);
    acao[1]['$'] = ci('a',0);
    acao[3]['+'] = ci('s',4);
    acao[3]['n'] = ci('s',2);
    
    for (int i=0;i<256;i++) {
        acao[2][i] = ci('r', 4);
        acao[4][i] = ci('r', 2);
        acao[5][i] = ci('r', 3);
    }
}

// faz reduce pela regra r
void reduce(int r) {
    string direito;
    char esquerdo;
    if (r==1) {} // S' -> E$ nunca eh reduzida (sua 'reducao' aceita a palavra)
    else if (r==2) { // S -> +
        esquerdo = 'S';
        direito = "+";
    } else if (r==3) { // E -> ESS
        esquerdo = 'E';
        direito = "ESS";
    } else if (r==4) { // E -> n
        esquerdo = 'E';
        direito = "n";
    }

    // desempilha lado direito
    for (int i=0;i<direito.size();i++) {
        est.pop();
        simb.pop();
    }

    // empilha lado esquerdo e novo estado
    simb.push(esquerdo);
    est.push(got[ est.top() ][ simb.top() ]);
}

int main() {

    init();

    cin >> s;
    s = s + "$";

    est.push(0);
    while (true) {
        if (acao[est.top()][s[spos]].first == '\0') {
            cout << "erro sintatico" << endl;
            return 1;
        } else if (acao[est.top()][s[spos]].first == 'a') {
            cout << "entrada valida!" << endl;
            return 0;
        } else if (acao[est.top()][s[spos]].first == 's') {
            // shift
            est.push(acao[est.top()][s[spos]].second);
            simb.push(s[spos++]);
        } else {
            // reduce
            reduce(acao[est.top()][s[spos]].second);
        }

    }

    return 0;
}
