**Trabajo para la UTN en la que se pide programar el juego de cartas 'Escoba del 15'**


**Manual de usuario:**

El juego de la escoba del 15 se juega con tres jugadores. Cada jugador recibe inicialmente tres cartas y se colocan cuatro cartas boca arriba sobre la mesa. El objetivo del juego es capturar cartas que sumen un total de 15 puntos.

**Reparto de cartas:**
Al iniciar el juego, se le pedirá al usuario que elija entre 2 o 3 jugadores.
Se reparten tres cartas a cada jugador y se muestran las cartas en la mano de cada uno.
Se muestran cuatro cartas boca arriba en la mesa.

**Turno de juego:**
Durante su turno, a cada jugador se le pide que elija una carta de su mano.
Si la carta seleccionada forma un total de 15 puntos con las cartas en la mesa, se retiran todas las cartas involucradas.
Si no es posible sumar 15 puntos, el jugador debe descartar una carta en la mesa.
Se muestran mensajes indicando qué cartas suman 15 puntos y cuáles se han descartado.

**Fin del juego:**
El juego continúa hasta que todas las cartas han sido capturadas o descartadas.
Se otorgan puntos a cada jugador según las cartas que hayan capturado.
El jugador que llega a los 15 puntos gana, de no ser así quien tenga más puntos al final del juego es declarado ganador.

**Interfaz de usuario:**
Se muestran mensajes detallados para guiar a los jugadores durante su turno.
Se proporciona información sobre las cartas en la mano de cada jugador y las cartas en la mesa.
Se muestran mensajes indicando qué cartas se han seleccionado y qué acciones se han tomado en cada turno.




**Generación de la baraja:** La función carta cartas(carta baraj[], int cap) se encarga de generar las cartas de la baraja española, excluyendo los 8 y 9 de cada palo. Utiliza un bucle anidado para iterar sobre los valores y los palos de las cartas y los almacena en un arreglo de estructuras carta.

**Reparto de cartas:** La función prototipoRepartir(carta baraj[], carta manoJuga[], int& cantEnMano) se utiliza para repartir cartas a un jugador. Genera números aleatorios para seleccionar cartas de la baraja y las asigna a la mano del jugador, asegurándose de no repetir cartas.

**Suma de 15:** Se implementan varias funciones (suma15, suma15DosCartas, suma15TresCartas, etc.) para verificar si hay combinaciones de cartas en la mesa que sumen 15. Estas funciones recorren las cartas en la mesa y comprueban si su valor suma 15 junto con otras cartas seleccionadas.

**Captura de cartas:** La función saco se utiliza para capturar las cartas que suman 15 de la mesa y las elimina de esta. También se marca la carta como parte del juego para evitar que se capturen varias veces.

**Conteo de puntos:** La función puntos1 recibe una lista enlazada con las cartas que ha capturado el jugador para facilitar el cálculo, a medida que las saca de la lista, cuenta los puntos de un jugador, considerando la cantidad de cartas, sietes y siete de oro. Los puntos de escoba los pasamos por referencia en una función escoba.

**Sistema de puntos:**
7 de oro: 1 punto
Setenta: mayor cantidad de 7 que el rival: 1 punto, en caso de igualdad no se suma nada
Mayor cantidad de cartas: 1 punto
Mayor cantidad de oros: 1 punto, en caso de igualdad no se suma nada

**Finalización del juego:** La función mazoVacio verifica si todas las cartas de la baraja han sido utilizadas, lo que indica el final del juego.

**Inicialización:** Se proporcionan funciones para inicializar variables y estructuras al comienzo de cada ronda o juego (inicializarBaraja, inicializarJugador).

**Combinatoria:** La combinación de cartas para verificar si suman 15 se realiza mediante varias funciones que recorren las cartas en la mesa y comprueben todas las combinaciones posibles. 

**Combinación de dos cartas (suma15DosCartas):**
Utiliza dos bucles anidados para recorrer todas las cartas en la mesa y seleccionar dos cartas diferentes.
Se verifica si la suma de los valores de las dos cartas seleccionadas es igual a 15.
Este proceso se repite tanto para combinatoria de tres, cuatro, cinco y hasta seis cartas (cantidad de cartas = cantidad de bucles anidados).
