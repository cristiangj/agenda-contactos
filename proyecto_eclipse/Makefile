all: GestorAgenda.o

GestorAgenda.o: GestorAgenda.h GestorAgenda.cpp Contacto.h Contacto.cpp GestorBackup.h GestorBackup.cpp PersistenciaAgenda.h PersistenciaAgenda.cpp
	g++ -std=c++11 GestorAgenda.cpp Contacto.cpp GestorBackup.cpp PersistenciaAgenda.cpp -c