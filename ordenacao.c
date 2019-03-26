/*
*    Métodos de ordenação básicos usando C
*
*/

/* Bibliotecas importadas.. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Definir o tamanho do vetor.. */
#define TAM 1000

/* Estrutura para armazenaros dados.. */
typedef struct {
	int num;
	char name;
	float price;
} Store[TAM];

/* Cabeçalho dos métodos de ordenação.. */
void showstruct(Store store, int n, int count);
void bubblesort(Store store, int n);
void insertionsort(Store store, int n);
void selectionsort(Store store, int n);
void shellsort(Store store, int n);
int partition(Store store, int low, int high);
void quicksort(Store store, int low, int high);
void merge(Store store, int l, int m, int r);
void mergesort(Store store, int l, int r);

/* Programa principal.. */
int main(int argc, char const *argv[])
{
	int op;
	srand(time(NULL));
	
	Store store;

	// Preenche o vetor com valores aleatórios..
	for (int i = 0; i < TAM; i++)
	{
		store[i].num = rand() % TAM;
		store[i].name = rand() % 25 + 65;
		store[i].price = rand() % TAM + (TAM * 3);
	}	

	printf("\n---Menu---\n1. Bubble Sort\n2. Insertion Sort\n3."
		 " Selection Sort\n4. Shell Sort\n5. Quicksort\n"
		 "6. Heapsort\n7. Mergesort\n0. Sair\n:: ");
	scanf("%d", &op);
	switch(op) {
		case 0:
			return 0;
		break;
		case 1:
			// Invoca o método de ordenação Bubble Sort..
			bubblesort(store, TAM);
		break;
		case 2:
			// Invoca o método de ordenação Insertion Sort..
			insertionsort(store, TAM);
		break;
		case 3:
			// Invoca o método de ordenação Selection Sort..
			selectionsort(store, TAM);
		break;
		case 4:
			// Invoca o método de ordenação Shell Sort..
			shellsort(store, TAM);
		break;
		case 5:
			// Invoca o método de ordenação Quick Sort..
			quicksort(store, 0, TAM - 1);
			showstruct(store, TAM, 0);
		break;
		case 6:

		break;
		case 7:
			// Invoca o método de ordenação Merge Sort..
			mergesort(store, 0, TAM - 1);
			showstruct(store, TAM, 0);
		break;
		default: printf("Invalid Option..\n");
	}
	

	return 0;
}

void showstruct(Store store, int n, int count) {
	printf("#---------------------------#\n");
	for (int i = 0; i < TAM; i++)
	{
		printf("Number %d\tName %c\tPrice %.2f\n", store[i].num,
			store[i].name, store[i].price);
	}

	printf("--- TROCAS %d ---\n", count);
}

// Bubble Sort
void bubblesort(Store store, int n) {
	int AUX, count;
	count = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			/* Verifica se o valor na posição J é maior que o       *
			*  valor da posição J+1, se for o caso ocorre a troca.. */
			if (store[j].num > store[j+1].num) 
			{
				AUX = store[j+1].num;
				store[j+1].num = store[j].num;
				store[j].num = AUX;
				
				/* Contador para saber a quantidade de trocas feitas.. */
				count++;
			}
		}
	}

	showstruct(store, n, count);
}

// Insertion Sort
void insertionsort(Store store, int n) {
	int key, j, count;
	count = 0; 

    for (int i = 1; i < n; i++) 
    { 
        /* Armazena o valor da posição [i] em uma  *
        *  variável auxiliar..                     */
        key = store[i].num; 
        j = i - 1; 
  
  		/* Verifica se o valor apontado por j é maior      *
  		*  que o valor armazenado em key, se for será      *
  		*  feito uma verificação com os valores anteriores *
  		*  a j para saber se ele é o menor valor ou não    *
  		*  e coloca-lo na sua ordem correta..             */
        while (j >= 0 && store[j].num > key) 
        { 
            store[j+1].num = store[j].num; 
            j = j - 1; 

            count++; 
        }
        
        // Coloca o valor de key na ordem correta..
        store[j+1].num = key; 
    } 

	showstruct(store, n, count);

}

// Selection Sort
void selectionsort(Store store, int n) {
	int AUX, count, min_idx;
	count = 0;

	for (int i = 0; i < n-1; i++)
	{
		// Aceita que o primeiro valor do vetor a ser observado
		// é o menor valor..
		min_idx = i;
		for (int j = i+1; j < n; j++)
		{
			/* Verifica se algum outro valor é menor do que o que *
			*  está sendo observado. Se for verdade então o index  *
			*  desse valor será armazenado no min_idx, caso falso *
			*  o menor valor é o primeiro..                       */
			if (store[j].num < store[min_idx].num) 
			{
				min_idx = j;
				count++;
			}
		}

		// Faz a troca dos valores..
		AUX = store[i].num;
		store[i].num = store[min_idx].num;
		store[min_idx].num = AUX;
	}

	showstruct(store, n, count);
}

// Shell Sort
void shellsort(Store store, int n) {
	int key, count, h, j, i;
	count = 0;

	// Cálculo para saber o tamanho do h..
	for (h = 1; h < n; h = 3*h +1);

	// Enquanto o h for maior que 0 será feita a ordenação..
	while (h > 0) 
	{
		h = (h - 1) / 3;

		for (i = h; i < n; i++) 
		{
			// Armazena o valor da posição i do vetor na variável key
			// para ser comparada com outros valores do vetor..
			key = store[i].num;
			j = i;
		
			while (store[j - h].num > key) 
			{
				store[j].num = store[j - h].num;
				j -= h;

				count++;

				if (j < h) break;
			}
			store[j].num = key;
		}
	}

	showstruct(store, n, count);
}

// Quick Sort
int partition(Store store, int low, int high) {
	int pivot = store[high].num;
	int i = (low - 1);
	int AUX;

	for (int j = low; j <= high - 1; j++) 
	{
		if (store[j].num <= pivot) 
		{
			i++;

			AUX = store[i].num;
			store[i].num = store[j].num;
			store[j].num = AUX;
		}
	}
	AUX = store[i + 1].num;
	store[i + 1].num = store[high].num;
	store[high].num = AUX;

	return (i + 1);
}

void quicksort(Store store, int low, int high) {
	if (low < high) 
	{
		int pi = partition(store, low, high);

		quicksort(store, low, pi - 1);
		quicksort(store, pi + 1, high);
	}
}

// Merge Sort
void merge(Store store, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Vetores temporários para manuseio dos valores..
	int L[n1], R[n2]; 

	for (i = 0; i < n1; i++)
		L[i] = store[l + 1].num;
	for (j = 0; j < n2; j++)
		R[j] = store[m + 1 + j].num;

	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			store[k].num = L[i];
			i++;
		} else {
			store[k].num = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) 
    { 
        store[k].num = L[i]; 
        i++; 
        k++; 
    } 

    while (j < n2) 
    { 
        store[k].num = R[j]; 
        j++; 
        k++; 
    } 

}

void mergesort(Store store, int l, int r) {
	if (l < r) {
		int middle = l + (r - l) / 2;
		
		// Recursividade na primeira metade..
		mergesort(store, l, middle);
		// Recursividade na segunda metade..
		mergesort(store, middle + 1, r);
		// Mescla as duas metades do primeiroe segundo passo..
		merge(store, l, middle, r);
	}
}

// Heap Sort