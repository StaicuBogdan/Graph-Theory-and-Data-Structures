

class Graph:  # graful problemei
    def __init__(self, matrice, noduri):
        self.matrice = matrice
        self.noduri = noduri
        self.visited = [False for i in range(len(m))]

    # va genera succesorii nodului in functie de indice
    def genereazaSuccesori(self, indice):
        listaSuccesori = []
        for i in range(len(self.matrice)):
            if self.matrice[indice][i] == 1:
                listaSuccesori.append(i)
        return listaSuccesori

    def __repr__(self):
        sir = ""
        for (k, v) in self.__dict__.items():
            sir += "{} = {}\n".format(k, v)
        return sir


##############################################################################################
#                                 Initializare problema                                      #
##############################################################################################

m = [
    [0, 1, 0, 1, 1, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 1, 0, 1, 0, 0],
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 1, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 1, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
]

noduri = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]
graph = Graph(m, noduri)


def dfs(gr, i):
    if gr.visited[i]:
        return
    gr.visited[i] = True
    print(gr.noduri[i])

    vecini = gr.genereazaSuccesori(i)
    for v in range(len(vecini)):
        dfs(gr, vecini[v])


dfs(graph, 0)

