# Taller-2-estructura-de-datos

Paralelo C1

Clerians Márquez, 20.717.942-6 ; Valentina López, 21.392.825-2

Algoritmo minimax
====

### Definición

El algoritmo Minimax toma su nombre de su estrategia central: minimizar la máxima pérdida esperable ante la mejor jugada del oponente. Se fundamenta en la teoría de juegos, enraizándose en el concepto de equilibrio de Nash, que sostiene que en un juego con estrategias definidas, ningún jugador ganará cambiando su estrategia mientras los demás mantengan la suya.

Este algoritmo desglosa el juego en un árbol de juego, una estructura de datos que representa todos los posibles movimientos futuros en el juego. Cada nodo del árbol es una «posición» o estado del juego, y las aristas son movimientos que conectan un estado con otro. Minimax evalúa las posiciones al final de este árbol (nodos hoja), asignándoles valores basados en su utilidad para un jugador, para después retroceder y asignar un valor a los nodos padres.

El algoritmo de Alpha-Beta Pruning, tiene como objetivo reducir el tamaño del árbol de búsqueda. Para lograrlo, debemos proporcionar al algoritmo Min-Max criterios de detección que le indiquen cuándo debe detener la búsqueda en ciertas regiones del árbol una vez que haya encontrado el mínimo o máximo garantizado en ese nivel.


### Ejemplificación y análisis

Caso Simple: Juego de Nim


Reglas: Hay varias pilas de objetos, donde los jugadores alternan turnos, en cada turno un jugador debe tomar al menos un objeto de una pila, y puede tomar cualquier cantidad de objetos de esa pila. El jugador que tome el último objeto gana el juego.



```c++
// Implementación del algoritmo Minimax
int minimax(vector<int>& piles, bool isMax) {
    if (isGameOver(piles)) return isMax ? -1 : 1;

    if (isMax) {
        int best = -INF;
        for (int i = 0; i < piles.size(); ++i) {
            if (piles[i] > 0) {
                for (int k = 1; k <= piles[i]; ++k) {
                    piles[i] -= k;
                    best = max(best, minimax(piles, !isMax));
                    piles[i] += k;
                }
            }
        }
        return best;
    } else {
        int best = INF;
        for (int i = 0; i < piles.size(); ++i) {
            if (piles[i] > 0) {
                for (int k = 1; k <= piles[i]; ++k) {
                    piles[i] -= k;
                    best = min(best, minimax(piles, !isMax));
                    piles[i] += k;
                }
            }
        }
        return best;
    }
}
```

isMax: Inicializa best con -INF, luego recorre todas las pilas y todas las posibles jugadas tomando desde 1 a k objetos de una pila. Juega el turno, llama recursivamente a minimax con el jugador contrario, y deshace el turno, por ultimo actualiza best con el valor máximo encontrado

!isMax: Inicializa best con INF, luego recorre todas las pilas y todas las posibles jugadas. Juega un turno, llama recursivamente a minimax con el jugador contrario, y deshace el turno, por ultimo actualiza best con el valor mínimo encontrado
```c++
// Función para encontrar el mejor movimiento
Move findBestMove(vector<int>& piles) {
    int bestVal = -INF;
    Move bestMove = {-1, -1};

    for (int i = 0; i < piles.size(); ++i) {
        if (piles[i] > 0) {
            for (int k = 1; k <= piles[i]; ++k) {
                piles[i] -= k;
                int moveVal = minimax(piles, false);
                piles[i] += k;
                if (moveVal > bestVal) {
                    bestMove.pileIndex = i;
                    bestMove.objectsTaken = k;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}
```
Esta función se centra en recorrer todas las pilas. Para cada pila, si tiene objetos (piles[i] > 0), recorre todas las posibles jugadas tomando desde 1 a k objetos, luego realiza la jugada (piles[i] -= k), evalúa el valor de esa jugada usando minimax, y deshace la jugada (piles[i] += k).


Si el valor de la jugada (moveVal) es mayor que el mejor valor encontrado (bestVal), actualiza bestMove y bestVal.
```c++
int main() {
    vector<int> piles = {3, 4, 5};
    
    cout << "Estado inicial de las pilas:\n";
    printPiles(piles);

    Move bestMove = findBestMove(piles);
    cout << "La mejor jugada es tomar " << bestMove.objectsTaken 
         << " objetos de la Pila " << bestMove.pileIndex + 1 << endl;

    return 0;
}

```

### Búsqueda en el arbol de juego tic-tac-toe

En nuestro tablero tendremos 9 grados de profundidad pero por cada grado habrá 9 nodos diferentes por las posiciones.
![image](https://github.com/user-attachments/assets/8a521007-8ad2-435e-81c2-1ebaab419d80)

Al implementar nuestro algoritmo obtendremos algo parecido al siguiente árbol del juego:
![Captura8](https://github.com/user-attachments/assets/a60ebfb8-e84f-475c-9355-51ce9e2e6fd4)


