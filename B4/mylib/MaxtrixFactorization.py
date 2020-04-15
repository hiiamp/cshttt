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
        xm = 0
        sl = self.user*self.item
        for u in range(self.user):
            for i in range(self.item):
                if self.data[u][i] > 0:
                    xm += self.data[u][i]
                else:
                    sl -= 1
        xm = xm/(self.user*self.item)
        print(xm)
        bu = np.zeros((self.user))
        bi = np.zeros((self.item))
        sl = self.user
        for u in range(self.user):
            temp = 0
            for i in range(self.item):
                if self.data[u][i] > 0:
                    temp += self.data[u][i] - xm
                else:
                    sl -= 1
            sl = max(sl, 1)
            bu[u] = temp/sl
        sl = self.item
        for i in range(self.item):
            temp = 0
            for u in range(self.user):
                if self.data[u][i] > 0:
                    temp += self.data[u][i] - xm
                else:
                    sl -= 1
            sl = max(sl, 1)
            bi[i] = temp/sl
        while stop > 0:
            stop -= 1
            for u in range(self.user):
                for i in range(self.item):
                    if self.data[u][i] > 0:
                        Rp = 0
                        for j in range(self.k):
                            Rp += np.dot(self.W[u][j], self.Ht[j][i])
                        sub_RR = self.data[u][i] - Rp
                        bu[u] += b*(sub_RR - ld*bu[u])
                        bi[i] += b*(sub_RR - ld*bi[i])
                        xm += b*sub_RR
                        for j in range(self.k):
                            self.W[u][j] += 2*b*sub_RR*self.Ht[j][i] - ld*self.W[u][j]
                            self.Ht[j][i] += 2*b*sub_RR*self.W[u][j] - ld*self.Ht[j][i]
        print(self.data)
        return self.W, self.Ht, bu, bi, xm