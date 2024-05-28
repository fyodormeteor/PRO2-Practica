/** @file Barco.hh
    @brief Especificación de la clase Barco
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include "Ciudad.hh"
#include <iostream>
#include <list>
#include <map>
#endif

using namespace std;

/** @class Barco
    @brief Un Barco puede hacer viajes sobre una cuenca de la clase Rio.

    Siempre es almacenado dentro de una instancia de clase Rio.
    Almacena el identificador y la cantidad de un Producto que quiere comprar, y similarmente con otro Producto que quiere vender.
    Emplea una estructura auxiliar InfoViaje para la busqueda de la "mejor" ruta en la cuenca, para poder hacer viajes
    donde el Barco intenta maximizar la cantidad vendida/comprada en las instancias de Ciudad de la cuenca.
*/

class Barco {

private:
    
    /** @brief Indica si el barco esta inicializado.
    */
    bool ini;
    
    /** @brief Almacena el identificador del Producto que el Barco quiere comprar.
    */
    int comprar_id;

    /** @brief Almacena el identificador del Producto que el Barco quiere vender.
    */
    int vender_id;

    /** @brief Almacena la cantidad del Producto que el Barco quiere comprar.
    */
    int comprar_cantidad;

    /** @brief Almacena la cantidad del Producto que el Barco quiere vender.
    */
    int vender_cantidad;

    /** @brief Almacena las ultimas ciudades visitadas en los viajes que ha hecho el Barco.
    */
    list<string> cronologia;

    /** @brief Es usado para contener informacion auxiliar necesaria para realizar la operacion 'hacer_viaje'.
    */  
    struct InfoViaje;

    /** @brief  Metodo auxiliar para la operacion 'hacer_viaje'.
                Es usado para obtener un arbol auxiliar que dirigirá el barco hacia la "mejor" ruta.

            Los nodos contienen informacion sobre la cantidad que el Barco
            puede comprar/vender en la Ciudad de esa posicion de la cuenca.
            Tambien contienen informacion sobre la compra/venta acumulada
            para poder tomar la ruta donde, en total, se compra y se vende la cantidad maxima.
            Tambien contienen informacion sobre la 'altura' de la Ciudad,
            para distinguir entre 2 rutas que son igual de provechosas pero una es mas corta que otra.

    \pre        <em>cierto</em>
    \post       Los nodos del arbol son instancias del struct auxiliar InfoViaje,
                El tamaño de arbol auxiliar es menor o igual al tamaño de la cuenca
    */
    BinTree<InfoViaje> hacer_viaje_arbol_aux
    (const BinTree<string>& cuenca, const map<string, Ciudad>& nombre2ciudad, int potencial_comprar, int potencial_vender) const;

    /** @brief  Metodo auxiliar para la operacion 'hacer_viaje'.
                Es usado para recorrer la cuenca, empleando el arbol de InfoViaje, para modificar las ciudades y obtener la ultima Ciudad visitada.
    \pre        <em>cierto</em>
    \post       Las ciudades de la cuenca que forman parte de la "mejor" ruta se han modificado correctamente,
                <em>id_ciudad</em> pasa a contener la ultima ciudad donde el Barco ha comerciado
    */
    void hacer_viaje_modificar_ciudades
    (const BinTree<string>& cuenca, map<string, Ciudad>& nombre2ciudad, const BinTree<InfoViaje>& aux,
     int pes_com, int vol_com, int pes_ven, int vol_ven, string& id_ciudad) const;

public:
    
    /** @brief  Creadora por defecto.
    \pre        <em>cierto</em>
    \post       El resultado es un Barco no inicializado
    \coste      Constante
    */
    Barco();
    
    /** @brief  Lee la informacion del barco.
    \pre        En el canal de entrada estan preparados 4 enteros IDCOMPRAR, CANTCOMPRAR, IDVENDER, CANTVENDER,
                informacion de productos con id IDCOMPRAR y IDVENDER existen,
                CANTCOMPRAR >= 0, CANTVENDER >= 0, CANTCOMPRAR + CANTVENDER > 0
    \post       El parametro implicito pasa a tener comprar_id = IDCOMPRAR, comprar_cantidad = CANTCOMPRAR, vender_id = IDVENDER, vender_cantidad = CANTVENDER
    \coste      Constante
    */
    void leer();
    
    /** @brief  Escribe la informacion del barco junto a su cronologia de viajes.
    \pre        <em>cierto</em>
    \post       Se han escrito al canal de salida los atributos (comprar_id, vender_id, comprar_cantidad, vender_cantidad)
                y la cronologia de viajes del parametro implicito
    \coste      Lineal
    */
    void escribir() const;

    /** @brief  Modifica los atributos del barco.
    \pre        Informacion de productos con id <em>comprar_id</em> y <em>vender_id</em> existen,
                <em>comprar_cantidad</em> >= 0, <em>vender_cantidad</em> >= 0,
                <em>comprar_cantidad</em> + <em>vender_cantidad</em> > 0
    \post       El parametro implicito pasa a tener los nuevos atributos
    \coste      Constante
    */
    void modificar(const int comprar_id, const int comprar_cantidad, const int vender_id, const int vender_cantidad);

    /** @brief  Elimina la cronologia del barco.
    \pre        <em>cierto</em>
    \post       La cronologia esta vacia
    \coste      Lineal
    */
    void reinicializar_cronologia();

    /** @brief  Encuentra la "mejor" ruta de la cuenca y hace el viaje.
    \pre        <em>cierto</em>
    \post       El Barco ha hecho el viaje sobre la cuenca, modificando las ciudades, y actualizando su cronologia,
                Se ha escrito al canal de salida las unidades de productos que el Barco ha conseguido comprar/vender en la ruta
    */
    void hacer_viaje(const BinTree<string>& cuenca, map<string, Ciudad>& nombre2ciudad, const vector<pair<int,int>> id2infoprod);

};

#endif