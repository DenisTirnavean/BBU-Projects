#pragma once
#include "Repository.h"

class ActUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActUndo() = default;
};

class UndoAdd :public ActUndo {
private:
    Repository_abstract* rep;
    Carte added;
public:
    UndoAdd(Repository_abstract* f, const Carte& lst) : rep{ f }, added{ lst } {}
    virtual void doUndo() override {
        rep->sterge_carte(added);
    }
};

class UndoDelete : public ActUndo {
private:
    Repository_abstract* rep;
    Carte removed;
    int poz;
public:
    UndoDelete(Repository_abstract* r, const Carte& lst, const int pozitie) : rep{ r }, removed{ lst }, poz{ pozitie } {}
    virtual void doUndo() override {
        rep->insert(removed, poz);
    }
};

class UndoModify : public ActUndo {
private:
    Repository_abstract* rep;
    Carte unmodifyed;
    const int position;
public:
    UndoModify(Repository_abstract* r, const Carte& carte, const int poz) : rep{ r }, unmodifyed{ carte }, position{ poz } {}
    virtual void doUndo() override {
        rep->modifica_carte(position, unmodifyed);
    }
};