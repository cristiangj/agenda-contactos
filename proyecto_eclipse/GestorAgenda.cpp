/*
 * GestorAgenda.cpp
 *
 *  Created on: 08/12/2014
 *      Author: aurora
 */


#include "GestorAgenda.h"
#include <cctype>	//std::tolower
#include <string>
#include <list>

namespace agenda{


std::string simplificaCadena(std::string cad){

	for(int i=0;i<cad.length();i++){
		cad[i]=tolower(cad[i]);
		//Falta averiguar como quitar tildes
	}
	return cad;
}




bool nombresIguales(Contacto a, Contacto b){

	a.setApellidos(simplificaCadena(a.getApellidos()));
	a.setNombre(simplificaCadena(a.getNombre()));

	b.setApellidos(simplificaCadena(b.getApellidos()));
	b.setNombre(simplificaCadena(b.getNombre()));

	if((a.getNombre()==b.getNombre())&&(a.getApellido()==b.getApellido()))
		return true;
	else
		return false;
}



bool comparaNombre(Contacto a, Contacto b){

	a.setApellidos(simplificaCadena(a.getApellidos()));
	b.setApellidos(simplificaCadena(b.getApellidos()));

	int i=0;
	while((i<a.getApellidos().length())&&(i<b.getApellidos().length())){
		if(a.getApellidos()[i]<b.getApellidos()[i])
			return true;
		else{
			if(a.getApellidos()[i]>b.getApellidos()[i])
				return false;
		}
	}

	a.setNombre(simplificaCadena(a.getNombre()));
	b.setNombre(simplificaCadena(b.getNombre()));

	i=0;
	while((i<a.getNombre().length())&&(i<b.getNombre().length())){
			if(a.getNombre()[i]<b.getNombre()[i])
				return true;
			else{
				if(a.getNombre()[i]>b.getNombre()[i])
					return false;
			}
	}
	return true;
}




bool comparaNConsultas(Contacto a, Contacto b){

	if(a.getNConsultas()>=b.getNConsultas())
		return true;
	else
		return false;
}



bool GestorAgenda::addContacto(Contacto c){	//Función cambiada de void a bool

	listaContactos_.push_back(c);
	listaContactos_.sort(comparaNombre);
	//Añadir comprobación si existe contacto de igual nombre
}




void GestorAgenda::borrarContacto(Contacto c){	//Se podría comprobar si se ha borrado un contacto

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		if(nombresIguales(*i,c)){
			listaContactos_.erase(i);
			break;
		}
	}
}




std::list<Contacto> GestorAgenda::buscarContactoApellidos(std::string apellidos){

	apellidos=simplificaCadena(apellidos);
	std::list<Contacto> result;

	for(list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		i->getApellidos()=simplificaCadena(i->getApellidos());
		if(i->getApellidos()==apellidos)
			result.push_back(*i);
	}

	return result;
}




std::list<Contacto> GestorAgenda::buscarContactoFavoritos(){

	std::list<Contacto> result;

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		if(i->getFavorito()==true)
			result.push_back(*i);
	}
	return result;
}




std::list<Contacto> GestorAgenda::masUsados(int cuantos){

	std::list<Contacto> result;

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		if(i->getNConsultas()>result.end()){
			result.pop_back();
			result.push_back(*i);
		}
		result.sort(comparaNConsultas);
	}
	return result;
}

} /*namespace agenda*/
