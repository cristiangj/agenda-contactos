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
#include <vector>
#include <iostream>
#include <cstdlib>

namespace agenda{

char Menus::principal(std::vector<Contacto> masUsados) {
	std::string aux;
	char seleccion;
	std::list<char> caracValidos;

	//Lista de caracteres válidos de este menú
	caracValidos.push_back('a');
	caracValidos.push_back('b');
	caracValidos.push_back('c');
	caracValidos.push_back('f');
	for(int i=0 ; i < CONTACTOS_MAS_USADOS ; ++i){
		caracValidos.push_back('1' + i);
	}

	system("clear");
	std::cout <<	"Agenda contactos" << std::endl <<
					"====================" << std::endl <<
					std::endl <<
					"Contactos más usados:" << std::endl;

	//ATENCIÓN: El índice que aparece por pantalla empieza
	//en 1, mientras que el vector empieza en 0
	for(int i=0 ; i < masUsados.size() ; ++i){
		std::cout <<	(i+1) << ") " << masUsados.at(i).getApellidosyNombre() << std::endl;
	}

	std::cout << std::endl <<
			"a: Añadir un contacto" << std::endl <<
			"b: Buscar un contacto por apellido" << std::endl <<
			"c: Copias de seguridad" << std::endl <<
			"f: Generar una agenda en formato de texto" << std::endl <<
			"" << std::endl <<
			"Introduce un número para acceder a uno de los contactos" << std::endl <<
			"más usados o introduce una letra para una de las opciones" << std::endl <<
			std::endl <<
			std::endl <<
			std::endl <<
			std::endl;

	bool selValida = true; //¿Es la selección válida?
	do{
		std::cout << "--> " << std::endl;
		std::cin >> aux;

		if(!selValida){
			std::cout << "Selección inválida" << std::endl;
		}
	}while(!selValida);

}

std::string Menus::busqueda() {
}

Contacto Menus::listado(std::vector<Contacto> lista) {
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

bool Menus::comprobarEntradaValida(std::list<char> caracValidos, char c) {
	bool valido = false;
	std::list<char>::iterator it;

	for(it = caracValidos.begin() ; it != caracValidos.end() && !valido; ++it){
		if(c == (*it)) valido = true;
	}

	return valido;
}

}
