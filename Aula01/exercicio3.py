import matplotlib.pyplot as plt
import numpy as np

# Definição dos valores de n
n = np.arange(1, 5, dtype=int)

# Cálculo das complexidades
complexidade_A = n ** 5
complexidade_B = 2 ** n

# Criação do gráfico
plt.figure(figsize=(8, 5))
plt.plot(n, complexidade_A, marker='o', linestyle='-', label='Algoritmo A (O(n^5))')
plt.plot(n, complexidade_B, marker='s', linestyle='--', label='Algoritmo B (O(2^n))')

# Personalização do gráfico
plt.xlabel('Tamanho do problema (n)')
plt.ylabel('Complexidade')
plt.title('Comparação de Complexidades')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)

# Salvar e exibir
plt.savefig('complexidades.png', dpi=300)
plt.show()
