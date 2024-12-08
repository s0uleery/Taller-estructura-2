#include <iostream>
#include "Tablero.h"
#include <string>

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
            cout << tablero[i][j]; 
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
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
            cout << tab[i][j]; 
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
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
    for (int i = 0; i < 3; i++) { 
        if (tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) return true; 
        if (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador) return true; 
    } 
    if (tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) return true; 
    if (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador) return true; 
    return false;
};
bool Tablero ::hayEmpate(){
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++) { 
            if (tablero[i][j] == ' ') 
            return false; 
        } 
    } 
    return true;
};