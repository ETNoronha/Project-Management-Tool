#include "AtividadeDeEsforcoFixo.h"

#include <cmath>
#include <iostream>
#include <stdexcept>



AtividadeDeEsforcoFixo::AtividadeDeEsforcoFixo(string nome, int horasNecessarias) :
Atividade(nome) {
    if (horasNecessarias <= 0) {
        throw new invalid_argument ("AtividadeDeEsforcoFixo::AtividadeDeEsforcoFixo");
    }
    this->horasNecessarias = horasNecessarias;
}

AtividadeDeEsforcoFixo::~AtividadeDeEsforcoFixo() {

}

int AtividadeDeEsforcoFixo::getHorasNecessarias() {
    return horasNecessarias;
}

int AtividadeDeEsforcoFixo::getDuracao() {
    if (estaTerminada()) {
        return duracaoReal;
    }

    double horasDiariasTotais = 0;
    int quantidadeDePessoas = 0;

    for (int i = 0; i < quantidadeDeRecursos; i++) {
        Pessoa* pessoa = dynamic_cast<Pessoa*>(recursos[i]);

        if (pessoa) {
            horasDiariasTotais += pessoa->getHorasDiarias();
            quantidadeDePessoas++;
        }
    }

    if (!quantidadeDePessoas) {
        throw new logic_error ("AtividadeDeEsforcoFixo::getDuracao");
    }

    return ceil ((double) (horasNecessarias)/horasDiariasTotais);

}
