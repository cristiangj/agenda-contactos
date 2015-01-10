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

GestorAgenda *GestorAgenda::instancia = 0;

std::string GestorAgenda::simplificaCadena(std::string cad){

	//Quita las tildes
	std::vector <std::string> tildes={"Á","á","É","é","Í","í","Ó","ó","Ú","ú"};	//Al compilar: g++ -std=c++11 archivo.cpp (inicialización de vector válida a partir del estandar 2011)
	std::vector <std::string> notildes={"A","a","E","e","I","i","O","o","U","u"};
	size_t reemplazo;
	for(int i=0;i<tildes.size();i++){
		while((reemplazo=cad.find(tildes[i])) != std::string::npos)
			cad.replace(reemplazo, tildes[i].size(),notildes[i]);
	}

	//Quita las mayúsculas
	for(int i=0;i<cad.length();i++)
		cad[i]=tolower(cad[i]);

	return cad;
}



int GestorAgenda::comparaNombres(const Contacto &a, const Contacto &b){
	std::string nombreA = simplificaCadena(a.getNombre());
	std::string apellidoA = simplificaCadena(a.getApellidos());
	std::string nombreB = simplificaCadena(b.getNombre());
	std::string apellidoB = simplificaCadena(b.getApellidos());

	int i=0;
	while((i<apellidoA.length())&&(i<apellidoB.length())){
		if(apellidoA[i]<apellidoB[i])
			return A_ANTES_B;

		if(apellidoA[i]>apellidoB[i])
			return B_ANTES_A;
	}
	//Si llega hasta aquí => apellidos iguales

	i=0;
	while((i<nombreA.length())&&(i<nombreB.length())){
			if(nombreA[i]<nombreB[i])
				return A_ANTES_B;

			if(nombreA[i]>nombreB[i])
				return B_ANTES_A;
	}
	//Si llega hasta aquí => nombres completos iguales

	return A_IGUAL_B;
}

bool GestorAgenda::compare(const Contacto &c1, const Contacto &c2){
	int check = comparaNombres(c1,c2);
	bool ret;

	switch(check){
	case A_ANTES_B:
		ret = true;
		break;

	case B_ANTES_A:
	case A_IGUAL_B:
		ret = false;
		break;
	}

	return ret;
}



bool GestorAgenda::comparaConsultas(Contacto a, Contacto b){
	bool aMAYORb;
	if(a.getNconsultas()>=b.getNconsultas()) aMAYORb = true;
	else if(a.getNconsultas()<b.getNconsultas()) aMAYORb = false;
	return aMAYORb;
}

void GestorAgenda::setListaContactos(std::list<Contacto> lista){
	listaContactos_=lista;
	PersistenciaAgenda::guardaBD(listaContactos_);
}


bool GestorAgenda::addContacto(Contacto c){

	listaContactos_.push_back(c);
	ordenaListaContactos();
	PersistenciaAgenda::guardaBD(listaContactos_);

//	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
//		if(comparaNombres(*i,c)==B_ANTES_A || listaContactos_.empty()){
//			listaContactos_.insert(i,c);
//			PersistenciaAgenda::guardaBD(listaContactos_);
//			break;
//		}
//
//		if(comparaNombres(*i,c)==A_IGUAL_B)	//Comprobar si altera el formato de los nombre en listaContactos_
//			return false;
//
//	}
	return true;
}


bool GestorAgenda::modificarContacto(Contacto nuevo, Contacto viejo){
	bool retorna=false;
	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end() && !retorna; i++){
		if(i->getApellidosyNombre().compare(viejo.getApellidosyNombre()) == 0){
			i = listaContactos_.erase(i);
			listaContactos_.insert(i,nuevo);
			retorna=true;
			PersistenciaAgenda::guardaBD(listaContactos_);
		}
	}
	ordenaListaContactos();

	return retorna;
}



bool GestorAgenda::borrarContacto(Contacto c){	//Función cambiada de void a bool

	bool retorna=false;

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end() && !retorna; i++){
		if(i->getApellidosyNombre().compare(c.getApellidosyNombre()) == 0){	//Comprobar si altera el formato de los nombres en listaContactos_
			listaContactos_.erase(i);
			retorna=true;
			PersistenciaAgenda::guardaBD(listaContactos_);
		}
	}
	return retorna;
}

void GestorAgenda::ordenaListaContactos(){
	listaContactos_.sort(GestorAgenda::compare);
}


std::vector<Contacto> GestorAgenda::buscarContactoApellidos(std::string apellidos){

	apellidos=simplificaCadena(apellidos);
	std::string aux;	//Los cambios en el formato del nombre se harán sobre una cadena auxiliar para no alterar mayúsculas y tildes en listaContactos_
	std::vector<Contacto> result;

	for(std::list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		aux=simplificaCadena(i->getApellidos());
		if(aux.find(apellidos) != std::string::npos) //si forma parte de los apellidos
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
	std::vector<Contacto> result;
	std::list<Contacto> aux=listaContactos_;
	aux.sort(comparaConsultas);
	auto j=aux.begin();
	for(int i=0;i<cuantos && j != aux.end();i++,j++)
		result.push_back(*j);
	return result;
}



bool GestorAgenda::imprimirTexto(){	//Función cambiada de void a bool
	if(GestorBackup::crearArchivoTexto(listaContactos_))
		return true;
	else
		return false;
}

} /* namespace agenda */
