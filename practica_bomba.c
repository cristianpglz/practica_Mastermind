/*

 CURSO MASTERMIND
 
 
 EJERCICIO: Desactivar la Bomba
 
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int generarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(NULL));

    int nivel;
    printf("--- Niveles de dificultad ---\n");
    printf("1. Fácil (Números del 10 al 50)\n");
    printf("2. Medio (Números del 10 al 60)\n");
    printf("3. Difícil (Números del 10 al 70)\n");
    printf("4. Experto (Números del 10 al 80)\n");
    printf("5. Personalizado (Números del 10 al 100)\n");
    printf("Elige un nivel de dificultad (1-5): ");
    scanf("%d", &nivel);

    int rangoMaximo = 0;
    switch (nivel) {
        case 1:
            rangoMaximo = 50;
            break;
        case 2:
            rangoMaximo = 60;
            break;
        case 3:
            rangoMaximo = 70;
            break;
        case 4:
            rangoMaximo = 80;
            break;
        case 5:
            rangoMaximo = 100;
            break;
        default:
            rangoMaximo = 100;
    }

    // Generar el número objetivo
    int numeroObjetivo = generarNumeroAleatorio(1, rangoMaximo);

    // Generar los 5 números aleatorios sin repetición
    int numeros[5];
    int numerosGenerados = 0;

    while (numerosGenerados < 5) {
        int num = generarNumeroAleatorio(1, 10);
        bool repetido = false;
        for (int i = 0; i < numerosGenerados; i++) {
            if (numeros[i] == num) {
                repetido = true;
                break;
            }
        }
        if (!repetido) {
            numeros[numerosGenerados] = num;
            numerosGenerados++;
        }
    }

    // Mostrar los números generados al usuario
    printf("Se ha generado un número objetivo entre 1 y %d: %d\n", rangoMaximo, numeroObjetivo);
    printf("Se han generado 5 números del 1 al 10 sin repetir:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    // Generar la operación matemática para que el resultado sea el número objetivo
    char operacion[100];
    char operadores[] = "+-*";
    sprintf(operacion, "%d", numeros[0]);
    for (int i = 1; i < 5; i++) {
        char operador = operadores[rand() % 3];
        char numero[5];
        sprintf(numero, "%d", numeros[i]);
        strcat(operacion, &operador);
        strcat(operacion, numero);
    }

    // Calcular el resultado de la operación
    int resultadoObjetivo = 0;
    sscanf(operacion, "%d", &resultadoObjetivo);

    // Mostrar la operación al usuario
    printf("Completa la operación utilizando los números proporcionados y las operaciones (+, -, *) para obtener el número objetivo:\n");
    printf("%s = ?\n", operacion);

    // Leer el resultado ingresado por el usuario
    int resultadoUsuario;
    printf("Ingresa el resultado: ");
    scanf("%d", &resultadoUsuario);

    // Mostrar si el usuario acertó o no
    if (resultadoUsuario == resultadoObjetivo) {
        printf("¡Felicidades! Has desactivado la bomba.\n");
    } else {
        printf("La bomba ha explotado. El número objetivo era: %d\n", resultadoObjetivo);
    }

    return 0;
}
