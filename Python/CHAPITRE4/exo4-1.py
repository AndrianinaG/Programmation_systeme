import os

r, w = os.pipe()

pid = os.fork()

if pid == 0:
    os.close(r)
    print("Entrez un mot à rechercher dans le fichier : ", end="")
    mot = input().strip()
    os.write(w, mot.encode())
    os.close(w)
    os._exit(0)
else:
    os.close(w)
    mot = os.read(r, 1024).decode().strip()
    os.close(r)

    with open("/home/andrianina/fichier.txt", "r") as f:
        contenu = f.read().split()

    if mot in contenu:
        print("Mot trouvé dans le fichier (1)")
    else:
        print("Mot non trouvé dans le fichier (0)")

    os.wait()