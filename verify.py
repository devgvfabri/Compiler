
SECTOR_SIZE = 512

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

with open("programa.img", "rb") as f:
    original = f.read()

with open("teste.img", "rb") as f:
    lido = f.read()

# Verifica tamanho dos arquivos
if len(original) % SECTOR_SIZE != 0:
    raise ValueError("programa.img possui tamanho inválido!")

if len(lido) % SECTOR_SIZE != 0:
    raise ValueError("teste.img possui tamanho inválido!")

total_original = len(original) // SECTOR_SIZE
total_lido = len(lido) // SECTOR_SIZE

print("===================================")
print("       VERIFICACAO DO CARTAO SD")
print("===================================")
print(f"Setores originais: {total_original}")
print(f"Setores lidos:     {total_lido}")
print()

setores_ok = 0
setores_erro = 0

total = max(total_original, total_lido)

for setor in range(21):

    inicio = setor * SECTOR_SIZE
    fim = inicio + SECTOR_SIZE

    original_setor = original[inicio:fim]
    lido_setor = lido[inicio:fim]

    nome = setores.get(setor, "Reservado")

    print("===================================")
    print(f"SETOR {setor} - {nome}")
    print("===================================")

    if len(original_setor) != SECTOR_SIZE:
        print("ERRO: setor ausente ou incompleto na imagem original.")
        setores_erro += 1
        continue

    if len(lido_setor) != SECTOR_SIZE:
        print("ERRO: setor ausente ou incompleto na imagem lida.")
        setores_erro += 1
        continue

    if original_setor == lido_setor:
        print(f"VERIFICACAO OK! Setor {setor} identico.")
        setores_ok += 1

    else:
        print(f"ERRO! Setor {setor} diferente.")
        setores_erro += 1

        for i in range(SECTOR_SIZE):

            if original_setor[i] != lido_setor[i]:

                print(f"Primeiro erro no byte do setor: {i}")
                print(f"Offset absoluto na imagem: {inicio + i}")
                print(f"Esperado: {original_setor[i]:02X}")
                print(f"Lido:     {lido_setor[i]:02X}")
                break

    print()

print("===================================")
print("          RESULTADO FINAL")
print("===================================")
print(f"Setores corretos: {setores_ok}")
print(f"Setores com erro: {setores_erro}")
print(f"Total verificado: {total}")

if setores_erro == 0 and total_original == total_lido:
    print("\nIMAGEM DO CARTAO SD VALIDADA!")
else:
    print("\nFALHA NA VALIDACAO DO CARTAO SD!")
