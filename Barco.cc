/** @file Barco.cc
    @brief Implementación de la clase Barco
*/

#include "Barco.hh"

struct Barco::InfoViaje
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

Barco::Barco()
{
    ini = false;
    cronologia = list<string>();
}

void Barco::leer()
{
    ini = true;
    cin >> comprar_id >> comprar_cantidad >> vender_id >> vender_cantidad;
}

void Barco::escribir() const
{
    if (!ini)
    {
        cout << "Barco no esta inicializado" << endl;
        return;
    }
    
    cout << comprar_id << ' ' << comprar_cantidad << ' ' << vender_id << ' ' << vender_cantidad << endl;

    list<string>::const_iterator it = cronologia.begin();
    while (it != cronologia.end())
    {
        cout << *it << endl;
        it++;
    }
}

void Barco::modificar(const int comprar_id, const int comprar_cantidad, const int vender_id, const int vender_cantidad)
{
    ini = true;

    this->comprar_id = comprar_id;
    this->comprar_cantidad = comprar_cantidad;
    this->vender_id = vender_id;
    this->vender_cantidad = vender_cantidad;
}

void Barco::reinicializar_cronologia()
{
    cronologia.clear(); // .clear() Linear in size
}

void Barco::hacer_viaje(const BinTree<string>& cuenca, map<string, Ciudad>& nombre2ciudad, const vector<pair<int,int>> id2infoprod)
{
    if (!ini)
    {
        cout << "Barco no esta inicializado" << endl;
        return;
    }

    auto arbol_aux = hacer_viaje_arbol_aux(cuenca, nombre2ciudad, comprar_cantidad, vender_cantidad);

    int pes_com = id2infoprod.at(comprar_id-1).first;
    int vol_com = id2infoprod.at(comprar_id-1).second;
    int pes_ven = id2infoprod.at(vender_id-1).first;
    int vol_ven = id2infoprod.at(vender_id-1).second;

    string ultima_ciudad = "";

    if (!arbol_aux.empty() and arbol_aux.value(). InfoViaje::altura != 0)
        hacer_viaje_modificar_ciudades(cuenca, nombre2ciudad, arbol_aux, pes_com, vol_com, pes_ven, vol_ven, ultima_ciudad);

    if (arbol_aux.value(). InfoViaje::potencial() != 0) cronologia.push_back(ultima_ciudad);

    cout << arbol_aux.value(). InfoViaje::potencial() << endl;
}

void Barco::hacer_viaje_modificar_ciudades
(const BinTree<string>& cuenca, map<string, Ciudad>& nombre2ciudad, const BinTree<InfoViaje>& aux,
 int pes_com, int vol_com, int pes_ven, int vol_ven, string& id_ciudad) const
{
    Barco::InfoViaje in = aux.value();
    
    if (in.compra > 0 or in.venta > 0)
    {
        id_ciudad = cuenca.value();

        if (in.compra > 0)
            nombre2ciudad.at(id_ciudad). Ciudad::vender_producto (comprar_id, in.compra, pes_com, vol_com);

        if (in.venta > 0)
            nombre2ciudad.at(id_ciudad). Ciudad::comprar_producto(vender_id , in.venta , pes_ven, vol_ven);
    }

    if (in.altura > 1)
    {
        Barco::InfoViaje il = aux.left().value();
        Barco::InfoViaje ir = aux.right().value();
        
        if (il.potencial() > ir.potencial())
        {
            hacer_viaje_modificar_ciudades(cuenca.left(), nombre2ciudad, aux.left(), pes_com, vol_com, pes_ven, vol_ven, id_ciudad);
        }
        else if (il.potencial() < ir.potencial())
        {
            hacer_viaje_modificar_ciudades(cuenca.right(), nombre2ciudad, aux.right(), pes_com, vol_com, pes_ven, vol_ven, id_ciudad);
        }
        else
        {
            if (il.altura > ir.altura)
            {
                hacer_viaje_modificar_ciudades(cuenca.right(), nombre2ciudad, aux.right(), pes_com, vol_com, pes_ven, vol_ven, id_ciudad);
            }
            else if (il.altura <= ir.altura)
            {
                hacer_viaje_modificar_ciudades(cuenca.left(), nombre2ciudad, aux.left(), pes_com, vol_com, pes_ven, vol_ven, id_ciudad);
            }
        }
    }
}

BinTree<Barco::InfoViaje> Barco::hacer_viaje_arbol_aux
(const BinTree<string>& cuenca, const map<string, Ciudad>& nombre2ciudad, int potencial_comprar, int potencial_vender) const
{
    Barco::InfoViaje v = Barco::InfoViaje();
    // Casos base:
    //     - La cuenca esta vacia
    //     - No queda más potencial de vender/comprar (es decir se han acabado los productos que el barco puede comerciar)

    if (cuenca.empty())                                     return BinTree<InfoViaje>();
    if (potencial_comprar <= 0 and potencial_vender <= 0)   return BinTree<InfoViaje>();

    // Caso recursivo:

        // Calculo de la cantidad que se podra comprar/vender en la Ciudad del nodo con las 'unidades restantes' en el barco (potencial_comprar/vender).
        // Las ciudades no se ven modificadas dentro de estos calculos.

    Ciudad c = nombre2ciudad.at(cuenca.value());

    v.compra = 0;
    if (c.existe_producto_en_inventario(comprar_id))
    {
        int exceso = c.exceso_de_producto_en_inventario(comprar_id);
        if (exceso > 0)
        {
            if (exceso <= potencial_comprar) v.compra = exceso;
            else v.compra = potencial_comprar;
        }
    }

    v.venta = 0;
    if (c.existe_producto_en_inventario(vender_id))
    {
        int exceso = c.exceso_de_producto_en_inventario(vender_id);
        if (exceso < 0)
        {
            exceso = abs(exceso);
            if (exceso <= potencial_vender) v.venta = exceso;
            else v.venta = potencial_vender;
        }
    }

        // Llamadas rec. en post-orden para obtener los subarboles auxiliares usando el potencial actualizado

    auto l = hacer_viaje_arbol_aux(cuenca.left() , nombre2ciudad, potencial_comprar-v.compra, potencial_vender-v.venta);
    auto r = hacer_viaje_arbol_aux(cuenca.right(), nombre2ciudad, potencial_comprar-v.compra, potencial_vender-v.venta);

        /* Calculo de los atributos del nodo (InfoViaje)
           4 casos:
               - Potencial izq. == Potencial der. == 0
                    Si no se compra/vende nada en el nodo, 'altura' es 0. En caso contrario 'altura' es 1.
                    'compra_acumulada' es la compra del nodo.
                    (Similarmente con 'venta_acumulada')

               - Potencial izq. >  Potencial der.
                    'altura' es la altura del subarbol izq. + 1
                    'compra_acumulada' es la suma de la compra acumulada del subarbol izq. y la compra del nodo.
                    (Similarmente con 'venta_acumulada')
  
               - Potencial izq. <  Potencial der.
                    'altura' es la altura del subarbol der. + 1
                    'compra_acumulada' es la suma de la compra acumulada del subarbol der. y la compra del nodo.
                    (Similarmente con 'venta_acumulada')

               - Potencial izq. == Potencial der. != 0
                    'altura' del nodo es la altura minima de los dos subarboles + 1
                    'compra_acumulada' es la suma de la compra acumulada del subarbol con menor altura y la compra del nodo.
                    (Similarmente con 'venta_acumulada')
        */
    
    int lpot = 0;
    if (!l.empty()) lpot = l.value(). InfoViaje::potencial();

    int rpot = 0;
    if (!r.empty()) rpot = r.value(). InfoViaje::potencial();

    if (lpot == 0 and rpot == 0)
    {    
        v.altura = 0;
        v.compra_acumulada = v.compra;
        v.venta_acumulada = v.venta;
        if (v.potencial() > 0) v.altura = 1;
    }
    else if (lpot > rpot)
    {
        v.altura = l.value().altura + 1;
        v.compra_acumulada = l.value(). InfoViaje::compra_acumulada + v.compra;
        v.venta_acumulada  = l.value(). InfoViaje::venta_acumulada + v.venta;
    }
    else if (lpot < rpot)
    {
        v.altura = r.value().altura + 1;
        v.compra_acumulada = r.value(). InfoViaje::compra_acumulada + v.compra;
        v.venta_acumulada  = r.value(). InfoViaje::venta_acumulada + v.venta;
    }
    else
    {
        v.altura = min(l.value().altura, r.value().altura) + 1;
        if (l.value().altura > r.value().altura)
        {
            v.compra_acumulada = r.value(). InfoViaje::compra_acumulada + v.compra;
            v.venta_acumulada  = r.value(). InfoViaje::venta_acumulada + v.venta;
        }
        else if (l.value().altura <= r.value().altura)
        {
            v.compra_acumulada = l.value(). InfoViaje::compra_acumulada + v.compra;
            v.venta_acumulada  = l.value(). InfoViaje::venta_acumulada + v.venta;
        }
    }

    return BinTree<InfoViaje>(v, l, r);
}

