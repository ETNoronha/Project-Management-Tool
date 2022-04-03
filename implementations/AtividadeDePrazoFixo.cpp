#include "AtividadeDePrazoFixo.h"

#include <stdexcept>

using namespace std;

AtividadeDePrazoFixo::AtividadeDePrazoFixo(string nome, int dias) :
Atividade(nome) {
    if (dias <= 0) {
        throw new invalid_argument ("AtividadeDePrazoFixo::AtividadeDePrazoFixo");
    }
    this->dias = dias;
}

AtividadeDePrazoFixo::~AtividadeDePrazoFixo() {

}


int AtividadeDePrazoFixo::getPrazo() {
    return dias;
}

int AtividadeDePrazoFixo::getDuracao() {
    if (estaTerminada()) {
        return duracaoReal;
    } else {
        return dias;
    }
}
