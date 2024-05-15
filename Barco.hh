/** @file Barco.hh
    @brief Especificación de la clase Barco
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#include "Producto.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
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

    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       *
    \coste      *
    */
    Barco();
    
    /** @brief  Lee la informacion del barco.
    \pre        En el canal de entrada estan preparados 4 enteros IDCOMPRAR, CANTCOMPRAR, IDVENDER, CANTVENDER
    \post       El parametro implicito pasa a tener comprar_id = IDCOMPRAR, comprar_cantidad = CANTCOMPRAR, vender_id = IDVENDER, vender_cantidad = CANTVENDER
    \coste      *
    */
    void leer() const;
    
    /** @brief  Escribe la informacion del barco junto a su cronologia de viajes.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos (comprar_id, vender_id, comprar_cantidad, vender_cantidad)
                y la cronologia de viajes del parametro implicito
    \coste      *
    */
    void escribir() const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void modificar(const int id_comprar, const int cantidad_comprar, const int id_vender, const int cantidad_vender);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void hacer_viaje(const BinTree<string>& b, map<string, Ciudad>& nombre2ciudad);

    // - compute auxiliar weighted tree (possibly with pair<weight,height>, where height of node = max(height.left, height.right) + 1)
    // - travel aux tree parallel to original tree
    // - modify cities during this travel
    // - save the last city you sold/bought to/from, end the travel there

};

#endif