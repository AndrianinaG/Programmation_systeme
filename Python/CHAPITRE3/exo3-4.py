import os
import shutil

source = os.getcwd()
nom_source = os.path.basename(source.rstrip(os.sep)) or "racine"

while True:
    rep = input().strip()

    if rep.lower() in {"q", "quit", "exit"}:
        break

    if rep and os.path.isdir(rep):
        destination = os.path.join(rep, nom_source)
        shutil.copytree(source, destination, dirs_exist_ok=True)