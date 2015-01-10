/*
 * PersistenciaAgenda.h
 *
 *  Created on: 9/12/2014
 *      Author: cristian
 */

#ifndef PERSISTENCIAAGENDA_H_
#define PERSISTENCIAAGENDA_H_

#include <list>
#include <string>
#include "Contacto.h"

namespace agenda{

class PersistenciaAgenda {
private:
	 static std::string nombreFichero;

public:
	static bool guardaBD(std::list<Contacto> lista);
	static std::list<Contacto> leeBD();

};

} /* namespace agenda */

#endif /* PERSISTENCIAAGENDA_H_ */
