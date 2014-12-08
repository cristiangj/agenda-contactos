/*
 * GestorAgenda.h
 *
 *  Created on: 08/12/2014
 *      Author: aurora
 */

#ifndef GESTORAGENDA_H_
#define GESTORAGENDA_H_

//incluir .h de la clase contacto
#include <list>
#include <string>

using namespace std;

class GestorAgenda {
private:
	list<Contacto> listaContactos_;
	bool comparaApellido(Contacto a, Contacto b);
	string simplificaCadena(string cad);

public:
	GestorAgenda() {
		// TODO Auto-generated constructor stub

	};
	virtual ~GestorAgenda() {
		// TODO Auto-generated destructor stub
	};

	void addContacto(Contacto c);

	list<Contacto&> buscarContactoApellidos(string apellidos);
	list<Contacto&> buscarContactoFavoritos();
};

#endif /* GESTORAGENDA_H_ */
