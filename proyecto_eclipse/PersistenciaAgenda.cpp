/*
 * PersistenciaAgenda.cpp
 *
 *  Created on: 9/12/2014
 *      Author: cristian
 */

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstring>
#include "PersistenciaAgenda.h"

using namespace std;

namespace agenda{

	bool PersistenciaAgenda::guardaBD(list<Contacto> listaAgenda){

		ofstream ficheroSalida(nombreFichero.c_str(),ios::out | ios::binary |ios::trunc);

		/*al añadir el flag ios::binary el flag ios::out hay que añadirlo ya que el valor por defecto
		 no se tiene en cuenta,añadimos tambien ios::trunc por si no existe el fichero crearlo o si ya
		 contiene datos los borra y los reemplaza por los nuevos*/

			if(ficheroSalida.is_open()){

			
			/*NOTA: podemos escribir el bloque completo (el objeto) que se encuentra en esa posicion de la lista
			 a traves del iterador asignado a listaAgenda*/

				for (it=listaAgenda.begin();it!=listaAgenda.end();it++){

					ficheroSalida.write((char *) &(*it),sizeof(Contacto));

				}

				ficheroSalida.close();
			
				return true;

			}else{

				cout << "\n ~~ Error en la creación de fichero" << endl;
				
				return false;
				
			}
	}

	list<Contacto> PersistenciaAgenda::leeBD(){

		ifstream ficheroEntrada(nombreFichero.c_str(),ios::in | ios::binary);

		list<Contacto> listaAgenda;
		Contacto c;

		if(ficheroEntrada.is_open()){

			ficheroEntrada.seekg(0);			//establecemos el apuntador al inicio del fichero por seguridad

			/*Se puede leer cada contacto como un bloque completo según el tamaño que ocupe dicho
			 contacto,el tamaño de bloque para cada contacto lo calculamos con sizeof*/

			while(ficheroEntrada.eof()!=EOF){

				ficheroEntrada.read((char *) &c,sizeof(c));
				listaAgenda.push_back(c);

			}

			ficheroEntrada.close();
			
			return listaAgenda;
		
		}else{
			
			cout << "\n ~~ Error en la apertura de fichero" << endl;
			
		}

	}

}
