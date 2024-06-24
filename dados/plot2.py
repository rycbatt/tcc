import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

plt.rcParams.update({
    'font.size': 14,         # Tamanho da fonte geral
    'axes.titlesize': 18,    # Tamanho da fonte do título dos eixos
    'axes.labelsize': 16,    # Tamanho da fonte dos rótulos dos eixos
    'xtick.labelsize': 14,   # Tamanho da fonte dos rótulos do eixo x
    'ytick.labelsize': 14,   # Tamanho da fonte dos rótulos do eixo y
    'legend.fontsize': 14    # Tamanho da fonte da legenda
})

# Dados de RSSI para diferentes distâncias

rssi_values_1m = [-45, -45, -44, -45, -44, -45, -42, -45, -45, -45]
rssi_values_2m = [-48, -48, -49, -48, -48, -48, -48, -48, -48, -47] 
rssi_values_3m = [-55, -53, -55, -53, -54, -55, -55, -55, -54, -54]
rssi_values_4m = [-55, -54, -54, -55, -54, -54, -54, -54, -54, -54] 
rssi_values_5m = [-61, -70, -66, -66, -68, -73, -67, -66, -67, -66] 

#rssi_values_1m = [-51, -50, -50, -51, -51, -51, -51, -50, -50, -51]
#rssi_values_2m = [-56, -57, -56, -57, -56, -56, -56, -56, -57, -56]
#rssi_values_3m = [-65, -64, -63, -63, -63, -63, -63, -64, -64, -63]
#rssi_values_4m = [-67, -64, -65, -65, -65, -64, -64, -65, -63, -64]
#rssi_values_5m = [-66, -64, -65, -67, -69, -65, -63, -65, -63, -63]

# Combine all RSSI values with corresponding distance labels
rssi_combined = pd.DataFrame({
    'RSSI': rssi_values_1m + rssi_values_2m + rssi_values_3m + rssi_values_4m + rssi_values_5m,
    'Distance': ['1m'] * len(rssi_values_1m) + ['2m'] * len(rssi_values_2m) + ['3m'] * len(rssi_values_3m) + ['4m'] * len(rssi_values_4m) + ['5m'] * len(rssi_values_5m)
})

# Generate the boxplot
plt.figure(figsize=(12, 6))
sns.boxplot(x='Distance', y='RSSI', data=rssi_combined, palette="Set2")
plt.ylabel('RSSI (dBm)')
plt.xlabel('Distância')
plt.grid(True)
plt.show()
