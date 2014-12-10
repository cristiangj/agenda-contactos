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

namespace agenda{

class GestorAgenda
{
private:
	std::list<Contacto> listaContactos_;

	inline bool cargaListaContactos(std::list<Contacto> nuevaLista){listaContactos_=nuevaLista;};

	bool nombresIguales(Contacto a, Contacto b);
	bool comparaNombre(Contacto a, Contacto b);
	bool comparaNConsultas(Contacto a, Contacto b);

	std::string simplificaCadena(std::string cad);

public:
	GestorAgenda() {
		// TODO Auto-generated constructor stub
		cargaListaContactos(nuevaLista);
	};
	virtual ~GestorAgenda() {
		// TODO Auto-generated destructor stub
		PersistenciaAgenda respaldo;
		respaldo.escribeBD(listaContactos_);
	};

	std::list<Contacto> buscarContactoApellidos(std::string apellidos);
	std::list<Contacto> buscarContactoFavoritos();
	std::list<Contacto> masUsados(int cuantos);

	void addContacto(Contacto c);
	inline bool modificarContacto(Contacto c, std::list<Cambio> cambios){c.modificar(cambios)};
	void borrarContacto(Contacto c);

};

} /*namespace agenda*/
#endif /* GESTORAGENDA_H_ */
