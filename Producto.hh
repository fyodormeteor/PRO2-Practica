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
    
    // ??
    Producto();
    
    /** @brief  Creadora que inicializa la cantidad y la necesidad.
    \pre        <em>cant</em> >= 0, <em>necd</em> > 0
    \post       El resultado es Producto con atributos <em>cantidad</em> y <em>necesidad</em>
    \coste      *
    */
    Producto(const int cant, const int necd);
    
    /** @brief  Escribe la cantidad y necesidad del producto.
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
    \pre        <em>cant</em> >= 0
    \post       *
    \coste      *
    */
    void establecer_cantidad(const int cant);

    /** @brief  *
    \pre        <em>necd</em> > 0
    \post       *
    \coste      *
    */
    void establecer_necesidad(const int necd);

    /** @brief  Definicion del operador += para sumar valores al atributo necesidad.
    \pre        *
    \post       *
    \coste      *
    */
    void operator+=(const int cant);
};

#endif