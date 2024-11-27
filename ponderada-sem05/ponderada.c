#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 100000000 // Tamanho do vetor

int main() {
    int i;
    long long soma = 0;  // Variável para armazenar o somatório final
    int *vetor;

    // Alocar memória para o vetor
    vetor = (int *) malloc(N * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memória!\n");
        return -1;
    }

    // Inicializar o vetor com valores aleatórios entre 1 e 100
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        vetor[i] = rand() % 100 + 1;
    }

    // Definir o número de threads
    omp_set_num_threads(8);

    // Iniciar a região paralela
    #pragma omp parallel
    {
        long long soma_local = 0; // Variável local para evitar condições de corrida

        // Distribuir o trabalho entre as threads
        #pragma omp for
        for (i = 0; i < N; i++) {
            soma_local += vetor[i];
        }

        // Combinar os resultados parciais em uma região crítica
        #pragma omp critical
        {
            soma += soma_local;
        }
    }

    // Exibir o resultado final
    printf("O somatório dos elementos do vetor é: %lld\n", soma);

    // Liberar a memória alocada
    free(vetor);

    return 0;
}
