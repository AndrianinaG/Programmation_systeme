import os
import signal
import time
import sys

def calcul_infini():
    compteur = 0
    resultat = 0
    while True:
        compteur += 1
        resultat += compteur * compteur
        if compteur % 500_000 == 0:
            print(f"[Fils] compteur={compteur} | résultat={resultat}")
        time.sleep(0.0001)

def main():
    pid = os.fork()

    if pid == 0:
        calcul_infini()
        sys.exit(0)

    # Père
    etat = "actif"
    print(f"Fils créé (PID={pid})")
    print("s=endormir | r=réveiller | q=quitter\n")

    while True:
        choix = input(f"[{etat}] choix : ").strip().lower()

        if choix == 's':
            if etat == "actif":
                os.kill(pid, signal.SIGSTOP)
                etat = "endormi"
                print("Fils endormi.\n")
            else:
                print("Fils déjà endormi.\n")

        elif choix == 'r':
            if etat == "endormi":
                os.kill(pid, signal.SIGCONT)
                etat = "actif"
                print("Fils réveillé.\n")
            else:
                print("Fils déjà actif.\n")

        elif choix == 'q':
            if etat == "endormi":
                os.kill(pid, signal.SIGCONT)
            os.kill(pid, signal.SIGTERM)
            os.waitpid(pid, 0)
            print("Fils tué. Au revoir !")
            sys.exit(0)

        else:
            print("Choix invalide (s / r / q)\n")

if __name__ == "__main__":
    main()