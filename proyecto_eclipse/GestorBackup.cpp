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

				/*copiamos en el archivo binario cada contacto con la sobrecarga del operador << realizada
				 en Contacto.cpp*/

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

					/*extraemos del archivo binario cada contacto con la sobrecarga del operador >> realizada
					 en Contacto.cpp*/

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

			if (ficheroSalida.is_open()){

				vector<string> telefonos_aux;
				vector<Direccion> direcciones_aux;
				vector<CuentaRedSocial> redes_aux;
				list<Contacto>::iterator it;
				int nveces=0,i;


				for (it=listaAgenda.begin();it!=listaAgenda.end();++it){

					ficheroSalida << "Mi agenda,exportada en fecha: " << dameFecha() << endl;
					ficheroSalida << "=================================================" << endl;
					ficheroSalida << "Nombre: " << (*it).getNombre() << endl;
					ficheroSalida << "Apellidos: " << (*it).getApellidos() << endl;
					ficheroSalida << "DNI: " << (*it).getDni() << endl;

					telefonos_aux = (*it).getTelefonos();
					nveces = telefonos_aux.size();

						for (i=0;i<nveces;i++){

							ficheroSalida << "Teléfono " << i << ":" << telefonos_aux[i] << endl;

						}

					ficheroSalida << "Correo-electrónico: " << (*it).getCorreoE() << endl;

					direcciones_aux = (*it).getDirecciones();
					nveces=direcciones_aux.size();

					ficheroSalida << "Dirección/es: " << endl;

						for (i=0;i<nveces;i++){

							ficheroSalida << "calle: " << direcciones_aux[i].calle << endl;
							ficheroSalida << "número: " << direcciones_aux[i].numero << endl;
							ficheroSalida << "piso: " << direcciones_aux[i].piso << endl;
							ficheroSalida << "puerta: " << direcciones_aux[i].puerta << endl;

						}

					ficheroSalida << "Anotaciones: " << (*it).getCorreoE() << endl;
					ficheroSalida << "Favorito: " << (*it).getFavoritos() << endl;

					redes_aux = (*it).getRedes();
					nveces = redes_aux.size();
					ficheroSalida << "Cuenta Red/es: " < endl;

						for (i=0;i<nveces;i++){

							ficheroSalida << "Red: " << redes_aux[i].red << endl;
							ficheroSalida << "Usuario: " << redes_aux[i].usuario << endl;

						}

				}

				return true;

			}else{

				return false;

			}

	}

} /* namespace agenda */
