#ifndef PESSOA_H
#define PESSOA_H

#include <string>

#include "Recurso.h"

using namespace std;


class Pessoa : public Recurso {
public:

    Pessoa(string nome, double valorPorHora, int horasDiarias);
    Pessoa(string nome, int horasDiarias);
    virtual ~Pessoa();

    virtual double getValorPorHora();
    virtual int getHorasDiarias();
    virtual bool recebeValorPadrao();

    static void setValorPorHoraPadrao(double valor);
    static double getValorPorHoraPadrao();

    double getCusto(int dias);
    void imprimir();

private:

    double valorPorHora;
    int horasDiarias;
    bool recebeuValorPadrao;
    static double valorPorHoraPadrao;


};

#endif // PESSOA_H
