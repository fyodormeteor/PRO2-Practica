#include "Producto.hh"

Producto::Producto()
{
    cantidad = 0;
    necesidad = 1;
}

Producto::Producto(const int cant, const int necd)
{
    cantidad = cant;
    necesidad = necd;
}

void Producto::escribir() const
{
    cout << cantidad << ' ' << necesidad << endl;
}

int Producto::obtener_cantidad() const
{
    return cantidad;
}

int Producto::obtener_necesidad() const
{
    return necesidad;
}

int Producto::obtener_exceso() const
{
    return cantidad - necesidad;
}

void Producto::establecer_cantidad(const int cant)
{
    cantidad = cant;
}

void Producto::establecer_necesidad(const int necd)
{
    necesidad = necd;
}

void Producto::operator+=(const int cant)
{
    cantidad += cant;
}