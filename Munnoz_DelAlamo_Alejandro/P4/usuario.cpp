/* Clases Clave y Usuario */
/* Archivo CPP*/
/* Alejandro Muñoz Del Álamo Copyright 2016*/

#include <random>
#include <unistd.h>
#include "usuario.hpp"
#include <set>
#include <iomanip>


/*Clase Clave */

/*Constructor*/
Clave::Clave(const char* clave)
{
	if(strlen(clave)<5) 			/* Si la clave es de menos de 5 caracteres*/
		throw Incorrecta(CORTA);	/* lanza una excepción de tipo Incorrecta(CORTA)*/	

	/* Cálculo de salt*/
	const char* plantilla = {"abzdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"};
	std::random_device r;
	std::uniform_int_distribution<size_t> d(0,63);
	char sal_[2] = {plantilla[d(r)], plantilla[d(r)]};

	char* encriptada = crypt(clave,sal_); /*Encriptado de la contrasena*/

	if (encriptada == nullptr)			/* Si la clave encriptada resulta puntero nulo*/
		throw Incorrecta(ERROR_CRYPT);	/* lanza una excepción de tipo Incorrecta(ERROR_CRYPT)*/

	password_ = encriptada; /*Asignación de la clave encriptada al atributo de la clase Clave*/
}

/* Métodos Observadores*/
bool Clave::verifica(const char* clave) const
{
	return (Cadena(crypt(clave, password_.c_str()))== password_);
}

/* Fin clase Clave */

/* Clase Usuario */
std::set<Cadena> id_users;
/* Constructor */
Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& apell, const Cadena& dir, const Clave& pass):
id_(id), nombre_(nom), apellidos_(apell), direccion_(dir), contrasena_(pass)
{
	if (id_users.insert(id_).second == false) 	/* Si el identificador del usuario ya existe*/
		throw Id_duplicado(id_); 				/* lanza la excepción Id_duplicado*/
}

/* Métodos Modificadores*/
void Usuario::es_titular_de(Tarjeta& T) noexcept
{
	if (T.titular() == this)			/* Si el titular de la tarjeta es el usuario actual */
		tarjetas_[T.numero()] = &T;		/* introduce la tarjeta en el contenedor de tarjetas del usuario */
}

void Usuario::no_es_titular_de(Tarjeta& T) noexcept
{
	tarjetas_.erase(T.numero()); 	/* Elimina la tarjeta del contenedor de tarjetas del usuario*/
	T.anula_titular();				/* Anula el titular de la tarjeta */
}

void Usuario::compra (Articulo& A, unsigned int cantidad) noexcept
{
	if(cantidad == 0)			/* Si la cantidad del artículo es 0 */
		carro_.erase(&A);		/* Elimina el articulo del carro */
	else 						/* Si la cantidad del articulo no es 0 */
		carro_[&A] = cantidad;	/* Asigna al artículo del carro dicha cantidad */
}

/* Destructor */
Usuario::~Usuario()
{
	for(Usuario::Tarjetas::const_iterator it = tarjetas_.begin(); it != tarjetas_.end(); it++) /* Para todas las tarjetas del usuario actual*/
	{
		(it->second)->anula_titular();		/* Anula el titular de cada tarjeta */
	}

	id_users.erase(id_);	/* Elimina el usuario */
}

std::ostream& operator <<(ostream& os, const Usuario& u)
{
	os << u.id() << " [" << u.contrasena_.clave() << "] " << u.nombre() << " " << u.apellidos() << endl;
	os << u.direccion() << endl;
	os << "Tarjetas:\n";

	for (Usuario::Tarjetas::const_iterator it = u.tarjetas().begin(); it != u.tarjetas().end(); it++)
		os << *(it->second) << endl;

	return os;
}

std::ostream& mostrar_carro(ostream& os, const Usuario& u)
{
	os << "Carrito de compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]\n";

	if (u.n_articulos()!=0)
	{
		os << "Cant. Artículo\n";
		os << "=======================================================================\n";
		for(auto it = u.compra().begin(); it != u.compra().end(); it++)
		{
			os << it->second << " [" << it->first->referencia() << "] \"" << it->first->titulo() << "\", " << it->first->f_publi().anno();
			os << ". " << setprecision(2) << fixed << it->first->precio() << " €" << endl;
		}
	}

	return os;
}

/* Fin clase Usuario */
/* Fin usuario.cpp */