#ifndef ATIVIDADE_H
#define ATIVIDADE_H

#include "Recurso.h"

#include <string>

using namespace std;

class Atividade {
public:
    Atividade(string nome);
    virtual ~Atividade();

    virtual string getNome();

    virtual void adicionar(Recurso* r);
    virtual Recurso** getRecursos();
    virtual int getQuantidadeDeRecursos();

    virtual int getDuracao() = 0;
    virtual double getCusto();

    virtual void terminar(int duracaoReal);
    virtual bool estaTerminada();

    virtual void imprimir();
    static const int MAX_RECURSOS = 10;

protected:

    string nome;
    int quantidadeDeRecursos;
    int duracaoReal;
    Recurso *recursos[MAX_RECURSOS];


};

#endif // ATIVIDADE_H
