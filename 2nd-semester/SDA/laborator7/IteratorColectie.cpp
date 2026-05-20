
#include "IteratorColectie.h"
#include "Colectie.h"

IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
    stiva = new int[col.dim()];
    capacitate = col.dim();
    top = -1;
    curent = col.radacina;
    prim();
}

TElem IteratorColectie::element() const {

    if (!valid())
        throw exception();
    return col.noduri[curent].e;
}

bool IteratorColectie::valid() const {

    return curent != -1;
}

void IteratorColectie::urmator() {
    if (!valid())
        throw exception();
  
    //se scoate nodul vizitat, ajungem la ce aveam inaintea lui pe stiva
    int nod = stiva[top--];
    curent = col.noduri[nod].dreapta;

    //continuam parcurgerea pe subarborele drept
    while (curent != -1) {
        stiva[++top] = curent;
        curent = col.noduri[curent].stanga;
    }

    if (top != -1)
        curent = stiva[top];
    else
        curent = -1;
}

void IteratorColectie::prim() {
    top = -1;
    curent = col.radacina;
    //itiliazam stiva pentru eficientizare functie element()
    while (curent != -1) {
        stiva[++top] = curent; //radacina
        curent = col.noduri[curent].stanga; //stanga
    }
    /*
    * |------------|
    * |   stanga   |
    * |____________|
    * |            |
    * |  radacina  |
    * |____________|
    */
    //la final curent este cel mai din stanga nod
    if (top != -1)
        curent = stiva[top];
    else
        curent = -1;
}

