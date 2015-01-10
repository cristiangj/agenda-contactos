/*
 * Contacto.h
 *
 *  Created on: 10/12/2014
 *      Author: Enrique
 */

#ifndef CONTACTO_H_
#define CONTACTO_H_

#include <string>
#include <vector>
#include <list>
#include <istream>
#include <ostream>

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

		bool setNombre (std::string nombre);
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

		inline void delTelefono (int pos) {telefonos_.erase(telefonos_.begin() + pos);}; //Elimina el teléfono en la posicion indicada

		bool setDireccion (Direccion dir);
		inline std::vector <Direccion> getDirecciones () {return direcciones_;};
		inline void delDireccion (int pos) {direcciones_.erase(direcciones_.begin() + pos);}; //Elimina la dirección en la posición indicada

		bool setRed (CuentaRedSocial red);
		inline std::vector <CuentaRedSocial> getRedes () {return redes_;};
		inline void delRed (int pos) {redes_.erase(redes_.begin() + pos);}; //Elimina la red en la posición indicada

		static std::string getNombreRed(tipoRed t);

		friend std::ostream& operator<<(std::ostream &out,Contacto &c);
		friend std::istream& operator>>(std::istream &in,Contacto &c);
};

} /* namespace agenda */

#endif /* CONTACTO_H_ */

