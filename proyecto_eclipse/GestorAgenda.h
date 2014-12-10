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

class GestorAgenda
{
private:
	list<Contacto> listaContactos_;

	bool comparaNombre(Contacto a, Contacto b);
	bool comparaNConsultas(Contacto a, Contacto b);

	string simplificaCadena(string cad);

public:
	GestorAgenda() {
		// TODO Auto-generated constructor stub

	};
	virtual ~GestorAgenda() {
		// TODO Auto-generated destructor stub
	};

	bool cargaListaContactos(list<Contacto> nuevaLista);

	list<Contacto&> buscarContactoApellidos(string apellidos);
	list<Contacto&> buscarContactoFavoritos();
	list<Contacto&> masUsados(int cuantos);

	void addContacto(Contacto c);
	inline bool modificarContacto(Contacto c, list<Cambio> cambios){c.modificar(cambios)};
	void borrarContacto(Contacto c);

	list<string> listarCopiasSeguridad();
	void crearCopiaSeguridad();
	void restaurarCopiaSegurirad(string id);
	list<string> borrarCopiaSeguridad(string id); //???

	void imprimirTexto(string nombreFichero);
};

#endif /* GESTORAGENDA_H_ */
