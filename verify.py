with open("programa.img", "rb") as f:
    original = f.read(512)

with open("leitura.img", "rb") as f:
    lido = f.read(512)

if original == lido:
    print("VERIFICACAO OK!")
    print("O setor 0 do cartão é exatamente igual ao programa.img.")
else:
    print("ERRO!")
    
    for i in range(512):
        if original[i] != lido[i]:
            print(f"Primeiro erro no byte: {i}")
            print(f"Esperado: {original[i]:02X}")
            print(f"Lido:     {lido[i]:02X}")
            break