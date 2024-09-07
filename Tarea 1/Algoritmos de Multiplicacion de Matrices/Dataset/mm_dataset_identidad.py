import numpy as np

def generate_identity_matrix(size):
    return np.eye(size, dtype=int)

def save_matrices_to_file(mat1, mat2, filename):
    with open(filename, 'w') as f:
        f.write(f"{mat1.shape[0]} {mat1.shape[1]}\n")
        for row in mat1:
            f.write(' '.join(map(str, row)) + '\n')
        f.write(f"{mat2.shape[0]} {mat2.shape[1]}\n")
        for row in mat2:
            f.write(' '.join(map(str, row)) + '\n')

if __name__ == "__main__":
    size1 = int(input("Ingrese el tamaño de la primera matriz identidad: "))
    size2 = int(input("Ingrese el tamaño de la segunda matriz identidad: "))
    mat1 = generate_identity_matrix(size1)
    mat2 = generate_identity_matrix(size2)
    save_matrices_to_file(mat1, mat2, "dataset.txt")
