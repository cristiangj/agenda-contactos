/*
 * Menus_test.cpp
 *
 *  Created on: 10/12/2014
 *      Author: javier
 */

#include "Menus.h"

using namespace agenda;

int main(){
	Contacto c;
	c = Menus::addContacto();

	Menus::visionado(c);
}
