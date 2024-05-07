/**
 * @mainpage Ejemplo de diseño modular:  Gestión de una lavadora.
 
En este ejemplo se construye un programa modular que ofrece un menú de opciones para gestionar una lavadora.
Se introducen las clases <em>Lavadora</em>, <em>Cubeta</em> y <em>Prenda</em>.

Sólo se documentan elementos públicos. En una próxima sesión se verá un ejemplo
de proyecto completamente documentado, incluyendo los elementos privados.
*/

/** @file program.cc
    @brief Programa principal para el proyecto *
*/

#include "Rio.hh"
#include "Ciudad.hh"
#include "Barco.hh"

#ifndef NO_DIAGRAM 
#include <string>
#endif

/** @brief Subrutina auxiliar para facilitar la escritura de errores
*/
void Error()
{
    cout << "#ERROR# ";
}

/** @brief Programa principal para *
*/
int main()
{
    Rio r = Rio();

    r.leer_informacion_productos();
    r.leer_cuenca();
    r.leer_barco();

    string command;
    cin >> command;

    while (command != "fin")
    {
        if (command == "leer_rio" or command == "lr")
        {
            r.leer_cuenca();
        }
        else if (command == "leer_inventario" or command == "li")
        {
            string idciudad;
            cin >> idciudad;
            if (r.existe_ciudad(idciudad))
            {
                Ciudad c = r.ciudad_con_id(idciudad);
                c.leer_inventario();
            }
            else
            {
                Error();
                cout << "Ciudad con identificador " << idciudad << " no existe." << endl;
            }
        }
        else if (command == "leer_inventarios" or command == "ls")
        {
            string idciudad;
            cin >> idciudad;
            while (idciudad != "#")
            {
                if (r.existe_ciudad(idciudad))
                {
                    Ciudad c = r.ciudad_con_id(idciudad);
                    c.leer_inventario();
                }
                else
                {
                    Error();
                    cout << "Ciudad con identificador " << idciudad << " no existe." << endl;
                }
                cin >> idciudad;
            }  
        }
        else if (command == "modificar_barco" or command == "mb")
        {
            int comprarid, comprarcant, venderid, vendercant;
            cin >> comprarid >> comprarcant >> venderid >> vendercant;
            if (!r.existe_producto(comprarid) or !r.existe_producto(venderid))
            {
                Error();
                cout << "Producto no existe." << endl;
            }
            else if (comprarid == venderid)
            {
                Error();
                cout << "Los productos no pueden ser iguales." << endl;
            }
            else
            {
                Barco b = r.barco_del_rio();
                b.modificar(comprarid, comprarcant, venderid, vendercant);
            }
        }
        else if (command == "escribir_barco" or command == "eb")
        {
            Barco b = r.barco_del_rio();
            b.escribir();
        }
        else if (command == "consultar_num" or command == "cn")
        {
            cout << r.cantidad_de_productos() << endl;
        }
        else if (command == "agregar_productos" or command == "ap")
        {
            int prodcant;
            cin >> prodcant;
            for(int i = 0; i < prodcant; ++i)
            {
                int peso, volumen;
                cin >> peso >> volumen;
                r.agregar_producto(peso, volumen);
            }
        }
        else if (command == "escribir_producto" or command == "ep")
        {
            int idprod; 
            cin >> idprod;
            if (r.existe_producto(idprod))
            {
                r.escribir_producto(idprod);
            }
            else
            {
                Error();
                cout << "Producto con identificador " << idprod << " no existe." << endl;
            }
        }
        else if (command == "escribir_ciudad" or command == "ec")
        {
            string idciudad; 
            cin >> idciudad;
            if (r.existe_ciudad(idciudad))
            {
                Ciudad c = r.ciudad_con_id(idciudad);
                c.escribir();
            }
            else
            {
                Error();
                cout << "Ciudad con identificador " << idciudad << " no existe." << endl;
            }
        }
        else if (command == "poner_prod" or command == "pp")
        {
            string idciudad;
            int idprod, cant, necd;
            cin >> idciudad >> idprod >> cant >> necd;

            if (!r.existe_producto(idprod))
            {
                Error();
                cout << "Producto con identificador " << idprod << " no existe." << endl; 
            }
            else if (!r.existe_ciudad(idciudad))
            {
                Error();
                cout << "Ciudad con identificador " << idciudad << " no existe." << endl; 
            }
            else
            {
                Ciudad c = r.ciudad_con_id(idciudad);
                if (c.existe_producto_en_inventario(idprod))
                {
                    Error();
                    cout << "El producto " << idprod << " ya existe en el inventario de la ciudad con identificador " << idciudad << endl;
                }
                else
                {
                    c.agregar_inventario(idprod, cant, necd);
                }
            }
        }
        else if (command == "modificar_prod" or command == "mp")
        {
            string idciudad;
            int idprod, cant, necd;
            cin >> idciudad >> idprod >> cant >> necd;

            if (!r.existe_producto(idprod))
            {
                Error();
                cout << "Producto con identificador " << idprod << " no existe." << endl; 
            }
            else if (!r.existe_ciudad(idciudad))
            {
                Error();
                cout << "Ciudad con identificador " << idciudad << " no existe." << endl; 
            }
            else
            {
                Ciudad c = r.ciudad_con_id(idciudad);
                if (!c.existe_producto_en_inventario(idprod))
                {
                    Error();
                    cout << "El producto " << idprod << " no existe en el inventario de la ciudad con identificador " << idciudad << endl;
                }
                else
                {
                    c.modificar_inventario(idprod, cant, necd);
                }
            }
        }
        else if (command == "quitar_prod" or command == "qp")
        {
            string idciudad;
            int idprod;
            cin >> idciudad >> idprod;

            if (!r.existe_producto(idprod))
            {
                Error();
                cout << "Producto con identificador " << idprod << " no existe." << endl; 
            }
            else if (!r.existe_ciudad(idciudad))
            {
                Error();
                cout << "Ciudad con identificador " << idciudad << " no existe." << endl; 
            }
            else
            {
                Ciudad c = r.ciudad_con_id(idciudad);
                if (!c.existe_producto_en_inventario(idprod))
                {
                    Error();
                    cout << "El producto " << idprod << " no existe en el inventario de la ciudad con identificador " << idciudad << endl;
                }
                else
                {
                    c.quitar_inventario(idprod);
                }
            }
        }
        else if (command == "consultar_prod" or command == "cp")
        {
            string idciudad;
            int idprod;
            cin >> idciudad >> idprod;

            if (!r.existe_producto(idprod))
            {
                Error();
                cout << "Producto con identificador " << idprod << " no existe." << endl; 
            }
            else if (!r.existe_ciudad(idciudad))
            {
                Error();
                cout << "Ciudad con identificador " << idciudad << " no existe." << endl; 
            }
            else
            {
                Ciudad c = r.ciudad_con_id(idciudad);
                if (!c.existe_producto_en_inventario(idprod))
                {
                    Error();
                    cout << "El producto " << idprod << " no existe en el inventario de la ciudad con identificador " << idciudad << endl;
                }
                else
                {
                    Producto p = c.producto_con_id(idprod);
                    p.escribir();
                }
            }
        }
        else if (command == "comerciar" or command == "co")
        {
            string idciudad1, idciudad2;
            cin >> idciudad1 >> idciudad2;

            if (r.existe_ciudad(idciudad1) and r.existe_ciudad(idciudad2))
            {
                r.comerciar(idciudad1, idciudad2);
            }
            else
            {
                Error();
                cout << "Alguna de las dos (o las dos) ciudades no existen." << endl;
            }
        }
        else if (command == "redistribuir" or command == "re")
        {
            r.redistribuir();
        }
        else if (command == "hacer_viaje" or command == "hv")
        {
            r.hacer_viaje();
        }
        else
        {
            Error();
            cout << "Comando invalido." << endl;
        }

        cin >> command;
    }
}