#include "Barco.hh"

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

void Barco::hacer_viaje(const BinTree<string>& cuenca, map<string, Ciudad>& nombre2ciudad, const vector<pair<double,double>> id2infoprod)
{
    if (!ini)
    {
        cout << "Barco no esta inicializado" << endl;
        return;
    }

    auto arbol_aux = hacer_viaje_arbol_aux(cuenca, nombre2ciudad, comprar_cantidad, vender_cantidad);

    double pes_com = id2infoprod.at(comprar_id-1).first;
    double vol_com = id2infoprod.at(comprar_id-1).second;
    double pes_ven = id2infoprod.at(vender_id-1).first;
    double vol_ven = id2infoprod.at(vender_id-1).second;

    string ultima_ciudad = "";

    if (arbol_aux.value().altura > 0)
        hacer_viaje_modificar_ciudades(cuenca, nombre2ciudad, arbol_aux, pes_com, vol_com, pes_ven, vol_ven, ultima_ciudad);

    cronologia.push_back(ultima_ciudad);

    cout << arbol_aux.value().compra_acumulada << ' ' << arbol_aux.value().venta_acumulada << endl;
}

void Barco::hacer_viaje_modificar_ciudades
(const BinTree<string>& cuenca, map<string, Ciudad>& nombre2ciudad, const BinTree<InfoViaje>& aux,
 double pes_com, double vol_com, double pes_ven, double vol_ven, string& id_ciudad)
{
    id_ciudad = cuenca.value();

    if (aux.value().compra > 0)
        nombre2ciudad.at(id_ciudad).vender_producto (comprar_id, aux.value().compra, pes_com, vol_com);

    if (aux.value().venta > 0)
        nombre2ciudad.at(id_ciudad).comprar_producto(vender_id , aux.value().venta , pes_ven, vol_ven);

    if (aux.value().altura > 1)
    {
        if(aux.left().value().potencial() > aux.right().value().potencial())
        {
            hacer_viaje_modificar_ciudades(cuenca.left(), nombre2ciudad, aux.left(), pes_com, vol_com, pes_ven, vol_ven, id_ciudad);
        }
        else if(aux.left().value().potencial() < aux.right().value().potencial())
        {
            hacer_viaje_modificar_ciudades(cuenca.right(), nombre2ciudad, aux.right(), pes_com, vol_com, pes_ven, vol_ven, id_ciudad);
        }
        else
        {
            if (aux.left().value().altura > aux.right().value().altura)
            {
                hacer_viaje_modificar_ciudades(cuenca.right(), nombre2ciudad, aux.right(), pes_com, vol_com, pes_ven, vol_ven, id_ciudad);
            }
            if (aux.left().value().altura <= aux.right().value().altura) //?
            {
                hacer_viaje_modificar_ciudades(cuenca.left(), nombre2ciudad, aux.left(), pes_com, vol_com, pes_ven, vol_ven, id_ciudad);
            }
        }
    }
}

BinTree<InfoViaje> Barco::hacer_viaje_arbol_aux
(const BinTree<string>& cuenca, const map<string, Ciudad>& nombre2ciudad, int potencial_comprar, int potencial_vender)
{
    InfoViaje v = InfoViaje();
    // Casos base:
    //     - La cuenca esta vacia
    //     - No queda más potencial de vender/comprar (es decir se han acabado los productos que el barco puede comerciar)

    if (cuenca.empty())                                     return BinTree<InfoViaje>(v);
    if (potencial_comprar <= 0 and potencial_vender <= 0)   return BinTree<InfoViaje>(v);

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
           3 casos:
               - Potencial izq. >  Potencial der.
                    'altura' es la altura del subarbol izq. + 1
                    'compra_acumulada' es la suma de la compra acumulada del subarbol izq. y la compra del nodo.
                    (Similarmente con 'venta_acumulada')
  
               - Potencial izq. <  Potencial der.
                    'altura' es la altura del subarbol der. + 1
                    'compra_acumulada' es la suma de la compra acumulada del subarbol der. y la compra del nodo.
                    (Similarmente con 'venta_acumulada')

               - Potencial izq. == Potencial der.
                    'altura' del nodo es la altura minima de los dos subarboles + 1
                    'compra_acumulada' es la suma de la compra acumulada del subarbol con menor altura y la compra del nodo.
                    (Similarmente con 'venta_acumulada')
                    (Si las dos alturas son iguales, se escoge el subarbol izq.)
        
        */
    
    if (l.value().potencial() > r.value().potencial())
    {
        v.altura = l.value().altura + 1;
        v.compra_acumulada = l.value().compra_acumulada + v.compra;
        v.venta_acumulada  = l.value().venta_acumulada + v.venta;
    }
    else if (l.value().potencial() < r.value().potencial())
    {
        v.altura = r.value().altura + 1;
        v.compra_acumulada = r.value().compra_acumulada + v.compra;
        v.venta_acumulada  = r.value().venta_acumulada + v.venta;
    }
    else
    {
        v.altura = min(l.value().altura, l.value().altura) + 1;
        if (l.value().altura > r.value().altura)
        {
            v.compra_acumulada = r.value().compra_acumulada + v.compra;
            v.venta_acumulada  = r.value().venta_acumulada + v.venta;
        }
        else if (l.value().altura <= r.value().altura)
        {
            v.compra_acumulada = l.value().compra_acumulada + v.compra;
            v.venta_acumulada  = l.value().venta_acumulada + v.venta;
        }
    }

    return BinTree<InfoViaje>(v, l, r);
}

