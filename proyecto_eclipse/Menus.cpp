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

int Menus::principal(std::vector<Contacto> masUsados) {
	std::string aux;
	std::list<char> caracValidos;

	//Lista de caracteres válidos de este menú
	caracValidos = {'a','b','c','f'};
	for(int i=0 ; i < CONTACTOS_MAS_USADOS ; ++i){
		caracValidos.push_back('1' + i);
	}

	limpiaPantalla();
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
		std::cout << "--> ";
		std::cin >> aux;

		selValida = comprobarEntradaValida(caracValidos,aux.at(0));
		if(!selValida){
			std::cout << "Selección inválida" << std::endl;
		}
	}while(!selValida);

	return ((int) aux.at(0));
}

std::string Menus::busqueda() {
	std::string busca; //Apellido a buscar

	limpiaPantalla();
	std::cout << "Introduce el apellido que deseas buscar:" << std::endl;
	std::cin >> busca;

	return busca;
}

Contacto Menus::listado(std::vector<Contacto&> lista) {
	int seleccion;

	std::cout << "Selecciona un contacto:" << std::endl << std::endl;

	for(int i=0 ; i < lista.size() ; ++i){
		std::cout << (i+1) << ") " << lista.at(i).getApellidosyNombre() << std::endl;
	}

	bool selValida = false; //¿Es la selección válida?
	do{
		std::cout << "--> ";
		std::cin >> seleccion;

		//Comprobación de la seleccion
		((seleccion-1) < 0 || seleccion > lista.size())? selValida = false : selValida = true;

		if(!selValida){
			std::cout << "Selección inválida" << std::endl;
		}
	}while(!selValida);

	return seleccion;
}

Contacto Menus::addContacto() {
	std::cout << "Introduce los datos del contacto:" << std::endl <<
				"(Los datos marcados con (*) son obligatorios)" << std::endl;

	std::string aux;
	bool valido;
	Contacto c;

	//Nombre
	do{
		std::cout << "Nombre(*): ";
		std::cin >> aux;
		valido = c.setNombre(aux);

		if(!valido) std::cout << "Selección inválida" << std::endl;
	}while(!valido);

	//Apellidos
	do{
		std::cout << "Apellidos(*): ";
		std::cin >> aux;
		valido = c.setApellidos(aux);

		if(!valido) std::cout << "Selección inválida" << std::endl;
	}while(!valido);

	//DNI
	do{
		std::cout << "DNI: ";
		std::cin >> aux;
		valido = c.setDNI(aux);

		if(!valido) std::cout << "Selección inválida" << std::endl;
	}while(!valido);

	//Teléfonos
	int i = 0;
	do{
		valido = true;
		std::cout << "Teléfono " << (i+1) << ": ";
		std::cin >> aux;

		if(aux.size() != 0){ //Si el usuario no introduce nada, no se introduce ningún telefono más
			valido = c.setTelefono(i,aux);

			if(!valido){
				std::cout << "Selección inválida" << std::endl;
				continue;
			}
		}
		++i;
	}while(!valido);

	//Correo electrónico
	do{
		std::cout << "Correo electrónico: ";
		std::cin >> aux;
		valido = c.setCorreoE(aux);

		if(!valido) std::cout << "Selección inválida" << std::endl;
	}while(!valido);

	//Direcciones
	i = 0;
	do{
		valido = true;
		std::cout << "Dirección " << (i+1) << ": ";
		std::cin >> aux;

		if(aux.size() != 0){ //Si el usuario no introduce nada, no se introduce ninguna dirección más
			valido = c.setDireccion(i,aux);

			if(!valido){
				std::cout << "Selección inválida" << std::endl;
				continue;
			}
		}
		++i;
	}while(!valido);

	//Cuentas redes sociales
	int selec;
	bool nuevaRed;
	do{
		nuevaRed = false;
		std::cout << "¿Deseas introducir una cuenta de redes sociales? (s/N):" << std::endl;
		std::cin >> aux;
		if(aux.size() == 1 && tolower(aux.at(0)) == 's') nuevaRed = true;

		if(nuevaRed){
			i = 0;
			tipoRed t;
			do{
				valido = true;
				std::cout << "¿Qué tipo de cuenta desea añadir?" << std::endl <<
							"1) Facebook" << std::endl << "2) Twitter" << std::endl << "3) Google +" << std::endl <<
							"--> " ;
				std::cin >> selec;
				switch(selec){
				case 1:
					t = facebook;
					break;
				case 2:
					t = twitter;
					break;
				case 3:
					t = googleplus;
					break;
				default:
					std::cout << "Selección inválida" << std::endl;
					valido = false;
				}
			}while(!valido);

			std::cout << "Nombre de usuario: ";
			std::cin >> aux;

			CuentaRedSocial cuenta = {t,aux};
			c.setRed(i,cuenta);

			++i;
		}
	}while(nuevaRed);

	//Favorito
	std::cout << "¿Deseas que el contacto aparezca en tu lista de favoritos? (s/N): ";
	std::cin >> aux;
	if(aux.size() == 1 && tolower(aux.at(0)) == 's'){
		c.setFavorito(true);
		std::cout << "El contacto aparecerá en tu lista de favoritos" << std::endl;
	}
	else{
		c.setFavorito(false);
		std::cout << "El contacto NO aparecerá en tu lista de favoritos" << std::endl;
	}

	//Anotación
	std::cout << "Añade a continuación cualquier anotación que quieras hacer sobre el usuario (puedes dejarlo en blanco):" << std::endl;
	std::cin >> aux;
	c.setAnotacion(aux);

	return c;
}

int Menus::copiaSeguridad() {
}

std::string Menus::formatoLegible() {
}

std::list<Cambio> Menus::modificarContacto() {
}

void Menus::limpiaPantalla() {
	system("clear");
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
