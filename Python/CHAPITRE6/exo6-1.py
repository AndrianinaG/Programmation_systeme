import os
import sys

SEUIL = 1_000_000
print(f"Fichiers de plus de  1Mo dans (avec UID associé) : {', '.join(sys.argv[1:])}")
print("------------------------------------------------------------------------------------------------------------------------------------")


for rep in sys.argv[1:]:
    if not os.path.isdir(rep):
        continue

    for nom in os.listdir(rep):
        chemin = os.path.join(rep, nom)

        if os.path.isfile(chemin) and os.path.getsize(chemin) > SEUIL:
            uid = os.stat(chemin).st_uid
            print(chemin, uid)