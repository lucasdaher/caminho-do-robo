#include "robo.h"

Caminho *iniciarCaminho(int N)
{
  Caminho *novo_caminho = (Caminho *)malloc(sizeof(Caminho));
  if (novo_caminho == NULL)
  {
    perror("Nao foi possivel alocar memoria para este caminho.\n");
    exit(EXIT_FAILURE);
  }

  novo_caminho->Origem = (Ponto *)malloc(sizeof(Ponto));
  if (novo_caminho->Origem == NULL)
  {
    perror("Nao foi possivel alocar memoria para o ponto de origem.\n");
    free(novo_caminho);
    exit(EXIT_FAILURE);
  }

  novo_caminho->Origem->X = 0;
  novo_caminho->Origem->Y = 0;
  novo_caminho->Origem->Proximo = NULL;
  novo_caminho->N = N;
  novo_caminho->Distancia = 0;

  return novo_caminho;
}

Ponto Final(Caminho *C)
{
  Ponto pontoFinal;
  pontoFinal.X = 0;
  pontoFinal.Y = 0;

  if (C == NULL || C->N < 0)
  {
    pontoFinal.X = -1;
    pontoFinal.Y = -1;
    return pontoFinal;
  }

  Ponto *atual = C->Origem;
  int distanciaPasso = 1, direcao = 0;

  for (int i = 0; i < C->N; i++)
  {
    for (int j = 0; j < distanciaPasso; j++)
    {
      switch (direcao)
      {
      case 0:
        pontoFinal.X++;
        break;
      case 1:
        pontoFinal.Y++;
        break;
      case 2:
        pontoFinal.X--;
        break;
      case 3:
        pontoFinal.Y--;
        break;
      }

      if (j == distanciaPasso - 1)
      {
        Ponto *novoPonto = (Ponto *)malloc(sizeof(Ponto));
        if (novoPonto == NULL)
        {
          perror("Erro ao alocar memoria para um novo ponto.\n");
          exit(EXIT_FAILURE);
        }
        novoPonto->X = pontoFinal.X;
        novoPonto->Y = pontoFinal.Y;
        novoPonto->Proximo = NULL;
        atual->Proximo = novoPonto;
        atual = novoPonto;
      }

      C->Distancia++;
    }

    direcao = (direcao + 1) % 4;
    if (i % 2 == 1)
    {
      distanciaPasso++;
    }
  }

  return pontoFinal;
}

int Distancia(Caminho *C)
{
  if (C == NULL)
  {
    return 0;
  }
  return C->Distancia;
}

int main()
{
  int N;

  printf("Digite o numero de ciclos: \n");
  scanf("%d", &N);

  Caminho *caminhoRobo = iniciarCaminho(N);

  Ponto pontoFinal = Final(caminhoRobo);
  int distanciaTotal = Distancia(caminhoRobo);

  if (pontoFinal.X == -1 && pontoFinal.Y == -1)
  {
    printf("Ponto final: NULL\n");
    printf("Distancia total percorrida: %d\n", distanciaTotal);
  }
  else
  {
    printf("Ponto final: (%d, %d)\n", pontoFinal.X, pontoFinal.Y);
    printf("Distancia total percorrida: %d\n", distanciaTotal);

    Ponto *atual = caminhoRobo->Origem;
    while (atual != NULL)
    {
      printf("(%d, %d) -> ", atual->X, atual->Y);
      atual = atual->Proximo;
    }
    printf("NULL\n");
  }

  Ponto *atual = caminhoRobo->Origem;
  while (atual != NULL)
  {
    Ponto *temp = atual;
    atual = atual->Proximo;
    free(temp);
  }

  free(caminhoRobo);

  return 0;
}