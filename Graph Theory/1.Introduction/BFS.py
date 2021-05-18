

class Graph:  # graful problemei
    def __init__(self, matrice, noduri, start, scop):
        self.matrice = matrice
        self.noduri = noduri
        self.start = start
        self.scop = scop
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
start = "a"
scop = "f"
graph = Graph(m, noduri, start, scop)


def bfs(gr):
    # doua functii, prima face BFS si gaseste lista de tati pana la nodul cautat
    prev = solve(gr, gr.noduri.index(gr.start))

    # a doua functie reconstruieste drumul
    return reconstructPath(gr, prev)


def solve(gr, s):
    q = [s]

    gr.visited[s] = True
    prev = [None for i in range(len(gr.noduri))]
    while q:
        nodCurent = q.pop(0)
        vecini = gr.genereazaSuccesori(nodCurent)

        for v in range(len(vecini)):
            if not gr.visited[vecini[v]]:
                q.append(vecini[v])
                gr.visited[vecini[v]] = True
                prev[vecini[v]] = nodCurent
    return prev


def reconstructPath(gr, prev):
    path = []
    nod = gr.noduri.index(gr.scop)

    while nod is not None:
        path.insert(0, gr.noduri[nod])
        nod = prev[nod]

    if path[0] == gr.start:
        return path

    return []


lista = bfs(graph)

print(lista)

