// Clase Pedido 
// Archivo HPP
// Alejandro Muñoz Del Álamo Copyright 2016


#ifndef PEDIDO_H_
#define PEDIDO_H_

#include "fecha.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include <iomanip>

class Tarjeta; 
class Usuario_Pedido;
class Pedido_Articulo;

// Clase Pedido 

class Pedido
{
public:

	// Clase Pedido::Vacio 
	class Vacio
	{
	public:

		Vacio(const Usuario& usuario) : usuario_(&usuario){}
		const Usuario& usuario() const {return *usuario_;}

	private:
		const Usuario* usuario_;
	};

	// Clase Pedido::Impostor 
	class Impostor
	{
	public:

		Impostor(const Usuario& usuario) : usuario_(&usuario){}
		const Usuario& usuario() const {return *usuario_;}

	private:
		const Usuario* usuario_;
	};

	// Clase Pedido::SinStock 
	class SinStock
	{
	public:

		SinStock(const Articulo& articulo) : articulo_(&articulo){}
		const Articulo& articulo() const {return *articulo_;}

	private:
		const Articulo* articulo_;
	};

	// Constructor 
	Pedido(Usuario_Pedido& uP, Pedido_Articulo& pA, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha = Fecha());

	// Métodos Observadores 
	int numero() const;
	const Tarjeta* tarjeta() const;
	Fecha fecha() const;
	double total() const;
	static int n_total_pedidos();

private:

	//Atributos
	static int NumPed;
	int num_;
	const Tarjeta* tarjeta_;
	double total_;
	Fecha f_ped_;

};

std::ostream& operator << (std::ostream& os, const Pedido& pedido);

#endif

// Fin pedido.hpp 