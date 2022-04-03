#ifndef PROJETO_H
#define PROJETO_H

#define MAXIMO_ATIVIDADES 10
#define MAXIMO_RECURSOS 10

#include "Pessoa.h"
#include "Atividade.h"

#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Projeto {
public:

    Projeto (string nome);
    ~Projeto();
    string getNome ();

    virtual void adicionar (Atividade* a);
    virtual vector<Atividade*>* getAtividades ();
    virtual void adicionar(Recurso *r);
    virtual list<Recurso*>* getRecursos();

    virtual int getDuracao();
    virtual int getDuracao(bool terminadas);
    virtual double getCusto();
    virtual void imprimir();

private:

    string nome;

    vector<Atividade*>* atividades;
    list<Recurso*>* recursos;

};

#endif // PROJETO_H
