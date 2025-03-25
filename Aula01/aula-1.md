## Estrutura Avançada de Dados - Aula 1  
### Aluno: Klaus Becker  

## Exercício 1  

Diga qual a classe de complexidade Big-Oh para o algoritmo abaixo, assumindo 
que é uma matriz quadrada.

```c++
public static int somar(int[][] a) {
    int soma = 0;
    for (int i = 0; i < a.length; i++) {
    for (int j = 0; j < a[i].length; j++) {
        soma += a[i][j];
    }
    }
    return soma;
}
```
### Resposta

O código em questão trata-se de um algoritmo de ordem O(n^2), pois ele percorre a matriz a, que é uma matriz quadrada, com dois laços aninhados, um para percorrer as linhas e outro para percorrer as colunas. 

## Exercício 2

Diga qual a classe de complexidade Big-Oh para o algoritmo abaixo, assumindo 
que é uma matriz quadrada.

```c++
public static void imprimir(int[][] a) {
	int i = 0;
	while (i < a.length) {
		int j = 0;
		while (j < a[i].length; j++) {
			System.out.print(a[i][j] + " ");
			j++;
		}
		System.out.println();
		i++;
	}
}
```
### Resposta

Assim como no exercício anterior, o código em questão trata-se de um algoritmo de ordem O(n^2), pois ele percorre a matriz a, que é uma matriz quadrada, com dois laços aninhados, um para percorrer as linhas e outro para percorrer as colunas, sendo que nesse caso, o algoritmo imprime os elementos da matriz, entretanto, a complexidade do algoritmo não é alterada visto que trata-se de instruções com tempo constante.

## Exercício 3

Dois algoritmos *A* e *B* possuem complexidade *O(n^5)* e *O(2^n)*, respectivamente. 
Você utilizaria o algoritmo *B* ao invés do *A* em qual caso? Desenvolva um gráfico com análise dos dois algoritmos e justifique a sua resposta.

### Resposta

Abaixo pode ser observado o gráfico com a análise dos dois algoritmos. 

![Gráfico](../complexidades.png)

A partir do gráfico podemos observar que o algoritmo *B* é mais eficiente que o algoritmo *A* para todos os valores de *n*. Portanto, o algoritmo *B* seria utilizado ao invés do algoritmo *A* em todos os casos.
