/*
 * GestorAgenda.h
 *
 *  Created on: 08/12/2014
 *      Author: aurora
 */

#ifndef GESTORAGENDA_H_
#define GESTORAGENDA_H_

//incluir .h de la clase Contacto
//incluir .h de la clase GestorBackup
//incluir .h de la clase PersistenciaAgenda
#include <list>
#include <string>

namespace agenda {

class GestorAgenda {

private:
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
	 * Necesaria para addContacto y borrarContacto
	 */
	int comparaNombres(Contacto a, Contacto b);

	/*
	 * Función que compara el número de consultas de dos contactos
	 * Necesaria para masUsados
	 */
	inline bool comparaConsultas(Contacto a, Contacto b) {if(a.getConsultas()>=b.getConsultas()) return true; else return false;};

	/*
	 * Función que sustituye caracteres críticos para búsqueda de contactos por letras normales
	 * Necesaria para comparaNombres y buscarContactoApellidos
	 */
	std::string simplificaCadena(std::string cad);


public:
	GestorAgenda() {
		// TODO Auto-generated constructor stub
		PersistenciaAgenda respaldo;	//Por medio de la clase PersistenciaAgenda recupera los datos desde un fichero
		std::list<Contacto> nuevaLista = respaldo.leeBD();
		cargaListaContactos(nuevaLista);
	};

	virtual ~GestorAgenda() {
		// TODO Auto-generated destructor stub
		PersistenciaAgenda respaldo;	//Por medio de la clase PersistenciaAgenda guarda los datos en un fichero
		respaldo.escribeBD(listaContactos_);
	};

	/*
	 * Función que devuelve todos los contactos que coinciden con el apellido pasado como parámetros
	 */
	std::list<Contacto> buscarContactoApellidos(std::string apellidos);

	/*
	 * Función que devuelve todos los contactos preseleccionados como favoritos
	 */
	std::list<Contacto> buscarContactoFavoritos();

	/*
	 * Función que devuelve un número pasado como parámetro de contactos seleccionándolos por el número de consultas de cada contacto
	 */
	std::vector<Contacto> masUsados(int cuantos);

	/*
	 * Añade un contacto a listaContactos_
	 */
	bool addContacto(Contacto c);

	/*
	 * Llama a la clase Contacto para que aplique modificaciones a un contacto
	 */
	inline bool modificarContacto(Contacto c, std::list<Cambio> cambios) {if (c.modificar(cambios)) return true; else return false;};

	/*
	 * Borra un contacto si está en la lista
	 */
	bool borrarContacto(Contacto c);

	/*
	 * Llama a la clase GestorBackup para que presente los datos actuales de la agenda en un formato legible para el usuario
	 */
	bool imprimirTexto(std::string nombreFichero);

}; /* class GestorAgenda */
} /* namespace agenda */
#endif /* GESTORAGENDA_H_ */
