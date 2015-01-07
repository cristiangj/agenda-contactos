#ifndef CONTACTO_H
#define CONTACTO_H

#include <iostream>
#include <string>
#include <vector>

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

using namespace std;

enum tipoRed {twitter, facebook, googleplus};

struct Direccion {
	string calle;
	int numero;
	int piso;
	int puerta;
};

struct CuentaRedSocial {
	tipoRed red;
	string usuario;
};

struct Cambio {
	int idCampo;
	string valor;
};

class Contacto {
	private:
		string nombre_;
		string apellidos_;
		string dni_;
		vector <string> telefonos_;
		string correoE_;
		vector <Direccion> direcciones_;
		string anotaciones_;
		bool favoritos_;
		int nconsultas_;
		vector <CuentaRedSocial> redes_;

	public:
		Contacto (string nombre="", string apellidos="", string dni="", string correoe="", string anotaciones="", bool favoritos="", int nconsultas=0);

		void setNombre (string nombre);
		inline string getNombre () {return nombre_;};

		bool setApellidos (string apellidos);
		inline string getApellidos () {return apellidos_;};
		inline string getApellidosyNombre () {return (apellidos_+", "+nombre_);};

		bool setDni (string dni);
		inline string getDni () {return dni_;};

		bool setCorreoE (string correoe);
		inline string getCorreoE () {return correoE_;};

		void setAnotaciones (string anotaciones);
		inline string getAnotaciones () {return anotaciones_;};

		void setFavoritos (bool favoritos);
		inline bool getFavoritos () {return favoritos_;};

		void setNconsultas (int nconsultas);
		inline int getNconsultas () {return nconsultas_;};
		void anadirNconsultas ();

		bool setTelefono (string telefono);
		inline vector <string> getTelefonos () {return telefonos_;};

		bool setDireccion (Direccion dir);
		inline vector <Direccion> getDireccion () {return direcciones_;};

		bool setRed (CuentaRedSocial red);
		inline vector <CuentaRedSocial> getRedes () {return redes_;};

		bool modificar (list<Cambio> cambios);
}

#endif
