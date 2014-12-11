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
#include <vector>

namespace agenda{


#define A_IGUAL_B 0
#define A_ANTES_QUE_B 1
#define B_ANTES_QUE_A 2



std::string simplificaCadena(std::string cad){

	for(int i=0;i<cad.length();i++){
		cad[i]=tolower(cad[i]);
		//Falta averiguar como quitar tildes
	}
	return cad;
}



int comparaNombres(Contacto a, Contacto b){

	a.setApellidos(simplificaCadena(a.getApellidos()));
	b.setApellidos(simplificaCadena(b.getApellidos()));

	int i=0;
	while((i<a.getApellidos().length())&&(i<b.getApellidos().length())){
		if(a.getApellidos()[i]<b.getApellidos()[i])
			return A_ANTES_QUE_B;

		if(a.getApellidos()[i]>b.getApellidos()[i])
			return B_ANTES_QUE_A;
	}

	a.setNombre(simplificaCadena(a.getNombre()));
	b.setNombre(simplificaCadena(b.getNombre()));

	i=0;
	while((i<a.getNombre().length())&&(i<b.getNombre().length())){
			if(a.getNombre()[i]<b.getNombre()[i])
				return A_ANTES_QUE_B;

			if(a.getNombre()[i]>b.getNombre()[i])
				return B_ANTES_QUE_A;
	}

	return A_IGUAL_B;
}




bool GestorAgenda::addContacto(Contacto c){

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		if(comparaNombres(*i,c)==A_IGUAL_B)
			return false;
		if(comparaNombres(*i,c)==B_ANTES_QUE_A){
			listaContactos_.insert(i,c);
			break;
		}
	}
	return true;
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

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
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




std::vector<Contacto> GestorAgenda::masUsados(int cuantos){

	std::vector<Contacto> result(5);
	Contacto aux,sig;
	int z;

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		for(int j=0;j<cuantos;j++){
			if(!comparaNConsultas(*i,result[j])){
				for(z=cuantos;z>0;z--)
					result[z]=result[z-1];
				z[0]=*i;
			}
		}
	}
	return result;
}



bool GestorAgenda::imprimirTexto(std::string nombreFichero){	//Función cambiada de void a bool
	GestorBackup respaldo;
	if(respaldo.crearArchivoTexto(listaContactos_))	//Aquí habría que pasar también nombre fichero
		return true;
	else
		return false;
}

} /*namespace agenda*/
