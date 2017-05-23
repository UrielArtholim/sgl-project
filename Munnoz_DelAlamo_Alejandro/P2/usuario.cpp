/* Clases Clave y Usuario */
/* Archivo CPP*/
/* Alejandro Muñoz Del Álamo Copyright 2017 */

#include "usuario.hpp"
#include <random>
#include <unistd.h>
#include <set>
#include <iomanip>

// |-> Clase Clave

//Constructor de Clave
Clave::Clave(const char* clave)
{
	if(strlen(clave < 5))		// Si la clave es de menos de 5 caracteres, lanza la excepción Incorrecta(CORTA)
		throw Incorrecta(CORTA);

	const char* plantilla = ("abcdefghijklmnopqrstvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"); // Plantilla para la selección aleatoria
	std::random_device r;
	std::uniform_int_distribution<size_t> d(0,63);
	char sal[2] = {plantilla[d(r)], plantilla[d(r)]} // Selección aleatoria de sal mediante una distribución uniforme 

	char* encriptada = crypt(clave,sal); // Encriptado de la contraseña
	if (encriptada == nullptr)
		throw Incorrecta(ERROR_CRYPT);	// Si la clave resulta puntero nulo, lanza la excepción Incorrecta(ERROR_CRYPT)

	clave_ = encriptada;	// Asignación de la clave encriptada al atributo correspondiente
}


// Metodos observadores
Clave::verifica(const char* clave)
{
	return (Cadena(crypt(clave, clave_.c_str())) == clave_);
}



// |-> Clase Usuario
std::set<Cadena> usuarios;

//Constructor de Usuario
Usuario::Usuario(Cadena cad_id, Cadena cad_nom, Cadena cad_apell, Cadena cad_dir, Clave clave_contra):
				id_(cad_id), nombre_(cad_nom), apellidos(cad_apell), direccion_(cad_dir), clave_(clave_contra)
{
	if (usuarios.insert(id_).second == false)
		throw Id_duplicado(id_);	//Si el id de usuario ya esta utilizado, lanza la excepción Id_duplicado(id_)
}


//Metodos modificadores
void Usuario::es_titular_de(Tarjeta& t) noexcept
{
	if (t.titular() == this)
		tarjetero[t.numero()] = &t;
}

void Usuario::no_es_titular_de(Tarjeta& t) noexcept
{
	tarjetero.erase(t.numero());
	t.anula_titular();
}

void Usuario::compra (Articulo& a, unsigned int cantidad)
{
	if (cantidad == 0)
		carro.erase(&a);
	else
		carro[&a] = cantidad;
}


//Destructor
Usuario::~Usuario()
{
	for (Usuario::tarjetero::const_iterator it = tarjetero.begin(); it != tarjetero.end(); ++it)
		(it->second)->anula_titular();

	usuario.erase(id_);
}


//Operador de inserción
std::ostream& operator <<(ostream& os, const Usuario& u)
{
	os << u.id() << " [" << u.contrasena_.clave() << "] " << u.nombre() << " " << u.apellidos() << endl;
	os << u.direccion() << endl;
	os << "Tarjetas:\n";

	for (Usuario::Tarjetas::const_iterator it = u.tarjetas().begin(); it != u.tarjetas().end(); it++)
		os << *(it->second) << endl;

	return os;
}
//Método mostrar_carro
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

/* Fin usuario.cpp *