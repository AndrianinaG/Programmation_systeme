import subprocess

nom_fichier = input()
subprocess.run(["/usr/bin/emacs", nom_fichier])