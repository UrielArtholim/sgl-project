/* 
 	* Práctica 0: Fecha 
	* POO 2016-2017
	* Fecha.hpp
	* Copyright © Alejandro Muñoz Del Álamo  2017
 	*/ 

#ifndef FECHA_HPP
#define FECHA_ĤPP

#include <iostream>
#include "cadena.hpp"

class Fecha
{
public:

	class Invalida
	{
	public:
		Invalida(const char* mensaje):info_(mensaje){}
		const char* por_que() const {return info_;}
	private:
		const char* info_;
	};

	// Constructores
	explicit Fecha(int d = 0, int m = 0, int a = 0);

	// Constructor de copia
	Fecha(const Fecha& fecha);

	// Constructor de conversion
	Fecha(const char* cadena);

	// Función para comprobar la corrección de las fechas
	bool comprobarFecha(const Fecha& fecha);

	// Operadores con asignación
	Fecha& operator +=(int num);
	Fecha& operator -=(int num);

	// Resta con numero de dias como entero largo sin signo
	unsigned long int operator - (const Fecha& fecha);

	// Operador de asignación
	Fecha& operator = (const Fecha& fecha);

	// Metodos observadores
	int dia(){return dia_;}
	int mes(){return mes_;}
	int anno(){return anno_;}
	const int dia() const {return dia_;}
	const int mes() const {return mes_;}
	const int anno() const {return anno_;}

	// Conversión implicita a cadena
	const char* cadena() const;

	// Operadores de comparación
	bool operator <(const Fecha& fecha);
	bool operator <=(const Fecha& fecha);
	bool operator >(const Fecha& fecha);
	bool operator >=(const Fecha& fecha);
	bool operator ==(const Fecha& fecha);
	bool operator !=(const Fecha& fecha);

private:

	int dia_, mes_, anno_;
};

#endif // FECHA_HPP