import matplotlib.pyplot as plt
import numpy as np

casos = ['Caso 1', 'Caso 2', 'Caso 3', 'Caso 4', 'Caso 5', 'Caso 6', 'Caso 7', 'Caso 8', 'Caso 9', 'Caso 10', 'Caso 11', 'Caso 12', 'Caso 13']
fuerza_bruta = [0.4324, 0.3884, 0.4093, 0.4506, 0.7715, 0.3748, 0.3317, 0.4653, 0.6449, 0.4115, 0.3521, 113.5680, 215.6670]
programacion_dinamica = [0.3125, 0.3790, 0.4083, 0.4376, 0.3904, 0.3494, 0.3242, 0.3343, 0.3145, 0.3332, 0.3311, 1.7319, 0.3069]
plt.figure(figsize=(10, 6))
bar_width = 0.35
index = np.arange(len(casos))
plt.bar(index, fuerza_bruta, bar_width, label='Fuerza Bruta', color='skyblue')
plt.bar(index + bar_width, programacion_dinamica, bar_width, label='Programación Dinámica', color='lightgreen')
plt.xlabel('Casos')
plt.ylabel('Tiempo de Ejecución [ms]')
plt.title('Comparación de Tiempos de Ejecución: Fuerza Bruta vs Programación Dinámica')
plt.xticks(index + bar_width / 2, casos, rotation=45, ha='right')
plt.yscale('log')
plt.legend()
plt.tight_layout()
plt.show()
