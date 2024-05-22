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
    @brief *
*/

class Ciudad {

private:

    map<int,Producto> inventario;

    int peso_total;
    int volumen_total;

public:

    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       *
    \coste      *
    */
    Ciudad();
    
    /** @brief  Escribe el peso total y volumen total de la ciudad.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos peso_total y volumen_total del parametro implicito
    \coste      *
    */
    void escribir_peso_y_volumen() const;

    /** @brief  *
    \pre        <em>cierto</em>
    \post       *
    \coste      *
    */
    void escribir_inventario() const;
    
    /** @brief  Escribe el inventario, peso total y volumen total de la ciudad.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida el inventario y los atributos (peso_total, volumen_total) del parametro implicito
    \coste      *
    */
    void escribir() const;

    /** @brief  Comprueba si existe un producto con identificador "id" en el inventario de la ciudad.
    \pre        <em>cierto</em>
    \post       El resultado indica si existe Producto con identificador <em>id</em> en el inventario del parametro implicito
    \coste      *
    */
    bool existe_producto_en_inventario(const int id) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void escribir_producto(int id) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void reinicializar_inventario();

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void agregar_inventario(const int idprod, const int peso, const int volumen, const int cantidad, const int necesidad);

    /** @brief  *
    \pre        Ciudad tiene el producto*
    \post       *
    \coste      *
    */
    void modificar_inventario(const int idprod, const int peso, const int volumen, const int cantidad, const int necesidad);

    /** @brief  *
    \pre        Ciudad tiene el producto*
    \post       *
    \coste      *
    */
    void quitar_inventario(const int idprod, const int peso, const int volumen);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    int cantidad_de_producto_en_inventario(const int idprod) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    int necesidad_de_producto_en_inventario(const int idprod) const;
    
    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    int exceso_de_producto_en_inventario(const int idprod) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void comprar_producto(const int idprod, int cantidad, const int peso, const int volumen);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void vender_producto(const int idprod, int cantidad, const int peso, const int volumen);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void comerciar_con(Ciudad& c, const vector<pair<int,int>>& id2infoprod);
};

#endif