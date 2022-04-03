#include <iostream>
#include <string>
#include <cmath>
#include "Pessoa.h"
#include "Atividade.h"
#include "Projeto.h"
#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"
#include "Ferramenta.h"
#include "Recurso.h"
#include "PersistenciaDeProjeto.h"
#include "ErroDeArquivo.h"

using namespace std;

template <typename tipo>
tipo readUser() {
    tipo variavel;
    cin >> variavel;
    return variavel;
}

void printTela2() {
    cout << "1 - Adicionar recurso" << endl;
    cout << "2 - Adicionar atividade" << endl;
    cout << "3 - Terminar atividade" << endl;
    cout << "4 - Imprimir Projeto" << endl;
    cout << "5 - Definir valor por hora padrao" << endl;
    cout << "6 - Salvar" << endl;
    cout << "0 - Sair" << endl;
    cout << "Escolha a opcao: ";
}

//Imprime Recursos em um Projeto
void printRecursos(Projeto *projeto) {
    list<Recurso*> :: iterator it = projeto->getRecursos()->begin();

    for (int i = 0 ; it != projeto->getRecursos()->end(); it++, i++) {
        cout << i + 1 << " - ";
        (*it)->imprimir();
    }
}

//Adiciona uma Ferramenta a um Projeto
void adicionaFerramenta(Projeto *projeto) {
    cout << "Nome: ";
    string nome = readUser <string> ();

    cout << "Custo diario: ";
    double custoDiario = readUser <double> ();

    projeto->adicionar(new Ferramenta(nome, custoDiario));
}

//Adiciona uma Pessoa a um Projeto
void adicionaPessoa(Projeto *projeto) {
    cout << "Nome: ";
    string nome = readUser <string> ();

    cout << "Horas diarias: ";
    int horasDiarias = readUser <int> ();

    cout << "Valor por hora padrao (s/n)? ";

    if (readUser <string> () == "s") {
        projeto->adicionar(new Pessoa(nome, horasDiarias));
    } else {
        cout << "Valor por hora (em R$): ";
        projeto->adicionar(new Pessoa(nome, readUser <double> (), horasDiarias));
    }
}

//Adiciona uma Atividade a um Projeto
void adicionaAtividade(Projeto *projeto) {
    cout << "Nome: ";
    string nome = readUser <string> ();

    cout << "Prazo fixo (p) ou trabalho fixo (t)? ";
    if (readUser <string> () == "p") {
        cout << "Dias necessarios: ";
        projeto->adicionar(new AtividadeDePrazoFixo(nome, readUser <int> ()));
    } else {
        cout << "Horas Necessarias: ";
        projeto->adicionar(new AtividadeDeEsforcoFixo(nome, readUser <int> ()));
    }
}

//Adiciona um Recurso a ultima Atividade adicionada a um Projeto
void adicionaRecursoEmAtividade (Projeto *projeto, int posicaoRecurso) {
    try {
        list <Recurso*> :: iterator it = projeto->getRecursos()->begin();
        advance(it, posicaoRecurso);
        projeto->getAtividades()->back()->adicionar((*it));
    } catch (invalid_argument *e) {
        cout << "Nao foi possivel adicionar recurso" << endl;
        delete e;
    }
}

void printAtividades(Projeto *projeto) {
    vector<Atividade*> :: iterator it = projeto->getAtividades()->begin();
    for (int i = 1; it != projeto->getAtividades()->end(); i++, it++) {
        cout << i << " - " << (*it)->getNome() << endl;
    }
}

void terminaAtividade(Projeto *projeto, int posicaoAtividade) {
    if (projeto->getAtividades()->at(posicaoAtividade)->estaTerminada()) {
        cout << "Atividade ja terminada" << endl;
    } else {
        cout << "Duracao real: ";
        projeto->getAtividades()->at(posicaoAtividade)->terminar(readUser <int> ());
    }
}


void case_1(Projeto *projeto) {
    cout << "Ferramenta (f) ou Pessoa (p): ";
    if (readUser <string> () == "f") {
        adicionaFerramenta(projeto);
    } else {
        adicionaPessoa(projeto);
    }
}

void case_2(Projeto *projeto) {
    adicionaAtividade(projeto);
    string opcao;

    do {
        cout << "Deseja adicionar um recurso (s/n)? ";
        opcao = readUser <string> ();

        if (opcao == "s") {
            printRecursos(projeto);

            cout << "Escolha um recurso ou 0 para cancelar: ";
            int posicaoRecurso = readUser <int> ();

            if (posicaoRecurso) {
                adicionaRecursoEmAtividade (projeto, posicaoRecurso - 1);
            }
        }
    } while (opcao != "n");
}

void case_3(Projeto *projeto) {
    printAtividades(projeto);

    cout << "Escolha uma atividade ou 0 para cancelar: ";
    int posicaoAtividade = readUser <int> ();

    if (posicaoAtividade) {
        terminaAtividade(projeto, posicaoAtividade - 1);
    }
}

void case_4(Projeto *projeto) {
    projeto->imprimir();
}

void case_5(Projeto *projeto) {
    cout << "Valor atual: R$" << Pessoa::getValorPorHoraPadrao() << " por hora" << endl;
    cout << "Novo valor: ";
    Pessoa::setValorPorHoraPadrao(readUser <double> ());
}

void case_6(Projeto *projeto) {
    PersistenciaDeProjeto *persistencia = new PersistenciaDeProjeto();

    cout << "Nome do arquivo: ";
    persistencia->salvar(projeto, readUser <string> ());

    delete persistencia;
}

Projeto* carregarProjeto() {
    PersistenciaDeProjeto *persistencia = new PersistenciaDeProjeto();

    cout << "Digite o nome do arquivo: ";

    Projeto *projeto = persistencia->carregar(readUser <string> ());
    delete persistencia;
    return projeto;
}

int main() {
    int opcao;
    Projeto *projeto;

    cout << "Deseja carregar um novo projeto (s/n)? ";

    try {

        if (readUser <string> () == "s") {
            projeto = carregarProjeto();
        } else {
            cout << "Digite o nome do projeto: ";
            projeto = new Projeto(readUser <string> ());
        }

        do {
            printTela2();
            opcao = readUser <int> ();
            cout << endl;

            switch (opcao) {
            case 1:
                case_1(projeto);
                cout << endl;
                break;

            case 2:
                case_2(projeto);
                cout << endl;
                break;

            case 3:
                case_3(projeto);
                cout << endl;
                break;

            case 4:
                case_4(projeto);
                cout << endl;
                break;

            case 5:
                case_5(projeto);
                cout << endl;
                break;

            case 6:
                case_6(projeto);
                cout << endl;
                break;
            }
        } while (opcao != 0);
    } catch (ErroDeArquivo* e) {
        cout << "Erro: " << e->what();
        delete e;
        return 0;
    } catch (logic_error *e) {
        cout << "Erro: " << e->what();
        delete e;
        return 0;
    } catch (invalid_argument *e) {
        cout << "Erro: " << e->what();
        delete e;
        return 0;
    } catch (runtime_error *e) {
        cout << "Erro : " << e->what();
        delete e;
        return 0;
    } catch (overflow_error *e) {
        cout << "Erro : " << e->what();
        delete e;
        return 0;
    }
    return 0;
}


