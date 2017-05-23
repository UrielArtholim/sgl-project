/* Clase Usuario-Pedido */
/* Archivo HPP*/
/* Alejandro Muñoz Del Álamo Copyright 2016*/

#ifndef USUARIO_PEDIDO_H
#define USUARIO_PEDIDO_H

#include "usuario.hpp"
#include "pedido.hpp"

class Pedido;

/* Clase Usuario_Pedido */
class Usuario_Pedido
{
public:

	typedef std::set <Pedido*> Pedidos;
	typedef std::map <Usuario*, Pedidos> UsuarioPedidos;
	typedef std::map <Pedido*, Usuario*> PedidoUsuario;

	/* Metodos Modificadores: Asociacion*/
	void asocia (Usuario& usuario, Pedido& pedido)
	{
		usuarioPedidos_[&usuario].insert(&pedido);
		pedidoUsuario_[&pedido] = &usuario;
	}

	void asocia (Pedido& pedido, Usuario& usuario)
	{
		asocia(usuario, pedido);
	}

	/* Metodos Observadores */
	Pedidos& pedidos (Usuario& usuario) {return usuarioPedidos_[&usuario];}
	Usuario* cliente (Pedido& pedido) {return pedidoUsuario_[&pedido];}

private:

	UsuarioPedidos usuarioPedidos_;
	PedidoUsuario pedidoUsuario_;
};

#endif

/* Fin usuario-pedido.hpp */