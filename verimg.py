with open("programa.img", "rb") as arquivo:
    setor = arquivo.read(512)

print("===================================")
print("       PRIMEIRO SETOR")
print("===================================")

for endereco in range(0, 512, 16):

    dados = setor[endereco:endereco + 16]

    hexadecimal = " ".join(
        f"{byte:02X}" for byte in dados
    )

    print(f"{endereco:04X}: {hexadecimal}")