#include "Rio.hh"

Rio::Rio() 
{
    cuenca = BinTree<string>();
    barco = Barco();
    nombre2ciudad = map<string, Ciudad>();
    id2infoprod = vector<pair<int,int>>();
}

void Rio::leer_cuenca()
{
    nombre2ciudad.clear(); // Limpiar mapa de ciudades
    cuenca = leer_cuenca_rec();
    barco.reinicializar_cronologia(); // Limpiar cronologia del barco de la cuenca anterior
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
    nombre2ciudad[idciudad] = Ciudad();

    auto tree_left = leer_cuenca_rec();
    auto tree_right = leer_cuenca_rec();

    return BinTree<string>(idciudad, tree_left, tree_right);
}

void Rio::leer_informacion_productos(const int cantidad)
{
    for (int i = 0; i < cantidad; ++i)
    {
        int p, v;
        cin >> p >> v;
        id2infoprod.push_back(make_pair(p, v));
    }
}

void Rio::leer_barco()
{
    barco.leer();
}

void Rio::leer_y_poner_producto_ciudad(const string nombre)
{
    int idprod, cant, necd;
    cin >> idprod >> cant >> necd;

    int p = peso_del_producto(idprod);
    int v = volumen_del_producto(idprod);
    nombre2ciudad[nombre].agregar_inventario(idprod, p, v, cant, necd);
}

bool Rio::existe_ciudad(const string nombre) const
{
    int n = nombre2ciudad.count(nombre); // .count() Logaritmico
    if (n == 1) return true;
    return false;
}

void Rio::escribir_ciudad(const string nombre) const
{
    nombre2ciudad.at(nombre).escribir();
}

bool Rio::ciudad_tiene_producto(const string nombre, const int idprod) const
{
    return nombre2ciudad.at(nombre).existe_producto_en_inventario(idprod);
}

void Rio::escribir_producto_de_ciudad(const string nombre, const int idprod) const
{
    nombre2ciudad.at(nombre).escribir_producto(idprod);
}

void Rio::reinicializar_inventario_de_ciudad(const string nombre)
{
    nombre2ciudad[nombre].reinicializar_inventario();
}

void Rio::agregar_inventario_de_ciudad(const string nombre, const int idprod, const int cant, const int necd)
{
    int p = peso_del_producto(idprod);
    int v = volumen_del_producto(idprod);
    nombre2ciudad[nombre].agregar_inventario(idprod, p, v, cant, necd);
    nombre2ciudad[nombre].escribir_peso_y_volumen();
}

void Rio::modificar_inventario_de_ciudad(const string nombre, const int idprod, const int cant, const int necd)
{
    int p = peso_del_producto(idprod);
    int v = volumen_del_producto(idprod);
    nombre2ciudad[nombre].modificar_inventario(idprod, p, v, cant, necd);
    nombre2ciudad[nombre].escribir_peso_y_volumen();
}

void Rio::quitar_inventario_de_ciudad(const string nombre, const int idprod)
{
    int p = peso_del_producto(idprod);
    int v = volumen_del_producto(idprod);
    nombre2ciudad[nombre].quitar_inventario(idprod, p, v);
    nombre2ciudad[nombre].escribir_peso_y_volumen();
}

bool Rio::existe_producto(const int id) const
{
    return (id-1 < cantidad_de_productos());
}

int Rio::peso_del_producto(const int id) const
{
    return id2infoprod[id-1].first;
}

int Rio::volumen_del_producto(const int id) const
{
    return id2infoprod[id-1].second;
}

void Rio::escribir_informacion_producto(const int id) const
{
    cout << id << ' ' << peso_del_producto(id) << ' ' << volumen_del_producto(id) << endl;
}

int Rio::cantidad_de_productos() const
{
    return id2infoprod.size();
}

void Rio::modificar_barco(const int comprar_id, const int comprar_cantidad, const int vender_id, const int vender_cantidad)
{
    barco.modificar(comprar_id, comprar_cantidad, vender_id, vender_cantidad);
}

void Rio::escribir_barco()
{
    barco.escribir();
}

void Rio::hacer_viaje_en_barco()
{
    barco.hacer_viaje(cuenca, nombre2ciudad, id2infoprod);
}

void Rio::comerciar(const string nombre1, const string nombre2)
{
    nombre2ciudad[nombre1].comerciar_con(nombre2ciudad[nombre2], id2infoprod);
}

void Rio::redistribuir()
{
    if (cuenca.empty()) return;
    redistribuir_rec(cuenca);
}

void Rio::redistribuir_rec(const BinTree<string>& b)
{
    string c = b.value();

    if (!b.left().empty())
    {
        string c1 = b.left().value();
        comerciar(c, c1);
        redistribuir_rec(b.left());
    }

    if (!b.right().empty())
    {
        string c2 = b.right().value();
        comerciar(c, c2);
        redistribuir_rec(b.right());
    }
}