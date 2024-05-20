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

#define ERR_CIUDADNOEXISTE          "no existe la ciudad"
#define ERR_PRODUCTONOEXISTE        "no existe el producto"
#define ERR_MISMOPRODUCTO           "no se puede comprar y vender el mismo producto"
#define ERR_CIUDADNOTIENEPRODUCTO   "la ciudad no tiene el producto"
#define ERR_CIUDADYATIENEPRODUCTO   "la ciudad ya tiene el producto"
#define ERR_CIUDADREPETIDA          "ciudad repetida"
#define ERR_COMANDOINVALIDO         "comando invalido"

/** @brief  Subrutina auxiliar para facilitar la escritura de errores.
*/
void Error(string mensaje)
{
    cout << "error: " << mensaje << endl;
}

/** @brief  Subrutina auxiliar para leer y quitar <em>n</em> elementos (double) del canal de entrada.
            Util para poder seguir con la ejecucion del programa despues de un caso erroneo.
\pre        n >= 0
*/
void Desechar(int n)
{
    double d;
    for(int i = 0; i < n; ++i) cin >> d;
}

/** @brief  Programa principal para el proyecto
*/
int main()
{
    Rio r = Rio();

    int prodcant;
    cin >> prodcant;
    r.leer_informacion_productos(prodcant);
    r.leer_cuenca();
    r.leer_barco();

    string command;
    cin >> command;

    while (command != "fin")
    {
        if (command == "leer_rio" or command == "lr")
        {
            cout << '#' << command << endl;
            
            r.leer_cuenca();
        }
        else if (command == "leer_inventario" or command == "li") 
        {
            string idciudad;
            int size_inventario;
            cin >> idciudad >> size_inventario;

            cout << '#' << command << ' ' << idciudad << endl;

            if (!r.existe_ciudad(idciudad))
            {
                Error(ERR_CIUDADNOEXISTE);
                Desechar(3*size_inventario);
            }
            // Caso sin errores
            else
            {
                r.reinicializar_inventario_de_ciudad(idciudad);
                for(int i = 0; i < size_inventario; ++i)
                {
                    r.leer_y_poner_producto_ciudad(idciudad);
                }
            }
        }
        else if (command == "leer_inventarios" or command == "ls") //*
        {
            // Se garantiza que las ciudades existen.

            cout << '#' << command << endl;
            
            string idciudad;
            cin >> idciudad;
            while (idciudad != "#")
            {
                int n;
                cin >> n;
                
                r.reinicializar_inventario_de_ciudad(idciudad);
                for(int i = 0; i < n; ++i)
                {
                    r.leer_y_poner_producto_ciudad(idciudad);
                }

                cin >> idciudad;
            }
        }
        else if (command == "modificar_barco" or command == "mb")
        {
            cout << '#' << command << endl;
            
            int comprarid, comprarcant, venderid, vendercant;
            cin >> comprarid >> comprarcant >> venderid >> vendercant;

            if      (!r.existe_producto(comprarid) or !r.existe_producto(venderid)) Error(ERR_PRODUCTONOEXISTE);
            else if (comprarid == venderid)                                         Error(ERR_MISMOPRODUCTO);
            // Caso sin errores
            else r.modificar_barco(comprarid, comprarcant, venderid, vendercant);
        }
        else if (command == "escribir_barco" or command == "eb")
        {
            cout << '#' << command << endl;
            
            r.escribir_barco();
        }
        else if (command == "consultar_num" or command == "cn")
        {
            cout << '#' << command << endl;
            
            cout << r.cantidad_de_productos() << endl;
        }
        else if (command == "agregar_productos" or command == "ap")
        {
            int prodcant;
            cin >> prodcant;
            cout << '#' << command << ' ' << prodcant << endl;

            r.leer_informacion_productos(prodcant);
        }
        else if (command == "escribir_producto" or command == "ep")
        {
            int idprod; 
            cin >> idprod;
            cout << '#' << command << ' ' << idprod << endl;

            if (r.existe_producto(idprod)) r.escribir_informacion_producto(idprod);
            // Caso erroneo
            else Error(ERR_PRODUCTONOEXISTE);
        }
        else if (command == "escribir_ciudad" or command == "ec")
        {
            string idciudad; 
            cin >> idciudad;
            cout << '#' << command << ' ' << idciudad << endl;

            if (r.existe_ciudad(idciudad)) r.escribir_ciudad(idciudad);
            // Caso erroneo
            else Error(ERR_CIUDADNOEXISTE);
        }
        else if (command == "poner_prod" or command == "pp")
        {
            string idciudad;
            int idprod, cant, necd;
            cin >> idciudad >> idprod >> cant >> necd;
            cout << '#' << command << ' ' << idciudad << ' ' << idprod << endl;

            if      (!r.existe_producto(idprod))                    Error(ERR_PRODUCTONOEXISTE);
            else if (!r.existe_ciudad(idciudad))                    Error(ERR_CIUDADNOEXISTE);
            else if (r.ciudad_tiene_producto(idciudad, idprod))     Error(ERR_CIUDADYATIENEPRODUCTO);
            // Caso sin errores
            else r.agregar_inventario_de_ciudad(idciudad, idprod, cant, necd);
        }
        else if (command == "modificar_prod" or command == "mp")
        {
            string idciudad;
            int idprod, cant, necd;
            cin >> idciudad >> idprod >> cant >> necd;
            cout << '#' << command << ' ' << idciudad << ' ' << idprod << endl;

            if      (!r.existe_producto(idprod))                    Error(ERR_PRODUCTONOEXISTE);
            else if (!r.existe_ciudad(idciudad))                    Error(ERR_CIUDADNOEXISTE);
            else if (!r.ciudad_tiene_producto(idciudad, idprod))    Error(ERR_CIUDADNOTIENEPRODUCTO);
            // Caso sin errores
            else r.modificar_inventario_de_ciudad(idciudad, idprod, cant, necd);
        }
        else if (command == "quitar_prod" or command == "qp")
        {
            string idciudad;
            int idprod;
            cin >> idciudad >> idprod;
            cout << '#' << command << ' ' << idciudad << ' ' << idprod << endl;

            if      (!r.existe_producto(idprod))                    Error(ERR_PRODUCTONOEXISTE);
            else if (!r.existe_ciudad(idciudad))                    Error(ERR_CIUDADNOEXISTE);
            else if (!r.ciudad_tiene_producto(idciudad, idprod))    Error(ERR_CIUDADNOTIENEPRODUCTO);
            // Caso sin errores
            else r.quitar_inventario_de_ciudad(idciudad, idprod);
        }
        else if (command == "consultar_prod" or command == "cp")
        {
            string idciudad;
            int idprod;
            cin >> idciudad >> idprod;
            cout << '#' << command << ' ' << idciudad << ' ' << idprod << endl;

            if      (!r.existe_producto(idprod))                    Error(ERR_PRODUCTONOEXISTE);
            else if (!r.existe_ciudad(idciudad))                    Error(ERR_CIUDADNOEXISTE);
            else if (!r.ciudad_tiene_producto(idciudad, idprod))    Error(ERR_CIUDADNOTIENEPRODUCTO);
            // Caso sin errores
            else r.escribir_producto_de_ciudad(idciudad, idprod);
        }
        else if (command == "comerciar" or command == "co")
        {
            string idciudad1, idciudad2;
            cin >> idciudad1 >> idciudad2;
            cout << '#' << command << ' ' << idciudad1 << ' ' << idciudad2 << endl;

            if      (!r.existe_ciudad(idciudad1) or !r.existe_ciudad(idciudad2))    Error(ERR_CIUDADNOEXISTE);
            else if (idciudad1 == idciudad2)                                        Error(ERR_CIUDADREPETIDA);
            // Caso sin errores
            else r.comerciar(idciudad1, idciudad2);
        }
        else if (command == "redistribuir" or command == "re")
        {
            cout << '#' << command << endl;
            
            r.redistribuir();
        }
        else if (command == "hacer_viaje" or command == "hv")
        {
            cout << '#' << command << endl;
            
            r.hacer_viaje_en_barco();
        }
        else if (command == "//")
        {
            string trash;
            getline(cin, trash);
        }
        else
        {
            Error(ERR_COMANDOINVALIDO);
        }

        cin >> command;
    }
}