#ifndef ATIVIDADEDEPRAZOFIXO_H
#define ATIVIDADEDEPRAZOFIXO_H

#include "Atividade.h"


class AtividadeDePrazoFixo : public Atividade {
public:
    AtividadeDePrazoFixo(string nome, int dias);
    virtual ~AtividadeDePrazoFixo();

    virtual int getPrazo();

    int getDuracao();

protected:
    int dias;

private:
};

#endif // ATIVIDADEDEPRAZOFIXO_H
