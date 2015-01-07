/*
 * Contacto.h
 *
 *  Created on: 10/12/2014
 *      Author: Enrique
 */

#ifndef CONTACTO_H_
#define CONTACTO_H_

#define CAMPO_NOMBRE 1
#define CAMPO_APELLIDO 2
#define CAMPO_DNI 3
#define CAMPO_TELEFONO 4
#define CAMPO_CORREOE 5
#define CAMPO_DIRECCION 6
#define CAMPO_ANOTACION	7
#define CAMPO_FAVORITOS	8
#define CAMPO_CONSULTA 9
#define CAMPO_RED 10

#include <string>
#include <vector>
#include <list>

namespace agenda {

enum tipoRed {twitter, facebook, googleplus};

struct Direccion {
	std::string calle;
	int numero;
	int piso;
	int puerta;
};

struct CuentaRedSocial {
	tipoRed red;
	std::string usuario;
};

struct Cambio {
	int idCampo;
	std::string valor;
	int valorN;
};

class Contacto {
	private:
		std::string nombre_;
		std::string apellidos_;
		std::string dni_;
		std::vector <std::string> telefonos_;
		std::string correoE_;
		std::vector <Direccion> direcciones_;
		std::string anotaciones_;
		bool favoritos_;
		int nconsultas_;
		std::vector <CuentaRedSocial> redes_;

	public:
		Contacto (std::string nombre="", std::string apellidos="", std::string dni="", std::string correoe="", std::string anotaciones="", bool favoritos="", int nconsultas=0);

		void setNombre (std::string nombre);
		inline std::string getNombre () {return nombre_;};

		bool setApellidos (std::string apellidos);
		inline std::string getApellidos () {return apellidos_;};
		inline std::string getApellidosyNombre () {return (apellidos_+", "+nombre_);};

		bool setDni (std::string dni);
		inline std::string getDni () {return dni_;};

		bool setCorreoE (std::string correoe);
		inline std::string getCorreoE () {return correoE_;};

		void setAnotaciones (std::string anotaciones);
		inline std::string getAnotaciones () {return anotaciones_;};

		void setFavoritos (bool favoritos);
		inline bool getFavoritos () {return favoritos_;};

		void setNconsultas (int nconsultas);
		inline int getNconsultas () {return nconsultas_;};
		void anadirNconsultas ();

		bool setTelefono (std::string telefono);
		inline std::vector <std::string> getTelefonos () {return telefonos_;};

		bool setDireccion (Direccion dir);
		inline std::vector <Direccion> getDirecciones () {return direcciones_;};

		bool setRed (CuentaRedSocial red);
		inline std::vector <CuentaRedSocial> getRedes () {return redes_;};

		void modificar (std::list<Cambio> cambios);
};

} /* namespace agenda */

#endif /* CONTACTO_H_ */
