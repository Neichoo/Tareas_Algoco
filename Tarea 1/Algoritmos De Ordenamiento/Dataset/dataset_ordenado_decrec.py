cantidad = int(input("Introduce la cantidad de elementos: "))
numeros = list(range(cantidad - 1, -1, -1))
with open("dataset.txt", "w") as archivo:
    archivo.write(f"{cantidad}\n")
    archivo.write(" ".join(map(str, numeros)) + "\n")
