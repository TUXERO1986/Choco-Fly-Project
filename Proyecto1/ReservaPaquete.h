#include "Reserva.h"
#include "Ticket.h" // O como le hayas puesto a tu clase hija de vuelo
#include "ReservaHotel.h"

class ReservaPaquete : public Reserva
{
private:
    Ticket* vueloReservado;
    ReservaHotel* hotelReservado;
	Ticket* vueloRetorno; 

public:
    ReservaPaquete(string NombreU, string nombreUsuario, Ticket* vueloIda, Ticket* vueloRetorno, ReservaHotel* hotel);
    ~ReservaPaquete();

    void MostrarReserva() override;
    string aTextoArchivo() override;
    float getPrecioTotal() override;
    Ticket* getVueloReservado();
	Ticket* getVueloRetorno();
    ReservaHotel* getHotelReservado();
    void setVueloReservado(Ticket* vuelo);
	void setVueloRetorno(Ticket* vuelo);
    void setHotelReservado(ReservaHotel* hotel);
};

