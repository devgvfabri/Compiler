with open("codigoBinario.txt", "r") as arquivo:
    linhas = [
        linha.strip()
        for linha in arquivo
        if linha.strip()
    ]

with open("programa.img", "rb") as arquivo:
    dados = arquivo.read()

erro = False

for i, bits in enumerate(linhas):

    esperado = int(bits, 2).to_bytes(4, "big")

    inicio = i * 4
    recebido = dados[inicio:inicio + 4]

    if esperado != recebido:

        print(f"ERRO na instrução {i}")
        print(f"Esperado : {esperado.hex(' ').upper()}")
        print(f"Recebido : {recebido.hex(' ').upper()}")

        erro = True
        break

if not erro:
    print("===================================")
    print("      VERIFICAÇÃO OK")
    print("===================================")
    print(f"{len(linhas)} instruções verificadas.")