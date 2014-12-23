/*
 * Contacto.h
 *
 *  Created on: 10/12/2014
 *      Author: javier
 */

#ifndef CONTACTO_H_
#define CONTACTO_H_

#include <string>

namespace agenda {

struct Cambio{

};

class Contacto {
private:
	std::string nombre;
	std::string apellidos;
	std::string dni;
	int edad;

public:
	Contacto();
	std::string getApellidosyNombre();

	const std::string& getApellidos() const {
		return apellidos;
	}

	void setApellidos(const std::string& apellidos) {
		this->apellidos = apellidos;
	}

	const std::string& getDni() const {
		return dni;
	}

	void setDni(const std::string& dni) {
		this->dni = dni;
	}

	int getEdad() const {
		return edad;
	}

	void setEdad(int edad) {
		this->edad = edad;
	}

	const std::string& getNombre() const {
		return nombre;
	}

	void setNombre(const std::string& nombre) {
		this->nombre = nombre;
	}
};

} /* namespace agenda */

#endif /* CONTACTO_H_ */
