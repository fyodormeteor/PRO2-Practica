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
    @brief El Rio es la clase principal del programa.
    
    Maneja la estructura arborea de la cuenca, contiene las instancias de Ciudad, y contiene un Barco que puede hacer viajes.
    La clase Rio tambien almacena todos los pesos y volumenes de los productos que se han definido.
*/

class Rio {

private:
    
    /** @brief Almacena la estructura arborea de las ciudades. Los nodos del arbol corresponden al identificador de la Ciudad.
    */
    BinTree<string> cuenca;

    /** @brief Almacena la instancia de Barco perteneciente al rio.
    */
    Barco barco;
    
    /** @brief Almacena la instancias de Ciudad. El key del mapa corresponde al identificador de Ciudad.
    */
    map<string, Ciudad> nombre2ciudad;

    /** @brief Almacena la informacion (peso, volumen) de los productos. [id].first es el peso, [id].second es el volumen.
     *         Cada nueva informacion de producto tendra su id correlativo a partir del ultimo existente, empezando por id = 0.
    */
    vector<pair<int,int>> id2infoprod;
    

    /** @brief  Metodo auxiliar para la operacion 'leer_rio'.
    \pre        El canal de entrada contiene una estructura arborea en pre-orden
    \post       El resultado es un arbol binario con la estructura arborea,
                Se han creado nuevas instancias de Ciudad con los identificadores leidos
                del canal del entrada y se han guardado en un diccionario del parametro implicito
    \coste      Lineal
    */
    BinTree<string> leer_cuenca_rec();

    /** @brief  Metodo auxiliar para la operacion 'redistribuir'.
    \pre        La cuenca no esta vacia
    \post       Cada Ciudad ha comerciado con las dos ciudades situadas rio arriba hasta llegar a las Ciudades de los nacimientos
    \coste      Cuadratico
    */
    void redistribuir_rec(const BinTree<string>& b);

public:

// Constructores

    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       El resultado es un Rio vacio
    \coste      Constante
    */
    Rio();

// Operaciones de leer

    /** @brief  Lee una nueva estructura de ciudades desde el canal de entrada.
    \pre        El canal de entrada contiene una estructura arborea en pre-orden
    \post       El parametro implicito pasa a contener una nueva estructura arborea de nuevas instancias de Ciudad,
                Las nuevas instancias de Ciudad se han guardado en un diccionario del parametro implicito
                Barco se ha actualizado correctamente (se ha eliminado su cronologia de la cuenca anterior)
    \coste      Lineal
    */
    void leer_cuenca();

    /** @brief  Lee la informacion de productos desde el canal de entrada.
    \pre        El canal de entrada contiene <em>cantidad</em> parejas de pesos y volumenes
    \post       El parametro implicito pasa a contener la nueva informacion de productos,
                Los identificadores de los nuevos productos son correlativos a partir del ultimo producto existente antes de la operacion
    \coste      Lineal
    */
    void leer_informacion_productos(const int cantidad);

    /** @brief  Lee la informacion del barco desde el canal de entrada.
    \pre        El canal de entrada contiene 4 enteros: comprar_id, comprar_cantidad, vender_id, vender_cantidad
    \post       Barco se ha actualizado correctamente
    \coste      Constante
    */
    void leer_barco();

    /** @brief  Lee la informacion de un producto y lo pone en el inventario de la ciudad.
    \pre        El canal de entrada contiene el id de un producto que existe y cantidad (int >= 0) & necesidad (int > 0)
    \post       Ciudad con id <em>nombre</em> pasa a contener el nuevo producto
    \coste      Logaritmico
    */
    void leer_y_poner_producto_ciudad(const string nombre);

// Operaciones con ciudades
    
    /** @brief  Comprueba si existe una ciudad.
    \pre        <em>cierto</em>
    \post       El resultado indica si Ciudad con identificador <em>nombre</em> existe
    \coste      Logaritmico
    */
    bool existe_ciudad(const string nombre) const;

    /** @brief  Escribe los contenidos del inventario, peso total y volumen total de la ciudad.
    \pre        Ciudad con id <em>nombre</em> existe
    \post       Se han escrito al canal de salida el inventario y peso_total & volumen_total de la Ciudad
    \coste      Logaritmico
    */
    void escribir_ciudad(const string nombre) const;

    /** @brief  Comprueba si una ciudad tiene un producto.
    \pre        Ciudad con id <em>nombre</em> existe
    \post       El resultado indica si Ciudad <em>nombre</em> tiene el Producto <em>idprod</em>
    \coste      Logaritmico
    */
    bool ciudad_tiene_producto(const string nombre, const int idprod) const;

    /** @brief  Escribe la cantidad y necesidad de un producto dentro del inventario de una ciudad.
    \pre        Ciudad con id <em>nombre</em> existe y tiene Producto con id <em>idprod</em> en su inventario
    \post       Se han escrito al canal de salida la cantidad & necesidad del Producto
    \coste      Logaritmico
    */
    void escribir_producto_de_ciudad(const string nombre, const int idprod) const;

    /** @brief  Borra los contenidos del inventario de una ciudad.
    \pre        Ciudad con id <em>nombre</em> existe
    \post       El inventario de Ciudad <em>nombre</em> esta vacio, peso_total y volumen_total de la Ciudad son 0
    \coste      Lineal
    */
    void reinicializar_inventario_de_ciudad(const string nombre);

    /** @brief  Añade un producto al inventario de una ciudad.
    \pre        Ciudad con id <em>nombre</em> existe y no tiene Producto con id <em>idprod</em>,
                informacion de producto con id <em>idprod</em> existe
    \post       El inventario de Ciudad <em>nombre</em> pasa a tener un nuevo Producto con atributos <em>cant</em> y <em>necd</em>,
                atributos peso_total y volumen_total de Ciudad <em>nombre</em> se han actualizado correctamente
    \coste      Logaritmico
    */
    void agregar_inventario_de_ciudad(const string nombre, const int idprod, const int cant, const int necd);

    /** @brief  Modifica un producto del inventario de una ciudad.
    \pre        Ciudad con id <em>nombre</em> existe y tiene Producto con id <em>idprod</em>,
                informacion de producto con id <em>idprod</em> existe
    \post       El Producto <em>idprod</em> de Ciudad <em>nombre</em> pasa a tener nuevos atributos <em>cant</em> y <em>necd</em>,
                atributos peso_total y volumen_total de Ciudad <em>nombre</em> se han actualizado correctamente
    \coste      Logaritmico
    */
    void modificar_inventario_de_ciudad(const string nombre, const int idprod, const int cant, const int necd);

    /** @brief  Elimina un producto del inventario de una ciudad.
    \pre        Ciudad con id <em>nombre</em> existe y tiene Producto con id <em>idprod</em>,
                informacion de producto con id <em>idprod</em> existe
    \post       El Producto <em>idprod</em> de Ciudad <em>nombre</em> se ha eliminado,
                atributos peso_total y volumen_total de Ciudad <em>nombre</em> se han actualizado correctamente
    \coste      Logaritmico
    */
    void quitar_inventario_de_ciudad(const string nombre, const int idprod);

// Operaciones con informacion de productos

    /** @brief  Comprueba si existe la informacion de un producto.
    \pre        <em>cierto</em>
    \post       El resultado indica si existe la informacion de un producto con identificador <em>id</em>
    \coste      Constante
    */
    bool existe_producto(const int id) const;

    /** @brief  Consulta el peso de un producto.
    \pre        Informacion de producto con identificador <em>id</em> existe
    \post       El resultado es el peso de un producto con identificador <em>id</em>
    \coste      Constante
    */
    int peso_del_producto(const int id) const;

    /** @brief  Consulta el volumen de un producto.
    \pre        Informacion de producto con identificador <em>id</em> existe
    \post       El resultado es el volumen de un producto con identificador <em>id</em>
    \coste      Constante
    */
    int volumen_del_producto(const int id) const;

    /** @brief  Escribe la informacion (peso, volumen) de un producto.
    \pre        Informacion de producto con identificador <em>id</em> existe
    \post       Se ha escrito al canal de salida la informacion de un producto (peso, volumen) con identificador <em>id</em>
    \coste      Constante
    */
    void escribir_informacion_producto(const int id) const;

    /** @brief  Consulta la cantidad de productos existentes.
    \pre        <em>cierto</em>
    \post       El resultado es la cantidad de productos que tienen su informacion (peso y volumen) definida
    \coste      Constante
    */
    int cantidad_de_productos() const;

// Operaciones con barco

    /** @brief  Modifica los atributos del barco del rio.
    \pre        Productos con id <em>comprar_id</em> y <em>vender_id</em> existen,
                <em>comprar_cantidad</em> >= 0, <em>vender_cantidad</em> >= 0,
                <em>comprar_cantidad</em> + <em>vender_cantidad</em> > 0
    \post       Barco pasa a tener los nuevos atributos
    \coste      Constante
    */
    void modificar_barco(const int comprar_id, const int comprar_cantidad, const int vender_id, const int vender_cantidad);

    /** @brief  Escribe la informacion del barco del rio junto a su cronologia de viajes.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos (comprar_id, vender_id, comprar_cantidad, vender_cantidad)
                y la cronologia de viajes del Barco
    \coste      Lineal
    */
    void escribir_barco();
    
    /** @brief  El barco encuentra la "mejor" ruta en la cuenca y hace el viaje.
    \pre        <em>cierto</em>
    \post       El Barco ha hecho el viaje sobre la cuenca, modificando las ciudades, y actualizando su cronologia,
                Se ha escrito al canal de salida las unidades de productos que el Barco ha conseguido comprar/vender en la ruta
    */
    void hacer_viaje_en_barco();

    /** @brief  Efectua un comercio entre dos ciudades.
    \pre        Ciudad con id <em>nombre1</em> existe, Ciudad con id <em>nombre2</em> existe,
                <em>nombre1</em> != <em>nombre2</em>
    \post       Ciudad <em>nombre1</em> le ha dado todos los productos que le sobran a Ciudad <em>nombre2</em> hasta alcanzar,
                si es posible los que la Ciudad <em>nombre2</em> necesita, y viceversa.
    \coste      Lineal
    */
    void comerciar(const string nombre1, const string nombre2);

    /** @brief  Cada ciudad efectua comercio con las dos ciudades situadas rio arriba, recursivamente.
    \pre        <em>cierto</em>
    \post       Cada Ciudad ha comerciado con las dos ciudades situadas rio arriba hasta llegar a las Ciudades de los nacimientos
    \coste      Cuadratico
    */
    void redistribuir();
};

#endif