#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// funcion que ejecutara el hilo secundario
void* contar_descendente(void* arg) {
    for (int i = 10000; i >= 1; i--) {
        printf("Hilo secundario: %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t hilo_secundario;

    // Creacion del hilo secundario
    // pthread_create recibe la variable de hilo, atributos (NULL = por defecto)
    // la función a ejecutar y los argumentos para la función (NULL).
    if (pthread_create(&hilo_secundario, NULL, contar_descendente, NULL) != 0) {
        perror("Error al crear el hilo");
        return 1;
    }

    // El hilo main ejecuta su propio ciclo ascendente al mismo tiempo
    for (int i = 1; i <= 10000; i++) {
        printf("Hilo principal: %d\n", i);
    }

    // Esperar a que el hilo secundario termine antes de cerrar el programa
    // Si no usamos pthread_join, el main podria terminar y matar al hilo secundario a la mitad.
    if (pthread_join(hilo_secundario, NULL) != 0) {
        perror("Error al unir el hilo");
        return 1;
    }

    return 0;
}