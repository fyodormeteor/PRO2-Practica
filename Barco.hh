/** @file Barco.hh
    @brief Especificación de la clase Barco
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#ifndef NO_DIAGRAM
#include "BinTree.cc"
#include "Ciudad.hh"
#include <iostream>
#include <list>
#include <map>
#endif

using namespace std;

/** @class Barco
    @brief *
*/

class Barco {

private:

    bool ini;
    
    int comprar_id;
    int vender_id;
    int comprar_cantidad;
    int vender_cantidad;

    list<string> cronologia;

public:

    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       El resultado es un Barco no inicializado
    \coste      *
    */
    Barco();
    
    /** @brief  Lee la informacion del barco.
    \pre        En el canal de entrada estan preparados 4 enteros IDCOMPRAR, CANTCOMPRAR, IDVENDER, CANTVENDER,
                productos con identificador IDCOMPRAR y IDVENDER existen,
                CANTCOMPRAR >= 0, CANTVENDER >= 0, CANTCOMPRAR + CANTVENDER > 0
    \post       El parametro implicito pasa a tener comprar_id = IDCOMPRAR, comprar_cantidad = CANTCOMPRAR, vender_id = IDVENDER, vender_cantidad = CANTVENDER
    \coste      *
    */
    void leer();
    
    /** @brief  Escribe la informacion del barco junto a su cronologia de viajes.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos (comprar_id, vender_id, comprar_cantidad, vender_cantidad)
                y la cronologia de viajes del parametro implicito
    \coste      *
    */
    void escribir() const;

    /** @brief  *
    \pre        Productos con id <em>comprar_id</em> y <em>vender_id</em> existen,
                <em>comprar_cantidad</em> >= 0, <em>vender_cantidad</em> >= 0,
                <em>comprar_cantidad</em> + <em>vender_cantidad</em> > 0
    \post       El parametro implicito pasa a tener los nuevos atributos
    \coste      *
    */
    void modificar(const int comprar_id, const int comprar_cantidad, const int vender_id, const int vender_cantidad);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void reinicializar_cronologia();

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void hacer_viaje(const BinTree<string>& cuenca, map<string, Ciudad>& nombre2ciudad, const vector<pair<double,double>> id2infoprod);

    // - compute auxiliar weighted tree (possibly with pair<weight,height>, where height of node = max(height.left, height.right) + 1)
    // - travel aux tree parallel to original tree
    // - modify cities during this travel
    // - save the last city you sold/bought to/from, end the travel there
    
    // - o recorrido pre-orden con lista de 

};

#endif