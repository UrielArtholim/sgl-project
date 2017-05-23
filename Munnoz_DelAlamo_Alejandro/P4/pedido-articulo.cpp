/* Clase Pedido-Articulo */
/* Archivo CPP*/
/* Alejandro Muñoz Del Álamo Copyright 2016*/

#include "pedido-articulo.hpp"
#include <iomanip>
   
/* Clase LineaPedido */
/* Constructor */
LineaPedido::LineaPedido( double precioVenta, unsigned cantidad):
	precioVenta_(precioVenta), cantidad_(cantidad) 
{}

/* Métodos Observadores */
double LineaPedido::precio_venta() const{
	return precioVenta_;
}

unsigned LineaPedido::cantidad() const{
	return cantidad_;
}

/* Operador de Inserción */
std::ostream& operator << (std::ostream& os, const LineaPedido& linea)
{
	return os << std::fixed << std::setprecision(2) << linea.precio_venta()
			  << " €\t" << linea.cantidad();
}

/* Fin Clase LineaPedido */

/* Clase Pedido_Articulo */
/* Métodos Modificadores: Asociacion*/
void Pedido_Articulo::pedir (Pedido& p, Articulo& a, double precio, unsigned cantidad)
{
	LineaPedido lp(precio, cantidad);
	ped_art[&p].insert( std::make_pair(&a, lp));
	art_ped[&a].insert( std::make_pair(&p, lp));
}

void Pedido_Articulo::pedir (Articulo& a, Pedido& p, double precio, unsigned cantidad)
{
	pedir(p,a,precio,cantidad);
}	

/* Métodos Observadores */
Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p)
{return ped_art[&p];}	

Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& a)
{return art_ped[&a];}

/* Metodos de Insercion*/
void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
	double total=0.0;
	double ventas=0.0;
	for(auto i: ped_art)
	{
		os << std::endl << "Pedido num. " << (i.first)->numero() << std::endl;
		os << "Cliente: " << (((i.first)->tarjeta())->titular())->nombre() << "\t\rFecha: " << (i.first)->fecha() << std::endl
		   << "==============================================================================" << std::endl
		   << "PVP\t Cantidad\t Artículo" << std::endl
		   << "==============================================================================" << std::endl ;
		for ( Pedido_Articulo::ItemsPedido::const_iterator j = (i.second).begin(); j!=(i.second).end(); j++)
		{
			os << (j->second).precio_venta() <<" €\t" << (j->second).cantidad() << "\t\t[" << (j->first)->referencia()
			   << "] \"" << (j->first)->titulo() <<(j->second).cantidad() << "\"" << std::endl;
			total += ((j->second).precio_venta())*((j->second).cantidad());
			ventas += ((j->second).precio_venta())*((j->second).cantidad());
		}
		os << "==============================================================================" << std::endl
		   << "Total: " << ventas << " €" << std::endl << std::endl;
	    ventas = 0.0;
	}
	os << "\n TOTAL VENTAS \t" << std::fixed << std::setprecision(2) << total << " €" << std::endl;

}
	
void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
	double ventas = 0;
	unsigned int cantidad = 0;
	for(auto i: art_ped){
		os << std::endl << " Ventas de " << "[" << (i.first)->referencia() << "]" << " \"" << (i.first)->titulo() << "\""
		<< " [Pedidos: " << (i.second).size() << "]" << std::endl 
		<< "==============================================================================" << std::endl
		<<  "PVP\tCantidad\tFecha de venta" << std::endl
		<< "==============================================================================" << std::endl
		;
		for(Pedido_Articulo::Pedidos::const_iterator j = (i.second).begin(); j!= (i.second).end(); j++){
			os << (j->second).precio_venta() << " €\t" << (j->second).cantidad() << "\t\t" << (j->first)->fecha() << std::endl;
			ventas += ( (j->second).precio_venta())*((j->second).cantidad());
			cantidad += (j->second).cantidad();
		}
		os << "==============================================================================" << std::endl
		<< ventas << " €\t" << cantidad << std::endl << std::endl;
		ventas = cantidad = 0;
	}
}

/* Operadores de Insercion*/
std::ostream& operator << ( std::ostream& os, const Pedido_Articulo::ItemsPedido& itPedido){
	int ejemplares=0;
	double total=0.0;
	os << "\tCant.\tPrecio\tArticulo" << std::endl
	   << "==============================================================================" << std::endl;
	for(auto i: itPedido){
		os << "\t" << (i.second).cantidad() << "\t" << std::fixed << std::setprecision(2)
		   << (i.second).precio_venta() << " €\t" << *(i.first) << std::endl;
		ejemplares += (i.second).cantidad();
		total += ( (i.second).cantidad() * (i.second).precio_venta() );
	}
	
	return os << "==============================================================================" 
	<< std::endl << "Total   " << total <<" €";
}

std::ostream& operator << (std::ostream& os, const Pedido_Articulo::Pedidos& pedidos){
	double total=0.0;
	os << "\tCant.\tPrecio\tFecha" << std::endl
	   << "==============================================================================" << std::endl;
	for(auto i: pedidos){
		os << "\t" << (i.second).cantidad() << "\t" << std::fixed << std::setprecision(2)
		   << (i.second).precio_venta() << " €\t" << (i.first)->fecha() << std::endl;
		total += ( (i.second).cantidad() * (i.second).precio_venta() );
	}
	return os << "\tTotal: " << total <<" €";
}
