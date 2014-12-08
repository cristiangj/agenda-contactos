/*
 * GestorAgenda.cpp
 *
 *  Created on: 08/12/2014
 *      Author: aurora
 */

#include "GestorAgenda.h"
#include <cctype> //std::tolower


string simplificaCadena(string cad)
{
	for(int i=0;i<cad.length();i++){
		cad[i]=tolower(cad[i]);
		//Falta averiguar como quitar acentos
	}
	return cad;
}




bool comparaApellido(Contacto a,Contacto b)
{
	a.getApellidos()=simplificaCadena(a.getApellidos());
	b.getApellidos()=simplificaCadena(b.getApellidos());

	int i=0;
	while((i<a.getApellidos().length())&&(i<b.getApellidos().length())){
		if(a.getApellidos()[i]<b.getApellidos()[i])
			return true;
		else{
			if(a.getApellidos()[i]>b.getApellidos()[i])
				return false;
		}
	}

	a.getNombre()=simplificaCadena(a.getNombre());
	b.getNombre()=simplificaCadena(b.getNombre());

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





void GestorAgenda::addContacto(Contacto c)
{
	listaContactos_.push_back(c);
	listaContactos_.sort(comparaApellido);
}



list<Contacto&> GestorAgenda::buscarContactoApellidos(string apellidos)
{
	apellidos=simplificaCadena(apellidos);
	list<Contacto&>result;

	for(list<Contacto>::iterator i=listaContactos_.begin(); i!=listaContactos_.end(); i++){
		i->getApellidos()=simplificaCadena(i->getApellidos());
		if(i->getApellidos()==apellidos)
			result.push_back(*i);
	}

	return result;
}
