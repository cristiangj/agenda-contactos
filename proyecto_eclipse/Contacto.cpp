/*
 * Contacto.cpp
 *
 *  Created on: 10/12/2014
 *      Author: Enrique
 */

#include "Contacto.h"
#include <string>
#include <vector>
#include <list>

namespace agenda {

Contacto::Contacto (std::string nombre, std::string apellidos, std::string dni, std::string correoe, std::string anotaciones, bool favoritos, int nconsultas) {
	nombre_=nombre;
	apellidos_=apellidos;
	dni_=dni;
	correoE_=correoe;
	anotaciones_=anotaciones;
	favoritos_=favoritos;
	nconsultas_=nconsultas;

}



bool Contacto::setNombre (std::string nombre) {
	nombre_=nombre;
	return true;
}


bool Contacto::setApellidos (std::string apellidos) {
	if (!apellidos.empty()) {
		apellidos_=apellidos;
		return true;
	}
	else {
		return false;
	}
}


bool Contacto::setDni (std::string dni) {
	int tam=dni.length();

	if (tam==9) {
		dni_=dni;
		return true;
	}
	else {
		return false;
	}
}


bool Contacto::setCorreoE (std::string correoe) {
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


void Contacto::setAnotaciones (std::string anotaciones) {
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


bool Contacto::setTelefono (std::string telefono) {
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

std::string Contacto::getNombreRed(tipoRed t){
	std::string nombre;

	switch(t){
	case twitter:
		nombre = "Twitter";
		break;

	case facebook:
		nombre = "Facebook";
		break;

	case googleplus:
		nombre = "Goole +";
		break;

	default:
		nombre = "Red desconocida";
		break;
	}

	return nombre;
}

	istream& operator>>(istream &in,Contacto &c){

		/*variables auxiliares*/

		string nombre_aux, apellidos_aux, dni_aux, telefono_aux, correoE_aux,anotaciones_aux;
		char caracterNulo;
		bool favoritos_aux;
		int nveces=0,i,nconsultas_aux;
		vector<string> vectortelefonos_aux;
		vector<Direccion> vectordirecciones_aux;
		Direccion direcciondatos_aux;
		vector<CuentaRedSocial> vectorredes_aux;
		CuentaRedSocial redesdatos_aux;

		/*leer campos del fichero binario*/

		//Leer nombre

		while (in.peek() != '\0') nombre_aux.push_back(in.get());

		caracterNulo = in.get();							//se queda con el \0 no lo necesitamos para strings

		//Leer apellidos

		while (in.peek() != '\0') apellidos_aux.push_back(in.get());

		caracterNulo = in.get();

		//Leer dni

		while (in.peek() != '\0') dni_aux.push_back(in.get());

		caracterNulo = in.get();

		/*Leer telefonos, OJO: para leer un entero,en este caso el numero de elementos del vector, tenemos que
		 usar la funcion destinada a ello que es .read() porque de un binario los unicos datos que podemos leer
		 literalmente y sin ninguna funcion de conversion son los de tipo char*/

		in.read((char *) &nveces,sizeof(int));

			for (i=0;i<nveces;i++){

				//leer telefono

				while (in.peek() != '\0') telefono_aux.push_back(in.get());

				//introducir en el vector el telefono leido

				vectortelefonos_aux.push_back(telefono_aux);

				caracterNulo = in.get();

			}

		//leer correo

		while (in.peek() != '\0') correoE_aux.push_back(in.get());

		caracterNulo = in.get();

		//leer direcciones

		in.read((char *) &nveces,sizeof(int));

			for (i=0;i<nveces;i++){

				//leer calle

				while (in.peek() != '\0') direcciondatos_aux.calle.push_back(in.get());

				caracterNulo = in.get();

				//leer numero

				in.read((char *) &(direcciondatos_aux.numero),sizeof(int));

				//leer piso

				in.read((char *) &(direcciondatos_aux.piso),sizeof(int));

				//leer puerta

				in.read((char *) &(direcciondatos_aux.puerta),sizeof(int));

				//introducir en el vector la estructura leida

				vectordirecciones_aux.push_back(direcciondatos_aux);

			}

		//leer anotaciones

		while(in.peek() != '\0') anotaciones_aux.push_back(in.get());

		caracterNulo = in.get();

		//leer favoritos

		in.read((char *) &favoritos_aux,sizeof(bool));

		//leer nconsultas

		in.read((char *) &nconsultas_aux,sizeof(int));

		//leer redes

		in.read((char *) &nveces,sizeof(int));

		for (i=0;i<nveces;i++){

			//leer red

			in.read((char *) &(redesdatos_aux.red),sizeof(int));

			//leer usuario

			while (in.peek() != '\0') redesdatos_aux.usuario.push_back(in.get());

			caracterNulo = in.get();

			vectorredes_aux.push_back(redesdatos_aux);

		}

		/*asignamos a los campos privados de la clase Contacto los valores auxiliares obtenidos*/

		c.nombre_ = nombre_aux;
		c.apellidos_ = apellidos_aux;
		c.DNI_ = dni_aux;
		c.telefonos_ = vectortelefonos_aux;
		c.correoE_= correoE_aux;
		c.direcciones_ = vectordirecciones_aux;
		c.anotaciones_ = anotaciones_aux;
		c.favoritos_ = favoritos_aux;
		c.nconsultas_ = nconsultas_aux;
		c.redes_ = vectorredes_aux;

		return (in);
	}

	ostream& operator<<(ostream &out,Contacto &c){

		/*asignaciones a las variables auxiliares con los datos privados de la clase Contacto, los string al
		 ser objetos los convertimos a cadena de caracteres char (1 byte) por elemento porque los objetos como
		 tal no se pueden insertar en un archivo binario*/

		int i,nveces=0;
		const char * nombre_aux = c.nombre_.c_str();
		const char * apellidos_aux = c.apellidos_.c_str();
		const char * dni_aux = c.DNI_.c_str();
		vector<string> vectortelefonos_aux = c.telefonos_;
		const char * correoE_aux = c.correoE_.c_str();
		vector<Direccion> vectordirecciones_aux = c.direcciones_;
		const char * anotaciones_aux = c.anotaciones_.c_str();
		bool favoritos_aux = c.favoritos_;
		int nconsultas_aux = c.nconsultas_;
		vector<CuentaRedSocial> vectorredes_aux = c.redes_;

		/*escritura en el binario de las variables auxiliares, a la hora de leer el archivo binario usaremos
		 en las cadenas el caracter nulo '\0' para identificar dicho final de la cadena, OJO: en la escritura
		 usamos strlen para obtener el tamaño de la cadena pero tenemos que sumar 1 para el caracter nulo*/

		//escribir nombre

		out.write(nombre_aux, strlen(nombre_aux)+1);

		//escribir apellidos

		out.write(apellidos_aux, strlen(apellidos_aux)+1);

		//escribir dni

		out.write(dni_aux, strlen(dni_aux)+1);

		/*antes de escribir el numero de telefonos que posea el contacto insertamos en el archivo la cantidad
		 de elementos que posee el vector de telefonos (la cantidad de telefonos que hay) y asi a la hora de
		 leer el archivo sabremos cuantas posiciones del vector hemos de leer*/

		nveces = vectortelefonos_aux.size();
		out.write((char *) &nveces,sizeof(int));

			for (i=0;i<nveces;i++){

				const char * telefono_aux = vectortelefonos_aux[i].c_str();
				out.write(telefono_aux,strlen(telefono_aux)+1);

			}

		//escribir correo-electronico

		out.write(correoE_aux,strlen(correoE_aux)+1);

		/*aqui exactamente igual pero con la estructura Direccion, OJO: debemos insertala campo a campo por los
		 diferentes tamaños que los campos pueden tomar*/

		nveces = vectordirecciones_aux.size();
		out.write((char *) &nveces,sizeof(int));

			for (i=0;i<nveces;i++){

				//escribir calle

				const char * calle_aux = (vectordirecciones_aux[i].calle).c_str();
				out.write(calle_aux,strlen(calle_aux)+1);

				//escribir numero

				out.write((char *) &(vectordirecciones_aux[i].numero),sizeof(int));

				//escribir piso

				out.write((char *) &(vectordirecciones_aux[i].piso),sizeof(int));

				//escribir puerta

				out.write((char *) &(vectordirecciones_aux[i].puerta),sizeof(int));

			}

		//escribir anotaciones

		out.write(anotaciones_aux,strlen(anotaciones_aux)+1);

		//escribir favoritos

		out.write((char *) &favoritos_aux,sizeof(bool));

		//escribir nconsultas

		out.write((char *) &nconsultas_aux,sizeof(int));

		/*y aqui con la estructura CuentaRedSocial, tambien campo a campo*/

		nveces = vectorredes_aux.size();
		out.write((char *) &nveces,sizeof(int));

			for (i=0;i<nveces;i++){

				//escribir red

				out.write((char *) &(vectorredes_aux[i].red),sizeof(int));

				//escribir usuario

				const char * usuario_aux = (vectorredes_aux[i].usuario).c_str();
				out.write(usuario_aux,strlen(usuario_aux)+1);

			}

			return (out);
		}

} /* namespace agenda */

