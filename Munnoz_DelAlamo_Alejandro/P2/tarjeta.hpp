/* Clases Numero y Tarjeta */
/* Archivo HPP*/
/* Alejandro Muñoz Del Álamo Copyright 2017 */

#ifndef TARJETA_H
#define TARJETA_H

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

// Declaración adelantada
class Usuario;

// |-> Clase Numero
class Numero
{
public:

	enum Razon {LONGITUD, DIGITOS, NO_VALIDO};

	//Clase de excepción
	class Incorrecto
	{
	public:

		Incorrecto(Razon razon):r_(razon){}
		Razon razon() const {return r_;}
	
	private:

		Razon r_;
	};

	//Metodos
	Numero(const Cadena& num);
	operator const char*() const {return numero_.c_str();}

private:

	Cadena numero_;
};


// |-> Clase Tarjeta
class Tarjeta
{
public:

	//Clase de excepción
	class Caducada
	{
	public:

		Caducada(const Fecha& f):caducada_(f){}
		Fecha cuando() const {return caducada_;}

	private:

		Fecha caducada_;
	};
	
	//Atributo Publico
	enum Tipo {VISA, Mastercard, Maestro, JCB, AmericanExpress};

	//Constructor
	Tarjeta (Tipo t, Numero num, Usuario& u, Fecha f);

	//Prohibiciones
	Tarjeta(const Tarjeta& T) = delete; /* Evitar la copia de tarjetas */
	Tarjeta& operator =(const Tarjeta& T) = delete; /* Evitar el operador de asignación de tarjetas */

	//Métodos Observadores
	Tipo tipo() const {return tipo_;}
	Numero numero() const {return tarjeta_;}
	const Usuario* titular() const {return titular_;}
	Fecha caducidad() const {return f_caducidad_;}
	Cadena titular_facial() const {return titular_facial_;}

	// Métodos Modificadores
	void anula_titular(){titular_ = nullptr;}

	//Destructor
	~Tarjeta();

private:

	//Atributos
	Tipo tipo_;
	Numero tarjeta_;
	const Usuario* titular_;
	Fecha f_caducidad_;
	Cadena titular_facial_;

};

/* Fin clase Tarjeta */

/* Operadores Externos */
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo T);
std::ostream& operator <<(std::ostream& os, const Tarjeta& t);
bool operator <(const Tarjeta& t1, const Tarjeta& t2);
bool operator <(const Numero& n1, const Numero& n2);
bool operator ==(const Tarjeta& t1, const Tarjeta& t2);


#endif // TARJETA_H