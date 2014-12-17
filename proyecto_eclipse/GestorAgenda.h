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

namespace agenda {

class GestorAgenda {
private:
	std::list<Contacto> listaContactos_;

	inline void cargaListaContactos(std::list<Contacto> nuevaLista) {
		listaContactos_ = nuevaLista;
	}
	;	//Función cambiada de bool a void

	int comparaNombres(Contacto a, Contacto b);
	inline bool comparaNConsultas(Contacto a, Contacto b) {if(a.getNConsultas()>=b.getNConsultas()) return true; else return false;};

std::string simplificaCadena(std::string cad);

public:
GestorAgenda() {
	// TODO Auto-generated constructor stub
	PersistenciaAgenda respaldo;
	std::list<Contacto> nuevaLista = respaldo.leeBD();
	cargaListaContactos(nuevaLista);
}
;

virtual ~GestorAgenda() {
	// TODO Auto-generated destructor stub
	PersistenciaAgenda respaldo;
	respaldo.escribeBD(listaContactos_);
}
;

std::list<Contacto> buscarContactoApellidos(std::string apellidos);
std::list<Contacto> buscarContactoFavoritos();
std::list<Contacto> masUsados(int cuantos);

bool addContacto(Contacto c);
inline bool modificarContacto(Contacto c, std::list<Cambio> cambios) {
	if (c.modificar(cambios))
		return true;
	else
		return false;
}
;
void borrarContacto(Contacto c);

bool imprimirTexto(std::string nombreFichero);
};

} /*namespace agenda*/
#endif /* GESTORAGENDA_H_ */
