
SECTOR_SIZE = 512

with open("programa.img", "rb") as arquivo:
    setor0 = arquivo.read(SECTOR_SIZE)
    setor1 = arquivo.read(SECTOR_SIZE)

for numero, setor in enumerate([setor0, setor1]):
    print("===================================")
    print(f"       SETOR {numero}")
    print("===================================")

    if len(setor) == 0:
        print("Setor não encontrado!")
        continue

    for endereco in range(0, len(setor), 16):
        dados = setor[endereco:endereco + 16]

        hexadecimal = " ".join(
            f"{byte:02X}" for byte in dados
        )

        print(f"{endereco:04X}: {hexadecimal}")

    print()
