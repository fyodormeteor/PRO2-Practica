/** @file Ciudad.hh
    @brief Especificación de la clase Ciudad
*/

#ifndef _CIUDAD_HH_
#define _CIUDAD_HH_

#include "Producto.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <vector>
#endif

using namespace std;

/** @class Ciudad
    @brief Una Ciudad siempre es parte de una cuenca de la clase Rio.
    
    Tiene un inventario de productos (de instancias de Producto) con el cual puede comerciar con alguna otra Ciudad.
    Los productos que tiene la Ciudad siempre estan definidos en la informacion de productos (de clase Rio),
    pero no son necesariamente todos los posibles.
*/

class Ciudad {

private:
    /** @brief Almacena los productos que tiene/quiere la ciudad. El key del mapa corresponde al identificador del Producto.
    */
    map<int,Producto> inventario;

    /** @brief Almacena el peso total de la ciudad.
    */
    int peso_total;
    
    /** @brief Almacena el volumen total de la ciudad.
    */
    int volumen_total;

public:

    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       El resultado es una Ciudad vacia
    \coste      Constante
    */
    Ciudad();
    
    /** @brief  Escribe el peso total y volumen total de la ciudad.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos peso_total y volumen_total del parametro implicito
    \coste      Constante
    */
    void escribir_peso_y_volumen() const;

    /** @brief  Escribe el inventario de la ciudad.
    \pre        <em>cierto</em>
    \post       Se ha escrito al canal de salida el inventario del parametro implicito
    \coste      Lineal
    */
    void escribir_inventario() const;
    
    /** @brief  Escribe el inventario, peso total y volumen total de la ciudad.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida el inventario y los atributos peso_total, volumen_total del parametro implicito
    \coste      Lineal
    */
    void escribir() const;

    /** @brief  Comprueba si existe un producto en el inventario de la ciudad.
    \pre        <em>cierto</em>
    \post       El resultado indica si existe Producto con identificador <em>id</em> en el inventario
    \coste      Logaritmico
    */
    bool existe_producto_en_inventario(const int id) const;

    /** @brief  Escribe un producto del inventario de la ciudad.
    \pre        Producto con identificador <em>id</em> esta en el inventario
    \post       Se han escrito al canal de salida los atributos (cantidad, necesidad) del Producto
    \coste      Logaritmico
    */
    void escribir_producto(int id) const;

    /** @brief  Elimina el inventario de la ciudad
    \pre        <em>cierto</em>
    \post       El inventario esta vacio, peso_total = 0, volumen_total = 0
    \coste      Lineal
    */
    void reinicializar_inventario();

    /** @brief  Añade un producto al inventario de la ciudad
    \pre        Producto con id <em>idprod</em> NO esta en el inventario
    \post       El inventario tiene un nuevo Producto <em>idprod</em> con atributos <em>cantidad</em> y <em>necesidad</em>,
                atributos peso_total y volumen_total se han actualizado correctamente
    \coste      Logaritmico
    */
    void agregar_inventario(const int idprod, const int peso, const int volumen, const int cantidad, const int necesidad);

    /** @brief  Modifica un producto del inventario de la ciudad.
    \pre        Producto con id <em>idprod</em> esta en el inventario
    \post       Producto <em>idprod</em> del inventario pasa a tener atributos <em>cantidad</em> y <em>necesidad</em>,
                atributos peso_total y volumen_total se han actualizado correctamente
    \coste      Logaritmico
    */
    void modificar_inventario(const int idprod, const int peso, const int volumen, const int cantidad, const int necesidad);

    /** @brief  Elimina un producto del inventario de la ciudad.
    \pre        Producto con id <em>idprod</em> esta en el inventario
    \post       Producto <em>idprod</em> se ha eliminado del inventario
                atributos peso_total y volumen_total se han actualizado correctamente
    \coste      Logaritmico
    */
    void quitar_inventario(const int idprod, const int peso, const int volumen);

    /** @brief  Consulta la cantidad de un producto en el inventario.
    \pre        Producto con id <em>idprod</em> esta en el inventario
    \post       El resultado es la cantidad del Producto <em>idprod</em>
    \coste      Logaritmico
    */
    int cantidad_de_producto_en_inventario(const int idprod) const;
    
    /** @brief  Consulta el exceso de un producto en el inventario.
    \pre        Producto con id <em>idprod</em> esta en el inventario
    \post       El resultado es el exceso del Producto <em>idprod</em>, es decir las unidades que le sobran a la Ciudad de este Producto
    \coste      Logaritmico
    */
    int exceso_de_producto_en_inventario(const int idprod) const;

    /** @brief  Añade una cantidad a un producto del inventario.
    \pre        Producto con id <em>idprod</em> esta en el inventario
    \post       Producto <em>idprod</em> del inventario pasa a tener cantidad = cantidad + <em>cant</em>,
                atributos peso_total y volumen_total se han actualizado correctamente
    \coste      Logaritmico
    */
    void comprar_producto(const int idprod, int cant, const int peso, const int volumen);

    /** @brief  Quita una cantidad a un producto del inventario.
    \pre        Producto con id <em>idprod</em> esta en el inventario,
                <em>cant</em> >= -cantidad (del Producto con id <em>idprod</em>)
    \post       Producto <em>idprod</em> del inventario pasa a tener cantidad = cantidad - <em>cant</em>,
                atributos peso_total y volumen_total se han actualizado correctamente
    \coste      Logaritmico
    */
    void vender_producto(const int idprod, int cant, const int peso, const int volumen);

    /** @brief  Efectua un comercio entre la ciudad implicita y otra ciudad por referencia.
    \pre        Ciudad implicita es diferente a la Ciudad <em>c</em>
    \post       Ciudad implicita le ha dado todos los productos que le sobran a Ciudad <em>c</em> hasta alcanzar,
                si es posible los que la Ciudad <em>c</em> necesita, y viceversa.
    \coste      Lineal
    */
    void comerciar_con(Ciudad& c, const vector<pair<int,int>>& id2infoprod);
};

#endif