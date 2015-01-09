/*
 * GestorBackup.cpp
 *
 *  Created on: 14/12/2014
 *      Author: cristian
 */

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>										//biblioteca stringstream para concatenar con int
#include <ctime>
#include <cstdlib>										//biblioteca para poder usar system
#include <dirent.h>										//biblioteca para poder usar opendir
#include "Contacto.h"
#include "GestorBackup.h"

using namespace std;

namespace agenda {

	string GestorBackup::dameFecha (){

		ostringstream fecha;									//variable que guardara la fecha actual

		tm *tiempo;										//puntero a struct tm donde se almacena la fecha actual
		int dia,mes,anio;
		int hora,minutos,segundos;

		time_t fecha_sis;

		time(&fecha_sis);
		tiempo=localtime(&fecha_sis);

		dia=tiempo->tm_mday;
		mes=tiempo->tm_mon + 1;
		anio=tiempo->tm_year + 1900;
		hora=tiempo->tm_hour;
		minutos=tiempo->tm_min;
		segundos=tiempo->tm_sec;

		/*NOTA: el flujo es en direccion a las flechas*/

		fecha << hora << '-' << minutos << '-' << segundos << '_' << dia << '-' << mes << '-' << anio;

		/*usamos la funcion str() para hacer un casting de ostringstream a string*/

		return fecha.str();

	}

	bool GestorBackup::crearCopiaSeguridad(list<Contacto> listaAgenda){

			list<Contacto>::iterator it;						//iterador para recorrer la lista de contactos

			/*NOTA: para que el fichero se cree el directorio Backups debe estar ya creado*/

			string nombreFichero = "Backups/CS_" + dameFecha() + ".dat";

			ofstream ficheroSalida (nombreFichero.c_str(), ios::out | ios::binary | ios::trunc);

			if (ficheroSalida.is_open()){

				/*copiamos en el archivo binario cada contacto bloque a bloque segun su tamaño*/

				for (it=listaAgenda.begin();it!=listaAgenda.end();++it){

					ficheroSalida << (*it);

				}

				ficheroSalida.close();

				return true;

			}else{

				cout << "\n	~~Error, no se pudo crear la copia de seguridad" << endl;

				return false;

			}

	}

	bool GestorBackup::borrarCopiaSeguridad (string nombreFichero){

			if (!nombreFichero.c_str()){

				cout << "\n	~~Error,la copia de seguridad no existe" << endl;

				return false;

			}

		string comando="rm Backups/" + nombreFichero;

			if (system(comando.c_str())!=0){					//ejecutamos la orden para borrar el fichero

				cout << "\n ~~Error,no se pudo borrar la copia de seguridad" << endl;

				return false;

			}else{

				cout << "\n	~~Exito,se pudo borrar la copia de seguridad" << endl;

				return true;

			}
	}

	list<Contacto> GestorBackup::obtenerCopiaSeguridad(string nombreFichero){

		nombreFichero = "Backups/" + nombreFichero;			//le añadimos al nombre del fichero la ruta

		ifstream ficheroEntrada(nombreFichero.c_str(),ios::in | ios::binary);

		list<Contacto> listaAgenda;

		if (ficheroEntrada.is_open()){

			ficheroEntrada.seekg(0);

					/*leemos cada contacto bloque a bloque segun el tamaño de Contacto*/

					while (ficheroEntrada.peek() != EOF){

						Contacto c;
						ficheroEntrada >> c;
						listaAgenda.push_back(c);

					}

					ficheroEntrada.close();

					return listaAgenda;

		}else{

			cout << "\n	~~Error,no se pudo abrir el fichero" << endl;

		}

	}

	list<string> GestorBackup::getListaCopiasSeguridad(){

		list<string> listaCopias;							//lista para guardar los nom de los archivos leidos

		/* struct DIR para abrir el directorio y struct dirent la cual almacena los nombres de los
		ficheros,ambas estructuras definidas en dirent.h*/

		DIR *dir;
		dirent *pdir;

		string path="Backups";								//ruta donde se encuentran las copias de seguridad

		dir = opendir(path.c_str());

		if (dir){

			/*NOTA: readdir devuelve un puntero a NULL si se llega al final del directorio*/

			while((pdir = readdir(dir))!=NULL){

				listaCopias.push_back(pdir->d_name);

			}

			closedir(dir);

			return listaCopias;

		}else{

			cout << "\n ~~Error en la ruta del directorio" << endl;

		}
	}

	bool GestorBackup::crearArchivoTexto (list<Contacto> listaAgenda){

		ofstream ficheroSalida("Mi_agenda.txt",ios::out | ios::trunc);
		list<Contacto>::iterator it;
		int nveces=0,i;

			if (ficheroSalida.is_open()){

				for (it=listaAgenda.begin();it!=listaAgenda.end();++it){

					ficheroSalida << "Mi agenda,exportada en fecha: " << dameFecha() << endl;
					ficheroSalida << "=================================================" << endl;
					ficheroSalida << "Nombre: " << (*it).getNombre() << endl;
					ficheroSalida << "Apellidos: " << (*it).getApellidos() << endl;
					ficheroSalida << "DNI: " << (*it).getDni() << endl;
					nveces = (*it).telefonos.size();

						for (i=0;i<nveces;i++){

							ficheroSalida << "Telefono " << i << ":" << (*it).telefonos[i] << endl;

						}

					ficheroSalida << "Correo-electrónico: " << (*it).getCorreoE() << endl;
					nveces=(*it).direcciones_.size();
					ficheroSalida << "Dirección/es: " << endl;

						for (i=0;i<nveces;i++){

							ficheroSalida << "calle: " << (*it).direcciones_[i].calle << endl;
							ficheroSalida << "numero: " << (*it).direcciones_[i].numero << endl;
							ficheroSalida << "piso: " << (*it).direcciones_[i].piso << endl;
							ficheroSalida << "puerta: " << (*it).direcciones_[i].puerta << endl;

						}

					ficheroSalida << "Anotaciones: " << (*it).getCorreoE() << endl;
					ficheroSalida << "Favorito: " << (*it).getFavoritos() << endl;
					ficheroSalida << "NConsultas: " << (*it).getConsultas() << endl;

					nveces=(*it).redes_.size();
					ficheroSalida << "Cuenta Red/es: " < endl;

						for (i=0;i<nveces;i++){

							ficheroSalida << "Red: " << (*it).redes_[i].red << endl;
							ficheroSalida << "Usuario: " << (*it).redes_[i].usuario << endl;

						}

				}

				return true;

			}else{

				return false;

			}

	}

} /* namespace agenda */
