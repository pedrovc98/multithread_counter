#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define n_threads 4
int p = 0; /* Variável para guardar a quantidade identificada de números primos */

int digit(char a){ /* função que converte digito (em char) para int */
  int b = a - '0';
  if(b >=0 && b<=9) {
    return b;
  }
  else{
    return -1;
  } 
}

int prime(int a){ /*função que verifica se um número é primo */
  int b = a/2;
  int i = 2;
  int flag = 0;

  if(b < 2) flag = 1;
  else{
    for(i=2; i<=b && flag == 0; i++){
      if(a%i==0) flag = 1; /*número não é primo */
    }

    if(flag == 1) return 0; /* Não primo */
    else return 1; /* Primo */
    }
}

void* funcao_thread(void *arg) {
  int* N = (int*)arg;

  printf("Estou na thread %d!\n", *N);
  for (unsigned int i=0; i<5000000; i++);
  printf("Saindo da thread %d!\n", *N);
  return NULL;
}

int main() {

  char str[100];
  unsigned long int numbers[100];
  unsigned long int n = 0;
  int i, j = 0;
  int counter = 0;
  pthread_t threads[n_threads];
  int thread_args[n_threads];
 
/* Passo 1: Ler a string */ 
  fgets(str, sizeof(str), stdin);

/* Passo 2: Extrair valores da string */

  for(i=0; str[i]!='\n'; i++){
    if(digit(str[i])!=-1){ /*Adiciona digitos */
      n = n*10 + digit(str[i]);
      /* printf("Adicionei dígito\n"); */
    }
    if(digit(str[i])!=-1 && digit(str[i+1])==-1){
      numbers[j] = n; /*guarda o numero encontrado */
      /* printf("Guardei número: %d\n", n); */
      j++;
      n = 0;
    }
  }

/* Neste ponto, a variável j é a quantidade de 
        números armazenados */
/* Os valores a serem verificados estão no vetor numbers[] */
/* 
  for(i=0; i<j; i++){
    printf("%d\n", numbers[i]);
  } 
*/

/* Passo 3: Verificar se são primos em um máximo de 4 threads simultâneas */

/* --------------------------------------------- */

/* Primeiros testes para criação de threads */

  for (int i = 0; i < (n_threads); i++) {
    thread_args[i] = i;
    pthread_create(&(threads[i]), NULL, funcao_thread, &(thread_args[i]));
  }

/* Esperando threads terminarem! */
  for (int i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
