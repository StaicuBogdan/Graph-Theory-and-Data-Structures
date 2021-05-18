

class Graph:  # graful problemei
    def __init__(self, matrice, noduri):
        self.matrice = matrice
        self.noduri = noduri
        self.count = 0
        self.components = [0 for i in range(len(m))]
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
    [0, 1, 0, 0, 1, 0, 0, 0, 0, 0],
    [1, 0, 1, 0, 0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 1],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
]

n = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]
graph = Graph(m, n)


def findComponents(gr):
    for i in range(len(gr.matrice)):
        if not gr.visited[i]:
            gr.count += 1
            dfs(gr, i)
    return gr.count, gr.components


def dfs(gr, i):
    gr.visited[i] = True
    gr.components[i] = gr.count
    vecini = gr.genereazaSuccesori(i)
    for v in range(len(vecini)):
        if not gr.visited[vecini[v]]:
            dfs(gr, vecini[v])


k, lista_componente = findComponents(graph)

print(k)
print(lista_componente)

for i in range(1,max(lista_componente)+1):
    print(f"Grupa numarul {i}:", end=" ")
    for j in range(len(lista_componente)):
        if lista_componente[j] == i:
            print(graph.noduri[j], end=" ")
    print()


