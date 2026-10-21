
SECTOR_SIZE = 512
INSTRUCTION_SIZE = 4
INSTRUCTIONS_PER_SECTOR = SECTOR_SIZE // INSTRUCTION_SIZE


def carregar_programa(nome_arquivo):
    programa = bytearray()

    with open(nome_arquivo, "r") as arquivo:
        linhas = arquivo.readlines()

    numero_instrucao = 0

    for linha in linhas:
        bits = linha.strip()

        if not bits:
            continue

        if len(bits) != 32:
            raise ValueError(
                f"{nome_arquivo}: instrução {numero_instrucao} "
                f"possui {len(bits)} bits: {bits}"
            )

        if any(bit not in "01" for bit in bits):
            raise ValueError(
                f"{nome_arquivo}: instrução inválida: {bits}"
            )

        if numero_instrucao >= INSTRUCTIONS_PER_SECTOR:
            raise ValueError(
                f"{nome_arquivo} excede o limite de "
                f"{INSTRUCTIONS_PER_SECTOR} instruções por setor."
            )

        valor = int(bits, 2)
        programa.extend(valor.to_bytes(4, byteorder="big"))
        numero_instrucao += 1

    # Completa o setor com zeros até 512 bytes
    programa.extend(b'\x00' * (SECTOR_SIZE - len(programa)))

    return programa, numero_instrucao


# Programa 1: setor 0
programa0, instrucoes0 = carregar_programa("codigoBinario.txt")

# Programa 2: setor 1
programa1, instrucoes1 = carregar_programa("codigoBinario2.txt")

# Junta os dois setores na ordem correta
imagem = programa0 + programa1

# Gera a imagem do cartão SD
with open("programa.img", "wb") as arquivo:
    arquivo.write(imagem)

print("===================================")
print("         IMAGEM GERADA")
print("===================================")
print(f"Setor 0: {instrucoes0} instruções")
print(f"Setor 1: {instrucoes1} instruções")
print(f"Tamanho da imagem: {len(imagem)} bytes")
print(f"Total de setores: {len(imagem) // SECTOR_SIZE}")
print("Arquivo: programa.img")
