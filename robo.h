#ifndef ROBO_H
#define ROBO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Ponto
{
  int X;
  int Y;
  struct Ponto *Proximo;
} Ponto;

typedef struct Caminho
{
  Ponto *Origem;
  int N;
  int Distancia;
} Caminho;

Caminho *iniciarCaminho(int N);
Ponto Final(Caminho *C);
int Distancia(Caminho *C);

#endif