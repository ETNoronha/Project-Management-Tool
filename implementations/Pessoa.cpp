#include "Pessoa.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

double Pessoa::valorPorHoraPadrao = 10;

Pessoa::Pessoa(string nome, double valorPorHora, int horasDiarias) :
Recurso (nome) {
    if (valorPorHora <= 0 || horasDiarias <= 0) {
        throw new invalid_argument ("Pessoa::Pessoa (string, double, int)");
    } else {
        this->valorPorHora = valorPorHora;
        this->horasDiarias = horasDiarias;
    }
}

Pessoa::Pessoa(string nome, int horasDiarias) :
Recurso(nome) {
    if (horasDiarias <= 0) {
        throw new invalid_argument ("Pessoa::Pessoa (string, int)");
    }
    this->horasDiarias = horasDiarias;
    valorPorHora = 0;
}


Pessoa::~Pessoa() {

}

double Pessoa::getValorPorHora() {
    if (recebeValorPadrao()) {
        return Pessoa::valorPorHoraPadrao;
    } else {
        return valorPorHora;
    }
}

int Pessoa::getHorasDiarias() {
    return horasDiarias;
}

bool Pessoa::recebeValorPadrao() {
    if (!valorPorHora) {
        return true;
    } else {
        return false;
    }
}

void Pessoa::setValorPorHoraPadrao(double valor) {
    if (valor <= 0) {
        throw new invalid_argument ("Pessoa::setValorPorHoraPadrao(double)");
    }
    Pessoa::valorPorHoraPadrao = valor;
}

double Pessoa::getValorPorHoraPadrao() {
    return Pessoa::valorPorHoraPadrao;
}

double Pessoa::getCusto(int dias) {
    if (dias <= 0) {
        throw new invalid_argument ("Pessoa::getCusto -> dias <= 0");
    }

    if (recebeValorPadrao()) {
        return (dias * horasDiarias * Pessoa::valorPorHoraPadrao);
    } else {
        return (dias * horasDiarias * valorPorHora);
    }
}

void Pessoa::imprimir() {
    cout << "Pessoa: "  << nome << " - R$" << getValorPorHora() << " - " << horasDiarias << "h por dia" << endl;
}




































