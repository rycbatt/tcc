import matplotlib.pyplot as plt
import numpy as np

# Valores de RSSI e distâncias medidas pelos algoritmos fornecidos
rssi_values = [-56, -57, -56, -57, -56, -56, -56, -56, -57, -56]
distances_algorithm_1_1m = [1.328923, 1.407667, 1.328923, 1.407667, 1.328923, 1.328923, 1.328923, 1.328923, 1.407667, 1.328923]
#distances_algorithm_2_1m = [6.228857, 7.489759, 6.228857, 7.489759, 6.228857, 6.228857, 6.228857, 6.228857, 7.489759, 6.228857]

# Índices para as amostras
indices = range(len(rssi_values))
real_distance = 2


# Calcular as médias dos algoritmos
mean_algorithm_1 = np.mean(distances_algorithm_1_1m)
mean_algorithm_2 = np.mean(distances_algorithm_2_1m)
distance_lines = [real_distance] * len(indices)



# Line Plot
plt.figure(figsize=(10, 6))
plt.plot(indices, distances_algorithm_1_1m, marker='o', color='blue', label='Algoritmo 1', linestyle='-')
#plt.plot(indices, distances_algorithm_2_1m, marker='x', color='red', label='Algoritmo 2', linestyle='--')
#plt.plot(indices, [mean_algorithm_1]* len(indices), color='blue', linestyle='-', label='Média Algoritmo 1')
#plt.plot(indices, [mean_algorithm_2]* len(indices), color='red', linestyle='-', label='Média Algoritmo 2')
plt.plot(indices, distance_lines, color='black', linestyle='-', linewidth='2', label=f'Distancia Real {real_distance}m')

# Adicionar valores das médias no gráfico (à esquerda)
#plt.text(0, mean_algorithm_1, f'{mean_algorithm_1:.2f} ', color='blue', ha='right')
#plt.text(0, mean_algorithm_2, f'{mean_algorithm_2:.2f} ', color='red', ha='right')

plt.xlabel('RSSI (dBm)')
plt.ylabel('Distância medida (m)')
plt.title(f'Distâncias Medidas pelos Algoritmos 1 e 2 para {real_distance}m')
plt.legend()
plt.grid(True)
plt.xticks(indices, rssi_values)
plt.show()
