
SECTOR_SIZE = 512
NUM_SECTORS = 2

with open("programa.img", "rb") as f:
    original = f.read()

with open("teste.img", "rb") as f:
    lido = f.read()

for setor in range(NUM_SECTORS):
    inicio = setor * SECTOR_SIZE
    fim = inicio + SECTOR_SIZE

    original_setor = original[inicio:fim]
    lido_setor = lido[inicio:fim]

    print("===================================")
    print(f"       VERIFICANDO SETOR {setor}")
    print("===================================")

    if original_setor == lido_setor:
        print(f"VERIFICACAO OK! Setor {setor} identico.")
    else:
        print(f"ERRO! Setor {setor} diferente.")

        if len(original_setor) != len(lido_setor):
            print(f"Tamanho esperado: {len(original_setor)} bytes")
            print(f"Tamanho lido:     {len(lido_setor)} bytes")

        limite = min(len(original_setor), len(lido_setor))

        for i in range(limite):
            if original_setor[i] != lido_setor[i]:
                print(f"Primeiro erro no byte do setor: {i}")
                print(f"Offset absoluto na imagem: {inicio + i}")
                print(f"Esperado: {original_setor[i]:02X}")
                print(f"Lido:     {lido_setor[i]:02X}")
                break

    print()

# Verifica se os arquivos têm o tamanho esperado
if len(original) != NUM_SECTORS * SECTOR_SIZE:
    print(f"ATENCAO: programa.img possui {len(original)} bytes.")

if len(lido) != NUM_SECTORS * SECTOR_SIZE:
    print(f"ATENCAO: teste.img possui {len(lido)} bytes.")
