/*

 CURSO MASTERMIND
 
 
 EJERCICIO: Desactivar la Bomba
 
 
 */
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_EXPRESION 50

typedef struct {
    char data[MAX_EXPRESION];
    int top;
} Stack;

void push(Stack *s, char c) {
    if (s->top < MAX_EXPRESION - 1) {
        s->top++;
        s->data[s->top] = c;
    } else {
        printf("Error: Stack overflow\n");
        exit(1);
    }
}

char pop(Stack *s) {
    if (s->top >= 0) {
        char c = s->data[s->top];
        s->top--;
        return c;
    } else {
        printf("Error: Stack underflow\n");
        exit(1);
    }
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int precedence(char op) {
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b != 0)
                return a / b;
            else {
                printf("Error: Division by zero\n");
                exit(1);
            }
    }
    return 0;
}

int evaluarOperacion(const char *expresion) {
    Stack valores;
    valores.top = -1;
    
    Stack operadores;
    operadores.top = -1;
    
    for (int i = 0; expresion[i] != '\0'; i++) {
        if (isdigit(expresion[i])) {
            int valor = 0;
            while (isdigit(expresion[i])) {
                valor = valor * 10 + (expresion[i] - '0');
                i++;
            }
            i--;
            push(&valores, valor);
        } else if (expresion[i] == '(') {
            push(&operadores, '(');
        } else if (expresion[i] == ')') {
            while (!isEmpty(&operadores) && operadores.data[operadores.top] != '(') {
                int val2 = pop(&valores);
                int val1 = pop(&valores);
                char op = pop(&operadores);
                push(&valores, applyOp(val1, val2, op));
            }
            if (!isEmpty(&operadores) && operadores.data[operadores.top] == '(')
                pop(&operadores);
        } else if (expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/') {
            while (!isEmpty(&operadores) && precedence(operadores.data[operadores.top]) >= precedence(expresion[i])) {
                int val2 = pop(&valores);
                int val1 = pop(&valores);
                char op = pop(&operadores);
                push(&valores, applyOp(val1, val2, op));
            }
            push(&operadores, expresion[i]);
        }
    }
    
    while (!isEmpty(&operadores)) {
        int val2 = pop(&valores);
        int val1 = pop(&valores);
        char op = pop(&operadores);
        push(&valores, applyOp(val1, val2, op));
    }
    
    return pop(&valores);
}

int main() {
    int nivel;
    int numObjetivo;
    int numeros[5];
    int bombasDesactivadas = 0;
    int totalBombasDesactivadas = 0;
    int continuar = 1;

    srand(time(NULL));

    while (continuar) {
        printf("--- Niveles de dificultad ---\n");
        printf("1. Facil (Numeros del 10 al 50) (60 segundos)\n");
        printf("2. Medio (Numeros del 10 al 60)(45 segundos)\n");
        printf("3. Dificil (Numeros del 10 al 70)(30 segundos)\n");
        printf("4. Experto (Numeros del 10 al 80)(20 segundos)\n");
        printf("5. Personalizado (Numeros del 10 al 100)(en segundos)\n");
        
        // El jugador elige el nivel de dificultad
        printf("Elige un nivel de dificultad (1-5): ");
        scanf("%d", &nivel);

        int tiempoLimite = 0; // Variable para almacenar el tiempo límite

        switch (nivel) {
            case 1:
                tiempoLimite = 60;
                numObjetivo = rand() % 41 + 10;
                break;
            case 2:
                tiempoLimite = 45;
                numObjetivo = rand() % 51 + 10;
                break;
            case 3:
                tiempoLimite = 30;
                numObjetivo = rand() % 61 + 10;
                break;
            case 4:
                tiempoLimite = 20;
                numObjetivo = rand() % 71 + 10;
                break;
            case 5:
                printf("Ingresa el tiempo limite en segundos: ");
                scanf("%d", &tiempoLimite);
                numObjetivo = rand() % 91 + 10;
                break;
            default:
                printf("Opcion no valida\n");
                return 1;
        }

        int minNumero = (numObjetivo > 70) ? 6 : 1;

        // Genera 5 números aleatorios y no repetidos
        for (int i = 0; i < 5; i++) {
            numeros[i] = rand() % 10 + minNumero;
            for (int j = 0; j < i; j++) {
                if (numeros[i] == numeros[j]) {
                    i--;
                    break;
                }
            }
        }

        printf("Se han generado 5 numeros del %d al 10 sin repetir:\n", minNumero);
        for (int i = 0; i < 5; i++) {
            printf("%d ", numeros[i]);
        }
        printf("\n");

        printf("Tienes %d segundos para desactivar la bomba. El numero objetivo es: %d\n", tiempoLimite, numObjetivo);

        char expresion[MAX_EXPRESION];
        printf("Ingrese una operación matematica utilizando los números proporcionados y las operaciones (+, -, *, /) para obtener el numero objetivo:\n");
        scanf(" %[^\n]", expresion);

        // Temporizador
        time_t startTime = time(NULL);
        int elapsedTime = 0;
        int inputFlag = 0; // Bandera para verificar si el usuario ha ingresado una respuesta

        // Evalúa la operación matemática mientras haya tiempo
        while (elapsedTime < tiempoLimite) {
            time_t currentTime = time(NULL);
            elapsedTime = difftime(currentTime, startTime);

            int numerosValidos = 1;
            // Verifica si los números en la operación son válidos
            for (int i = 0; i < strlen(expresion); i++) {
                if (isdigit(expresion[i])) {
                    int numero = expresion[i] - '0';
                    int numeroValido = 0;
                    for (int j = 0; j < 5; j++) {
                        if (numero == numeros[j]) {
                            numeroValido = 1;
                            break;
                        }
                    }
                    if (!numeroValido) {
                        numerosValidos = 0;
                        break;
                    }
                }
            }

            // Si los números son válidos, evalúa la operación y compara con el objetivo
            if (numerosValidos) {
                int resultado = evaluarOperacion(expresion);

                if (resultado == numObjetivo) {
                    printf("Bomba desactivada! ¡Has ganado!\n");
                    bombasDesactivadas++;
                    printf("Bombas desactivadas en esta partida: %d\n", bombasDesactivadas);
                    break;  // Salir del bucle si se desactiva la bomba
                } else if (resultado != numObjetivo){
                    printf("La bomba ha explotado. El numero objetivo era: %d\n", numObjetivo);
                    bombasDesactivadas = 0;
                    break;  // Salir del bucle si la bomba explota
                }
                } else {
                    printf("Operación inválida. Los números en la operación deben ser los generados aleatoriamente.\n");
                    break;  // Salir del bucle si la operación es inválida
            }
        }

        // Pregunta si el jugador quiere seguir jugando
        printf("Quieres seguir jugando? (s/n): ");
        char respuesta;
        scanf(" %c", &respuesta);

        if (respuesta == 'n' || respuesta == 'N') {
            printf("Has desactivado un total de %d bombas.\n", totalBombasDesactivadas + bombasDesactivadas);
            totalBombasDesactivadas += bombasDesactivadas;
            bombasDesactivadas = 0;
            printf("Quieres reiniciar el juego? (s/n): ");  // Preguntar si desea reiniciar
            scanf(" %c", &respuesta);
            if (respuesta == 'n' || respuesta == 'N') {
                continuar = 0;  // Finalizar el juego
            }
        }
    }

    printf("Gracias por jugar!\n");

    return 0;
}
