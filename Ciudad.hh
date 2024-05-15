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

    string nombre;
    
    map<int,Producto> inventario;

    double peso_total;
    double volumen_total;

public:

    /** @brief  Creadora con identificador/nombre de la ciudad.
    \pre        <em>cierto</em>
    \post       *
    \coste      *
    */
    Ciudad(string nombre);
    
    /** @brief  Escribe el peso total y volumen total de la ciudad.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos peso_total y volumen_total del parametro implicito
    \coste      *
    */
    void escribir_peso_y_volumen() const;

    /** @brief  Escribe el peso total y volumen total de la ciudad.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos peso_total y volumen_total del parametro implicito
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

    /** @brief  Devuelve el producto con identificador "id" del inventario de la ciudad.
    \pre        Producto con identificador <em>id</em> existe en el inventario
    \post       El resultado es la instancia de Producto con identificador <em>id</em> del inventario del parametro implicito
    \coste      *
    */
    Producto producto_con_id(const int id) const;

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
    void agregar_inventario(const int idprod, const double peso, const double volumen, const int cantidad, const int necesidad);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void modificar_inventario(const int id_prod, const double peso, const double volumen, const int cantidad, const int necesidad);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void quitar_inventario(const int id_prod);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void comerciar_con(Ciudad& c, const vector<pair<double,double>>& id2prodinfo);
};

#endif