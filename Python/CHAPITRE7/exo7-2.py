n = int(input("Entrer la taille du tableau : "))
tab = []
for i in range(n):
    val = int(input(f"tab[{i}] = "))
    tab.append(val)
for i in range(n):
    print(f"tab[{i}] = {tab[i]}")

indice = int(input("Entrer l'indice du tableau a afficher : "))
answer = False

while not answer:
    if 0 <= indice < n:
        print(f"tab[{indice}] = {tab[indice]}")
        answer = True
        break
    else:
        indice=int(input(f"Indice invalide. Veuillez entrer un indice entre 0 et {n-1} : "))
        answer = False