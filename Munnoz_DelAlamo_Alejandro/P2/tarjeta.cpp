/* Clases Numero y Tarjeta */
/* Archivo CPP*/
/* Alejandro Muñoz Del Álamo Copyright 2017 */


#include "tarjeta.hpp"
#include "articulo.hpp"
#include "usuario.hpp"
#include <cctype> 		// Biblioteca necesaria para usar el método isdigit()
#include <algorithm>	// Biblioteca necesaria para usar funciones lambda[]
#include <functional>

//Algoritmo Luhn
bool luhn (const Cadena& numero, size_t n);

//Constructor de Numero
Numero::Numero(const Cadena& digitos)
{
	Cadena n((digitos));

	auto i = std::remove_if(n.begin(), n.end(), [](char c) {return std::isspace(c);}); /* Esta función hace que los espacios en la cadena queden al final */
	*i = '\0'; /* Incluimos el caracter terminador en la cadena */

	auto f = std::find_if(n.begin(), n.end(),[](char a) {return std::negate<int>(isdigit(a));}); /* Esta funcion comprueba que todos los caracteres de la cadena son dígitos */
	if (i != f)																		/* En caso de no ser dígito */
		throw Incorrecto(DIGITOS);													/* lanza la excepción Incorrecto(DIGITOS) */

	Cadena cadenaFinal(n.c_str());

	if((cadenaFinal.length() < 13) || (cadenaFinal.length() > 19)) 	/* Si la longitud del numero es menor de 13 digitos o mayor de 19 digitos */
		throw Incorrecto(LONGITUD);							/* lanza la excepción Incorrecto(LONGITUD) */

	if(!luhn(cadenaFinal, cadenaFinal.length()))	/* Si el algoritmo de luhn devuelve falso */
		throw Incorrecto(NO_VALIDO);		/* lanza la excepción Incorrecto(NO_VALIDO) */

	numero_ = cadenaFinal;
}


//Constructor de Tarjeta
Tarjeta::Tarjeta(Tipo t, Numero tjt, Usuario& u, Fecha f):tipo_(t), tarjeta_(tjt), titular_(&u), f_caducidad_(f)
{
	titular_facial_ = u.nombre() + " " + u.apellidos(); /* Asignamos a titular_facial el nombre y los apellidos del titular */

	for(size_t i = 0; i < titular_facial_.length(); ++i)	/* Convertimos todos los caracteres del titular facial a mayúsculas*/
		titular_facial_[i] = toupper(titular_facial_[i]);
	u.es_titular_de(*this); 	/* Asigna la tarjeta actual a un usuario */

	const Fecha hoy;				/* Creamos una fecha con el día de hoy */
	if((hoy < caducidad()) == false)	/* Si la fecha de caducidad es mayor o igual que la fecha de hoy */
		throw Caducada(caducidad());		/* lanza la excepción Caducada(f_cad) */
}

//Destructor de Tarjeta
Tarjeta::~Tarjeta()
{
	if (titular())
		const_cast<Usuario*>(titular_) -> no_es_titular_de(*this);
}


//Operadores Externos
bool operator <(const Numero& n1, const Numero& n2)
{
	return(strcmp(n1, n2) < 0);
}


bool operator <(const Tarjeta& t1, const Tarjeta& t2)
{
	if (strcmp(t1.numero(),t2.numero()) < 0)
		return true;
	else 
		return false;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo T)
{
	Cadena t;
	switch(T)
	{
		case 0: t = "VISA"; break;
		case 1: t = "Mastercard"; break;
		case 2: t = "Maestro"; break;
		case 3: t = "JCB"; break;
		case 4: t = "AmericanExpress"; break;
	}; 

	os << t;
	return os;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& T)
{
	int a = T.caducidad().anno()%100;


	os << T.tipo() << endl;
	os << T.numero() << endl;
	os << T.titular_facial() << endl;
	os << "Caduca: " << (T.caducidad().mes()<10 ? "0" : "") << T.caducidad().mes() << (a<10 ? "/0" : "/") << a << endl;

	return os;
}

// Fin tarjeta.hpp