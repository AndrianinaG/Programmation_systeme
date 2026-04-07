import os

pid = os.fork()

if pid == 0:
    print("je suis le fils")
else:
    print("je suis le père")