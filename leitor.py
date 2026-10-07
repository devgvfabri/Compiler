SECTOR_SIZE = 512
INSTRUCTION_SIZE = 4

arquivo_nome = "teste.img"

with open(arquivo_nome, "rb") as arquivo:
    dados = arquivo.read()

print("===================================")
print("       LEITURA DO PROGRAMA")
print("===================================")

print(f"Tamanho do arquivo: {len(dados)} bytes")
print(f"Setores: {len(dados) // SECTOR_SIZE}")
print()

# Verifica se o tamanho é múltiplo de 4
if len(dados) % INSTRUCTION_SIZE != 0:
    print("ERRO: tamanho não é múltiplo de 4.")
    exit()

numero_instrucoes = len(dados) // INSTRUCTION_SIZE

print(f"Quantidade de palavras de 32 bits: {numero_instrucoes}")
print()

for i in range(128):

    inicio = i * INSTRUCTION_SIZE
    fim = inicio + INSTRUCTION_SIZE

    # Pega 4 bytes
    instrucao_bytes = dados[inicio:fim]

    # Converte para inteiro
    valor = int.from_bytes(
        instrucao_bytes,
        byteorder="big"
    )

    # Converte para binário de 32 bits
    bits = format(valor, "032b")

    # Mostra apenas instruções diferentes de zero
    if valor != 0:

        print(
            f"Instrução {i:3d}: "
            f"{bits}    "
            f"{valor:08X}"
        )

print()
print("===================================")
print("             FIM")
print("===================================")