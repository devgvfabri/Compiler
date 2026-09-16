SECTOR_SIZE = 512
INSTRUCTION_SIZE = 4

# Lê as instruções
with open("codigoBinario.txt", "r") as arquivo:
    linhas = arquivo.readlines()

programa = bytearray()

numero_instrucao = 0

for linha in linhas:

    bits = linha.strip()

    # Ignora linhas vazias
    if not bits:
        continue

    # Verifica se realmente temos 32 bits
    if len(bits) != 32:
        raise ValueError(
            f"Instrução {numero_instrucao} possui {len(bits)} bits: {bits}"
        )

    # Verifica se só existem 0 e 1
    if any(bit not in "01" for bit in bits):
        raise ValueError(
            f"Instrução {numero_instrucao} inválida: {bits}"
        )

    # Converte binário para inteiro
    valor = int(bits, 2)

    # Converte para 4 bytes, big-endian
    bytes_instrucao = valor.to_bytes(4, byteorder="big")

    programa.extend(bytes_instrucao)

    numero_instrucao += 1


# Completa o último setor com zeros
tamanho_original = len(programa)

resto = tamanho_original % SECTOR_SIZE

if resto != 0:
    programa.extend(
        b'\x00' * (SECTOR_SIZE - resto)
    )


# Cria a imagem
with open("programa.img", "wb") as arquivo:
    arquivo.write(programa)


print("===================================")
print("       IMAGEM GERADA")
print("===================================")
print(f"Instruções : {numero_instrucao}")
print(f"Tamanho original : {tamanho_original} bytes")
print(f"Tamanho da imagem : {len(programa)} bytes")
print(f"Setores : {len(programa) // SECTOR_SIZE}")
print("Arquivo : programa.img")