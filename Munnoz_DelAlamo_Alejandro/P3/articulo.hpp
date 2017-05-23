/* Clase Artículo */
/* Archivo HPP*/
/* Alejandro Muñoz Del Álamo Copyright 2016*/

#ifndef ARTICULO_H_
#define ARTICULO_H_

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iomanip>
#include <set>

using namespace std;

/* Clase Artículo */
class Articulo
{
public:

	typedef std::set<Autor*> Autores;

	class Autores_vacios{};

	/* Constructor */
	Articulo(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio); 

	/* Métodos Observadores */
	Cadena referencia() const noexcept {return referencia_;}
	Cadena titulo() const noexcept {return titulo_;}
	Fecha f_publi() const noexcept {return f_publi_;}
	double precio() const noexcept {return precio_;}
	const Autores& autores() const noexcept {return autores_;}
	virtual void impresion_especifica(std::ostream& os) const = 0; /* Metodo virtual puro de impresion*/
	virtual ~Articulo() = default; /* Declaración virtual del destructor */
	
	//unsigned int stock() const {return stock_;}

	/* Métodos Modificadores */
	double& precio() {return precio_;}
	//unsigned int& stock() {return stock_;}

private:

	Autores autores_;
	Cadena referencia_;
	Cadena titulo_;
	Fecha  f_publi_;
	double precio_;
	//unsigned int stock_;
};

ostream& operator << (ostream& os, const Articulo& art);

/* Fin Clase Artículo */

/* Clase ArticuloAlmacenable */
class ArticuloAlmacenable: public Articulo
{
public:

	/* Constructor */
	ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio, size_t stock);
	
	/* Métodos Observadores */
	size_t stock() const noexcept{return stock_;}
	
	/* Métodos Modificadores */
	size_t& stock() noexcept{return stock_;}

	/* Destructor */
	~ArticuloAlmacenable(){}

protected:
	
	size_t stock_;

};

/* Fin Clase ArticuloAlmacenable */

/* Clase Libro */
class Libro: public ArticuloAlmacenable
{
public:

	/* Constructor */
	Libro(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio, size_t num_pag, size_t stock);

	/* Métodos Observadores */
	size_t n_pag() const noexcept {return n_pag_;}
	void impresion_especifica(std::ostream& os) const noexcept;

private:

	const size_t n_pag_;

};

/* Fin Clase Libro */

/* Clase Cederron */
class Cederron: public ArticuloAlmacenable
{
public:

	/* Constructor */
	Cederron(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio, size_t tam, size_t stock);

	/* Métodos Observadores */
	size_t tam() const noexcept {return tam_;}
	void impresion_especifica(std::ostream& os) const noexcept;

private:

	const size_t tam_;

};

/* Fin Clase Cederron */

/* Clase LibroDigital */
class LibroDigital: public Articulo
{
public:

	/* Constructor */
	LibroDigital(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fpub, double precio, const Fecha& fecha_cadu);

	/* Métodos Observadores */
	const Fecha& f_expir() const noexcept {return f_expir_;}
	void impresion_especifica(std::ostream& os) const;

private:

	const Fecha f_expir_;

};

/* Fin Clase LibroDigital */

#endif

/* Fin articulo.hpp */