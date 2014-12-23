/*
 * Contacto.cpp
 *
 *  Created on: 10/12/2014
 *      Author: javier
 */

#include "Contacto.h"
#include <string>

namespace agenda {

Contacto::Contacto() {
	// TODO Auto-generated constructor stub

}

std::string Contacto::getApellidosyNombre(){
	std::string aux;

	aux = apellidos + ", " + nombre;

	return aux;
}

} /* namespace agenda */
