
SECTOR_SIZE = 512

# Identificação dos setores
setores = {
    10: "gcdbinario",
    11: "fatorial",
    12: "fibonacci",
    13: "mmc",
    14: "media",
    15: "potencia",
    16: "inverter",
    17: "maxvetor",
    18: "buscabinbinario",
    19: "buscabinbinario",
    20: "sort",
    21: "sort"
}


def visualizar_setor(arquivo, numero_setor):

    arquivo.seek(numero_setor * SECTOR_SIZE)
    setor = arquivo.read(SECTOR_SIZE)

    print("===================================")
    print(f"          SETOR {numero_setor}")
    print("===================================")

    if len(setor) != SECTOR_SIZE:
        print("Setor não encontrado ou incompleto!")
        return

    nome = setores.get(numero_setor, "Reservado")
    print(f"Programa: {nome}")
    print()

    for endereco in range(0, SECTOR_SIZE, 16):

        dados = setor[endereco:endereco + 16]

        hexadecimal = " ".join(
            f"{byte:02X}" for byte in dados
        )

        print(f"{endereco:04X}: {hexadecimal}")

    print()


with open("programa.img", "rb") as arquivo:

    tamanho = arquivo.seek(0, 2)
    total_setores = tamanho // SECTOR_SIZE

    print(f"Tamanho da imagem: {tamanho} bytes")
    print(f"Total de setores: {total_setores}")

    for numero in range(total_setores):
        visualizar_setor(arquivo, numero)
