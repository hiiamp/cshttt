import numpy as np
from mylib import MaxtrixFactorization


with open('input.txt', 'r') as f:
    line = f.readline()
    user, item = [int(x) for x in line.split()]
    k = int(f.readline())
    data = np.array([float(x) for x in f.readline().split()])
    for i in range(user-1):
        data = np.vstack([data, [float(x) for x in f.readline().split()]])
    f.close()
myMF = MaxtrixFactorization.MaxtrixFactorization(user=user, item=item, data=data, k=k)
W, H, bu, bi, xm = myMF.excute()
print(bu)
print(np.dot(W, H))