cantidad = int(input("Introduce la cantidad de elementos: "))
numeros = list(range(cantidad))
with open("dataset.txt", "w") as archivo:
    archivo.write(f"{cantidad}\n")
    archivo.write(" ".join(map(str, numeros)) + "\n")