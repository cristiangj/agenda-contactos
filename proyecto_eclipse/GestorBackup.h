/*
 * GestorBackup.h
 *
 *  Created on: 14/12/2014
 *      Author: cristian
 */

#ifndef GESTORBACKUP_H_
#define GESTORBACKUP_H_

#include <list>
#include <string>
#include "Contacto.h"

namespace agenda {

class GestorBackup {
private:
	/*esta funcion nos devolvera un string con la fecha actual*/
	std::string static dameFecha();

public:
	static bool crearCopiaSeguridad (std::list<Contacto> listaAgenda);
	static bool borrarCopiaSeguridad (std::string nombreCopia);
	static std::list<Contacto> obtenerCopiaSeguridad (std::string nombreCopia);
	static std::list<std::string> getListaCopiasSeguridad ();
	static bool crearArchivoTexto (std::list<Contacto> listaAgenda);

};

} /* namespace agenda */

#endif /* GESTORBACKUP_H_ */
