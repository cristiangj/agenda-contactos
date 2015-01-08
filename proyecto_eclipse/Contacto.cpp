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



bool Contacto::setNombre (std::string nombre) {
	nombre_=nombre;
	return true;
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

std::string Contacto::getNombreRed(tipoRed t){
	std::string nombre;

	switch(t){
	case twitter:
		nombre = "Twitter";
		break;

	case facebook:
		nombre = "Facebook";
		break;

	case googleplus:
		nombre = "Goole +";
		break;

	default:
		nombre = "Red desconocida";
		break;
	}

	return nombre;
}

} /* namespace agenda */

