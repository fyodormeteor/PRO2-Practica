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
    @brief Un Producto siempre es parte del inventario de una Ciudad.
    
    El identificador del Producto es almacenado como el key del mapa 'inventario' de la clase Ciudad.
    Dentro de Producto se almacena la cantidad y la necesidad que tiene la Ciudad de el. NO se almacena el peso y el volumen, ya que esa informacion ya se
    encuenta en el vector 'id2infoprod' de la clase Rio.
*/

class Producto {

private:

    /** @brief Almacena la cantidad del Producto. Es decir, la Ciudad que contiene el Producto tiene <em>cantidad</em> unidades de el.
    */
    int cantidad;

    /** @brief Almacena la necesidad del Producto. Es decir, la Ciudad que contiene el Producto quiere <em>necesidad</em> unidades de el.
    */
    int necesidad;

public:
    
    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       El resultado es Producto con atributos cantidad = 0 y necesidad = 1
    \coste      Constante
    */
    Producto();
    
    /** @brief  Creadora que inicializa la cantidad y la necesidad.
    \pre        <em>cant</em> >= 0, <em>necd</em> > 0
    \post       El resultado es Producto con atributos cantidad = <em>cant</em> y necesidad = <em>necd</em>
    \coste      Constante
    */
    Producto(const int cant, const int necd);
    
    /** @brief  Escribe la cantidad y necesidad del producto.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos (cantidad, necesidad) del parametro implicito
    \coste      Constante
    */
    void escribir() const;

    /** @brief  Consulta la cantidad del producto.
    \pre        <em>cierto</em>
    \post       El resultado es la cantidad del parametro implicito
    \coste      Constante
    */
    int obtener_cantidad() const;

    /** @brief  Consulta la necesidad del producto.
    \pre        <em>cierto</em>
    \post       El resultado es la necesidad del parametro implicito
    \coste      Constante
    */
    int obtener_necesidad() const;

    /** @brief  Consulta el exceso del producto, es decir consulta el numero de unidades que sobran.
    \pre        <em>cierto</em>
    \post       El resultado es necesidad - cantidad
    \coste      Constante
    */
    int obtener_exceso() const;
   
    /** @brief  Establece la cantidad del producto.
    \pre        <em>cant</em> >= 0
    \post       El parametro implicito pasa a tener cantidad = <em>cant</em>
    \coste      Constante
    */
    void establecer_cantidad(const int cant);

    /** @brief  Establece la necesidad del producto.
    \pre        <em>necd</em> > 0
    \post       El parametro implicito pasa a tener necesidad = <em>necd</em>
    \coste      Constante
    */
    void establecer_necesidad(const int necd);

    /** @brief  Definicion del operador += para sumar valores al atributo necesidad.
    \pre        <em>cant</em> >= -cantidad
    \post       El parametro implicito pasa a tener cantidad = cantidad + <em>cant</em>
    \coste      Constante
    */
    void operator+=(const int cant);
};

#endif