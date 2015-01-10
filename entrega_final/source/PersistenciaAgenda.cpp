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

string PersistenciaAgenda::nombreFichero="contacto_db.bin";

	bool PersistenciaAgenda::guardaBD(list<Contacto> listaAgenda){
		std::list<Contacto>::iterator it;

		ofstream ficheroSalida(nombreFichero.c_str(),ios::out | ios::binary |ios::trunc);

		/*al añadir el flag ios::binary el flag ios::out hay que añadirlo ya que el valor por defecto
		 no se tiene en cuenta,añadimos tambien ios::trunc por si no existe el fichero crearlo o si ya
		 contiene datos los borra y los reemplaza por los nuevos*/

			if(ficheroSalida.is_open()){
				cout << "Guardando" << endl;
			/*escribimos cada contacto de la agenda en nuestro archivo binario con el operator << 
			sobrecargado en la clase contacto y definido en Contacto.cpp, se hace asi debido a que 
			un objeto no se puede introducir directamente en un archivo binario, NOTA: utilizamos este
			archivo generado porque asi al abrir el programa poder tener la agenda tal y como la 
			teniamos cuando cerramos el programa*/

				for (it=listaAgenda.begin();it!=listaAgenda.end();it++){
					ficheroSalida << (*it);

				}

				ficheroSalida.close();
			
				return true;

			}else{

				cout << "\n ~~ Error en la creación de fichero" << endl;
				
				return false;
				
			}
	}

	list<Contacto> PersistenciaAgenda::leeBD(){
		std::list<Contacto>::iterator it;

		ifstream ficheroEntrada(nombreFichero.c_str(),ios::in | ios::binary);

		list<Contacto> listaAgenda;

		if(ficheroEntrada.is_open()){

			ficheroEntrada.seekg(0);		//establecemos el apuntador al inicio del fichero por seguridad

			/*Para introducir cada contacto de nuevo en una lista y poder tenerla en memoria y hacer uso
			de ella en nuestro programa usamos el operator >> sobrecargado en la clase Contacto y 
			definido en Contacto.cpp*/

			while(ficheroEntrada.peek() != EOF){

				Contacto c;
				ficheroEntrada >> c;
				listaAgenda.push_back(c);

			}

			ficheroEntrada.close();
		
		}else{
			
			cout << "\n ~~ Error en la apertura de fichero" << endl;
			
		}

		return listaAgenda;

	}

}
