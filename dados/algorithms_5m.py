import matplotlib.pyplot as plt
import numpy as np

# Valores de RSSI e distâncias medidas pelos algoritmos fornecidos
rssi_values = [-66, -64, -65, -67, -69, -65, -63, -65, -63, -63]
distances_algorithm_1_1m = [2.363197, 2.106202, 2.231002, 2.503226, 2.808665, 2.231002, 1.988383, 2.231002, 1.988383, 1.988383]
#distances_algorithm_2_1m = [18.837881, 16.316076, 17.576979, 20.098783, 22.620588, 17.576979, 15.055174, 17.576979, 15.055174, 15.055174]

# Índices para as amostras
indices = range(len(rssi_values))

# Calcular as médias dos algoritmos
mean_algorithm_1 = [np.mean(distances_algorithm_1_1m)] * len(indices)
mean_algorithm_2 = [np.mean(distances_algorithm_2_1m)] * len(indices)

# Line Plot
plt.figure(figsize=(10, 6))
plt.plot(indices, distances_algorithm_1_1m, marker='o', color='blue', label='Algoritmo 1', linestyle='-')
plt.plot(indices, distances_algorithm_2_1m, marker='x', color='red', label='Algoritmo 2', linestyle='--')
plt.plot(indices, mean_algorithm_1, color='blue', linestyle='-', label='Média Algoritmo 1')
plt.plot(indices, mean_algorithm_2, color='red', linestyle='-', label='Média Algoritmo 2')
plt.xlabel('RSSI (dBm)')
plt.ylabel('Distância medida (m)')
plt.title('Line Plot das Distâncias Medidas pelos Algoritmos para 1 Metro')
plt.legend()
plt.grid(True)
plt.xticks(indices, rssi_values)
plt.show()
