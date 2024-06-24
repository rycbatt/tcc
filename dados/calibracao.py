import matplotlib.pyplot as plt


# Valores de RSSI de calibração
rssi_valores = [-51, -51, -51, -51, -50, -51, -50, -50, -52, -52, -52, -53, -52, -52, -53, -51, 
                -52, -51, -51, -51, -51, -51, -51, -50, -50, -50, -51, -51, -51, -51, -51, 
                -52, -51, -52, -52, -51, -51, -52, -51, -50, -51, -52, -50, -51, -50, -50, 
                -50, -51, -51, -50]

# Número de amostras
amostras = list(range(1, len(rssi_valores) + 1))

plt.figure(figsize=(8, 5))  # Aumentar a largura para 15 polegadas e altura para 5 polegadas

# Ajustar os ticks dos eixos
plt.xticks(range(0, len(amostras) + 1, 10))
plt.yticks(range(min(rssi_valores), max(rssi_valores)+1, 1))

# Criar o gráfico de linhas conectando os pontos
plt.plot(amostras, rssi_valores, marker='o', linestyle='-', color='blue', label='RSSI')

# Adicionar título e rótulos aos eixos
plt.title('RSSI para diferentes amostras')
plt.xlabel('Índice')
plt.ylabel('RSSI (dBm)')

# Adicionar uma grade ao gráfico
plt.grid(True)

# Adicionar uma legenda
plt.legend()

# Mostrar o gráfico
plt.show()

