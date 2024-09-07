import numpy as np

def generate_binary_matrix(rows, cols):
    return np.random.randint(0, 2, size=(rows, cols))

def save_matrices_to_file(mat1, mat2, filename):
    with open(filename, 'w') as f:
        f.write(f"{mat1.shape[0]} {mat1.shape[1]}\n")
        for row in mat1:
            f.write(' '.join(map(str, row)) + '\n')
        f.write(f"{mat2.shape[0]} {mat2.shape[1]}\n")
        for row in mat2:
            f.write(' '.join(map(str, row)) + '\n')

if __name__ == "__main__":
    rows1 = int(input("Ingrese el número de filas de la primera matriz: "))
    cols1 = int(input("Ingrese el número de columnas de la primera matriz: "))
    rows2 = int(input("Ingrese el número de filas de la segunda matriz: "))
    cols2 = int(input("Ingrese el número de columnas de la segunda matriz: "))
    mat1 = generate_binary_matrix(rows1, cols1)
    mat2 = generate_binary_matrix(rows2, cols2)
    save_matrices_to_file(mat1, mat2, "dataset.txt")

