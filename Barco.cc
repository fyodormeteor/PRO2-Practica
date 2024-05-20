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
}

