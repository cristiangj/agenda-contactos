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

#define MENU_ANADIR_CONTACTO -1
#define MENU_BUSCAR_CONTACTO_APELLIDO -2
#define MENU_MOSTRAR_FAVORITOS -3
#define MENU_COPIAS_SEGURIDAD -4
#define MENU_FORMATO_TEXTO -5

#define MENU_CREAR_COPIA -1
#define MENU_RESTAURAR_COPIA -2
#define MENU_ELIMINAR_COPIA -3
#define MENU_ATRAS -4

#define MENU_MODIFICAR_CONTACTO -1
#define MENU_BORRAR_CONTACTO -2

namespace agenda {

class Menus {
private:
	static bool comprobarEntradaValida(std::list<char> caracValidos, char c); //Recibe una lista de caracteres y comprueba si el caracter en cuestión está incluido
	static void limpiaPantalla(); //Limpia la pantalla del terminal
	static void imprimeTitulo(); //Imprime el encabezado de la aplicación
	static std::string getEntrada(); //Toma una línea de entrada del teclado (cin)
	static int getEntradaInt(); //Toma un entero del teclado (y limpia cin)

public:
	//Menú principal:
	//-Devuelve:
	//
	static int principal(std::vector<Contacto> masUsados);

	static std::string busqueda();
	static int listado(std::vector<Contacto> lista);
	static int visionado(Contacto &c); //Muestra por pantalla el contacto y devuelve la opción seleccionada

	static Contacto addContacto();
	static void  modificarContacto(Contacto &c);
	static bool borrarContacto();

	static int copiaSeguridad();
	static bool crearCopiaSeguridad();
	static std::string restaurarCopiaSeguridad();
	static std::string eliminarCopiaSeguridad();

	static void formatoLegible();
};

} /* namespace agenda */

#endif /* MENUS_H_ */
