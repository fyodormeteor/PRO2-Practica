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

public:
    
    /** @brief Es usado para contener informacion auxiliar necesaria para realizar la operacion 'hacer_viaje'.
    */
    struct InfoViaje
    {
        /** @brief Almacena la altura. Cuanto menor la 'altura', mas corta es la ruta.
        */
        int altura;

        /** @brief Almacena la compra acumulada. Es la cantidad total que el Barco podra comprar en toda la ruta.
        */
        int compra_acumulada;

        /** @brief Almacena la venta acumulada. Es la cantidad total que el Barco podra vender en toda la ruta.
        */
        int venta_acumulada;

        /** @brief Almacena la compra. Es la cantidad que el Barco puede comprar en una Ciudad particular de la ruta.
        */
        int compra;

        /** @brief Almacena la venta. Es la cantidad que el Barco puede vender en una Ciudad particular de de la ruta.
        */
        int venta;
        
        /** @brief Constructora por defecto.
        */
        InfoViaje()
        {
            altura = 0;
            compra = 0;
            venta  = 0;
            compra_acumulada = 0;
            venta_acumulada = 0;
        }

        /** @brief El "potencial" es igual a la suma de la compra y venta total de la ruta.
        */
        int potencial() const
        {
            return compra_acumulada+venta_acumulada;
        }
    };
    
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

    /** @brief  Metodo auxiliar para la operacion 'hacer_viaje'.
                Es usado para obtener un arbol auxiliar que dirigirá el barco hacia la "mejor" ruta.
    \pre        <em>cierto</em>
    \post       Los nodos del arbol son instancias del struct auxiliar InfoViaje.
                Contienen informacion sobre la cantidad que el Barco
                puede comprar/vender en la Ciudad de esa posicion de la cuenca.
                Tambien contiene informacion sobre la compra/venta acumulada
                para poder tomar la ruta donde, en total, se compra y se vende la cantidad maxima.
                Tambien contiene informacion sobre la 'altura' de la Ciudad,
                para distinguir entre 2 rutas que son igual de provechosas pero una es mas corta que otra.
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
};

#endif