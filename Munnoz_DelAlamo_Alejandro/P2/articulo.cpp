/* Clase Articulo */
/* Archivo CPP*/
/* Alejandro Muñoz Del Álamo Copyright 2017 */

#include "articulo.hpp"

//Constructor de Artículo
Articulo::Articulo(Cadena cad_ref, Cadena cad_tit, Fecha fec_pub, double coste, unsigned cantidad):
				   referencia_(cad_ref), titulo_(cad_tit), f_publi_(fec_pub), precio_(coste), stock_(cantidad){}


//Operador de inserción
std::ostream& operator << (std::ostream& os, const Articulo& art)
{
	os << "[" << art.referencia().c_str() << "] \"" << art.titulo().c_str() << "\", " << art.f_publi() << ". " << art.precio() << " €" << endl;

	return os;
}