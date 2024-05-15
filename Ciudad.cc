#include "Ciudad.hh"

Ciudad::Ciudad(string nombre)
{
    this->nombre = nombre;

    peso_total = .0;
    volumen_total = .0;
}

void Ciudad::escribir_peso_y_volumen() const
{
    cout << peso_total << ' ' << volumen_total << endl;
}

void Ciudad::escribir_inventario() const
{
    map<int,Producto>::const_iterator it = inventario.begin();

    while(it != inventario.end())
    {
        int id = it->first;
        Producto p = it->second;

        cout << id << ' ';
        p.escribir();

        it++;
    }
}

void Ciudad::escribir() const
{
    escribir_inventario();
    escribir_peso_y_volumen();
}

bool Ciudad::existe_producto_en_inventario(const int id) const
{
    if (inventario.count(id) == 1) return true;
    return false;
}

void Ciudad::comerciar_con(Ciudad& c, const vector<pair<double,double>>& id2prodinfo)
{
    map<int,Producto>::iterator it1 = inventario.begin();
    map<int,Producto>::iterator it2 = c.inventario.begin();

    double cambio_peso = .0;
    double cambio_volumen = .0;

    while(it1 != inventario.end() and it2 != c.inventario.end())
    {
        // 3 casos:
        //     - Ambos iteradores apuntan a productos con identificadores iguales:  intentar comerciar el producto
        //     - Iterador 1 apunta a un producto con identificador mas grande:      aumentar iterador 2
        //     - Iterador 2 apunta a un producto con identificador mas grande:      aumentar iterador 1

        if (it1->first == it2->first)
        {
            Producto p1 = it1->second;
            Producto p2 = it2->second;

            int c1_exceso = p1.obtener_exceso();
            int c2_exceso = p2.obtener_exceso();

            // 2 casos:
            //     - Ambas ciudades quieren o les sobra el producto:      no hacer nada
            //     - Una ciudad quiere el producto y a la otra le sobra:  hacer comercio

            if (c1_exceso < 0 and c2_exceso > 0) // Ciudad implicita quiere y a Ciudad c le sobra
            {
                int cantidad_comerciada = min(c2_exceso, -c1_exceso);

                p1 += cantidad_comerciada;
                p2 += -cantidad_comerciada;

                cambio_peso += cantidad_comerciada * id2prodinfo[it1->first].first;
                cambio_volumen += cantidad_comerciada * id2prodinfo[it1->first].second;
            }

            if (c2_exceso < 0 and c1_exceso > 0) // Ciudad c quiere y a Ciudad implicita le sobra
            {
                int cantidad_comerciada = min(c1_exceso, -c2_exceso);

                p1 += -cantidad_comerciada;
                p2 += cantidad_comerciada;

                cambio_peso -= cantidad_comerciada * id2prodinfo[it1->first].first;
                cambio_volumen -= cantidad_comerciada * id2prodinfo[it1->first].second;
            }

            it1++;
            it2++;
        }
        else if (it1->first > it2->first) it2++;
        else it1++;
    }

    // No se crean nuevos productos:
    // es decir, la suma de los pesos y volumenes de ambas ciudades se mantiene constante durante el comercio

    peso_total += cambio_peso;
    volumen_total += cambio_volumen;
    c.peso_total -= cambio_peso;
    c.volumen_total -= cambio_volumen;
}