/*
 * Menus.cpp
 *
 *  Created on: 10/12/2014
 *      Author: javier
 */

#include "Menus.h"
#include "Contacto.h"
#include <string>
#include <list>
#include <iostream>
#include <cstdlib>

namespace agenda{

char Menus::principal(std::list<Contacto> masUsados) {
	std::string aux;
	char seleccion;

	system("clear");
	std::cout <<	"Agenda contactos" << std::endl <<
					"====================" << std::endl <<
					std::endl <<
					"Contactos más usados:" << std::endl;

	for(auto i = masUsados.begin() ; i != masUsados.end() ; ++i){

	}


}

std::string Menus::busqueda() {
}

Contacto Menus::listado(std::list<Contacto> lista) {
}

Contacto Menus::addContacto() {
}

int Menus::copiaSeguridad() {
}

std::string Menus::formatoLegible() {
}

std::list<Cambio> Menus::modificarContacto() {
}

bool Menus::borrarContacto() {
}

}
