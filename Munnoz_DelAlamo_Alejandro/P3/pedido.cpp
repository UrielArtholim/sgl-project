// Clase Pedido 
// Archivo CPP
// Alejandro Muñoz Del Álamo Copyright 2016

#include "pedido.hpp"
#include "tarjeta.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

// Clase Pedido 

// Inicialización de variable static de la clase Pedido 
int Pedido::NumPed = 0;

// Constructor
Pedido::Pedido(Usuario_Pedido& uP, Pedido_Articulo& pA, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha):
num_(NumPed+1), tarjeta_(&tarjeta), total_(0.0), f_ped_(fecha)
{
	if(usuario.compra().empty()) // Si el carro está vacío 
		throw Vacio(usuario);	 // lanza la excepción Pedido::Vacio 

	if (&usuario != tarjeta.titular()) 	// Si el usuario no es el titular de la tarjeta 
		throw Impostor(usuario);	   	// lanza la excepción Pedido::Impostor 

	if (f_ped_ > tarjeta.caducidad())					// Si la fecha introducida es mayor que la fecha de caducidad de la tarjeta 
		throw Tarjeta::Caducada(tarjeta.caducidad());	// lanza la excepción Tarjeta::Caducada 

	auto carrito = usuario.compra();

	for (auto i = carrito.begin(); i!= carrito.end(); i++)
	{
		if ((i->first)->stock() < i->second)
		{
			Articulo* articulo = i->first;
				
			auto j = usuario.compra().begin();
			while(j!= usuario.compra().end())
			{
				const_cast<Usuario::Articulos&>(usuario.compra()).clear();
				j = usuario.compra().begin();
			}
			throw SinStock(*articulo);
		}
	}
	// Si solo tenemos libros digitales pasados de fecha 
	if(usuario.compra().empty())
		throw Vacio(usuario);	 // lanza la excepción Pedido::Vacio 

	// Asociación entre Usuario y Pedido 
	uP.asocia(usuario, *this);
	uP.asocia(*this, usuario);

	// Asociación entre Pedido y Articulo 
	Usuario::Articulos carro = usuario.compra();
	for (auto c : carro)
	{
		pA.pedir(*this, *(c.first), (c.first)->precio(), c.second); // Asociamos el pedido al artículo 
		pA.pedir(*(c.first), *this, (c.first)->precio(), c.second);	// Asociamos el pedido al artículo 
		total_ = total_ + ((c.first)->precio() * c.second); // Obtenemos el total: Precio * Cantidad 
		//usuario.compra(*(c.first),0); // Actualizamos el carro de la compra 
		
		if(ArticuloAlmacenable* pArtAlm = dynamic_cast<ArticuloAlmacenable*>(c.first))
		{
			pArtAlm->stock() -= c.second; // Actualizamos el stock de la tienda 
			//(*c.first) = *pArtAlm;
		}
		usuario.compra(*c.first, 0);
	}

	const_cast<Usuario::Articulos&>(usuario.compra()).clear();
	NumPed++;
} 

// Métodos observadores 
int Pedido::numero() const 
{return num_;}

const Tarjeta* Pedido::tarjeta() const 
{return tarjeta_;}

Fecha Pedido::fecha() const 
{return f_ped_;}

double Pedido::total() const 
{return total_;}

int Pedido::n_total_pedidos() 
{return NumPed;}

std::ostream& operator << (std::ostream& os, const Pedido& pedido)
{
	return os << std::endl << "\tNúm. pedido:\t" << pedido.numero() 
			  << std::endl << "\tFecha:\t\t" << pedido.fecha() 
			  << std::endl << "\tPagado con:\t" << pedido.tarjeta()->tipo() << " n.º: " << pedido.tarjeta()->numero()
			  << std::endl << "\tImporte:\t" << std::fixed << std::setprecision(2) << pedido.total() << " €";
}


// Fin pedido.cpp