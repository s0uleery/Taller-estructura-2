#include <iostream>
#include "Tablero.h"
#include <string>
#include <climits>

using namespace std;

Tablero :: Tablero(){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            tablero[i][j] = ' ';
        }
    }
};

void Tablero ::mostrarTablero(){
    cout << "Tablero actual:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "" << tablero[i][j] << " | "; 
        }
        cout << "\n-----------\n";
    }
    cout << endl;
};

void Tablero :: posTablero(){
    int tab[3][3];
    int l = 1;
    
    cout << "Posiciones en el tablero:\n";
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            tab[i][j] = l++;
        }
    }
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "" << tab[i][j]<< " | "; 
        }
        cout << "\n-----------\n";
    }
    cout << endl;
};

bool Tablero :: movimientoValido(int fila, int columna){
    return fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero[fila][columna] == ' ';
};

void Tablero ::hacerMovimiento(int fila, int columna, char jugador){
    tablero[fila][columna] = jugador;
};

bool Tablero ::verificarGanador(char jugador){
    for (int i = 0; i < 3; i++) { //Ariba y abajo 
        if (tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) return true; 
        if (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador) return true; 
    } //diagonal
    if (tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) return true; 
    if (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador) return true; 
    return false;
};
bool Tablero :: hayEmpate(){
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++) { 
            if (tablero[i][j] == ' ') 
            return false; 
        } 
    } 
    return true;
};

char Tablero :: obtenerCelda(int fila, int columna) const { 
    return tablero[fila][columna]; 
}

void Tablero :: setCelda(int fila, int columna, char valor) {
    tablero[fila][columna] = valor;
}

int evaluarTablero(Tablero& juego){
    if(juego.verificarGanador('X'))return 10;
    if(juego.verificarGanador('O'))return -10;
    return 0;
}

int Tablero :: miniMaxSin(Tablero& tab, int profundidad, bool isMaximing){//minimax sin poda
    int resultado = evaluarTablero(tab);
    
    if(resultado == 10 || resultado == -10 || tab.hayEmpate()){
        return resultado; 
    }
    
    if(isMaximing){
        int mejor = -1000;
        for (int i = 0; i < 3; i++) { 
            for (int j = 0; j < 3; j++) { 
                if (tab.obtenerCelda(i, j) == ' '){
                    tab.hacerMovimiento(i,j,'X');
                    int puntaje = miniMaxSin(tab, profundidad + 1, false);
                    tab.setCelda(i,j,' ');
                    mejor = max(mejor, puntaje);
                }
            } 
        }
        return mejor;
    }else{
        int mejor = 1000;
        for (int i = 0; i < 3; i++) { 
            for (int j = 0; j < 3; j++) { 
                if (tab.obtenerCelda(i, j) == ' '){
                    tab.hacerMovimiento(i,j,'O');
                    int puntaje = miniMaxSin(tab, profundidad + 1, true);
                    tab.setCelda(i,j,' ');
                    mejor = min(mejor, puntaje);
                }
            } 
        }
        return mejor;
    }
}

int Tablero :: miniMaxCon(Tablero& tab, int profundidad, int alfa,int beta, bool isMaximing){//minimax con poda
    int resultado = evaluarTablero(tab);
    
    if(resultado == 10 || resultado == -10 || tab.hayEmpate()){
        return resultado; 
    }
    
    if(isMaximing){
        int mejor = -1000;
        for (int i = 0; i < 3; i++) { 
            for (int j = 0; j < 3; j++) { 
                if (tab.obtenerCelda(i, j) == ' '){
                    tab.hacerMovimiento(i,j,'X');
                    int puntaje = miniMaxCon(tab, profundidad + 1, alfa, beta, false);
                    tab.setCelda(i,j,' ');
                    mejor = max(mejor, puntaje);
                    alfa = max(alfa, mejor);
                    if(beta <= alfa)return mejor;
                }
            } 
        }
        return mejor;
    }else{
        int mejor = 1000;
        for (int i = 0; i < 3; i++) { 
            for (int j = 0; j < 3; j++) { 
                if (tab.obtenerCelda(i, j) == ' '){
                    tab.hacerMovimiento(i,j,'O');
                    int puntaje = miniMaxCon(tab, profundidad + 1, alfa, beta, true);
                    tab.setCelda(i,j,' ');
                    mejor = min(mejor, puntaje);
                    beta = min(beta, mejor);
                    if(beta <= alfa)return mejor;
                }
            } 
        }
        return mejor;
    }
}

std::pair<int, int> Tablero::encontrarMejorMovimiento() {
    int mejorV = INT_MIN;
    std::pair<int, int> mejorMovimiento = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Comprueba si la celda está vacía
            if (obtenerCelda(i, j) == ' ') {
                hacerMovimiento(i, j, 'X'); // Simula movimiento
                int movimiento = miniMaxCon(*this, 0, INT_MIN, INT_MAX, false);
                setCelda(i, j, ' '); // Revierte el movimiento
                
                if (movimiento > mejorV) {
                    mejorV = movimiento;
                    mejorMovimiento = {i, j};
                }
            }
        }
    }
    return mejorMovimiento;
}
