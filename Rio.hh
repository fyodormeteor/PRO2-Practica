/** @file Rio.hh
    @brief Especificación de la clase Rio
*/

#ifndef _RIO_HH_
#define _RIO_HH_

#include "Ciudad.hh"
#include "Barco.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <map>
#include <string>
#endif

using namespace std;

/** @class Rio
    @brief *
*/

class Rio {

private:
    
    BinTree<Ciudad> cuenca;
    Barco barco;
    map<int, pair<double,double>> informacion_productos;

public:

    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       El resultado es un Rio vacio
    \coste      *
    */
    Rio()
    {
        cuenca = BinTree<Ciudad>();
        barco = Barco();
        informacion_productos = map<int, pair<double,double>>();
    }

    /** @brief  *
    \pre        En el canal de entrada...
    \post       El parametro implicito pasa a...
    \coste      *
    */
    void leer_cuenca();

    /** @brief  *
    \pre        En el canal de entrada...
    \post       El parametro implicito pasa a...
    \coste      *
    */
    void leer_informacion_productos();

    /** @brief  *
    \pre        En el canal de entrada...
    \post       El parametro implicito pasa a...
    \coste      *
    */
    void leer_barco();

    
    /** @brief  Devuelve el barco del rio.
    \pre        <em>cierto</em>
    \post       El resultado es la instancia de Barco perteneciente a el parametro implicito
    \coste      *
    */
    Barco barco_del_rio() const;


    /** @brief  Comprueba si existe una ciudad con el identificador "id".
    \pre        <em>cierto</em>
    \post       El resultado indica si Ciudad con identificador <em>id</em> existe
    \coste      *
    */
    bool existe_ciudad(const string id) const;

    /** @brief  Devuelve la ciudad con el identificador "id".
    \pre        Ciudad con identificador <em>id</em> existe
    \post       El resultado es la instancia de Ciudad con identificador <em>id</em>
    \coste      *
    */
    Ciudad ciudad_con_id(const string id) const;


    /** @brief  Comprueba si existe un producto con identificador "id".
    \pre        <em>cierto</em>
    \post       El resultado indica si existe la informacion de un producto con identificador <em>id</em>
    \coste      *
    */
    bool existe_producto(const int id) const;

    /** @brief  Consulta el peso de un producto.
    \pre        Informacion de producto con identificador <em>id</em> existe
    \post       El resultado es el peso de un producto con identificador <em>id</em>
    \coste      *
    */
    double peso_del_producto(const int id) const;

    /** @brief  Consulta el volumen de un producto.
    \pre        Informacion de producto con identificador <em>id</em> existe
    \post       El resultado es el volumen de un producto con identificador <em>id</em>
    \coste      *
    */
    double volumen_del_producto(const int id) const;

    /** @brief  Añade la informacion de un producto nuevo.
    \pre        <em>cierto</em>
    \post       Se ha añadido la informacion (<em>peso</em> y <em>volumen</em>) de un producto nuevo a el parametro implicito
    \coste      *
    */
    void agregar_producto(const double peso, const double volumen);

    /** @brief  Escribe la informacion (peso, volumen) de un producto.
    \pre        Informacion de producto con identificador <em>id</em> existe
    \post       Se ha escrito al canal de salida la informacion de un producto con identificador <em>id</em>
    \coste      *
    */
    void escribir_producto(const int id) const;

    /** @brief  Consulta la cantidad de productos existentes.
    \pre        <em>cierto</em>
    \post       El resultado es la cantidad de productos
    \coste      *
    */
    int cantidad_de_productos() const;


    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void hacer_viaje();

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void comerciar(const string id1, const string id2);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void redistribuir();
};

#endif