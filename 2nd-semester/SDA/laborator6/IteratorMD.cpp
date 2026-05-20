#include "IteratorMD.h"
#include "MD.h"
#include <iostream>
using namespace std;

IteratorMD::IteratorMD(const MD& _md) : md(_md),indexTabela(0),indexValori(0) {
	/* de adaugat */
	prim();
}

TElem IteratorMD::element() const {
	/* de adaugat */
    
    if (!valid()) {
        throw std::exception();
    }
    return std::make_pair(md.tabela[indexTabela].cheie, md.tabela[indexTabela].valori[indexValori]);
}


bool IteratorMD::valid() const {
    return indexTabela < md.capacitate &&
        md.tabela[indexTabela].ocupat == used &&
        indexValori < md.tabela[indexTabela].valori.size();
}

void IteratorMD::urmator() {
	/* de adaugat */
    if (!valid()) {
        throw std::exception();
    }
    indexValori++;
    if (indexValori>=(int)md.tabela[indexTabela].valori.size()) {
        indexTabela++;
        indexValori = 0;
        while (indexTabela < md.capacitate &&(md.tabela[indexTabela].ocupat != used || md.tabela[indexTabela].valori.empty()))
            indexTabela++;
    }
}

void IteratorMD::prim() {
    indexTabela = 0;
    indexValori = 0;

    while (indexTabela < md.capacitate && (md.tabela[indexTabela].ocupat != used || md.tabela[indexTabela].valori.empty())) {
        indexTabela++;
    }
}

