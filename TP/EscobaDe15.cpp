#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;


struct carta
{
    int valor = 0;
    char palo = ' ';
    bool marcaBaraja = false;
    bool marcaJuego = false;
    bool marcaLista = false;
};

struct Nodo
{
    carta cartA;
    Nodo* sgte;
};

struct mesa
{
    carta cartas[15];
    int cantCartasEnMesa = 0;

};

struct jugador
{
    carta mano[3];
    int cartasEnMano = 0;
    int cantO = 0;
    int cant7 = 0;
    int sieteO = 0;
    int cantCartas = 0;
    int puntos= 0;
    Nodo* lista= NULL;
    int ultimaRonda = 0;
    int escobas= 0;
    bool ultQuince = false;
};


carta cartas(carta[], int);
void mostrarMano(jugador, int);
void mostrarMesa(mesa, int);
void repartirJ(carta[], carta[]);
void repartirMesa(carta[], carta[], int&);
int suma15(carta, carta[], int, int[]);
int suma15DosCartas(int, carta[], int, int[]);
int cartDistintas(carta , carta);
int charCmp(char, char);
int suma15TresCartas(int, carta[], int, int[]);
int suma15CuatroCartas(int, carta[], int, int[]);
int suma15CincoCartas(int, carta[], int, int[]);
int suma15SeisCartas(int, carta[], int, int[]);
int Suma15DeTodasFormas(carta, carta[], int, int[]);
void sacarDeLaMesa(int[], carta[], int);
int saco(carta[], int&, Nodo*& );
void prototipoRepartir(carta[], carta[], int&);
void sacarDeLaMano(int, carta[], int&);
void ponerEnLaMesa(carta, carta[], int&); 
Nodo* cargarAlFinal(Nodo*&, carta);
void puntos1(Nodo*, int&, int&, int&, int&);
void compararPuntosJugadores(jugador, int&,jugador, int&);
void inicializarLista(Nodo*&);
void repartirMesa2(carta[], carta[], int&);
bool mazoVacio(carta [], int);
carta pop(Nodo*&);
void inicializarBaraja(carta[], int , int&);
void inicializarJugador(carta [], int&, int&, int&, int&, int&, Nodo*&, int&, int&, bool&);
void sacarDeLaMesaIlegal(bool&);
int sacoIlegal(carta[], int&);
void jugadorConMasPuntos(int, int);
void escoba(int&);
void ultimoQuince(bool&, bool&);
// void ultimoQuince3(bool&, bool&, bool&);
void compararPuntosJugadores3(jugador, int&,jugador, int&, jugador, int&);
void ultimoQuince3(bool&, bool&, bool&);
void jugadorConMasPuntos3(int, int, int);


int main() {
    int cant = 40;
    carta baraja[cant];
    int cantJugadores=0;
    
    cout << "░▒▓██████████ ►╬◄██████████▓▒░\n";
    cout << "░▒▓██ ►╔╦╦╦═╦╗╔═╦═╦══╦═╗◄██▓▒░\n";
    cout << "░▒▓██ ►║║║║╩╣╚╣═╣║║║║║╩╣◄██▓▒░\n";
    cout << "░▒▓██ ►╚══╩═╩═╩═╩═╩╩╩╩═╝◄██▓▒░\n";
    cout << "░▒▓██████████ ►╬◄██████████▓▒░\n";  

    cout<< "\nSeleccione la cantidad de jugadores, porfavor: ";
    cin >> cantJugadores;
    int rondas =0;
    if (cantJugadores == 2)
    {
        cartas(baraja, cant);
        mesa tablero;
        jugador uno;
        jugador dos;
        prototipoRepartir(baraja, uno.mano, uno.cartasEnMano);
        prototipoRepartir(baraja,dos.mano, dos.cartasEnMano);
        repartirMesa2(baraja, tablero.cartas, tablero.cantCartasEnMesa);
        int turno = rand()%2;
  

        while (uno.puntos <= 15 && dos.puntos <= 15)
        {

            if (turno == 1)
            {    if (uno.cartasEnMano == 0)
                {
                    prototipoRepartir(baraja, uno.mano, uno.cartasEnMano);
                    mazoVacio(baraja,cant);
                }
            
                cout << "Jugador 1 elija una carta, en caso de no formar 15 se descartara." << endl;
                mostrarMano(uno, uno.cartasEnMano);
                mostrarMesa(tablero, tablero.cantCartasEnMesa);
                int opc= 0;
                cout << "Elija la de la posicion 1, 2 o 3 " << endl;
                cin >> opc ;
                int t= 8;
                int posiciones[t]; 
            
                turno = 2;
                switch (opc)
                {
                case 1:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(uno.mano[0], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(uno.escobas);
                        }

                        
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(uno.mano[0] ,tablero.cartas, tablero.cantCartasEnMesa);//------PONE EN LA MESA LA CARTA Y MARCA CON TRUE EL CAMPO MARCAJUEGO =TRUE
                            sacarDeLaMano(0,uno.mano, uno.cartasEnMano);//-------Saca de la mano del jugador
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);//-----Marca la carta para luego sacarla de la mesa
                            cargarAlFinal(uno.lista,uno.mano[0]);
                            sacarDeLaMano(0,uno.mano, uno.cartasEnMano);//-------Saca de la mano del jugador
                            saco(tablero.cartas, tablero.cantCartasEnMesa, uno.lista);//--------Saca de la mesa
                            ultimoQuince(uno.ultQuince, dos.ultQuince);

                            if (mazoVacio(baraja,cant))
                            {
                                cout << "Ultima ronda " << endl;
                                uno.ultimaRonda++;
                                cout << uno.ultimaRonda << endl;
                            }
                        }                             
                    }
                    break;
                case 2:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(uno.mano[1], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(uno.escobas);
                          
                        }
                  
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(uno.mano[1] ,tablero.cartas, tablero.cantCartasEnMesa);//------PONE EN LA MESA LA CARTA Y MARCA CON TRUE EL CAMPO MARCAJUEGO =TRUE
                            sacarDeLaMano(1,uno.mano, uno.cartasEnMano);      
                            
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);//-----Marca la carta para luego sacarla de la mesa
                            cargarAlFinal(uno.lista,uno.mano[1]);
                            sacarDeLaMano(1,uno.mano, uno.cartasEnMano);//-------Saca de la mano del jugador
                            saco(tablero.cartas, tablero.cantCartasEnMesa, uno.lista);//--------Saca de la mesa
                            ultimoQuince(uno.ultQuince, dos.ultQuince);
                            
                            if (mazoVacio(baraja,cant))
                            {
                                cout << "Ultima ronda " << endl;
                                uno.ultimaRonda++;
                                cout << uno.ultimaRonda << endl;
                            }                                                      
                        }
                    }
                    break;
            
                default:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(uno.mano[2], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(uno.escobas);
                         
                        }
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(uno.mano[2] ,tablero.cartas, tablero.cantCartasEnMesa);//------PONE EN LA MESA LA CARTA Y MARCA CON TRUE EL CAMPO MARCAJUEGO =TRUE
                            sacarDeLaMano(2,uno.mano, uno.cartasEnMano);//-------Saca de la mano del jugador
                            
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);//-----Marca la carta para luego sacarla de la mesa
                            cargarAlFinal(uno.lista,uno.mano[2]);
                            sacarDeLaMano(2,uno.mano, uno.cartasEnMano);//-------Saca de la mano del jugador
                            saco(tablero.cartas, tablero.cantCartasEnMesa, uno.lista);//--------Saca de la mesa
                            ultimoQuince(uno.ultQuince, dos.ultQuince);

                            if (mazoVacio(baraja,cant))
                            {
                                cout << "Ultima ronda " << endl;
                                uno.ultimaRonda++;
                                cout << uno.ultimaRonda << endl;
                            }
                            
                           
                        }
                    }
                    break;
                }
            
                cout << "Turno del jugador: " << turno << endl;

            }else if (turno == 2)
            {   
                if (dos.cartasEnMano == 0)
                {
                    prototipoRepartir(baraja, dos.mano, dos.cartasEnMano);
                    mazoVacio(baraja,cant);
                }
                
                cout << "Jugador 2 elija una carta, en caso de no formar 15 se descartara." << endl;
                mostrarMano(dos, dos.cartasEnMano);
                mostrarMesa(tablero, tablero.cantCartasEnMesa);
                int opc= 0;
                cout << "Elija la de la posicion 1, 2 o 3 " << endl;
                cin >> opc ;
                int t= 8;
                int posiciones[t];
                turno = 1;

                switch (opc)
                {
                case 1:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(dos.mano[0], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(dos.escobas);
                          
                        }
                        
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(dos.mano[0] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(0, dos.mano, dos.cartasEnMano);
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(dos.lista,dos.mano[0]);
                            sacarDeLaMano(0, dos.mano, dos.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, dos.lista);
                            ultimoQuince(dos.ultQuince, uno.ultQuince);

                           if (mazoVacio(baraja,cant))
                           {    
                                cout << "Ultima ronda" << endl;
                                dos.ultimaRonda++;
                                cout << dos.ultimaRonda << endl;
                           }
                           

                        }
                    
                    }
        
                    break;
                case 2:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(dos.mano[1], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(dos.escobas);
                          
                        }
                    
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(dos.mano[1] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(1, dos.mano, dos.cartasEnMano);
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(dos.lista,dos.mano[1]);
                            sacarDeLaMano(1, dos.mano, dos.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, dos.lista);
                            ultimoQuince(dos.ultQuince, uno.ultQuince);
                           if (mazoVacio(baraja,cant))
                           {    
                                cout << "Ultima ronda" << endl;
                                dos.ultimaRonda++;
                                cout << dos.ultimaRonda << endl;
                           }
                           

                        }
                      
                    }
                    break;
            
                default:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(dos.mano[2], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(dos.escobas);
                         
                        }
                      
                           if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(dos.mano[2] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(2, dos.mano, dos.cartasEnMano);
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(dos.lista,dos.mano[2]);
                            sacarDeLaMano(2, dos.mano, dos.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, dos.lista);
                            ultimoQuince(dos.ultQuince, uno.ultQuince);
                           if (mazoVacio(baraja,cant))
                           {    cout << "Ultima ronda" << endl;
                                dos.ultimaRonda++;
                                cout << dos.ultimaRonda << endl;
                           }
                           

                        }

                

                    }
                    break;
                }              
                cout << "Turno del jugador: " << turno << endl;           
            }
                if (mazoVacio(baraja, cant) && uno.cartasEnMano == 0 && dos.cartasEnMano == 0 && uno.ultQuince)
            {   int pos = tablero.cantCartasEnMesa;
                for (int i = 0; i < pos; i++)
                {
                    cargarAlFinal(uno.lista,tablero.cartas[i]);
                    sacarDeLaMesaIlegal(tablero.cartas[i].marcaJuego);
                    
                }
                sacoIlegal(tablero.cartas, tablero.cantCartasEnMesa);
            } else if (mazoVacio(baraja, cant) && uno.cartasEnMano == 0 && dos.cartasEnMano == 0 && dos.ultQuince)
            {   int pos = tablero.cantCartasEnMesa;
                for (int i = 0; i < pos; i++)
                {
                    cargarAlFinal(dos.lista,tablero.cartas[i]);
                    sacarDeLaMesaIlegal(tablero.cartas[i].marcaJuego);     
                }
                sacoIlegal(tablero.cartas, tablero.cantCartasEnMesa);
                
            } 
            
            for (int i = 0; i < tablero.cantCartasEnMesa; i++)
            {
                cout << "Quedo en el mazo: " << tablero.cartas[i].valor << tablero.cartas[i].palo << endl;
            }
           
            if(mazoVacio(baraja,cant) && uno.cartasEnMano == 0 && dos.cartasEnMano == 0){
                rondas++;// variable que contabiliza las rondas
                puntos1(uno.lista, uno.cant7, uno.cantO, uno.sieteO, uno.cantCartas);
                puntos1(dos.lista, dos.cant7,dos.cantO, dos.sieteO, dos.cantCartas);
                compararPuntosJugadores(uno, uno.puntos, dos, dos.puntos);
                inicializarLista(uno.lista);
                inicializarLista(dos.lista);
                inicializarJugador(uno.mano, uno.cant7, uno.cantCartas,uno.cantO, uno.cartasEnMano, uno.sieteO, uno.lista, uno.ultimaRonda, uno.escobas, uno.ultQuince);
                inicializarJugador(dos.mano, dos.cant7, dos.cantCartas, dos.cantO, dos.cartasEnMano, dos.sieteO, dos.lista, dos.ultimaRonda, dos.escobas, dos.ultQuince);
                inicializarBaraja(baraja, cant, rondas);
                repartirMesa2(baraja, tablero.cartas, tablero.cantCartasEnMesa);
            }
        }
        if (uno.puntos >= 15 || dos.puntos >= 15) {
            jugadorConMasPuntos(uno.puntos, dos.puntos);
        } //---------------------------------------------------- aca empieza para 3 jugadores       
    } else if (cantJugadores == 3)
    {
        cartas(baraja, cant);
        mesa tablero;
        jugador uno;
        jugador dos;
        jugador tres;
        prototipoRepartir(baraja, uno.mano, uno.cartasEnMano);
        prototipoRepartir(baraja, dos.mano, dos.cartasEnMano);
        prototipoRepartir(baraja, tres.mano, tres.cartasEnMano);
        repartirMesa2(baraja, tablero.cartas, tablero.cantCartasEnMesa);
        int turno = rand()%3 + 1;

        while(uno.puntos <= 15 && dos.puntos <= 15 && tres.puntos <= 15){
            
            if (turno == 1)
            {   
                if (uno.cartasEnMano == 0)
                {
                    prototipoRepartir(baraja, uno.mano, uno.cartasEnMano);
                    mazoVacio(baraja,cant);
                }
            
                cout << "Jugador 1 elija una carta, en caso de no formar 15 se descartara." << endl;
                mostrarMano(uno, uno.cartasEnMano);
                mostrarMesa(tablero, tablero.cantCartasEnMesa);
                int opc= 0;
                cout << "Elija la de la posicion 1, 2 o 3 " << endl;
                cin >> opc ;
                int t= 8;
                int posiciones[t]; 
                turno = 2;

                switch (opc)
                {
                    case 1:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(uno.mano[0], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(uno.escobas);
                        }

                        
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(uno.mano[0] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(0,uno.mano, uno.cartasEnMano);
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(uno.lista,uno.mano[0]);
                            sacarDeLaMano(0,uno.mano, uno.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, uno.lista);
                            ultimoQuince3(uno.ultQuince, dos.ultQuince, tres.ultQuince);

                            if (mazoVacio(baraja,cant))
                            {
                                cout << "Ultima ronda " << endl;
                                uno.ultimaRonda++;
                                cout << uno.ultimaRonda << endl;
                            }
                            
                        }
                    
                    }
                    break;

                    case 2:
                    {
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(uno.mano[1], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(uno.escobas);

                        }
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(uno.mano[1] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(1,uno.mano, uno.cartasEnMano);
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(uno.lista,uno.mano[1]);
                            sacarDeLaMano(1,uno.mano, uno.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, uno.lista);
                            ultimoQuince3(uno.ultQuince, dos.ultQuince, tres.ultQuince);

                             if (mazoVacio(baraja,cant))
                            {
                                cout << "Ultima ronda " << endl;
                                uno.ultimaRonda++;
                                cout << uno.ultimaRonda << endl;
                            }
                        }
                    }
                    break;

                    default:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(uno.mano[2], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(uno.escobas);
                        
                        }
                         if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(uno.mano[2] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(2,uno.mano, uno.cartasEnMano);
                           
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(uno.lista,uno.mano[2]);
                            sacarDeLaMano(2,uno.mano, uno.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, uno.lista);
                            ultimoQuince3(uno.ultQuince, dos.ultQuince, tres.ultQuince);

                            if (mazoVacio(baraja,cant))
                            {
                                cout << "Ultima ronda " << endl;
                                uno.ultimaRonda++;
                                cout << uno.ultimaRonda << endl;
                              
                            }        
                        }
                    }
                    break;
                }
                cout << "Turno del jugador: " << turno << endl;

            } else if(turno == 2)
            {

                if (dos.cartasEnMano == 0)
                {
                    prototipoRepartir(baraja, dos.mano, dos.cartasEnMano);
                    mazoVacio(baraja,cant);
                }
                
                cout << "Jugador 2 elija una carta, en caso de no formar 15 se descartara." << endl;
                mostrarMano(dos, dos.cartasEnMano);
                mostrarMesa(tablero, tablero.cantCartasEnMesa);
                int opc= 0;
                cout << "Elija la de la posicion 1, 2 o 3 " << endl;
                cin >> opc ;
                int t= 8;
                int posiciones[t];
                turno = 3;

                switch(opc)
                {
                    case 1:
                    {
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(dos.mano[0], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(dos.escobas);
                         
                        }
                 
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(dos.mano[0] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(0, dos.mano, dos.cartasEnMano);
                        }

                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(dos.lista,dos.mano[0]);
                            sacarDeLaMano(0, dos.mano, dos.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, dos.lista);
                            ultimoQuince3(dos.ultQuince, uno.ultQuince, tres.ultQuince);

                            if (mazoVacio(baraja,cant))
                           {    
                                cout << "Ultima ronda" << endl;
                                dos.ultimaRonda++;
                                cout << dos.ultimaRonda << endl;
                           }

                        }


                    }
                    break;
                    case 2:
                    {   
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(dos.mano[1], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(dos.escobas);
                         
                        }
                       
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(dos.mano[1] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(1, dos.mano, dos.cartasEnMano);
                        }

                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(dos.lista,dos.mano[1]);
                            sacarDeLaMano(1, dos.mano, dos.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, dos.lista);
                            ultimoQuince3(dos.ultQuince, uno.ultQuince, tres.ultQuince);
                        }
                        if (mazoVacio(baraja,cant))
                        {    
                            cout << "Ultima ronda" << endl;
                            dos.ultimaRonda++;
                            cout << dos.ultimaRonda << endl;
                        }
                    }
                
                break;
                
                default:
                {
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(dos.mano[2], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(dos.escobas);
                     
                        }

                         if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(dos.mano[2] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(2, dos.mano, dos.cartasEnMano);
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(dos.lista,dos.mano[2]);
                            sacarDeLaMano(2, dos.mano, dos.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, dos.lista);
                            ultimoQuince3(dos.ultQuince, uno.ultQuince, tres.ultQuince);
                           if (mazoVacio(baraja,cant))
                           {    cout << "Ultima ronda" << endl;
                                dos.ultimaRonda++;
                                cout << dos.ultimaRonda << endl;
                           }
                           
                        }
                }
                break;
            }

            } else if (turno == 3) {

                if (tres.cartasEnMano == 0)
                {
                    prototipoRepartir(baraja, tres.mano, tres.cartasEnMano);
                    mazoVacio(baraja,cant);
                }
                cout << "Jugador 3 elija una carta, en caso de no formar 15 se descartara." << endl;
                mostrarMano(tres, tres.cartasEnMano);
                mostrarMesa(tablero, tablero.cantCartasEnMesa);
                int opc= 0;
                cout << "Elija la de la posicion 1, 2 o 3 " << endl;
                cin >> opc ;
                int t= 8;
                int posiciones[t];
                turno = 1;

                switch (opc)
                {//sw
                case 1:
                    {//case  
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(tres.mano[0], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(tres.escobas);
                         
                        }

                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(tres.mano[0] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(0, tres.mano, tres.cartasEnMano);
                        }

                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(tres.lista,tres.mano[0]);
                            sacarDeLaMano(0, tres.mano, tres.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, tres.lista);
                            ultimoQuince3(tres.ultQuince, uno.ultQuince, dos.ultQuince);

                           if (mazoVacio(baraja,cant))
                           {    
                                cout << "Ultima ronda" << endl;
                                tres.ultimaRonda++;
                                cout << tres.ultimaRonda << endl;
                           }
                        }
                    }
                break;
                
                case 2:
                {  //case2 
                    
                    int cantCartasQueSumo15 = Suma15DeTodasFormas(tres.mano[1], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(tres.escobas);
                         
                        }
                        
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(tres.mano[1] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(1, tres.mano, tres.cartasEnMano);
                        }

                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(tres.lista,tres.mano[1]);
                            sacarDeLaMano(1, tres.mano, tres.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, tres.lista);
                            ultimoQuince3(tres.ultQuince, dos.ultQuince, uno.ultQuince);
                            if (mazoVacio(baraja,cant))
                            {    
                                cout << "Ultima ronda" << endl;
                                tres.ultimaRonda++;
                                cout << tres.ultimaRonda << endl;
                            }
                        }
                    }//case 2
                    break;

                    default:
                    {//case 3
                    
                        int cantCartasQueSumo15 = Suma15DeTodasFormas(tres.mano[2], tablero.cartas, tablero.cantCartasEnMesa, posiciones);
                        if (tablero.cantCartasEnMesa == cantCartasQueSumo15)
                        {
                            cout << "Es escoba!!" << endl;
                            escoba(tres.escobas);
                     
                        }
                        if (cantCartasQueSumo15 == -1)
                        {
                            ponerEnLaMesa(tres.mano[2] ,tablero.cartas, tablero.cantCartasEnMesa);
                            sacarDeLaMano(2, tres.mano, tres.cartasEnMano);
                        }
                        if (cantCartasQueSumo15 != -1)
                        {
                            sacarDeLaMesa(posiciones,tablero.cartas, cantCartasQueSumo15);
                            cargarAlFinal(tres.lista,tres.mano[2]);
                            sacarDeLaMano(2, tres.mano, tres.cartasEnMano);
                            saco(tablero.cartas, tablero.cantCartasEnMesa, tres.lista);
                            ultimoQuince3(tres.ultQuince, uno.ultQuince, dos.ultQuince);
                           if (mazoVacio(baraja,cant))
                           {    cout << "Ultima ronda" << endl;
                                tres.ultimaRonda++;
                                cout << tres.ultimaRonda << endl;
                           }
                        }

                        
                    }//case3
                    break;
                }//sw
                
                cout << "Turno del jugador: " << turno << endl;
            }
//----------------------------------------------------ACA HAY  ALGO RARO
            if (mazoVacio(baraja, cant) && uno.cartasEnMano == 0 && dos.cartasEnMano == 0 && tres.cartasEnMano == 0 && uno.ultQuince){
                int pos = tablero.cantCartasEnMesa;

                for (int i = 0; i < pos; i++)
                {
                    cargarAlFinal(uno.lista,tablero.cartas[i]);
                    sacarDeLaMesaIlegal(tablero.cartas[i].marcaJuego);
                    
                }
                sacoIlegal(tablero.cartas, tablero.cantCartasEnMesa);
            } else if (mazoVacio(baraja, cant) && uno.cartasEnMano == 0 && dos.cartasEnMano == 0 && tres.cartasEnMano == 0 && dos.ultQuince){//else if
                int pos = tablero.cantCartasEnMesa;
                for (int i = 0; i < pos; i++) {
                    cargarAlFinal(dos.lista,tablero.cartas[i]);
                    sacarDeLaMesaIlegal(tablero.cartas[i].marcaJuego);     
                }
                sacoIlegal(tablero.cartas, tablero.cantCartasEnMesa); 
            
            } else if(mazoVacio(baraja, cant) && uno.cartasEnMano == 0 && dos.cartasEnMano == 0 && tres.ultQuince && tres.cartasEnMano == 0) {
                int pos = tablero.cantCartasEnMesa;
                
                for (int i = 0; i < pos; i++) {
                    cout << "Cargo a la lista: " << tablero.cartas[i].valor << tablero.cartas[i].palo << endl;
                    cargarAlFinal(tres.lista,tablero.cartas[i]);
                    cout << "Saco de la mesa: " << tablero.cartas[i].valor << tablero.cartas[i].palo << endl;
                    sacarDeLaMesaIlegal(tablero.cartas[i].marcaJuego);
                }
                sacoIlegal(tablero.cartas, tablero.cantCartasEnMesa); 
                
                // if(mazoVacio(baraja,cant) && uno.cartasEnMano == 0 && dos.cartasEnMano == 0 && tres.cartasEnMano == 0 &&  ){
                // rondas++;
                // puntos1(uno.lista, uno.cant7, uno.cantO, uno.sieteO, uno.cantCartas);
                // puntos1(dos.lista, dos.cant7,dos.cantO, dos.sieteO, dos.cantCartas);
                // puntos1(tres.lista, tres.cant7,tres.cantO, tres.sieteO, tres.cantCartas);

                // compararPuntosJugadores3(uno, uno.puntos, dos, dos.puntos, tres, tres.puntos);
                // inicializarLista(uno.lista);
                // inicializarLista(dos.lista);
                // inicializarLista(tres.lista);
                // inicializarJugador(uno.mano, uno.cant7, uno.cantCartas,uno.cantO, uno.cartasEnMano, uno.sieteO, uno.lista, uno.ultimaRonda, uno.escobas, uno.ultQuince);
                // inicializarJugador(dos.mano, dos.cant7, dos.cantCartas, dos.cantO, dos.cartasEnMano, dos.sieteO, dos.lista, dos.ultimaRonda, dos.escobas, dos.ultQuince);
                // inicializarJugador(tres.mano, tres.cant7, tres.cantCartas, tres.cantO, tres.cartasEnMano, tres.sieteO, tres.lista, tres.ultimaRonda, tres.escobas, tres.ultQuince);
                // inicializarBaraja(baraja, cant, rondas);
                // repartirMesa2(baraja, tablero.cartas, tablero.cantCartasEnMesa);
                // }
            }//else  if

            if(mazoVacio(baraja,cant) && uno.cartasEnMano == 0 && dos.cartasEnMano == 0 && tres.cartasEnMano == 0   ){
                rondas++;
                puntos1(uno.lista, uno.cant7, uno.cantO, uno.sieteO, uno.cantCartas);
                puntos1(dos.lista, dos.cant7,dos.cantO, dos.sieteO, dos.cantCartas);
                puntos1(tres.lista, tres.cant7,tres.cantO, tres.sieteO, tres.cantCartas);

                compararPuntosJugadores3(uno, uno.puntos, dos, dos.puntos, tres, tres.puntos);
                inicializarLista(uno.lista);
                inicializarLista(dos.lista);
                inicializarLista(tres.lista);
                inicializarJugador(uno.mano, uno.cant7, uno.cantCartas,uno.cantO, uno.cartasEnMano, uno.sieteO, uno.lista, uno.ultimaRonda, uno.escobas, uno.ultQuince);
                inicializarJugador(dos.mano, dos.cant7, dos.cantCartas, dos.cantO, dos.cartasEnMano, dos.sieteO, dos.lista, dos.ultimaRonda, dos.escobas, dos.ultQuince);
                inicializarJugador(tres.mano, tres.cant7, tres.cantCartas, tres.cantO, tres.cartasEnMano, tres.sieteO, tres.lista, tres.ultimaRonda, tres.escobas, tres.ultQuince);
                inicializarBaraja(baraja, cant, rondas);
                repartirMesa2(baraja, tablero.cartas, tablero.cantCartasEnMesa);
            }
            
            if (uno.puntos >= 15 || dos.puntos >= 15 || tres.puntos >= 15) {
                jugadorConMasPuntos3(uno.puntos, dos.puntos, tres.puntos);
            }
 
        }
    }
    
    return 0;
}

carta cartas(carta baraj[], int cap){ 
    int pos=0;
    char palos[4] {'O','C','B','E'};
    for (int i = 1; i <13; i++)
    {
        if (i != 8 and i !=9)
        {
            for (int j = 0; j < 4; j++)
            {  
                baraj[pos].valor = i;
                baraj[pos].palo = palos[j];
            
                pos++;
            }
        }  
        
    }
    return baraj[cap];
}

void mostrarMano(jugador uno, int cantEnMano){ 
    cout << "Tus cartas: ";
    for (int i = 0; i < cantEnMano; i++)
    {
        cout << uno.mano[i].valor << uno.mano[i].palo << " ";

    }
    
}

void mostrarMesa(mesa tab, int cant){   
    cout << "\n" ;                      
    cout << "Cartas de la mesa: ";      
    for (int i = 0; i < cant; i++)
    {   
        cout << tab.cartas[i].valor <<  tab.cartas[i].palo << " ";
    }
    cout << "\n" ;
    
}


void repartirMesa2(carta baraj[], carta deLaMesa[], int& contador){
    int cant = 0;                                                       
    int i =0;
    while (cant != 4)
    {   
        int t = rand()%40;
        if (baraj[t].marcaBaraja != true and baraj[t].marcaJuego != true)
        {
            deLaMesa[i] = baraj[t];
            baraj[t].marcaBaraja = true;
            cant++;
            i++;
            contador++;
        }
        
    }
}

void prototipoRepartir(carta baraj[], carta manoJuga[], int& cantEnMano){
    int cant = 0;                                                       
    int i =0;
    while (cant != 3)
    {   
        int t = rand()%40;
        if (baraj[t].marcaBaraja != true and baraj[t].marcaJuego != true)
        {
            manoJuga[i] = baraj[t];
           
            baraj[t].marcaBaraja = true;
            cant++;
            i++;
            cantEnMano++;
        }
    }
    
}

int valor(carta cart){
    switch (cart.valor)
    {
    case 10:
        return 8;
        break;
    case 11:
        return 9;
        break;
    case 12:
        return 10;
        break;
    default:
        return cart.valor;
        break;
    }
    
}

int suma15(carta cart, carta tab[], int cap, int pos[] ){
    for (int i = 0; i < cap; i++)
    {
        if (valor(cart) + valor(tab[i]) == 15)
        {
            pos[0]= i;
            tab[i].marcaLista = true;
           
            return 1;
        }
        
    }
    
    return 0;
}

int charCmp(char a, char b){
    if (a != b)
    {
        return 1;
    }
    return 0;
}

int cartDistintas(carta a, carta b){
    int t = charCmp(a.palo, b.palo);
    if (a.valor != b.valor or t != 0)
    {
        return 1;
    }
    return 0;
}

int suma15DosCartas(carta cart, carta tab[], int cap, int posi[]){ //---------------UASAR FUERZA BRUTA
    for (int i = 0; i < cap; i++)
    {
        for (int j = 0; j < cap and cartDistintas(tab[i], tab[j]) ; j++)
        {
            if (valor(cart) + valor(tab[i]) + valor(tab[j]) == 15)
            {
                posi[0] = i;
                posi[1] = j;
                tab[i].marcaLista = true;
                tab[j].marcaLista = true;
                 

                return 1;
            }
            
        }
        
        
    }
    return 0;
}

int suma15TresCartas(carta cart ,carta tab[], int cap, int pos[]){
    for (int i = 0; i < cap; i++)
    {
        for (int j = 0; j < cap and cartDistintas(tab[i], tab[j]) ; j++)
        {
            for (int x = 0; x < cap and cartDistintas(tab[j], tab[x]); x++)
            {
                if (valor(cart) + valor(tab[i]) + valor(tab[j]) + valor(tab[x]) == 15)
                {
                    pos[0] = i;
                    pos[1] = j;
                    pos[2] = x;
                    tab[i].marcaLista = true;
                    tab[j].marcaLista = true;
                    tab[x].marcaLista = true;
                    return 1;
                }
                
            }
  
        }                
    }
    return 0;
}

int suma15CuatroCartas(carta cart ,carta tab[], int cap, int pos[]){
    for (int i = 0; i < cap; i++)
    {
        for (int j = 0; j < cap and cartDistintas(tab[i], tab[j]) ; j++)
        {
            for (int x = 0; x < cap and cartDistintas(tab[j], tab[x]); x++)
            {
               for (int y = 0; y < cap and cartDistintas(tab[x], tab[y]); y++)
               {
                    if (valor(cart) + valor(tab[i]) + valor(tab[j]) + valor(tab[x]) + valor(tab[y]) == 15)
                    {
                        pos[0] = i;
                        pos[1] = j;
                        pos[2] = x;
                        pos[3] = y;
                        tab[i].marcaLista = true;
                        tab[j].marcaLista = true;
                        tab[x].marcaLista = true;
                        tab[y].marcaLista = true;
                        return 1;
                    }
               }
               
            }
        }      
    }
    return 0;
}

int suma15CincoCartas(carta cart ,carta tab[], int cap, int pos[]){
    for (int i = 0; i < cap; i++)
    {
        for (int j = 0; j < cap and cartDistintas(tab[i], tab[j]) ; j++)
        {
            for (int x = 0; x < cap and cartDistintas(tab[j], tab[x]); x++)
            {
               for (int y = 0; y < cap and cartDistintas(tab[x], tab[y]); y++)
               {
                   for (int k = 0; k < cap and cartDistintas(tab[y], tab[k]); k++)
                   {
                        if (valor(cart) + valor(tab[i]) + valor(tab[j]) + valor(tab[x]) + valor(tab[y]) + valor(tab[k]) == 15)
                        {
                            pos[0] = i;
                            pos[1] = j;
                            pos[2] = x;
                            pos[3] = y;
                            pos[4] = k;
                            tab[i].marcaLista = true;
                            tab[j].marcaLista = true;
                            tab[x].marcaLista = true;
                            tab[y].marcaLista = true;
                            tab[k].marcaLista = true;
                            return 1;             
                        }
                   }
                   
               }
               
            }
            
            
        }
        
        
    }
    return 0;
}

int suma15SeisCartas(carta cart ,carta tab[], int cap, int pos[]){
    for (int i = 0; i < cap; i++)
    {
        for (int j = 0; j < cap and cartDistintas(tab[i], tab[j]) ; j++)
        {
            for (int x = 0; x < cap and cartDistintas(tab[j], tab[x]); x++)
            {
               for (int y = 0; y < cap and cartDistintas(tab[x], tab[y]); y++)
               {
                   for (int k = 0; k < cap and cartDistintas(tab[y], tab[k]); k++)
                   {
                        for (int t = 0; t < cap; t++)
                        {
                            if (valor(cart) + valor(tab[i]) + valor(tab[j]) + valor(tab[x]) + valor(tab[y]) + valor(tab[k]) + valor(tab[t]) == 15)
                            {
                                pos[0] = i;
                                pos[1] = j;
                                pos[2] = x;
                                pos[3] = y;
                                pos[4] = k;
                                pos[5] = t;
                                tab[i].marcaLista = true;
                                tab[j].marcaLista = true;
                                tab[x].marcaLista = true;
                                tab[y].marcaLista = true;
                                tab[k].marcaLista = true;
                                tab[t].marcaLista = true;
                                return 1;
                            }
                        }
                        
                   }
                   
               }
               
            }
            
            
        }
        
        
    }
    return 0;
}

Nodo* cargarAlFinal(Nodo*& L, carta cart){   
    Nodo* p = new Nodo();
    p->cartA = cart;
    p->sgte = NULL;
    if (L== NULL)
    {
        L= p;
    }else
    {
        Nodo* aux = L;
        while (aux->sgte != NULL)
        {
            aux = aux->sgte;
        }
        aux->sgte = p;
    }
        
    return p;
        
}


int saco(carta mesa[], int& cant, Nodo*& puntos1) {
    int t=0;
    carta arr[15];
    
    for (int i = 0; i < cant; i++)
    {
        if (mesa[i].marcaJuego != true)
        {                            
            arr[t] = mesa[i];           
            t++;                        
        }
        
    }
    //Meterla a la lista
    for (int i = 0; i < 15; i++)
    {
        if (mesa[i].marcaLista == true)
        {   carta r = mesa[i];
            cargarAlFinal(puntos1, r);
        }                       
        
    }


    for (int i = 0; i < cant; i++)
    {   
        mesa[i].marcaLista = false;
        mesa[i].marcaJuego= false;
        mesa[i].palo = ' ';
        mesa[i].valor = 0; 
    }
    

    for (int i = 0; i < t; i++)
    {
        mesa[i] = arr[i];
    }
    cant = t;
    return 0;
}

void sacarDeLaMesa(int pos[], carta mes[], int cap){
   
   for (int i = 0; i < cap; i++)
   {
        mes[pos[i]].marcaJuego = true;
   }
}

void sacarDeLaMano(int pos, carta mano[], int& cantEnMano){
    carta  arr[3];
    int t =0;
    for (int i = 0; i < cantEnMano ; i++)
    {
        if (i != pos)
        {
            arr[t] = mano[i];
            t++;
        }
        
    }

    for (int i = 0; i < cantEnMano; i++)
    {
        mano[i].marcaJuego= false;
        mano[i].palo = ' ';
        mano[i].valor = 0; 
    }

    for (int i = 0; i < t; i++)
    {
        mano[i] = arr[i];
    }
    cantEnMano--;
}

void ponerEnLaMesa(carta cart, carta mesa[], int& cantMesa){
    
    mesa[cantMesa] = cart;
    cantMesa++;
}

int Suma15DeTodasFormas(carta cart ,carta tab[], int cap, int pos[] ){ 
    cart.marcaJuego = true;
   if (suma15(cart, tab, cap, pos))
   {
    cart.marcaLista = true;
    cout << "Suma 15 con tu carta: " << cart.valor << cart.palo << " y " << tab[pos[0]].valor << tab[pos[0]].palo << endl;
    return 1;
   }else if (suma15DosCartas(cart, tab, cap, pos))
   {
    cart.marcaLista = true;
    cout << "Sumas 15 con tus cartas: " << cart.valor << cart.palo << ", "<< tab[pos[0]].valor << tab[pos[0]].palo << " y "<< tab[pos[1]].valor<< tab[pos[1]].palo  << endl;
    return 2;
   }else if (suma15TresCartas(cart, tab, cap, pos))
   {
    cart.marcaLista = true;
    cout << "Sumas 15 con tus cartas: " << cart.valor << cart.palo << ", " << tab[pos[0]].valor << tab[pos[0]].palo << ", "<< tab[pos[1]].valor << tab[pos[1]].palo << " y " << tab[pos[2]].valor << tab[pos[2]].palo << endl;
    return 3;
   }else if (suma15CuatroCartas(cart, tab, cap, pos))
   {
    cart.marcaLista = true;
    cout << "Sumas 15 con tus cartas: " << cart.valor << cart.palo << ", " << tab[pos[0]].valor << tab[pos[0]].palo << ", "<< tab[pos[1]].valor << tab[pos[1]].palo << ", " << tab[pos[2]].valor << tab[pos[2]].palo << " y "<< tab[pos[3]].valor << tab[pos[3]].palo << endl;
    return 4;
   }else if (suma15CincoCartas(cart, tab, cap, pos))
   {
    cart.marcaLista = true;
   cout << "Sumas 15 con tus cartas: " << cart.valor << cart.palo << ", " << tab[pos[0]].valor << tab[pos[0]].palo << ", "<< tab[pos[1]].valor << tab[pos[1]].palo << ", " << tab[pos[2]].valor << tab[pos[2]].palo << ", "<< tab[pos[3]].valor << tab[pos[3]].palo << " y " << tab[pos[4]].valor << tab[pos[4]].palo << endl;
    return 5;
   }else if (suma15SeisCartas(cart, tab, cap, pos))
   {
    cart.marcaLista = true;
    cout << "Sumas 15 con tus cartas: " << cart.valor << cart.palo << ", " << tab[pos[0]].valor << tab[pos[0]].palo << ", "<< tab[pos[1]].valor << tab[pos[1]].palo << ", " << tab[pos[2]].valor << tab[pos[2]].palo << ", "<< tab[pos[3]].valor << tab[pos[3]].palo << ", " << tab[pos[4]].valor << tab[pos[4]].palo << " y " << tab[pos[5]].valor << tab[pos[5]].palo << endl;
    return 6;
   }else
   {
    cout << "Tu carta se queda en el mazo!!! (*-*)" << endl;
   }
   

    return -1;
}


void puntos1(Nodo* cargarAlFinal, int& cant7, int& cantO, int& cantSietesDeOro, int& cantCartas) {

    Nodo* aux = cargarAlFinal;

    while(aux != NULL) {
                        
        carta cartaDesapilada = aux->cartA;
        cantCartas++;

        if(cartaDesapilada.palo == 'O') {
            cantO++;
        }
        if(cartaDesapilada.valor == 7) {
            
            if(cartaDesapilada.palo == 'O') {
                cantSietesDeOro++;
            }
            cant7++;               
        }
        aux= aux->sgte;
    }

    cout << "Cantidad oro: " << cantO << endl;
    cout << "7O: " << cantSietesDeOro << endl;
    cout << "Cantidad siete: " << cant7 << endl;
    cout << "Cantidad cartas: " << cantCartas << endl;   
}

void compararPuntosJugadores(jugador jugador1, int& puntosJ1, jugador jugador2, int& puntosJ2){
    
    if(jugador1.cantCartas > jugador2.cantCartas) {
        
        puntosJ1++;
    } else if (jugador1.cantCartas < jugador2.cantCartas){
        
        puntosJ2++;
    }
    

    if(jugador1.cant7 > jugador2.cant7) {
            
            puntosJ1++;
        } else if (jugador1.cant7 < jugador2.cant7){
            
            puntosJ2++;
        }
    

    if(jugador1.cantO > jugador2.cantO) {
            
            puntosJ1++;
        } else if (jugador1.cantO < jugador2.cantO){
            
            puntosJ2++;
    }
    
    if(jugador1.sieteO == 1) {
        
        puntosJ1++;
    
    } else if(jugador2.sieteO == 1) {
        
        puntosJ2++;

    } 

    for (int i = 0; i < jugador1.escobas; i++)
    {
        jugador1.puntos++;
    }
    cout << " Cantidad de escobas Jugador 1: " << jugador1.escobas << endl;
    for (int i = 0; i < jugador2.escobas; i++)
    {
        jugador2.puntos++;
    }
    cout << " Cantidad de escobas Jugador 2: " << jugador2.escobas << endl;
    
    

    cout << "PUNTOS JUGADOR 1: " << puntosJ1 << endl;// POR ESO MUESTRA SIEMPRE CERO PUNTOS
    cout << "PUNTOS JUGADOR 2: " << puntosJ2 << endl;
        
    
}

void compararPuntosJugadores3(jugador jugador1, int& puntosJ1, jugador jugador2, int& puntosJ2, jugador jugador3, int& puntosJ3) {
    if (jugador1.cantCartas > jugador2.cantCartas && jugador1.cantCartas > jugador3.cantCartas) {
        puntosJ1++;
    } else if (jugador2.cantCartas > jugador1.cantCartas && jugador2.cantCartas > jugador3.cantCartas) {
        puntosJ2++;
    } else if (jugador3.cantCartas > jugador1.cantCartas && jugador3.cantCartas > jugador2.cantCartas) {
        puntosJ3++;
    }

    if (jugador1.cant7 > jugador2.cant7 && jugador1.cant7 > jugador3.cant7) {
        puntosJ1++;
    } else if (jugador2.cant7 > jugador1.cant7 && jugador2.cant7 > jugador3.cant7) {
        puntosJ2++;
    } else if (jugador3.cant7 > jugador1.cant7 && jugador3.cant7 > jugador2.cant7) {
        puntosJ3++;
    }

    if (jugador1.cantO > jugador2.cantO && jugador1.cantO > jugador3.cantO) {
        puntosJ1++;
    } else if (jugador2.cantO > jugador1.cantO && jugador2.cantO > jugador3.cantO) {
        jugador2.puntos++;
    } else if (jugador3.cantO > jugador1.cantO && jugador3.cantO > jugador2.cantO) {
        puntosJ3++;
    }

    if (jugador1.sieteO == 1) {
        puntosJ1++;
    } else if (jugador2.sieteO == 1) {
        puntosJ2++;
    } else if (jugador3.sieteO == 1) {
        puntosJ3++;
    }

    for (int i = 0; i < jugador1.escobas; i++)
    {
        puntosJ1++;
    }
    cout << " Cantidad de escobas Jugador 1: " << jugador1.escobas << endl;
    for (int i = 0; i < jugador2.escobas; i++)
    {
        puntosJ2++;
    }
    cout << " Cantidad de escobas Jugador 2: " << jugador2.escobas << endl;
    for (int i = 0; i < jugador3.escobas; i++)
    {
        puntosJ3++;
    }
    cout << " Cantidad de escobas Jugador 3: " << jugador3.escobas << endl;
   

    cout << "PUNTOS JUGADOR 1: " << puntosJ1 << endl;
    cout << "PUNTOS JUGADOR 2: " << puntosJ2 << endl;
    cout << "PUNTOS JUGADOR 3: " << puntosJ3 << endl;
}

carta pop(Nodo* &pila){
    carta x;
    Nodo* p = pila;
    x = p->cartA;
    pila = p->sgte;
    delete p;
    return x;
}

void inicializarLista(Nodo*& lista){
    
    pop(lista);    
}


bool mazoVacio(carta baraja[], int cantidadDeCartas) {


    int cont = 0;

    for(int i = 0; i < cantidadDeCartas; i++) {


        if(baraja[i].marcaBaraja == true) {

            cont++;
        } 
    }

    if (cont == cantidadDeCartas) {
        cout << "Cantidad de cartas hasta ahora: " << cont << endl;
        
        return 1;
    }else
    {
        cout << "Cantidad de cartas hasta ahora: " << cont << endl;
    }
    
    return 0;//puede ser
}
// Porque viene aca??????????????'
void inicializarBaraja(carta baraj[], int cap, int& rondas){
    for (int i = 0; i < cap; i++)
    {
        baraj[i].marcaBaraja = false;
        baraj[i].marcaJuego = false;
        baraj[i].marcaLista = false;

    }
    cout << "Acabo la ronda "<< rondas << endl;
}

 void inicializarJugador(carta mano[], int& cant7, int& cantCartas, int& cantO, int& cartasEnMano, int& sieteO, Nodo*& L, int& ultimaRonda, int& escoba, bool& ultimoQuince ){
    for (int i = 0; i < 3; i++)
    {
        mano[i].marcaBaraja = false;
        mano[i].marcaJuego = false;
        mano[i].marcaLista = false;
        mano[i].palo = ' ';
        mano[i].valor =0;
    }
    cant7 = 0;
    cantCartas = 0;
    cantO = 0;
    cartasEnMano =0;
    sieteO =0;
    L= NULL;
    ultimaRonda = 0;
    escoba= 0;
    ultimoQuince = false;
}

void sacarDeLaMesaIlegal(bool& marca){
    marca = true;
}

int sacoIlegal(carta mesa[], int& cant) {
    int t=0;
    carta arr[8];
    
    for (int i = 0; i < cant; i++)
    {
        if (mesa[i].marcaJuego != true)
        {                            
            arr[t] = mesa[i];          
            t++;                       
        }
        
    }

    for (int i = 0; i < cant; i++)
    {   
        
        mesa[i].marcaJuego= false;
        mesa[i].palo = ' ';
        mesa[i].valor = 0; 
    }
    

    for (int i = 0; i < t; i++)
    {   
        mesa[i] = arr[i];
    }
    cant = t;
    return 0;
}


void escoba(int& punto){
    punto++;
}

void ultimoQuince(bool& primero, bool& segundo) {

    primero = true;
    segundo = false;

}

void ultimoQuince3(bool& primero, bool& segundo, bool& tercero) {

    primero = true;
    segundo = false;
    tercero = false;

}
void jugadorConMasPuntos(int j1, int j2){

    
    if (j1 > j2 )
    {
        cout <<"\nFelicitaciones jugador 1 has ganado la partida\n" << endl;

        cout << "───────────────────██████────────────────\n";
        cout << "─────────────────████████─█─────────────\n";
        cout << "─────────────██████████████─────────────\n";
        cout << "─────────────█████████████──────────────\n";
        cout << "──────────────███████████───────────────\n";
        cout << "───────────────██████████───────────────\n";
        cout << "────────────────████████────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "──────────────── ▌─────▌────────────────\n";
        cout << "────────────────███─█████───────────────\n";
        cout << "────────────████████████████────────────\n";
        cout << "──────────████████████████████──────────\n";
        cout << "────────████████████─────███████────────\n";
        cout << "──────███████████─────────███████───────\n";
        cout << "─────████████████───██─███████████──────\n";
        cout << "────██████████████──────────████████────\n";
        cout << "───████████████████─────█───█████████───\n";
        cout << "──█████████████████████─██───█████████──\n";
        cout << "──█████████████████████──██──██████████─\n";
        cout << "─███████████████████████─██───██████████\n";
        cout << "████████████████████████──────██████████\n";
        cout << "███████████████████──────────███████████\n";
        cout << "─██████████████████───────██████████████\n";
        cout << "─███████████████████████──█████████████─\n";
        cout << "──█████████████████████████████████████─\n";
        cout << "───██████████████████████████████████───\n";
        cout << "───────██████████████████████████████───\n";
        cout << "───────██████████████████████████───────\n";
        cout << "─────────────███████████████────────────\n";
        cout << "\n------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------\n"<< endl;

        cout << "UN MENSAJITO PARA VOS JUGADOR 2 \n" << endl;

        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
        cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
        cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    
    }    

    if (j2 > j1)
    {
        cout <<"\nFelicitaciones jugador 2 has ganado la partida\n" << endl;

        cout << "───────────────────██████────────────────\n";
        cout << "─────────────────████████─█─────────────\n";
        cout << "─────────────██████████████─────────────\n";
        cout << "─────────────█████████████──────────────\n";
        cout << "──────────────███████████───────────────\n";
        cout << "───────────────██████████───────────────\n";
        cout << "────────────────████████────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "──────────────── ▌─────▌────────────────\n";
        cout << "────────────────███─█████───────────────\n";
        cout << "────────────████████████████────────────\n";
        cout << "──────────████████████████████──────────\n";
        cout << "────────████████████─────███████────────\n";
        cout << "──────███████████─────────███████───────\n";
        cout << "─────████████████───██─███████████──────\n";
        cout << "────██████████████──────────████████────\n";
        cout << "───████████████████─────█───█████████───\n";
        cout << "──█████████████████████─██───█████████──\n";
        cout << "──█████████████████████──██──██████████─\n";
        cout << "─███████████████████████─██───██████████\n";
        cout << "████████████████████████──────██████████\n";
        cout << "███████████████████──────────███████████\n";
        cout << "─██████████████████───────██████████████\n";
        cout << "─███████████████████████──█████████████─\n";
        cout << "──█████████████████████████████████████─\n";
        cout << "───██████████████████████████████████───\n";
        cout << "───────██████████████████████████████───\n";
        cout << "───────██████████████████████████───────\n";
        cout << "─────────────███████████████────────────\n";
        cout << "\n------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------\n"<< endl;

        cout << "UN MENSAJITO PARA VOS JUGADOR 1 \n" << endl;

        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
        cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
        cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    }
    
}

void jugadorConMasPuntos3(int j1, int j2, int j3){


    if (j1 > j2 && j1 > j3)
    {
        cout <<"\nFelicitaciones jugador 1 has ganado la partida\n" << endl;

        cout << "───────────────────██████────────────────\n";
        cout << "─────────────────████████─█─────────────\n";
        cout << "─────────────██████████████─────────────\n";
        cout << "─────────────█████████████──────────────\n";
        cout << "──────────────███████████───────────────\n";
        cout << "───────────────██████████───────────────\n";
        cout << "────────────────████████────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "──────────────── ▌─────▌────────────────\n";
        cout << "────────────────███─█████───────────────\n";
        cout << "────────────████████████████────────────\n";
        cout << "──────────████████████████████──────────\n";
        cout << "────────████████████─────███████────────\n";
        cout << "──────███████████─────────███████───────\n";
        cout << "─────████████████───██─███████████──────\n";
        cout << "────██████████████──────────████████────\n";
        cout << "───████████████████─────█───█████████───\n";
        cout << "──█████████████████████─██───█████████──\n";
        cout << "──█████████████████████──██──██████████─\n";
        cout << "─███████████████████████─██───██████████\n";
        cout << "████████████████████████──────██████████\n";
        cout << "███████████████████──────────███████████\n";
        cout << "─██████████████████───────██████████████\n";
        cout << "─███████████████████████──█████████████─\n";
        cout << "──█████████████████████████████████████─\n";
        cout << "───██████████████████████████████████───\n";
        cout << "───────██████████████████████████████───\n";
        cout << "───────██████████████████████████───────\n";
        cout << "─────────────███████████████────────────\n";
        cout << "\n------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------\n"<< endl;

        cout << "UN MENSAJITO PARA VOS JUGADOR 2 \n" << endl;

        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
        cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
        cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";

        cout << "UN MENSAJITO PARA VOS JUGADOR 3 \n" << endl;

        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
        cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
        cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    
    
    }

    if (j2 > j1 && j2 > j3)
    {
   
        cout <<"\nFelicitaciones jugador 2 has ganado la partida\n" << endl;

        cout << "───────────────────██████────────────────\n";
        cout << "─────────────────████████─█─────────────\n";
        cout << "─────────────██████████████─────────────\n";
        cout << "─────────────█████████████──────────────\n";
        cout << "──────────────███████████───────────────\n";
        cout << "───────────────██████████───────────────\n";
        cout << "────────────────████████────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "──────────────── ▌─────▌────────────────\n";
        cout << "────────────────███─█████───────────────\n";
        cout << "────────────████████████████────────────\n";
        cout << "──────────████████████████████──────────\n";
        cout << "────────████████████─────███████────────\n";
        cout << "──────███████████─────────███████───────\n";
        cout << "─────████████████───██─███████████──────\n";
        cout << "────██████████████──────────████████────\n";
        cout << "───████████████████─────█───█████████───\n";
        cout << "──█████████████████████─██───█████████──\n";
        cout << "──█████████████████████──██──██████████─\n";
        cout << "─███████████████████████─██───██████████\n";
        cout << "████████████████████████──────██████████\n";
        cout << "███████████████████──────────███████████\n";
        cout << "─██████████████████───────██████████████\n";
        cout << "─███████████████████████──█████████████─\n";
        cout << "──█████████████████████████████████████─\n";
        cout << "───██████████████████████████████████───\n";
        cout << "───────██████████████████████████████───\n";
        cout << "───────██████████████████████████───────\n";
        cout << "─────────────███████████████────────────\n";
        cout << "\n------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------\n"<< endl;

        cout << "UN MENSAJITO PARA VOS JUGADOR 1 \n" << endl;

        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
        cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
        cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";

        cout << "UN MENSAJITO PARA VOS JUGADOR 3 \n" << endl;

        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
        cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
        cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    }
    
    if (j3 > j1 && j3>j2)  {

        cout <<"\nFelicitaciones jugador 3 has ganado la partida\n" << endl;

        cout << "───────────────────██████────────────────\n";
        cout << "─────────────────████████─█─────────────\n";
        cout << "─────────────██████████████─────────────\n";
        cout << "─────────────█████████████──────────────\n";
        cout << "──────────────███████████───────────────\n";
        cout << "───────────────██████████───────────────\n";
        cout << "────────────────████████────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "────────────────▐██████─────────────────\n";
        cout << "──────────────── ▌─────▌────────────────\n";
        cout << "────────────────███─█████───────────────\n";
        cout << "────────────████████████████────────────\n";
        cout << "──────────████████████████████──────────\n";
        cout << "────────████████████─────███████────────\n";
        cout << "──────███████████─────────███████───────\n";
        cout << "─────████████████───██─███████████──────\n";
        cout << "────██████████████──────────████████────\n";
        cout << "───████████████████─────█───█████████───\n";
        cout << "──█████████████████████─██───█████████──\n";
        cout << "──█████████████████████──██──██████████─\n";
        cout << "─███████████████████████─██───██████████\n";
        cout << "████████████████████████──────██████████\n";
        cout << "███████████████████──────────███████████\n";
        cout << "─██████████████████───────██████████████\n";
        cout << "─███████████████████████──█████████████─\n";
        cout << "──█████████████████████████████████████─\n";
        cout << "───██████████████████████████████████───\n";
        cout << "───────██████████████████████████████───\n";
        cout << "───────██████████████████████████───────\n";
        cout << "─────────────███████████████────────────\n";
        cout << "\n------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------"<< endl;
        cout << "------------------------------------------------------------------------\n"<< endl;

        cout << "UN MENSAJITO PARA VOS JUGADOR 1 \n" << endl;

        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
        cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
        cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";

        cout << "UN MENSAJITO PARA VOS JUGADOR 2 \n" << endl;

        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
        cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
        cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
        cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
        cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
        cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
        cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    }    
}
