import matplotlib.pyplot as plt
import numpy as np

# Valores de RSSI e distâncias medidas pelos algoritmos fornecidos
rssi_values = [-51, -50, -50, -51, -51, -51, -51, -50, -50, -51]
distances_algorithm_1_1m = [0.996552, 0.940806, 0.940806, 0.996552, 0.996552, 0.996552, 0.996552, 0.940806, 0.940806, 0.996552]
#distances_algorithm_2_1m = [0.075656, 1.336558, 1.336558, 0.075656, 0.075656, 0.075656, 0.075656, 1.336558, 1.336558, 0.075656]

# Índices para as amostras
indices = range(len(rssi_values))
real_distance = 1

# Calcular as médias dos algoritmos
mean_algorithm_1 = np.mean(distances_algorithm_1_1m)
#mean_algorithm_2 = np.mean(distances_algorithm_2_1m)

# Line Plot
plt.figure(figsize=(10, 6))
plt.plot(indices, distances_algorithm_1_1m, marker='o', color='blue', label='Algoritmo 1', linestyle='-')
#plt.plot(indices, distances_algorithm_2_1m, marker='x', color='red', label='Algoritmo 2', linestyle='--')
#plt.plot(indices, [mean_algorithm_1]*len(indices), color='blue', linestyle=':', label='Média Algoritmo 1')
#plt.plot(indices, [mean_algorithm_2]*len(indices), color='red', linestyle=':', label='Média Algoritmo 2')
plt.plot(indices, [real_distance]*len(indices), color='black', linestyle='-', linewidth=2, label=f'Distância Real {real_distance}m')
plt.xlabel('RSSI (dBm)')
plt.ylabel('Distância medida (m)')
plt.title(f'Distâncias Medidas pelos Algoritmos 1 e 2 para {real_distance}m')
plt.legend()
plt.grid(True)
plt.xticks(indices, rssi_values)

# Adicionar valores das médias no gráfico (à esquerda)
#plt.text(0, mean_algorithm_1, f'{mean_algorithm_1:.2f} ', color='blue', ha='right')
#plt.text(0, mean_algorithm_2, f'{mean_algorithm_2:.2f} ', color='red', ha='right')

plt.show()
