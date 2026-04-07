import os
import sys
import shutil

r = sys.argv[1]

source = os.getcwd()
nom = os.path.basename(source)
destination = os.path.join(r, nom)

shutil.copytree(source, destination, dirs_exist_ok=True)