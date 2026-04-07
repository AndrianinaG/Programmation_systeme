import os

pid1 = os.fork()

if pid1 == 0:
    print("je suis le fils 1", flush=True)
else:
    pid2 = os.fork()

    if pid2 == 0:
        print("je suis le fils 2", flush=True)
    else:
        print("je suis le père", flush=True)
        os.waitpid(pid1, 0)
        os.waitpid(pid2, 0)