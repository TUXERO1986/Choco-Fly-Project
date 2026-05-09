#pragma once
#include "Reserva.h"
#include <functional>
class ReservaHotel : public Reserva
{
private:
	string nombreHotel;
	string ciudad;
	int noches;
	float precioNoche;
	int habitacion;
	int tipoO;
	int tipoC;
	int tipoS;
	function <string(int)> ObtenerTipoO;
	function <string(int)> ObtenerTipoC;
	function <string(int)> ObtenerTipoS;

public:
	ReservaHotel(string codigoUsuario, string nombreUsuario, string nombreHotel, string ciudad, 
		float precioNoche, int noches,int habtiacion,int tipoO,int tipoC,int tipoS);
	void MostrarReserva() override;
	string aTextoArchivo() override;
	string getNombreHotel();
	string getCiudad();
	int getNoches();
	float getPrecioTotal();
	int getTipoO();
	int getTipoC();
	int getTipoS();
	int getHabitacion();
	void setNombreHotel(string nombreHotel);
	void setCiudad(string ciudad);
	void setNoches(int noches);
	void setPrecioNoche(float precioNoche);
	void setHabitacion(int habitacion);
	void setTipoO(int tipoO);
	void setTipoC(int tipoC);
	void setTipoS(int tipoS);
};

