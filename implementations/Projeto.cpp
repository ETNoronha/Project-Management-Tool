#include "Projeto.h"
#include <stdexcept>


using namespace std;

Projeto::Projeto (string nome) : nome(nome) {
    atividades = new vector<Atividade*>();
    recursos = new list<Recurso*>();
}

Projeto::~Projeto () {

}

string Projeto::getNome () {
    return nome;
}

void Projeto::adicionar (Atividade* a) {
    atividades->push_back(a);
}

vector<Atividade*>* Projeto::getAtividades () {
    return atividades;
}

void Projeto::adicionar(Recurso* r) {

    //Checa se a pessoa ja foi adicionada
    list<Recurso*>::iterator i = recursos->begin();
    while (i != recursos->end()) {
        if ((*i) == r) {
            throw new invalid_argument ("Recurso ja' Adicionado");
        }
        i++;
    }

    recursos->push_back(r);
}

list<Recurso*>* Projeto::getRecursos() {
    return recursos;
}


int Projeto::getDuracao () {
    int duracaoTotal = 0;
    vector<Atividade*>::iterator i = atividades->begin();

    while (i != atividades->end()) {
        duracaoTotal += (*i)->getDuracao();
        i++;
    }

    return duracaoTotal;
}

int Projeto::getDuracao(bool terminadas) {
    int duracao = 0;

    if (terminadas) {
        vector<Atividade*>::iterator i = atividades->begin();

        while (i != atividades->end()) {
            if ((*i)->estaTerminada()) {
                duracao += (*i)->getDuracao();
            }
            i++;
        }
    }else if (!terminadas) {
        vector<Atividade*>::iterator i = atividades->begin();

        while (i != atividades->end()) {
            if (!(*i)->estaTerminada()) {
                duracao += (*i)->getDuracao();
            }
            i++;
        }
    }
    return duracao;
}

double Projeto::getCusto () {
    double custoTotal =0;
    vector<Atividade*>::iterator i = atividades->begin();

    while (i != atividades->end()) {
        custoTotal += (*i)->getCusto();
        i++;
    }

    return custoTotal;
}

void Projeto::imprimir () {
    cout <<  nome << " - " << "R$" << getCusto() << endl;
    cout << "Duracao:" << endl;
    cout << "- Feito " << getDuracao(true) << " dias" << endl;
    cout << "- Falta " << getDuracao(false) << " dias " << endl;
    cout << "----" << endl;

    vector<Atividade*>::iterator it = atividades->begin();

    while (it != atividades->end()) {
        (*it)->imprimir();
        it++;
    }
}
