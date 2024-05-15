#include "Rio.hh"

Rio::Rio() 
{
    cuenca = BinTree<string>();
    barco = Barco();
    nombre2ciudad = map<string, Ciudad>();
    id2infoprod = vector<pair<double,double>>();
}

void Rio::leer_cuenca()
{
    nombre2ciudad.clear(); // Limpiar mapa
    cuenca = leer_cuenca_rec();
}

BinTree<string> Rio::leer_cuenca_rec() // Recursiva
{
    string idciudad;
    cin >> idciudad;

    // Caso base
    if (idciudad == "#")
    {
        return BinTree<string>();
    }
    // Caso recursivo
    Ciudad c = Ciudad(idciudad);
    nombre2ciudad[idciudad] = c;

    auto tree_left = leer_cuenca_rec();
    auto tree_right = leer_cuenca_rec();

    return BinTree<string>(idciudad, tree_left, tree_right);
}

void Rio::leer_informacion_productos(const int cantidad)
{
    for (int i = 0; i < cantidad; ++i)
    {
        double p, v;
        cin >> p >> v;
        pair<double, double> info(p, v);
        id2infoprod.push_back(info);
    }
}

Barco Rio::barco_del_rio() const
{
    return barco;
}

bool Rio::existe_ciudad(const string nombre) const
{
    int n = nombre2ciudad.count(nombre); // .count() Logaritmico
    if (n == 1) return true;
    return false;
}

Ciudad Rio::ciudad_con_nombre(const string nombre) const
{
    return nombre2ciudad.at(nombre); // .at() no puede modificar el mapa, en cambio, operator[] si.
}

void Rio::leer_y_poner_producto_ciudad(Ciudad& ciudad)
{
    int idprod, cant, necd;
    cin >> idprod >> cant >> necd;

    double peso = peso_del_producto(idprod);
    double volumen = volumen_del_producto(idprod);
    ciudad.agregar_inventario(idprod, peso, volumen, cant, necd);
}

bool Rio::existe_producto(const int id) const
{
    return (id < cantidad_de_productos());
}

double Rio::peso_del_producto(const int id) const
{
    return id2infoprod[id].first;
}

double Rio::volumen_del_producto(const int id) const
{
    return id2infoprod[id].second;
}

void Rio::escribir_producto(const int id) const
{
    cout << peso_del_producto(id) << ' ' << volumen_del_producto(id) << endl;
}

int Rio::cantidad_de_productos() const
{
    return id2infoprod.size();
}

void Rio::hacer_viaje_en_barco()
{
    barco.hacer_viaje(cuenca, nombre2ciudad);
}

void Rio::comerciar(const string nombre1, const string nombre2)
{
    Ciudad c1 = ciudad_con_nombre(nombre1);
    Ciudad c2 = ciudad_con_nombre(nombre2);
    
    c1.comerciar_con(c2, id2infoprod);
}

void Rio::redistribuir()
{
    if (cuenca.empty()) return;
    redistribuir_rec(cuenca);
}

void Rio::redistribuir_rec(const BinTree<string>& b)
{
    Ciudad c = nombre2ciudad.at(b.value());

    if (!b.left().empty())
    {
        Ciudad c1 = nombre2ciudad.at(b.left().value());
        c.comerciar_con(c1, id2infoprod);
        redistribuir_rec(b.left());
    }

    if (!b.right().empty())
    {
        Ciudad c2 = nombre2ciudad.at(b.right().value());
        c.comerciar_con(c2, id2infoprod);
        redistribuir_rec(b.right());
    }
}