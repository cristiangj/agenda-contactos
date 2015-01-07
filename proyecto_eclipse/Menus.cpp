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
#include <ctime>
#include <cstdio>

namespace agenda{

int Menus::principal(std::vector<Contacto> masUsados) {
	std::string aux;
	int seleccionUsuario; //Lo que en última instancia devolverá la función, la selección del usuario codificada

	limpiaPantalla();
	imprimeTitulo();
	std::cout << "Contactos más usados:" << std::endl;

	//ATENCIÓN: El índice que aparece por pantalla empieza
	//en 1, mientras que el vector empieza en 0
	for(int i=0 ; i < masUsados.size() ; ++i){
		std::cout <<	(i+1) << ") " << masUsados.at(i).getApellidosyNombre() << std::endl;
	}

	std::cout << std::endl <<
			"a: Añadir un contacto" << std::endl <<
			"b: Buscar un contacto por apellido" << std::endl <<
			"f: Mostrar contactos favoritos" << std::endl <<
			"c: Copias de seguridad" << std::endl <<
			"t: Generar una agenda en formato de texto" << std::endl <<
			std::endl <<
			"Introduce un número para acceder a uno de los contactos" << std::endl <<
			"más usados o introduce una letra para una de las opciones" << std::endl <<
			std::endl <<
			std::endl <<
			std::endl <<
			std::endl;

	bool selValida; //¿Es la selección válida?
	do{
		selValida = true;
		std::cout << "--> ";
		std::cin >> aux;

		if(atoi(aux.c_str()) > 0 && atoi(aux.c_str()) <= masUsados.size()){ //Si ha seleccionado un contacto más usado:
			seleccionUsuario = atoi(aux.c_str()) - 1;
		} else {
			switch(tolower(aux.at(0))){
			case 'a':
				seleccionUsuario = MENU_ANADIR_CONTACTO;
				break;
			case 'b':
				seleccionUsuario = MENU_BUSCAR_CONTACTO_APELLIDO;
				break;
			case 'f':
				seleccionUsuario = MENU_MOSTRAR_FAVORITOS;
				break;
			case 'c':
				seleccionUsuario = MENU_COPIAS_SEGURIDAD;
				break;
			case 't':
				seleccionUsuario = MENU_FORMATO_TEXTO;
				break;

			default:
				selValida = false;
				std::cout << "Selección inválida" << std::endl;
			}
		}
	}while(!selValida);

	//Finalmente se decide qué valor se devolverá

	return seleccionUsuario;
}

std::string Menus::busqueda() {
	std::string busca; //Apellido a buscar

	limpiaPantalla();
	std::cout << "Introduce el apellido que deseas buscar:" << std::endl;
	std::cin >> busca;

	return busca;
}

int Menus::listado(std::vector<Contacto&> lista) {
	int seleccion;

	limpiaPantalla();
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

int Menus::visionado(Contacto& c) {
	std::vector<std::string> telefonos = c.getTelefonos();
	std::vector<Direccion> direcciones = c.getDirecciones();
	std::vector<CuentaRedSocial> redes = c.getRedes();

	c.anadirNconsultas();

	limpiaPantalla();
	std::cout <<	"Apellidos: " << c.getApellidos() << std::endl <<
					"Nombre: " << c.getNombre() << std::endl <<
					"DNI: " << c.getDni() << std::endl;

	//Imprime teléfonos
	for(int i = 0 ; i < telefonos.size() ; ++i){
		std::cout <<	"Telefono " << (i+1) << ": " << telefonos.at(i) << std::endl;
	}

	std::cout << "Correo electrónico: " << c.getCorreoE() << std::endl;

	//Imprime direcciones
	for(int i=0 ; i < direcciones.size() ; ++i){
		std::cout << "Dirección " << (i+1) << ": " << direcciones.at(i) << std::endl;
	}

	//Imprime redes
	for(int i=0 ; i < redes.size() ; ++i){
		std::string nombreRed;
		switch(redes.at(i)){
		case facebook:
			nombreRed = "Facebook";
			break;
		case twitter:
			nombreRed = "Twitter";
			break;
		case googleplus:
			nombreRed = "Goolge+";
			break;
		}

		std::cout << "Cuenta de " << nombreRed << ": " << redes.at(i).usuario << std::endl;
	}

	std::string fav = c.getFavoritos()?"Sí":"No";
	std::cout <<	"Notas: " << c.getAnotaciones() << std::endl <<
					"¿Es favorito?: " << fav << std::endl << std::endl;

	//Selección de qué hacer con el contacto
	int seleccionUsuario;
	std::string aux;

	std::cout <<	"¿Qué quieres hacer?" << std::endl <<
					"m: Modificar contacto" << std::endl <<
					"b: Borrar contacto" << std::endl <<
					"a: Volver al menú principal" << std::endl << std::endl;

	bool selValida; //¿Es la selección válida?
	do{
		selValida = true;
		std::cout << "--> ";
		std::cin >> aux;

		switch(tolower(aux.at(0))){
		case 'm':
			seleccionUsuario = MENU_MODIFICAR_CONTACTO;
			break;
		case 'b':
			seleccionUsuario = MENU_BORRAR_CONTACTO;
			break;
		case 'a':
			seleccionUsuario = MENU_ATRAS;
			break;

		default:
			selValida = false;
			std::cout << "Selección inválida" << std::endl;
		}
	}while(!selValida);

	//Finalmente se decide qué valor se devolverá

	return seleccionUsuario;
}

Contacto Menus::addContacto() {
	limpiaPantalla();

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
		valido = c.setDni(aux);

		if(!valido) std::cout << "Selección inválida" << std::endl;
	}while(!valido);

	//Teléfonos
	int i = 0;
	do{
		valido = true;
		std::cout << "Teléfono: " << (i+1) << ": ";
		std::cin >> aux;

		if(aux.size() != 0){ //Si el usuario no introduce nada, no se introduce ningún telefono más
			valido = c.setTelefono(aux);

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
		//TODO : Corregir entrada de direcciones

		if(aux.size() != 0){ //Si el usuario no introduce nada, no se introduce ninguna dirección más
			valido = c.setDireccion(aux);

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
			c.setRed(cuenta);

			++i;
		}
	}while(nuevaRed);

	//Favorito
	std::cout << "¿Deseas que el contacto aparezca en tu lista de favoritos? (s/N): ";
	std::cin >> aux;
	if(aux.size() == 1 && tolower(aux.at(0)) == 's'){
		c.setFavoritos(true);
		std::cout << "El contacto aparecerá en tu lista de favoritos" << std::endl;
	}
	else{
		c.setFavoritos(false);
		std::cout << "El contacto NO aparecerá en tu lista de favoritos" << std::endl;
	}

	//Anotación
	std::cout << "Añade a continuación cualquier anotación que quieras hacer sobre el usuario (puedes dejarlo en blanco):" << std::endl;
	std::cin >> aux;
	c.setAnotaciones(aux);

	return c;
}

int Menus::copiaSeguridad() {
	int seleccionUsuario;

	limpiaPantalla();
	imprimeTitulo();

	std::string aux;

	std::cout << std::endl <<
				"c: crear copia de seguridad" << std::endl <<
				"r: restaurar copia de seguridad" << std::endl <<
				"e: eliminar copia de seguridad" << std::endl <<
				"a: volver al menú anterior" << std::endl <<
				std::endl <<
				std::endl <<
				std::endl <<
				std::endl <<
				std::endl;

	bool selValida; //¿Es la selección válida?
	do{
		selValida = true;
		std::cout << "--> ";
		std::cin >> aux;

		switch(tolower(aux.at(0))){
		case 'c':
			seleccionUsuario = MENU_CREAR_COPIA;
			break;
		case 'r':
			seleccionUsuario = MENU_RESTAURAR_COPIA;
			break;
		case 'e':
			seleccionUsuario = MENU_ELIMINAR_COPIA;
			break;
		case 'a':
			seleccionUsuario = MENU_ATRAS;
			break;

		default:
			selValida = false;
			std::cout << "Selección inválida" << std::endl;
		}
	}while(!selValida);

	return seleccionUsuario;
}

bool Menus::crearCopiaSeguridad() {
	std::string nombreCS;
	std::string aux;
	std::list<char> caracValidos = {'s','n'};
	bool seleccion;

	nombreCS = getNombreCSActual();

	limpiaPantalla();
	std::cout <<	"La copia de seguridad se guardará con el siguiente nombre:" << std::endl << std::endl <<
					nombreCS << std::endl << std::endl <<
					"¿Estás de acuerdo?" << std::endl <<
					std::endl <<
					std::endl <<
					std::endl <<
					std::endl;

	bool selValida = true; //¿Es la selección válida?
	do{
		std::cout << "(S/n)" << std::endl << "--> ";
		std::cin >> aux;

		selValida = comprobarEntradaValida(caracValidos,aux.at(0));
		if(!selValida){
			std::cout << "Selección inválida" << std::endl;
		}
	}while(!selValida);

	if(tolower(aux.at(0)) == 's')
		seleccion = true;
	else
		seleccion = false;

	return seleccion;
}

std::string Menus::restaurarCopiaSeguridad() {
	std::vector<std::string> copiasGuardadas = GestorBackup::getListaCopiasSeguridad();
	std::string aux;
	bool restaurar = false;
	int seleccion;
	std::string nombreRestauracion; //Nombre de la copia a restaurar (lo que la funcion devolverá)

	limpiaPantalla();
	std::cout << "Esta es la lista de las copias de seguridad guardadas:" << std::endl << std::endl;

	std::vector<std::string>::iterator i;
	int cuenta;

	for(i = copiasGuardadas.begin() , cuenta=1; i != copiasGuardadas.end() ; ++i , ++cuenta){
		std::cout << cuenta << ") " << (*i) << std::endl;
	}

	std::cout << std::endl <<	"¿Deseas restaurar alguna de ellas? (s/N)" << std::endl <<
								"--> ";
	std::cin >> aux;
	if(aux.size() == 1 && tolower(aux.at(0)) == 's') restaurar = true;

	if(restaurar){
		std::cout <<	"¿Cuál deseas restaurar?" << std::endl;

		bool selValida = true; //¿Es la selección válida?
		do{
			std::cout << "--> ";
			std::cin >> aux;

			seleccion = atoi(aux.c_str());

			selValida = seleccion > 0 && seleccion <= copiasGuardadas.size();
			if(!selValida){
				std::cout << "Selección inválida" << std::endl;
			}
		}while(!selValida);

		//Asignamos al valor devuelto la seleccion del usuario
		i = copiasGuardadas.begin();
		nombreRestauracion = *(i+(seleccion-1));
	}

	return nombreRestauracion;
}

std::string Menus::eliminarCopiaSeguridad() {
	std::list<std::string> copiasGuardadas = GestorBackup::getListaCopiasSeguridad();
	std::string aux;
	bool restaurar = false;
	int seleccion;
	std::string nombreBorrar; //Nombre de la copia a borrar (lo que la funcion devolverá)

	limpiaPantalla();
	std::cout << "Esta es la lista de las copias de seguridad guardadas:" << std::endl << std::endl;

	std::list<std::string>::iterator i;
	int cuenta;

	for(i = copiasGuardadas.begin() , cuenta=1; i != copiasGuardadas.end() ; ++i , ++cuenta){
		std::cout << cuenta << ") " << (*i) << std::endl;
	}

	std::cout << std::endl <<	"¿Deseas eliminar alguna de ellas? (s/N)" << std::endl <<
								"--> ";
	std::cin >> aux;
	if(aux.size() == 1 && tolower(aux.at(0)) == 's') restaurar = true;

	if(restaurar){
		std::cout <<	"¿Cuál deseas eliminar?" << std::endl;

		bool selValida = true; //¿Es la selección válida?
		do{
			std::cout << "--> ";
			std::cin >> aux;

			seleccion = atoi(aux.c_str());

			selValida = seleccion > 0 && seleccion <= copiasGuardadas.size();
			if(!selValida){
				std::cout << "Selección inválida" << std::endl;
			}
		}while(!selValida);

		//Asignamos al valor devuelto la seleccion del usuario
		i = copiasGuardadas.begin();
		nombreBorrar = *(i+(seleccion-1));
	}

	return nombreBorrar;
}

std::string Menus::formatoLegible() {
}

std::list<Cambio> Menus::modificarContacto() {
}

bool Menus::borrarContacto() {
}


void Menus::limpiaPantalla() {
	system("clear");
}

void Menus::imprimeTitulo() {
	std::cout <<	"Agenda contactos" << std::endl <<
					"====================" << std::endl << std::endl;
}

bool Menus::comprobarEntradaValida(std::list<char> caracValidos, char c) {
	bool valido = false;
	std::list<char>::iterator it;

	for(it = caracValidos.begin() ; it != caracValidos.end() && !valido; ++it){
		if(c == tolower(*it)) valido = true;
	}

	return valido;
}

//Sacado de http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
//aunque modificado
std::string Menus::getNombreCSActual(){
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[100];
	tstruct = *localtime(&now);
	sprintf(buf,"CS_%02d-%02d-%02d_%02d-%02d-%04d.dat", tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec, tstruct.tm_mday, tstruct.tm_mon+1, tstruct.tm_year+1900);

	return buf;
}

}
