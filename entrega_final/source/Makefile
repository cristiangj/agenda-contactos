CXX = g++
CXXFLAGS = --std=c++11
DEBUG = -g

agenda: Contacto.o Menus.o GestorAgenda.o GestorBackup.o PersistenciaAgenda.o
	mkdir -p Backups
	$(CXX) $^ Main.cpp -o $@ $(CXXFLAGS)
	
debug_agenda: Contacto.o Menus.o GestorAgenda.o GestorBackup.o PersistenciaAgenda.o
	$(CXX) $^ Main.cpp -o $@ $(CXXFLAGS) $(DEBUG)

Contacto.o: Contacto.cpp
	$(CXX) $^ -c $(CXXFLAGS)

Menus.o: Menus.cpp
	$(CXX) $^ -c $(CXXFLAGS)

GestorAgenda.o: GestorAgenda.cpp
	$(CXX) $^ -c $(CXXFLAGS)

GestorBackup.o: GestorBackup.cpp
	$(CXX) $^ -c $(CXXFLAGS)

PersistenciaAgenda.o: PersistenciaAgenda.cpp
	$(CXX) $^ -c $(CXXFLAGS)
	
.PHONY: clean

clean:
	rm *.o
	@echo "Borrados todos los ficheros objeto (*.o)"
