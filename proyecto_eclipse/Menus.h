/*
 * Menus.h
 *
 *  Created on: 10/12/2014
 *      Author: javier
 */

#ifndef MENUS_H_
#define MENUS_H_

#include "Contacto.h"
#include <vector>
#include <list>

#define CONTACTOS_MAS_USADOS 5 //Número de contactos más usados que se utilizarán en el menú principal

namespace agenda {

class Menus {
private:
	static bool comprobarEntradaValida(std::list<char> caracValidos, char c); //Recibe una lista de caracteres y comprueba si el caracter en cuestión está incluido
	static void limpiaPantalla(); //Limpia la pantalla del terminal
	static void imprimeTitulo(); //Imprime el encabezado de la aplicación
	static std::string getNombreCSActual();

public:
	static int principal(std::vector<Contacto> masUsados);

	static std::string busqueda();
	static Contacto listado(std::vector<Contacto&> lista);

	static Contacto addContacto();
	static std::list<Cambio>  modificarContacto();
	static bool borrarContacto();

	static int copiaSeguridad();
	static bool crearCopiaSeguridad();
	static std::string restaurarCopiaSeguridad();
	static void eliminarCopiaSeguridad();

	static std::string formatoLegible();
};

} /* namespace agenda */

#endif /* MENUS_H_ */
