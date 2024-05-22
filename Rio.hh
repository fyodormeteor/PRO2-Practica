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
    
    BinTree<string> cuenca;
    Barco barco;
    
    map<string, Ciudad> nombre2ciudad;
    vector<pair<double,double>> id2infoprod;
    

    /** @brief  Auxiliar.
    \pre        El canal de entrada contiene una estructura arborea en pre-orden,
    \post       El resultado es un arbol binario con la estructura arborea,
                Se han creado nuevas instancias de Ciudad con los identificadores leidos
                del canal del entrada y se han guardado en un diccionario del parametro implicito
    \coste      *
    */
    BinTree<string> leer_cuenca_rec();

    /** @brief  Auxiliar.
    \pre        *
    \post       *
                *
    \coste      *
    */
    void redistribuir_rec(const BinTree<string>& b);

public:

// Constructores

    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       El resultado es un Rio vacio
    \coste      *
    */
    Rio();

// Operaciones de leer

    /** @brief  Lee una nueva estructura de ciudades desde el canal de entrada.
    \pre        El canal de entrada contiene una estructura arborea en pre-orden
    \post       El parametro implicito pasa a contener una nueva estructura arborea de nuevas instancias de Ciudad,
                Las nuevas instancias de Ciudad se han guardado en un diccionario del parametro implicito
                Barco se ha actualizado correctamente
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

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void leer_barco();

    /** @brief  *
    \pre        El canal de entrada contiene el id de un producto que existe (int >= 0) y cantidad & necesidad (2 double >= 0)
    \post       *
    \coste      *
    */
    void leer_y_poner_producto_ciudad(const string nombre);

// Operaciones con ciudades
    
    /** @brief  Comprueba si existe una ciudad con el identificador "nombre".
    \pre        <em>cierto</em>
    \post       El resultado indica si Ciudad con identificador <em>nombre</em> existe
    \coste      Logarithmic in size*
    */
    bool existe_ciudad(const string nombre) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void escribir_ciudad(const string nombre) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    bool ciudad_tiene_producto(const string nombre, const int idprod) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void escribir_producto_de_ciudad(const string nombre, const int idprod) const;

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void reinicializar_inventario_de_ciudad(const string nombre);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void agregar_inventario_de_ciudad(const string nombre, const int idprod, const int cant, const int necd);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void modificar_inventario_de_ciudad(const string nombre, const int idprod, const int cant, const int necd);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void quitar_inventario_de_ciudad(const string nombre, const int idprod);

// Operaciones con informacion de productos

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
    void escribir_informacion_producto(const int id) const;

    /** @brief  Consulta la cantidad de productos existentes.
    \pre        <em>cierto</em>
    \post       El resultado es la cantidad de productos
    \coste      *
    */
    int cantidad_de_productos() const;

// Operaciones con barco

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void modificar_barco(const int comprar_id, const int comprar_cantidad, const int vender_id, const int vender_cantidad);

    /** @brief  *
    \pre        *
    \post       *
    \coste      *
    */
    void escribir_barco();
    
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
    void comerciar(const string nombre1, const string nombre2);

    /** @brief  *
    \pre        Ciudades con identificador <em>nombre1</em> y <em>nombre2</em> existen
    \post       *
    \coste      *
    */
    void redistribuir();
};

#endif