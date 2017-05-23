/* Clases Clave y Usuario */
/* Archivo HPP*/
/* Alejandro Muñoz Del Álamo Copyright 2017 */

#ifndef USUARIO_H
#define USUARIO_H

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include <map>
#include <unordered_map>

// |-> Clase Clave
class Clave
{
public:

	//Constructor de Clave
	Clave(const char* clave);

	//Métodos Observadores
	Cadena clave() const {return clave_;}
	bool verifica (const char* password) const;

	//Atributo (público)
	enum Razon {CORTA, ERROR_CRYPT};

	//Clase de Excepción
	class Incorrecta
	{
	public:

		//Constructor de Incorrecta
		Incorrecta(Razon r): razon_(r){}
		
		//Método observador
		Razon razon() const {return razon_;}

	private:

		Razon razon_;
	};

private:

	Cadena clave_;

};


// |-> Clase Usuario
class Usuario
{
public:

	//Definición de tipos publicos
	typedef std::map<Numero, Tarjeta*> Tarjetas;	// | 1º Numero, 2º Tarjeta | |-> TARJETERO DEL USUARIO
	typedef std::unordered_map<Articulo*, unsigned int> Articulos; // | 1º Articulo, 2º Cantidad | -> CARRITO DE LA COMPRA


	//Clase de excepción
	class Id_duplicado
	{
	public:

		Id_duplicado(Cadena id): id_dup(id){}
		Cadena idd() const {return id_dup;}

	private:
		Cadena id_dup;
	};

	//Constructor de Usuario
	Usuario(Cadena cad_id, Cadena cad_nom, Cadena cad_apell, Cadena cad_dir, Clave clave_contra);

	//Constructor de copia y operador de asignación
	Usuario(const Usuario& user) = delete;
	Usuario& operator = (const Usuario& user) = delete;

	//Métodos observadores
	Cadena id() const {return id_;}
	Cadena nombre() const {return nombre_;}
	Cadena apellidos() const {return apellidos_;}
	Cadena direccion() const {return direccion_;}
	const Tarjetas& tarjetas() const {return tarjetero;}
	size_t n_articulos() const {return carro.size();}
	const Articulos& compra() const {return carro;}

	friend std::ostream& operator << (std::ostream& os, const Usuario& user);

	//Métodos modificadores
	void es_titular_de (Tarjeta& t) noexcept;
	void no_es_titular_de (Tarjeta& t) noexcept;
	void compra(Articulo& a, unsigned int i = 1) noexcept;

	//Destructor
	~Usuario();

private:

	Cadena id_, nombre_, apellidos_, direccion_;
	Clave contrasena_;
	Tarjetas tarjetero;
	Articulos carro;

};

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user);

#endif // USUARIO_H