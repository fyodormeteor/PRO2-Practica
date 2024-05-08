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

    double peso;
    double volumen;
    int cantidad;
    int necesidad;

public:
    
    /** @brief  Lee la cantidad y la necesidad del producto desde el canal de entrada
    \pre        El canal de entrada contiene 2 enteros CANT, WANT
    \post       El parametro implicito pasa a tener cantidad = CANT, necesidad = WANT
    \coste      *
    */
    void leer();
    
    /** @brief  Escribe la cantidad y necesidad del producto
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos (cantidad, necesidad) del parametro implicito
    \coste      *
    */
    void escribir() const;
};

#endif