#include <iostream>
#include "Tienda.h"

// Constructor por defecto
Tienda::Tienda()
{
	this->nombre = "La Farra";
	this->contCodFactura = 1;
	TipoProducto licor("Licor", 0.19);
	TipoProducto snack("Snacks", 0.16);
	this->categorias[1] = licor;
	this->categorias[2] = snack;
	Producto productoUno(licor, "Cerveza", 2500, 1800, 100, 10);
	Producto productoDos(snack, "Papitas de limon margarita", 3000, 1000, 2, 50);
	Producto productoTres(snack, "Papitas de pollo margarita", 3000, 1000, 3, 50);

	// Inicializar valores de la tienda
	this->inventario[productoUno.getCodigo()] = productoUno;
	this->inventario[productoDos.getCodigo()] = productoDos;
	this->inventario[productoTres.getCodigo()] = productoTres;
}

bool Tienda::existeProductoPorCod(int codigo)
{
	// True si el mapa retorna un iterador diferente al iterador de fin de contenedor, esto significa
	// que existe. False en caso contrario.
	if (this->inventario.find(codigo) != this->inventario.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Tienda::agregarProducto()
{

	string nombre;
	float costo;
	float precio;
	int codigo;
	cout << "Ingrese el nombre del producto : ";
	getline(cin, nombre); // Mejor instruccion para recibir cadenas
	do
	{
		cout << "Ingrese el costo de compra del producto : ";
		cin >> costo;
		cout << "Ingrese el precio al que va a vender el producto : ";
		cin >> precio;
	} while (costo < 0 || precio < 0);

	bool existeProducto = true; // controlara que no existan productos con codigo repetido

	do
	{
		cout << "Ingrese la identificacion del producto : ";
		cin >> codigo;
		if (existeProductoPorCod(codigo))
		{
			existeProducto = false;
		}
	} while (existeProducto);

	// Terminada la validacion se agrega el producto

	Producto productoTemp;
	productoTemp.setNombre(nombre);
	productoTemp.setCosto(costo);
	productoTemp.setPrecio(precio);
	productoTemp.setCodigo(codigo);

	// Adición al mapa de productos
	inventario[codigo] = productoTemp;
	// Tambien se puede
	inventario.insert(std::pair<int, Producto>(codigo, productoTemp));
}

void Tienda::agregarDetalle(float &totalIVA, float &totalSinIVA, float &totalGeneral, Factura &factura)
{
	int codigo, cantidad;
	Producto productoTemp;
	float valorIVA, valorSinIVA, valorTotal;

	// Se busca el producto en el inventario.
	//Se pregunta hasta que se encuentre un producto con el codigo ingresado
	do
	{
		cout << "Ingrese el codigoProductoComprar \n";
		cin >> codigo;
	} while (!existeProductoPorCod(codigo)); // while(existeProductoPorCod(codigo) == false);
	productoTemp = this->inventario[codgio];
	// Se dispone de inventario para la venta
	Producto productoTemp = this->inventario[codigo]; // Se obtiene del mapa. Existe pq ya se hizo esta validacion
	do
	{
		cout << "Cuantos productos quiere comprar \n";
		cin >> cantidad;
	} while (cantidad <= 0 || cantidad > productoTemp.getCantUnidades()); // Cuando falla
	valorIVA = cantidad * productoTemp.getPrecio() * productoTemp.getTipoProducto().getIVA;
	valorSinIVA = cantidad * productoTemp.getPrecio();
	valorTotal = valorSinIVA + valorIVA;
	// Hago la venta
	float valorPagarIvaProd = cantidad *
							  productoTemp.getTipoProducto().getIva() * productoTemp.getPrecio();
	float valorPagarSinIVAProd = productoTemp.getPrecio() * cantidad;
	float valorTotalProd = valorPagarIvaProd + valorPagarSinIVAProd;

	cout << "lo que va";
	cout << valorPagarIvaProd << valorPagarSinIVAProd << valorTotalProd;

	// Agregan los datos al detalle de venta, aprovecho el constructor
	DetalleFactura detalle(productoTemp, cantidad, valorPagarSinIVAProd,
						   valorPagarIvaProd, valorTotalProd);

	// Agrega informacion a la factura
	factura.agregarDetalle(detalle);

	// Actualizar el acumulado total de la venta
	totalIVA += valorPagarIvaProd;
	totalGeneral += valorTotalProd;
	totalSinIVA += valorPagarSinIVAProd;

	// Disminuir a la cantidad de unidades vendidas al producto vendido
	this->inventario[codigo].setCantUnidades(productoTemp.getCantUnidades() - cantidad);
	this->gananciaTotal += calcularGanancia(productoTemp, cantidad);
}

void Tienda::vender()
{

	float totalIVA = 0, totalGeneral = 0;
	float totalSinIVA = 0;
	int opc = 0;
	Factura factura;
	string fecha;

	cout << "Ingrese la fecha de venta \n";
	cin >> fecha;
	factura.setFecha(fecha);

	// Asigno el codigo a la factura y luego actualizo el contador
	factura.setCod(this->contCodFactura++);
	do
	{
		cout << "Ingrese 1 para continuar la venta -1 para terminar \n";
		cin >> opc;

		if (opc != -1)
		{
			// Se llama  otra funcion que controla la adicion de productos
			// paso de parametros por referencia
			agregarDetalle(totalIVA, totalGeneral, totalSinIVA, factura);
		}

	} while (opc != -1); // -1 termina la venta

	// Se agregan los valores totales
	factura.setValorPagarSinIVA(totalSinIVA);
	factura.setValorTotalIVA(totalIVA);
	factura.setValorTotal(totalGeneral);

	// Se adiciona la factura a la coleccion para tener la lista de facturas
	facturas.push_back(factura);
	this->IVATotal += totalIVA;
}

void Tienda::mostrarFacturas()
{
	for (vector<Factura>::iterator pFactura = facturas.begin();
		 pFactura != facturas.end(); pFactura++)
	{
		pFactura->mostrarFactura();
	}
}

void Tienda::mostrarProductos()
{
	for (map<int, Producto>::iterator pProducto = inventario.begin();
		 pProducto != inventario.end(); pProducto++)
	{
		Producto valor = pProducto->second; // Se obtiene el valor asociado al mapa
		valor.mostrarProducto();
	}
}

void Tienda::mostrarProductosDisponibles()
{
	int cant;
	cout << "Ingrese la cantidad de productos: ";
	cin >> cant;
	for(map<int, Producto>::iterator pProducto = inventario.begin();
		 pProducto != inventario.end(); pProducto++)
		 Producto valor = pProducto->second;
		 if(valor.getCantUnidades()<-cant){
			 valor.mostrarProducto();
		 }
	}
}

float Tienda::calcularGanancia(Producto productoTemp, int cantidad)
{
	return (productoTemp.getPrecio() - productoTemp.getCosto())*cantidad;
}

void Tienda::mostrarValoresIVA()
{
	for (vector<Factura>::iterator pFactura = facturas.begin();
		 pFactura != facturas.end(); pFactura++)
	{
		pFactura->mostrarValorIVA();
	}
}

void Tienda::mostrarTipoProductosVendidos()
{
	int cantidadLicor = 0, cantidadSnack = 0;

	for (vector<Factura>::iterator pFactura = facturas.begin();
	 pFactura != facturas.end(); pFactura++)
	{
		for (vector<DetalleFactura>::iterator pDetalle = pFactura->getDetalles.begin();
	 	pDetalle != pFactura->getDetalles.end(); pDetalle++)
	 	{
			 if(detalle1.getProducto().getTipoProducto.getNombre == categorias[2].getNombre())
			 {
				 cantidadSnack += detalle1.getCantUnidVend();
			 }
			 if(detalle1.getProducto().getTipoProducto.getNombre == categorias[1].getNombre())
			 {
				 cantidadLicor += detalle1.getCantUnidVend();
			 }
		}
	}
	cout << "Numero de productos tipo " << categorias[tipo].getNombre() << " vendidos: " cantidad << ".\n";
	cout << "Numero de productos tipo " << categorias[tipo].getNombre() << " vendidos: " cantidad << ".\n";
}


string Tienda::getNombre()
{
	return nombre;
}