#pragma once
#include "produs.h"
#include "list.h"

void actualizareProdus(int id, MyList* lista, double pret);
/*functie care actualizeaza pretul unui produs
 *param: int id, produse lista (lista de produse), double pret (pretul nou)
 */

/* doamne ajuta si da bine DENIS_ADRIAN
*/

/*Functia de adaugare in stiva de undo - Salveaza starea listei curente pe undo_list
 *@lista - o lista
 *@undo_list - lista cu stari precedente ale listei
 *returns: -
*/
void add_to_undo(MyList* lista, MyList* undo_list);

/*Functia de undo modificari pe lista - Aduce lista la starea precedenta de dinainte de modificari
 *@lista - lista pe care dorim sa inversam modificarile
 *@undo_list - lista cu stari precedente ale listei
 *returns: -
*/
void undo(MyList* lista,MyList* undo_list);

void destroyUndo(MyList* lista);