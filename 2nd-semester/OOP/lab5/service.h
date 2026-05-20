#pragma once

#include "list.h"

typedef int(*fil_fct)(TElement, char*, char*);

void actualizareProdus(int id, MyList* lista, double pret);
/*functie care actualizeaza pretul unui produs
 *param: int id, produse lista (lista de produse), double pret (pretul nou)
 */

/* doamne ajuta si da bine DENIS_ADRIAN
*/

/*Functia de distrugere lista de undo
 */
void destroyUndo(MyList* lista);

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
MyList* undo(MyList* lista,MyList* undo_list);


/*Filtrarile facute de denis, Functia de filtrare dupa un anumit criteriu(tip sau cantitate mai mica decat un numar dat)
*/
MyList* filter(MyList* lista, char* fil_crt, char* fil_val, fil_fct fil);

/*Functia care verifica daca produsul respecta filtrul
* @produs - un produs
* @criteriu - sir de caractere, criteriul dupa care filtram
* @val - valoarea criteriului dupa care filtram(sir de caractere sau un numar)
*/
int functia_filtru(produs* pr, char* criteriu, char* val);