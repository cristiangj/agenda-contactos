/*
 * Contacto.cpp
 *
 *  Created on: 10/12/2014
 *      Author: Enrique
 */

#include "Contacto.h"
#include <string>
#include <vector>
#include <list>

namespace agenda {

Contacto::Contacto (std::string nombre, std::string apellidos, std::string dni, std::string correoe, std::string anotaciones, bool favoritos, int nconsultas) {
	nombre_=nombre;
	apellidos_=apellidos;
	dni_=dni;
	correoE_=correoe;
	anotaciones_=anotaciones;
	favoritos_=favoritos;
	nconsultas_=nconsultas;

}


void Contacto::setNombre (std::string nombre) {
	nombre_=nombre;
}


bool Contacto::setApellidos (std::string apellidos) {
	if (!apellidos.empty()) {
		apellidos_=apellidos;
		return true;
	}
	else {
		return false;
	}
}


bool Contacto::setDni (std::string dni) {
	int tam=dni.length();

	if (tam==9) {
		dni_=dni;
		return true;
	}
	else {
		return false;
	}
}


bool Contacto::setCorreoE (std::string correoe) {
	int tam=correoe.length();
	int pos=correoe.find("@");
	int pos2=correoe.find(".",pos);

	if ( (pos>0) && (pos2>pos+1 && pos2<(tam-1)) ) {
		correoE_=correoe;
		return true;
	}
	else {
		return false;
	}
}


void Contacto::setAnotaciones (std::string anotaciones) {
	anotaciones_=anotaciones;
}


void Contacto::setFavoritos (bool favoritos) {
	favoritos_=favoritos;
}


void Contacto::setNconsultas (int nconsultas) {
	nconsultas_=nconsultas;
}
void Contacto::anadirNconsultas () {
	nconsultas_++;
}


bool Contacto::setTelefono (std::string telefono) {
	int tam=telefono.length();

	if (tam==9) {
		telefonos_.push_back(telefono);
		return true;
	}
	else {
		return false;
	}
}


bool Contacto::setDireccion (Direccion dir) {
	if ( dir.calle.empty() || (dir.numero<1)) {
		return false;
	}
	else {
		direcciones_.push_back(dir);
		return true;
	}
}


bool Contacto::setRed (CuentaRedSocial red) {
	redes_.push_back(red);
	return true;
}


void Contacto::modificar (std::list<Cambio> cambios) {

	std::list <Cambio>::iterator i;
	for (i=cambios.begin(); i!=cambios.end(); i++) {

		switch(i->idCampo) {
		case CAMPO_NOMBRE:
			setNombre(i->valor);
		break;

		case CAMPO_APELLIDO:
			setApellidos(i->valor);
		break;

		case CAMPO_DNI:
			setDni(i->valor);
		break;

		case CAMPO_TELEFONO:
			setTelefono(i->valor);
		break;

		case CAMPO_CORREOE:
			setCorreoE(i->valor);
		break;

		case CAMPO_DIRECCION:
			Direccion d;
			d.calle = i->valor;
			d.numero = i -> valorN;

			setDireccion(d);
		break;

		case CAMPO_ANOTACION:
			setAnotaciones(i->valor);
		break;

		case CAMPO_FAVORITOS:
			bool fav;

			if(i->valor.compare("true") == 0) fav = true;
			else fav = false;

			setFavoritos(fav);
		break;

		case CAMPO_RED:
			CuentaRedSocial r;
			r.usuario = i->valor;
			r.red = i->valorN;

			setRed(r);
		break;

		}

	}
}

} /* namespace agenda */
