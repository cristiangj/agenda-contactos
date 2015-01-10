/*
 * Main.cpp
 *
 *  Created on: 10/1/2015
 *      Author: javier
 */

#include "GestorAgenda.h"
#include "Menus.h"
#include "GestorBackup.h"
#include <string>
#include <iostream>

using namespace agenda;

void menuContacto(Contacto c);
void menuCopiasSeguridad();

int main(){
	bool salir = false;
	Contacto c; //Contacto auxiliar
	std::string entrada;
	int seleccion;
	std::vector<Contacto> masUsados;
	std::vector<Contacto> listado;


	do{
		//Menú principal
		masUsados = GestorAgenda::getGestor()->masUsados(CONTACTOS_MAS_USADOS);
		seleccion = Menus::principal(masUsados);
		switch(seleccion){
		case MENU_ANADIR_CONTACTO:
			c = Menus::addContacto();
			if(GestorAgenda::getGestor()->addContacto(c) == false){
				std::cout << "What??" << std::endl;
			}
			break;

		case MENU_BUSCAR_CONTACTO_APELLIDO:
			entrada = Menus::busqueda();
			listado = GestorAgenda::getGestor()->buscarContactoApellidos(entrada);
			seleccion = Menus::listado(listado);

			if(seleccion != NO_ENCONTRADO) menuContacto(listado.at(seleccion));
			break;

		case MENU_COPIAS_SEGURIDAD:
			menuCopiasSeguridad();
			break;

		case MENU_MOSTRAR_FAVORITOS:
			listado = GestorAgenda::getGestor()->buscarContactoFavoritos();
			seleccion = Menus::listado(listado);

			if(seleccion != NO_ENCONTRADO) menuContacto(listado.at(seleccion));
			break;

		case MENU_FORMATO_TEXTO:
			GestorAgenda::getGestor()->imprimirTexto();
			Menus::formatoLegible();
			break;

		case MENU_ATRAS:
			salir = true;
			break;

		default: //Seleccionado un contacto de los más usados
			if(seleccion != NO_ENCONTRADO) menuContacto(masUsados.at(seleccion));
			break;
		}
	} while(!salir);
}

void menuContacto(Contacto c){
	int seleccion;
	bool borrado = false;
	std::string aux;
	bool salir = false;
	Contacto nuevo; //Contacto auxiliar

	do{
		seleccion = Menus::visionado(c);
		switch(seleccion){
		case MENU_MODIFICAR_CONTACTO:
			nuevo = Menus::modificarContacto(c);
			GestorAgenda::getGestor()->modificarContacto(nuevo,c);
			c = nuevo; //El contacto en cuestión pasa a ser el nuevo
			break;

		case MENU_BORRAR_CONTACTO:
			borrado = Menus::borrarContacto();

			if(borrado){
				GestorAgenda::getGestor()->borrarContacto(c);
				salir = true;
			}

			break;

		case MENU_ATRAS:
			salir = true;
			break;

		default:
			std::cout << "Selección inválida" << std::endl;
			std::cin >> aux;
			break;
		}
	}while(!salir);

	if(!borrado){ //Aumenta el número de consultas solo si no se ha borrado
		nuevo = c;
		nuevo.anadirNconsultas();
		GestorAgenda::getGestor()->modificarContacto(nuevo,c);
	}

}

void menuCopiasSeguridad(){
	bool salir = false;
	bool si;
	int seleccion;
	std::string entrada;
	std::list<Contacto> lista;

	do{
		seleccion = Menus::copiaSeguridad();
		switch(seleccion){
		case MENU_CREAR_COPIA:
			si = Menus::crearCopiaSeguridad();
			if(true){ //Si elige crearla
				GestorBackup::crearCopiaSeguridad(GestorAgenda::getGestor()->getListaContactos());
			}
			break;

		case MENU_ELIMINAR_COPIA:
			entrada = Menus::eliminarCopiaSeguridad();
			if(!entrada.empty()){
				GestorBackup::borrarCopiaSeguridad(entrada);
			}
			break;

		case MENU_RESTAURAR_COPIA:
			entrada = Menus::restaurarCopiaSeguridad();
			if(!entrada.empty()){
				lista = GestorBackup::obtenerCopiaSeguridad(entrada);
				if(!lista.empty()){
					GestorAgenda::getGestor()->setListaContactos(lista);
				}
			}
			break;

		case MENU_ATRAS:
			salir = true;
			break;
		}
	}while(!salir);
}
