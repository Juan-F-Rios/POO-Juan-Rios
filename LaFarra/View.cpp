#include "View.h"

View::View()
{
}

void View::mostrarMenuReportes()
{
    int opcion = -1;
    do
    {

        cout << "Menu Reportes\n";
        cout << "1. Reporte según cantidad disponible de productos \n";
        cout << "2. Cantidad de productos tipo snack y licores vendidos \n";
        cout << "3. Ganancias obtenidas por la tienda \n";
        cout << "4. Ver todos los productos de la tienda \n";
        cout << "5. Valor a pagar por IVA a la DIAN \n"
        cout << "0. Salir \n";
        std::cout << "Digita el numero para volver al menu principal: ";
        std::cin >> opcion;

        switch (opcion)
        {

        case 1:
            laFarra.mostrarProductosDisponibles();
            break;
        case 2:
            laFarra.mostrarTipoProductosVendidos();
            break;

        case 3:
            cout << "Las ganancias obtenida por la tienda fueron de: " << laFarra.getGananciaTotal() << ".\n";
            break;

        case 4:
            laFarra.mostrarProductos();
            break;
        
        case 5:
            cout << "El valor a pagar por IVA a la DIAN es de: " << laFarra.getIVATotal() << ".\n";

        }

    } while (opcion != 0);
}

void View::mostrarMenu()
{
    int opcion = -1;
    do
    {

        cout << "Menu Tienda\n";
        cout << "1. Agregar Productos \n";
        cout << "2. Mostrar Productos \n";
        cout << "3. Vender \n";
        cout << "4. Mostrar Ventas \n";
        cout << "5. Reportes \n";
        cout << "0. Salir \n";
        std::cout << "Digita el numero: ";
        std::cin >> opcion;

        switch (opcion)
        {

        case 1:
            laFarra.agregarProducto();
            break;
        case 2:
            laFarra.mostrarProductos();
            break;

        case 3:
            laFarra.vender();
            break;

        case 4:
            laFarra.mostrarFacturas();
            break;

        case 5:
            mostrarMenuReportes();
            break;
        }

    } while (opcion != 0);
}