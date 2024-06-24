import matplotlib.pyplot as plt
import numpy as np

# Valores de RSSI e distâncias medidas pelos algoritmos fornecidos
rssi_values = [-67, -64, -65, -65, -65, -64, -64, -65, -63, -64]
distances_algorithm_1_1m = [2.503226, 2.106202, 2.231002, 2.231002, 2.231002, 2.106202, 2.106202, 2.231002, 1.988383, 2.106202]
#distances_algorithm_2_1m = [20.098783, 16.316076, 17.576979, 17.576979, 17.576979, 16.316076, 16.316076, 17.576979, 15.055174, 16.316076]

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
