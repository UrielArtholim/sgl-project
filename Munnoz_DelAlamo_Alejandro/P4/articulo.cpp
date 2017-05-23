// Clase Artículo 
// Archivo CPP
// Alejandro Muñoz Del Álamo Copyright 2017

#include "articulo.hpp"
#include <iomanip>

// Métodos Clase Artículo 
// Constructor 
Articulo::Articulo(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio): 
autores_(autores),referencia_(ref), titulo_(tit), f_publi_(fpub), precio_(precio)
{
	if(autores.empty())
		throw Autores_vacios();
}
// Operador de Inserción 
std::ostream& operator << (std::ostream& os, const Articulo& art)
{
	os << "[" << art.referencia().c_str() << "] \"" << art.titulo().c_str() << "\", de ";

	Articulo::Autores::const_iterator it = art.autores().cbegin();

	while(it!= art.autores().cend())
	{
		os << (*it)->apellidos().c_str();
		++it;
		if (it != art.autores().cend())
			os << ", ";
	}

	os << ". " << art.f_publi().anno() << ". " 	<< std::fixed << std::setprecision(2) << art.precio() << " €\n\t";
	art.impresion_especifica(os);
	return os;
}

// Métodos Clase ArticuloAlmacenable 
// Constructor 
ArticuloAlmacenable::ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio, size_t stock):
Articulo(autores, ref, tit, fpub, precio), stock_(stock){}

// Métodos Clase Libro 
// Constructor 
Libro::Libro(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio, size_t num_pag, size_t stock):
ArticuloAlmacenable(autores, ref, tit, fpub, precio, stock), n_pag_(num_pag){}

// Método de impresión especifica 
void Libro::impresion_especifica(std::ostream& os) const noexcept
{
	os  << n_pag_ << " págs., " << stock_ << " unidades.";
}

// Métodos Clase Cederron 
// Constructor 
Cederron::Cederron(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio, size_t tam, size_t stock):
ArticuloAlmacenable(autores, ref, tit, fpub, precio, stock), tam_(tam){}

// Método de impresión especifica 
void Cederron::impresion_especifica(std::ostream& os) const noexcept
{
	os << tam_ << " MB, " << stock_ << " unidades.";
}

// Métodos Clase LibroDigital 
// Constructor 
LibroDigital::LibroDigital(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio, const Fecha& fecha_cadu):
Articulo(autores, ref, tit, fpub, precio), f_expir_(fecha_cadu){}

// Método de impresión especifica 
void LibroDigital::impresion_especifica(std::ostream& os) const 
{
	os << "A la venta hasta el " << f_expir_ << ".";
}

// Fin Clase LibroDigital 

//Fin articulo.cpp 