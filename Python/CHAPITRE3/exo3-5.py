import subprocess
import os

answer = True

while answer:
    nom = input().strip()

    if nom.lower() in {"q", "quit", "exit"}:
        answer = False
    else:
        pid = os.fork()
        if pid == 0:
            if nom:
                subprocess.run(["/usr/bin/vim", nom])
            os._exit(0)
        else:
            os.wait()

    if not answer:
        break

    print("Voulez-vous continuer ? (y/n)")
    reponse = input().strip().lower()

    if reponse in {"y", "yes"}:
        answer = True
    elif reponse in {"n", "no"}:
        answer = False
    else:
        print("Réponse non reconnue, arrêt du programme.")
        answer = False