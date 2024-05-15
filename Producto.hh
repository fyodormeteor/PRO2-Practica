/** @file Producto.hh
    @brief Especificación de la clase Producto
*/

#ifndef _PRODUCTO_HH_
#define _PRODUCTO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;

/** @class Producto
    @brief *
*/

class Producto {

private:

    int cantidad;
    int necesidad;

public:
    
    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       El resultado es *
    \coste      *
    */
    Producto();
    
    /** @brief  Lee la cantidad y la necesidad del producto desde el canal de entrada
    \pre        El canal de entrada contiene 2 enteros CANT, NECD
    \post       El parametro implicito pasa a tener cantidad = CANT, necesidad = NECD
    \coste      *
    */
    void leer();
    
    /** @brief  Escribe la cantidad y necesidad del producto
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos (cantidad, necesidad) del parametro implicito
    \coste      *
    */
    void escribir() const;

    /** @brief  *
    \pre        <em>cierto</em>
    \post       *
    \coste      *
    */
    int obtener_cantidad() const;

    /** @brief  *
    \pre        <em>cierto</em>
    \post       *
    \coste      *
    */
    int obtener_necesidad() const;

    /** @brief  *
    \pre        <em>cierto</em>
    \post       *
    \coste      *
    */
    int obtener_exceso() const;
   
    /** @brief  *
    \pre        * (no es 'cierto')
    \post       *
    \coste      *
    */
    void establecer_cantidad(const int cant);

    /** @brief  *
    \pre        * (no es 'cierto')
    \post       *
    \coste      *
    */
    void establecer_necesidad(const int necd);

    /** @brief  Añadir cantidad*
    \pre        *
    \post       *
    \coste      *
    */
    void operator+=(const int cantidad);
};

#endif