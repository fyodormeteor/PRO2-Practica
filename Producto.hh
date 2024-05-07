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
    
    /** @brief  Escribe la cantidad y necesidad del producto
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos <em>cantidad</em> y <em>necesidad</em> del parametro implicito
    \coste      *
    */
    void escribir() const;

};

#endif