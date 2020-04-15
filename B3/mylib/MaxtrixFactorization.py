import numpy as np


class MaxtrixFactorization:

    def __init__(self, user, item, data, k):
        self.user = user
        self.item = item
        self.data = data
        self.k = k
        self.W = np.random.rand(user, k)
        self.Ht = np.random.rand(k, item)

    def excute(self, b = 0.02, stop = 500, ld = 0.01):
        while stop > 0:
            stop -= 1
            for u in range(self.user):
                for i in range(self.item):
                    if self.data[u][i] > 0:
                        Rp = 0
                        for j in range(self.k):
                            Rp += np.dot(self.W[u][j], self.Ht[j][i])
                        sub_RR = self.data[u][i] - Rp
                        for j in range(self.k):
                            self.W[u][j] += 2*b*sub_RR*self.Ht[j][i] - ld*self.W[u][j]
                            self.Ht[j][i] += 2*b*sub_RR*self.W[u][j] - ld*self.Ht[j][i]
        print(self.data)
        return self.W, self.Ht