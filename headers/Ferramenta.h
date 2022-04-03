#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "Recurso.h"

#include <iostream>


class Ferramenta : public Recurso {
public:
    Ferramenta(string nome, double custoDiario);
    virtual ~Ferramenta();

    virtual double getCustoDiario();

    double getCusto(int dias);
    void imprimir();

protected:
    double custoDiario;

private:
};

#endif // FERRAMENTA_H
