#include "contacto.h"
#include <string>
#include <vector>
#include <list>

Contacto::Contacto (string nombre, string apellidos, string dni, string correoe, string anotaciones, bool favoritos, int nconsultas) {
	nombre_=nombre;
	apellidos_=apellidos;
	dni_=dni;
	correoE_=correoe;
	anotaciones_=anotaciones;
	favoritos_=favoritos;
	nconsultas_=nconsultas;

}


void Contacto::setNombre (string nombre) {
	nombre_=nombre;
}


bool Contacto::setApellidos (string apellidos) {
	if (!apellidos.empty()) {
		apellidos_=apellidos;
		return true;
	}
	else {
		return false;
	}
}


bool Contacto::setDni (string dni) {
	int tam=dni.length();

	if (tam==9) {
		dni_=dni;
		return true;
	}
	else {
		return false;
	}
}


bool Contacto::setCorreoE (string correoe) {
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


void Contacto::setAnotaciones (string anotaciones) {
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


bool Contacto::setTelefono (string telefono) {
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


bool Contacto::modificar (list<Cambio> cambios) {
	list <Cambio> cambios {
		list <Cambio>::iterator i;
		for (i=cambios.begin(); i!=cambios.end(); i++) {

			switch(i->idcampo) {
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
				setDireccion(i->valor);
			break;

			case CAMPO_ANOTACION:
				setAnotaciones(i->valor);
			break;

			case CAMPO_FAVORITOS:
				setFavoritos(i->valor);
			break;

			case CAMPO_CONSULTA:
				setNconsultas(i->valor);
			break;

			case CAMPO_RED:
				setRedes(i->valor);
			break;

		}

		}
	}
}
