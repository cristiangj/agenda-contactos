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
#define A_ANTES_B 1
#define B_ANTES_A 2



std::string simplificaCadena(std::string cad){

	//Quita las tildes
	std::vector <std::string> tildes={"Á","á","É","é","Í","í","Ó","ó","Ú","ú"};	//Al compilar: g++ -std=c++11 archivo.cpp (inicialización de vector válida a partir del estandar 2011)
	std::vector <std::string> notildes={"A","a","E","e","I","i","O","o","U","u"};
	size_t reemplazo;
	for(int i=0;i<tildes.size();i++){
		while((reemplazo=cad.find(tildes[i])))
			cad.replace(reemplazo, tildes[i].size(),notildes[i]);
	}

	//Quita las mayúsculas
	for(int i=0;i<cad.length();i++)
		cad[i]=tolower(cad[i]);

	return cad;
}



int comparaNombres(Contacto a, Contacto b){

	a.setApellidos(simplificaCadena(a.getApellidos()));
	b.setApellidos(simplificaCadena(b.getApellidos()));

	int i=0;
	while((i<a.getApellidos().length())&&(i<b.getApellidos().length())){
		if(a.getApellidos()[i]<b.getApellidos()[i])
			return A_ANTES_B;

		if(a.getApellidos()[i]>b.getApellidos()[i])
			return B_ANTES_A;
	}
	//Si llega hasta aquí => apellidos iguales

	a.setNombre(simplificaCadena(a.getNombre()));
	b.setNombre(simplificaCadena(b.getNombre()));

	i=0;
	while((i<a.getNombre().length())&&(i<b.getNombre().length())){
			if(a.getNombre()[i]<b.getNombre()[i])
				return A_ANTES_B;

			if(a.getNombre()[i]>b.getNombre()[i])
				return B_ANTES_A;
	}
	//Si llega hasta aquí => nombres completos iguales

	return A_IGUAL_B;
}



bool comparaConsultas(Contacto a, Contacto b){
	if(a.getNconsultas()>=b.getNconsultas()) return true;
	else if(a.getNconsultas()<b.getNconsultas()) return false;
	return (a.getNconsultas()>=b.getNconsultas());
}




bool GestorAgenda::addContacto(Contacto c){

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		if(comparaNombres(*i,c)==A_IGUAL_B)	//Comprobar si altera el formato de los nombre en listaContactos_
			return false;
		if(comparaNombres(*i,c)==B_ANTES_A){
			listaContactos_.insert(i,c);
			PersistenciaAgenda respaldo;
			respaldo.guardaBD(listaContactos_);
			break;
		}
	}
	return true;
}


bool GestorAgenda::modificarContacto(Contacto nuevo, Contacto viejo){

	bool retorna=false;
	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		if(comparaNombres(*i, viejo)==A_IGUAL_B){
			listaContactos_.erase(i);
			listaContactos_.insert(i,nuevo);
			retorna=true;
			PersistenciaAgenda respaldo;
			respaldo.guardaBD(listaContactos_);
			break;
		}
	}
	return retorna;
}



bool GestorAgenda::borrarContacto(Contacto c){	//Función cambiada de void a bool

	bool retorna=false;

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		if(comparaNombres(*i,c)==A_IGUAL_B){	//Comprobar si altera el formato de los nombres en listaContactos_
			listaContactos_.erase(i);
			retorna=true;
			PersistenciaAgenda respaldo;
			respaldo.guardaBD(listaContactos_);
			break;
		}
	}
	return retorna;
}




std::vector<Contacto> GestorAgenda::buscarContactoApellidos(std::string apellidos){

	apellidos=simplificaCadena(apellidos);
	std::string aux;	//Los cambios en el formato del nombre se harán sobre una cadena auxiliar para no alterar mayúsculas y tildes en listaContactos_
	std::vector<Contacto> result;

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		aux=simplificaCadena(i->getApellidos());
		if(aux==apellidos)
			result.push_back(*i);
	}
	return result;
}




std::vector<Contacto> GestorAgenda::buscarContactoFavoritos(){

	std::vector<Contacto> result;

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		if(i->getFavoritos()==true)
			result.push_back(*i);
	}
	return result;
}




std::vector<Contacto> GestorAgenda::masUsados(int cuantos){

	std::vector<Contacto> result(cuantos);
	std::list<Contacto> aux=listaContactos_;
	aux.sort(comparaConsultas);
	auto j=aux.begin();
	for(int i=0;i<cuantos;i++,j++)
		result[i]=*j;

	return result;
}



bool GestorAgenda::imprimirTexto(){	//Función cambiada de void a bool
	if(GestorBackup::crearArchivoTexto(listaContactos_))
		return true;
	else
		return false;
}

} /* namespace agenda */
