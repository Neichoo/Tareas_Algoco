import numpy as np
def generate_diagonal_matrix(size):
    matrix = np.zeros((size, size), dtype=int)
    np.fill_diagonal(matrix, np.random.randint(1, 1000, size=size))
    return matrix

def save_matrices_to_file(mat1, mat2, filename):
    with open(filename, 'w') as f:
        f.write(f"{mat1.shape[0]} {mat1.shape[1]}\n")
        for row in mat1:
            f.write(' '.join(map(str, row)) + '\n')
        f.write(f"{mat2.shape[0]} {mat2.shape[1]}\n")
        for row in mat2:
            f.write(' '.join(map(str, row)) + '\n')

if __name__ == "__main__":
    size1 = int(input("Ingrese el tamaño de la primera matriz diagonal: "))
    size2 = int(input("Ingrese el tamaño de la segunda matriz diagonal: "))
    mat1 = generate_diagonal_matrix(size1)
    mat2 = generate_diagonal_matrix(size2)
    save_matrices_to_file(mat1, mat2, "dataset.txt")
