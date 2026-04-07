import threading
import random

class TypeTableau:
    def __init__(self, taille):
        self.tab = [0] * taille
        self.nb_elements = taille
        self.x = 0

def remplir(tableau, taille):
    tableau.tab = [random.randint(0, 99) for _ in range(taille)]
    tableau.nb_elements = taille
    print("Tableau rempli:", tableau.tab)

def rechercher(tableau, x, resultat):
    resultat[0] = 1 if x in tableau.tab else 0

def main():
    taille = int(input("Taille du tableau: "))
    tableau = TypeTableau(taille)
    
    t1 = threading.Thread(target=remplir, args=(tableau, taille))
    t1.start()
    
    x = int(input("Entrez x: "))
    t1.join()
    
    resultat = [0]
    t2 = threading.Thread(target=rechercher, args=(tableau, x, resultat))
    t2.start()
    t2.join()
    
    if resultat[0] == 1:
        print("x trouvé dans le tableau (1)")
    else:
        print("x non trouvé dans le tableau (0)")

if __name__ == "__main__":
    main()