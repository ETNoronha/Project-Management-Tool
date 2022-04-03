//TO DO: invalid_argument if custoDiario be negative
#include "Ferramenta.h"

#include <stdexcept>

 using namespace std;

Ferramenta::Ferramenta(string nome, double custoDiario) :
Recurso(nome){
    if (custoDiario < 0) {
        throw new invalid_argument ("Ferrament::Ferrament -> custoDiario Negativo");
    } else {
        this->custoDiario = custoDiario;
    }
}

Ferramenta::~Ferramenta() {

}

double Ferramenta::getCustoDiario() {
    return custoDiario;
}

double Ferramenta::getCusto(int dias) {
    if (dias <= 0) {
        throw new invalid_argument ("Ferrament::getCusto -> dias Negativos ou Nulos");
    }
    return (dias * custoDiario);
}

void Ferramenta::imprimir() {
    cout << "Ferramenta: " << nome << " - R$" << custoDiario << " por dia" << endl;
}
