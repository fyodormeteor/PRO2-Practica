#include "Ciudad.hh"

Ciudad::Ciudad()
{
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
        cout << id+1 << ' ';
        escribir_producto(id+1);

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
    if (inventario.count(id-1) == 1) return true;
    return false;
}

void Ciudad::escribir_producto(int id) const
{
    inventario.at(id-1).escribir();
}

void Ciudad::reinicializar_inventario()
{
    inventario.clear(); // .clear() Linear in size
    peso_total = .0;
    volumen_total = .0;
}

void Ciudad::agregar_inventario(const int idprod, const double peso, const double volumen, const int cantidad, const int necesidad)
{
    inventario[idprod-1] = Producto(cantidad, necesidad);
    peso_total += peso*cantidad;
    volumen_total += volumen*cantidad;
}

void Ciudad::modificar_inventario(const int idprod, const double peso, const double volumen, const int cantidad, const int necesidad)
{
    peso_total -= cantidad_de_producto_en_inventario(idprod)*peso;
    volumen_total -= cantidad_de_producto_en_inventario(idprod)*volumen;

    inventario[idprod-1].establecer_cantidad(cantidad);
    inventario[idprod-1].establecer_necesidad(necesidad);

    peso_total += cantidad*peso;
    volumen_total += cantidad*volumen;
}

void Ciudad::quitar_inventario(const int idprod, const double peso, const double volumen)
{
    peso_total -= cantidad_de_producto_en_inventario(idprod)*peso;
    volumen_total -= cantidad_de_producto_en_inventario(idprod)*volumen;
    
    inventario.erase(idprod-1); // .erase(key) Logarithmic in size
}

int Ciudad::cantidad_de_producto_en_inventario(const int idprod) const
{
    return inventario.at(idprod-1).obtener_cantidad();
}

int Ciudad::necesidad_de_producto_en_inventario(const int idprod) const
{
    return inventario.at(idprod-1).obtener_necesidad();
}

int Ciudad::exceso_de_producto_en_inventario(const int idprod) const
{
    return inventario.at(idprod-1).obtener_exceso();
}

int Ciudad::comprar_producto(const int idprod, int& cantidad_disponible, const double peso, const double volumen)
{

}

int Ciudad::vender_producto(const int idprod, int& cantidad_disponible, const double peso, const double volumen)
{

}

void Ciudad::comerciar_con(Ciudad& c, const vector<pair<double,double>>& id2infoprod)
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
            int c1_exceso = it1->second.obtener_exceso();
            int c2_exceso = it2->second.obtener_exceso();

            // 2 casos:
            //     - Ambas ciudades quieren o les sobra el producto:      no hacer nada
            //     - Una ciudad quiere el producto y a la otra le sobra:  hacer comercio

            if (c1_exceso < 0 and c2_exceso > 0) // Ciudad implicita quiere y a Ciudad c le sobra
            {
                int cantidad_comerciada = min(c2_exceso, -c1_exceso);

                it1->second += cantidad_comerciada;
                it2->second += -cantidad_comerciada;

                cambio_peso += cantidad_comerciada * id2infoprod[it1->first].first;
                cambio_volumen += cantidad_comerciada * id2infoprod[it1->first].second;
            }

            if (c2_exceso < 0 and c1_exceso > 0) // Ciudad c quiere y a Ciudad implicita le sobra
            {
                int cantidad_comerciada = min(c1_exceso, -c2_exceso);

                it1->second += -cantidad_comerciada;
                it2->second += cantidad_comerciada;

                cambio_peso -= cantidad_comerciada * id2infoprod[it1->first].first;
                cambio_volumen -= cantidad_comerciada * id2infoprod[it1->first].second;
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