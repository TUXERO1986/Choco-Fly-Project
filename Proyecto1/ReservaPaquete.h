#include "ReservaVuelo.h"
#include "ReservaHotel.h"

class ReservaPaquete : public Reserva
{
private:
    ReservaVuelo* vueloReservado;
    ReservaHotel* hotelReservado;
	ReservaVuelo* vueloRetorno; 

public:
    ReservaPaquete(string NombreU, string nombreUsuario, ReservaVuelo* vueloIda, ReservaVuelo* vueloRetorno, ReservaHotel* hotel,int id);
    ~ReservaPaquete();

    void MostrarDatos() override;
    string aTextoArchivo() override;
    float getPrecioTotal() override;
    ReservaVuelo* getVueloReservado();
	ReservaVuelo* getVueloRetorno();
    ReservaHotel* getHotelReservado();
    void setVueloReservado(ReservaVuelo* vuelo);
	void setVueloRetorno(ReservaVuelo* vuelo);
    void setHotelReservado(ReservaHotel* hotel);
};

