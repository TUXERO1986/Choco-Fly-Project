#pragma once
#include<iostream>
class CiudadId
{
private:
	std::string nombre;
	int id;
public:
	CiudadId();
	CiudadId(std::string,int);

	std::string getNombre();
	int getId();
	void setNombre(std::string);
	void setId(int);
	int getIdPorNombre(std::string);
	std::string getNombrePorId(int id);
};

