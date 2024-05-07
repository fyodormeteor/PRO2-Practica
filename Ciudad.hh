/** @file Ciudad.hh
    @brief Especificación de la clase Ciudad
*/

#ifndef _CIUDAD_HH_
#define _CIUDAD_HH_

#include "Producto.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#endif

using namespace std;

/** @class Ciudad
    @brief *
*/

class Ciudad {

private:

    string nombre;
    
    map<int,Producto> inventario;

    int peso_total;
    int volumen_total;

public:

    /** @brief  Escribe el inventario, peso total y volumen total de la ciudad.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida el inventario y atributos <em>peso_total</em>, <em>volumen_total</em> del parametro implicito
    \coste      *
    */
    void escribir() const;

    /** @brief  Comprueba si existe un producto con identificador "id" en el inventario de la ciudad.
    \pre        <em>cierto</em>
    \post       El resultado indica si existe un producto con identificador <em>id</em> en el inventario del parametro implicito
    \coste      *
    */
    bool existe_producto_en_inventario(const int id) const;

    /** @brief  Devuelve el producto con identificador "id" del inventario de la ciudad.
    \pre        Producto con identificador <em>id</em> existe en el inventario
    \post       El resultado es la instancia de Producto con identificador <em>id</em> del inventario de la ciudad
    \coste      *
    */
    Producto producto_con_id(const int id) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void leer_inventario();

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void agregar_inventario(const int id_prod, const int cantidad, const int necesidad);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void modificar_inventario(const int id_prod, const int cantidad_nueva, const int necesidad_nueva);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void quitar_inventario(const int id_prod);
};

#endif