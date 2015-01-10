/*
 * GestorAgenda.h
 *
 *  Created on: 08/12/2014
 *      Author: aurora
 */

#ifndef GESTORAGENDA_H_
#define GESTORAGENDA_H_

#include "Contacto.h"
#include "GestorBackup.h"
#include "PersistenciaAgenda.h"
#include <list>
#include <string>

namespace agenda {

class GestorAgenda {

private:
	GestorAgenda() {
		PersistenciaAgenda respaldo;	//Por medio de la clase PersistenciaAgenda recupera los datos desde un fichero
		std::list<Contacto> nuevaLista = respaldo.leeBD();
		cargaListaContactos(nuevaLista);
	};

	GestorAgenda(GestorAgenda const&); //No implementar
	void operator=(GestorAgenda const&); // No implementar

	/*
	 * Variable tipo list para tener soporte donde modificar los contactos
	 */
	std::list<Contacto> listaContactos_;

	/*
	 * Función que copia una lista de contactos a la variable sobre la que vamos a trabajar
	 * Necesaria para el constructor
	 */
	inline void cargaListaContactos(std::list<Contacto> nuevaLista) {listaContactos_ = nuevaLista;};	//Función cambiada de bool a void

	/*
	 * Función que devuelve distintos enteros según el orden alfabético que tengan los contactos pasados como parámetros
	 * Necesaria para addContacto modificarContacto y borrarContacto
	 */
	int comparaNombres(Contacto a, Contacto b);

	/*
	* Función que compara el número de consultas de dos contactos
	* Necesaria para masUsados
	*/
	static bool comparaConsultas(const Contacto a, const Contacto b);

	/*
	 * Función que sustituye caracteres críticos para búsqueda de contactos por letras normales
	 * Necesaria para comparaNombres y buscarContactoApellidos
	 */
	std::string simplificaCadena(std::string cad);


public:
	/*
	 * Devuelve una instancia del gestor (para mantener el singleton)
	 */
	static GestorAgenda& getGestor(){
		static GestorAgenda instancia;
		return instancia;
	}

	virtual ~GestorAgenda() {
		// TODO Auto-generated destructor stub
		PersistenciaAgenda respaldo;	//Por medio de la clase PersistenciaAgenda guarda los datos en un fichero
		respaldo.guardaBD(listaContactos_);
	};


	std::list<Contacto> getListaContactos() { return listaContactos_;};
	void setListaContactos(std::list<Contacto> lista) { listaContactos_ = lista;};

	/*
	 * Función que devuelve todos los contactos que coinciden con el apellido pasado como parámetros
	 */
	std::vector<Contacto> buscarContactoApellidos(std::string apellidos);

	/*
	 * Función que devuelve todos los contactos preseleccionados como favoritos
	 */
	std::vector<Contacto> buscarContactoFavoritos();

	/*
	 * Función que devuelve un número pasado como parámetro de contactos seleccionándolos por el número de consultas de cada contacto
	 */
	std::vector<Contacto> masUsados(int cuantos);

	/*
	 * Añade un contacto a listaContactos_
	 */
	bool addContacto(Contacto c);

	/*
	 * Se le pasa un contacto antes y después de modificarlo, buscando el viejo y reemplanzandolo en listaContactos_ por el nuevo
	 */
	bool modificarContacto(Contacto nuevo, Contacto viejo);

	/*
	 * Borra un contacto si está en la lista
	 */
	bool borrarContacto(Contacto c);

	/*
	 * Llama a la clase GestorBackup para que presente los datos actuales de la agenda en un formato legible para el usuario
	 */
	bool imprimirTexto();



}; /* class GestorAgenda */
} /* namespace agenda */
#endif /* GESTORAGENDA_H_ */
