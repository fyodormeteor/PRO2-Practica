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
#include <vector>
#endif

using namespace std;

/** @class Rio
    @brief *
*/

class Rio {

private:
    
    BinTree<Ciudad> cuenca;
    map<string, Ciudad> id2ciudad;
    Barco barco;
    vector<pair<double,double>> id2producto;
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
        id2producto = vector<pair<double,double>>();
    }

    /** @brief  Lee una nueva estructura de ciudades desde el canal de entrada.
    \pre        El canal de entrada contiene una estructura arborea en pre-orden
    \post       El parametro implicito pasa a contener una nueva estructura arborea de nuevas instancias de Ciudad,
                Las nuevas instancias de Ciudad son vacias,
                Las instancias de Ciudad anteriores a la operacion se han desconstruido,
                La cronologia del Barco se ha borrado
    \coste      *
    */
    void leer_cuenca();

    /** @brief  Lee la informacion de productos desde el canal de entrada.
    \pre        El canal de entrada contiene <em>cantidad</em> parejas de pesos y volumenes
    \post       El parametro implicito pasa a contener la nueva informacion de productos,
                Los identificadores de los nuevos productos son correlativos a partir del ultimo producto existente antes de la operacion
    \coste      *
    */
    void leer_informacion_productos(const int cantidad);

    
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

    /** @brief  Escribe la informacion (peso, volumen) de un producto.
    \pre        Informacion de producto con identificador <em>id</em> existe
    \post       Se ha escrito al canal de salida la informacion de un producto (peso, volumen) con identificador <em>id</em>
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
    void hacer_viaje_en_barco();

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