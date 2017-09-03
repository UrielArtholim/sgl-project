/* Clases Clave y Usuario */
/* Alejandro Muñoz Del Álamo Copyright 2016*/

#ifndef USUARIO_H_
#define USUARIO_H_

#include "cadena.hpp"
#include "fecha.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include <set>
#include <map>
#include <unordered_map>

using namespace std;


/* Clase Clave */

class Numero;
class Tarjeta;
class Articulo;

class Clave
{
public:

	/* Constructor */
	Clave(const char* clave);

	/* Métodos Observadores*/
	Cadena clave() const {return password_;}
	bool verifica (const char* pass) const;

	/* Atributo Público */
	enum Razon {CORTA, ERROR_CRYPT};

	/* Clase de Excepción: Clave::Incorrecta */
	class Incorrecta
	{
	public:

		Incorrecta(Razon razon): r_(razon){};

		Razon razon() const {return r_;}

	private:
		
		Razon r_;
	};

private:

	Cadena password_;
};

/* Fin Clase Clave */

/* Clase Usuario */

class Usuario
{
public:

	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned int> Articulos;

	/* Clase de Excepción: Id_duplicado */
	class Id_duplicado
	{
	public:

		Id_duplicado(Cadena id_d): id_dup_(id_d){};
		Cadena idd() const {return id_dup_;}

	private:

		Cadena id_dup_;
	};

	/* Constructor */
	Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& pass);

	/* Prohibiciones */
	Usuario(const Usuario&) = delete; /* Evitar la copia de Usuario */
	Usuario& operator =(const Usuario&) = delete; /* Evitar la asignación de un objeto Usuario */

	/* Métodos Observadores */
	Cadena id() const {return id_;}
	Cadena nombre() const {return nombre_;}
	Cadena apellidos() const {return apellidos_;}
	Cadena direccion() const {return direccion_;}
	const Tarjetas& tarjetas() const {return tarjetas_;}
	size_t n_articulos() const {return carro_.size();}
	const Articulos& compra() const {return carro_;}

	/* Métodos modificadores */
	void es_titular_de (Tarjeta& t) noexcept;
	void no_es_titular_de (Tarjeta& t) noexcept;
	void compra(Articulo& a, unsigned int i = 1) noexcept;


	/* Métodos amigos */
	friend std::ostream& operator <<(std::ostream& os, const Usuario& usuario);

	/* Destructor */
	~Usuario();

private:

	Cadena id_, nombre_, apellidos_, direccion_;
	Clave contrasena_;
	Tarjetas tarjetas_;
	Articulos carro_;

};

/* Fin clase Usuario */

std::ostream& mostrar_carro(std::ostream& os, const Usuario& usuario);

#endif

/* Fin usuario.hpp */
