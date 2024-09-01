import random
cantidad_numeros = int(input("Ingresa la cantidad de números: "))
numeros = [str(random.randint(0, cantidad_numeros)) for i in range(cantidad_numeros)]
with open('dataset.txt', 'w') as file:
    file.write(f"{cantidad_numeros}\n")
    file.write(' '.join(numeros) + '\n')
