/* Clase Articulo */
/* Archivo HPP*/
/* Alejandro Muñoz Del Álamo Copyright 2017*/

#ifndef ARTICULO_H
#define ARTICULO_H

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iomanip>
#include <set>


class Articulo
{
public:

	// Constructor de Artículo
	explicit Articulo(Cadena cad_ref, Cadena cad_tit, Fecha fec_pub, double coste, unsigned cantidad);

	// Métodos observadores
	Cadena referencia() const {return referencia_;}
	Cadena titulo() const {return titulo_;}
	Fecha f_publi() const {return f_publi_;}
	double precio() const {return precio_;}
	unsigned stock() const {return stock_;}

	// Métodos modificadores
	double precio() {return precio_;}
	unsigned stock() {return stock_;}


private:

	// Atributos
	Cadena referencia_, titulo_;
	Fecha f_publi_;
	double precio_;
	unsigned stock_;

};

std::ostream& operator << (std::ostream& os, const Articulo& art);

#endif // ARTICULO_H