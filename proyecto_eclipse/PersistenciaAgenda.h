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
	 std::string nombreFichero="contacto_db.bin";
	 std::list<Contacto>::iterator it;			//iterador para la lista de Contactos

public:
	bool guardaBD(std::list<Contacto> lista);
	std::list<Contacto> leeBD();

};

} /* namespace agenda */

#endif /* PERSISTENCIAAGENDA_H_ */
