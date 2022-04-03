#include "Atividade.h"
#include "Pessoa.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

Atividade::Atividade(string nome) : nome (nome) {
    quantidadeDeRecursos = 0;
    duracaoReal = 0;
}

Atividade::~Atividade() {
}

string Atividade::getNome() {
    return nome;
}


void Atividade::adicionar(Recurso* r) {
    for (int i = 0; i < quantidadeDeRecursos; i++) {
        if (recursos[i] == r) {
            throw new invalid_argument ("Atividade::adicionar -> r Repetido");
        }
    }

    if (quantidadeDeRecursos >= Atividade::MAX_RECURSOS)  {
        throw new overflow_error ("Atividade::adicionar -> MAX_RECURSOS Atingido");
    } else {
        recursos[quantidadeDeRecursos] = r;
        quantidadeDeRecursos++;
    }
}

Recurso** Atividade::getRecursos() {
    return recursos;
}

int Atividade::getQuantidadeDeRecursos() {
    return quantidadeDeRecursos;
}

double Atividade::getCusto() {
    if (quantidadeDeRecursos== 0) {
        return 0;
    }

    double custoTotal = 0;

    for (int i = 0; i < quantidadeDeRecursos; i++) {
        custoTotal += recursos[i]->getCusto(getDuracao());
    }

    return custoTotal;
}

void Atividade::terminar(int duracaoReal) {
    if (duracaoReal <= 0) {
        throw new invalid_argument ("Atividade::terminar duracaoReal <= 0");
    }
    this->duracaoReal = duracaoReal;
}

bool Atividade::estaTerminada() {
    return duracaoReal;
}

void Atividade::imprimir() {
    cout << nome << " - " << getDuracao() << " dias - R$" << getCusto() << endl;
}
