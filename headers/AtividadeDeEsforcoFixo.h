#ifndef ATIVIDADEDEESFORCOFIXO_H
#define ATIVIDADEDEESFORCOFIXO_H

#include "Atividade.h"
#include "Pessoa.h"


class AtividadeDeEsforcoFixo : public Atividade {
public:
    AtividadeDeEsforcoFixo(string nome, int horasNecessarias);
    virtual ~AtividadeDeEsforcoFixo();

    virtual int getHorasNecessarias();

    int getDuracao();

protected:
    int horasNecessarias;

private:
};

#endif // ATIVIDADEDEESFORCOFIXO_H
