/** @file Barco.hh
    @brief Especificación de la clase Barco
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#include "Producto.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#endif

using namespace std;

/** @class Barco
    @brief *
*/

class Barco {

private:

    int comprar_id;
    int vender_id;
    int comprar_cantidad;
    int vender_cantidad;

    list<string> cronologia;

public:

    /** @brief  Escribe la informacion del barco junto a su cronologia de viajes.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos y la cronologia de viajes del parametro implicito
    \coste      *
    */
    void escribir() const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void modificar(const int id_comprar, const int cantidad_comprar, const int id_vender, const int cantidad_vender);

};

#endif