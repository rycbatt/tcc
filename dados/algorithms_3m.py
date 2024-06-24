import matplotlib.pyplot as plt
import numpy as np

# Valores de RSSI e distâncias medidas pelos algoritmos fornecidos
rssi_values = [-65, -64, -63, -63, -63, -63, -63, -64, -64, -63]
distances_algorithm_1_1m = [2.231002, 2.106202, 1.988383, 1.988383, 1.988383, 1.988383, 1.988383, 2.106202, 2.106202, 1.988383]
#distances_algorithm_2_1m = [17.576979, 16.316076, 15.055174, 15.055174, 15.055174, 15.055174, 15.055174, 16.316076, 16.316076, 15.055174]

# Índices para as amostras
indices = range(len(rssi_values))

# Calcular as médias dos algoritmos
mean_algorithm_1 = [np.mean(distances_algorithm_1_1m)] * len(indices)
mean_algorithm_2 = [np.mean(distances_algorithm_2_1m)] * len(indices)
real_distance = 3
distance_lines = [real_distance] * len(indices)

# Line Plot
plt.figure(figsize=(10, 6))
plt.plot(indices, distances_algorithm_1_1m, marker='o', color='blue', label='Algoritmo 1', linestyle='-')
plt.plot(indices, distances_algorithm_2_1m, marker='x', color='red', label='Algoritmo 2', linestyle='--')
#plt.plot(indices, mean_algorithm_1, color='blue', linestyle='-', label='Média Algoritmo 1')
#plt.plot(indices, mean_algorithm_2, color='red', linestyle='-', label='Média Algoritmo 2')
plt.plot(indices, distance_lines, color='black', linestyle='-', linewidth='2', label='Distancia Real')

plt.xlabel('RSSI (dBm)')
plt.ylabel('Distância medida (m)')
plt.title(f'Distâncias Medidas pelos Algoritmos 1 e 2 para {real_distance}m')
plt.legend()
plt.grid(True)
plt.xticks(indices, rssi_values)
plt.show()
