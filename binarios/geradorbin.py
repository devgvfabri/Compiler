
SECTOR_SIZE = 512
INSTRUCTION_SIZE = 4
INSTRUCTIONS_PER_SECTOR = SECTOR_SIZE // INSTRUCTION_SIZE

# Tabela de programas
programas = {
    "gcdbinario": {
        "arquivo": "gcdbinario.txt",
        "inicio": 10,
        "fim": 10,
        "tamanho": 65
    },
    "fatorial": {
        "arquivo": "fatorial.txt",
        "inicio": 11,
        "fim": 11,
        "tamanho": 72
    },
    "fibonacci": {
        "arquivo": "fibonacci.txt",
        "inicio": 12,
        "fim": 12,
        "tamanho": 70
    },
    "mmc": {
        "arquivo": "mmc.txt",
        "inicio": 13,
        "fim": 13,
        "tamanho": 83
    },
    "media": {
        "arquivo": "media.txt",
        "inicio": 14,
        "fim": 14,
        "tamanho": 95
    },
    "potencia": {
        "arquivo": "potencia.txt",
        "inicio": 15,
        "fim": 15,
        "tamanho": 65
    },
    "inverter": {
        "arquivo": "inverter.txt",
        "inicio": 16,
        "fim": 16,
        "tamanho": 124
    },
    "maxvetor": {
        "arquivo": "maxvetor.txt",
        "inicio": 17,
        "fim": 17,
        "tamanho": 104
    },
    "buscabinbinario": {
        "arquivo": "buscabinbinario.txt",
        "inicio": 18,
        "fim": 19,
        "tamanho": 146
    },
    "sort": {
        "arquivo": "sort.txt",
        "inicio": 20,
        "fim": 21,
        "tamanho": 200
    }
}


def carregar_programa(nome_arquivo):
    programa = bytearray()

    with open(nome_arquivo, "r") as arquivo:
        linhas = arquivo.readlines()

    quantidade = 0

    for linha in linhas:
        bits = linha.strip()

        if not bits:
            continue

        if len(bits) != 32:
            raise ValueError(
                f"{nome_arquivo}: instrução com {len(bits)} bits"
            )

        if any(bit not in "01" for bit in bits):
            raise ValueError(
                f"{nome_arquivo}: instrução inválida: {bits}"
            )

        valor = int(bits, 2)

        # Mantém a representação big-endian
        programa.extend(valor.to_bytes(4, byteorder="big"))

        quantidade += 1

    return programa, quantidade


def gerar_imagem():
    # Maior setor final utilizado
    ultimo_setor = max(
        p["fim"] for p in programas.values()
    )

    # Inicializa todos os setores com zeros.
    imagem = bytearray(
        (ultimo_setor + 1) * SECTOR_SIZE
    )

    print("===================================")
    print("       GERANDO IMAGEM SD")
    print("===================================")

    for nome, dados in programas.items():

        arquivo = dados["arquivo"]
        setor_inicio = dados["inicio"]
        setor_final = dados["fim"]
        tamanho_esperado = dados["tamanho"]

        programa, quantidade = carregar_programa(arquivo)

        # Confere quantidade de instruções
        if quantidade != tamanho_esperado:
            raise ValueError(
                f"{nome}: esperadas {tamanho_esperado} "
                f"instruções, encontradas {quantidade}"
            )

        # Calcula capacidade dos setores reservados
        capacidade = (
            setor_final - setor_inicio + 1
        ) * SECTOR_SIZE

        if len(programa) > capacidade:
            raise ValueError(
                f"{nome}: excedeu a capacidade dos setores"
            )

        # Calcula posição inicial dentro da imagem
        inicio_bytes = setor_inicio * SECTOR_SIZE

        # Copia o programa para a posição correspondente
        imagem[
            inicio_bytes:inicio_bytes + len(programa)
        ] = programa

        print(
            f"{nome:20} | "
            f"Setores {setor_inicio}-{setor_final} | "
            f"{quantidade} instruções"
        )

    # Salva imagem final
    with open("programa.img", "wb") as arquivo:
        arquivo.write(imagem)

    print("===================================")
    print("IMAGEM GERADA COM SUCESSO")
    print("===================================")
    print(f"Tamanho: {len(imagem)} bytes")
    print(f"Total de setores: {len(imagem) // SECTOR_SIZE}")
    print("Arquivo: programa.img")


if __name__ == "__main__":
    gerar_imagem()
