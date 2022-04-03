#include "PersistenciaDeProjeto.h"
#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"
#include "Pessoa.h"
#include "Ferramenta.h"
#include "ErroDeArquivo.h"
#include <algorithm>

template <typename tipo>
tipo readAuto (ifstream& arquivo) {
    tipo variavel;
    arquivo >> variavel;

    if (!arquivo.good()) {
        throw new ErroDeArquivo("Erro de Arquivo");
    }

    return variavel;
}



PersistenciaDeProjeto::PersistenciaDeProjeto() {

}

PersistenciaDeProjeto::~PersistenciaDeProjeto() {

}

Projeto* PersistenciaDeProjeto::carregar(string arquivo) {
    ifstream entrada;
    entrada.open(arquivo);

    if (entrada.fail()) {
        throw new ErroDeArquivo("Erro ao Abrir FileOut");
    }

    string nome = readAuto <string> (entrada);
    Projeto* p = new Projeto(nome);

    int quantidadeDeRecursos = readAuto <int> (entrada);

    // Adiciona recursos no projeto
    for (int i = 0; i < quantidadeDeRecursos; i++) {
        string tipoRecurso = readAuto <string> (entrada);

        if (tipoRecurso == "P") {
            string nome = readAuto <string> (entrada);
            double valorPorHora = readAuto <double> (entrada);
            double horasDiarias = readAuto <double> (entrada);

            if (valorPorHora > 0) {
                Pessoa* pessoa = new Pessoa(nome, valorPorHora, horasDiarias);
                p->adicionar(pessoa);
            } else if (valorPorHora == -1) {
                p->adicionar(new Pessoa(nome, horasDiarias));
            } else if (valorPorHora != -1) {
                throw new ErroDeArquivo("Erro de Arquivo");
            }
        } else if (tipoRecurso == "F") {
            string nome = readAuto <string> (entrada);
            double custoDiario = readAuto <double> (entrada);

            try {
                p->adicionar(new Ferramenta(nome, custoDiario));
            } catch (invalid_argument *e) {
                delete e;
                throw new ErroDeArquivo("custoDiario negativo");
            }
        } else throw new ErroDeArquivo("Erro de Arquivo");
    }// end

    int quantidadeDeAtividades = readAuto <int> (entrada);

    // Adiciona as atividades no projeto
    for (int i = 0;i < quantidadeDeAtividades; i++) {
        string tipoAtividade = readAuto <string> (entrada);

        if (tipoAtividade == "E") {
            //obtendo valores para chamar construtor de atividade
            string nome = readAuto <string> (entrada);
            double horasNecessarias = readAuto <double> (entrada);
            bool estaTerminada = (readAuto <string> (entrada) == "T");
            double duracao;
            if (estaTerminada) {
                duracao = readAuto <double> (entrada);
            }

            p->adicionar(new AtividadeDeEsforcoFixo(nome, horasNecessarias));
            if (estaTerminada) {
                p->getAtividades()->back()->terminar(duracao);
            }

        } else if (tipoAtividade == "P") {
            //obtendo valores para chamar construtor de atividade
            string nome = readAuto <string> (entrada);
            double prazo = readAuto <double> (entrada);
            bool estaTerminada = (readAuto <string> (entrada) == "T");
            double duracao;
            if (estaTerminada) {
                duracao = readAuto <double> (entrada);
            }

            p->adicionar(new AtividadeDePrazoFixo(nome, prazo));
            if (estaTerminada) {
                p->getAtividades()->back()->terminar(duracao);
            }
        } else throw new ErroDeArquivo("Erro de Arquivo");

        int quantidadeDeRecursos = readAuto <int> (entrada);

        // Adiciona recursos as atividades
        for (int j = 0; j < quantidadeDeRecursos; j++) {
            string nome = readAuto <string> (entrada);

            list<Recurso*> :: iterator it = p->getRecursos()->begin();
            while (it != p->getRecursos()->end()) {
                if ((*it)->getNome() == nome) {
                    p->getAtividades()->back()->adicionar((*it));
                }
                it++;
            }
        }// end
    }// end
    return p;
}

void PersistenciaDeProjeto::salvar(Projeto* p, string arquivo) {
    ofstream saida;
    saida.open(arquivo);

    if (saida.fail()) {
        throw new ErroDeArquivo("Erro ao Abrir FileOut");
    }

    saida << p->getNome() << endl;
    saida << p->getRecursos()->size() << endl;

    list<Recurso*> :: iterator i = p->getRecursos()->begin();

    while (i != p->getRecursos()->end()) {
        Pessoa* pessoa = dynamic_cast<Pessoa*>(*i);
        Ferramenta* ferramenta = dynamic_cast<Ferramenta*>(*i);

        if (pessoa) {
            saida << "P " << pessoa->getNome() << " ";
            saida << (pessoa->recebeValorPadrao()? -1:pessoa->getValorPorHora()) << " ";
            saida << pessoa->getHorasDiarias() << endl;
        } else if (ferramenta) {
            saida << "F " << ferramenta->getNome() << " ";
            saida << ferramenta->getCustoDiario() << endl;
        }
        i++;
    }
    saida << p->getAtividades()->size() << endl;

    vector<Atividade*> :: iterator it = p->getAtividades()->begin();

    while (it != p->getAtividades()->end()) {

        AtividadeDeEsforcoFixo* esforco = dynamic_cast<AtividadeDeEsforcoFixo*>(*it);
        AtividadeDePrazoFixo* prazo = dynamic_cast<AtividadeDePrazoFixo*>(*it);

        if (esforco) {
            saida << "E " << esforco->getNome() << " " << esforco->getHorasNecessarias() << " ";
            saida << (esforco->estaTerminada()? "T ":"N\n");
            if (esforco->estaTerminada()) {
                saida << esforco->getDuracao() << endl;
            }
        } else if (prazo) {
            saida << "P " << prazo->getNome() << " " << prazo->getPrazo() << " ";
            saida << (prazo->estaTerminada()? "T":"N\n");
            if (prazo->estaTerminada()) {
                saida << prazo->getDuracao() << endl;
            }
        }
        saida << (*it)->getQuantidadeDeRecursos() << endl;

        for (int w = 0; w < (*it)->getQuantidadeDeRecursos(); w++) {
            saida << (*it)->getRecursos()[w]->getNome() << " ";
        }
        saida << endl;
        it++;
    }
    saida << endl;
}
