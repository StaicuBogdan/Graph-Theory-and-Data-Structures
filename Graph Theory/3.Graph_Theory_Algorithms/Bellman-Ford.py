

class Edge:
    def __init__(self, fr, to, cost):
        self.fr = fr
        self.to = to
        self.cost = cost


def bellmanFord(g, v, start):
    """
    Parcurg toate muchiile din graf de v-1 ori (v = nr de noduri) de doua ori.
    Prima data le parcurg pentru a calcula costurile minime pentru a ajunge in fiecare nod.
    Iar a doua oara le parcurg pentru a vedea care cost se mai modifica. daca se modifica la a doua parcurgere,
    inseamna ca acel nod e intr-un ciclu negativ, sau e afectat de un ciclu negativ din drumul sau.

    Trebuie parcurse de v-1 ori toate muchiile grafului pentru a ne asigura ca se propaga in graf efectul ciclului
    negativ si sa nu pierdem vreun nod care nu a apucat sa isi modifice costul din cauza acestuia.
    """
    dist = [float('inf') for i in range(v)]
    dist[start] = 0

    for i in range(v - 1):
        for edge in g:
            if dist[edge.fr] + edge.cost < dist[edge.to]:
                dist[edge.to] = dist[edge.fr] + edge.cost

    for i in range(v - 1):
        for edge in g:
            if dist[edge.fr] + edge.cost < dist[edge.to]:
                dist[edge.to] = float('-inf')

    return dist


graph = [
    Edge(0, 1, 5),
    Edge(1, 2, 20),
    Edge(1, 5, 30),
    Edge(1, 6, 60),
    Edge(2, 3, 10),
    Edge(2, 4, 75),
    Edge(3, 2, -15),
    Edge(4, 9, 100),
    Edge(5, 4, 25),
    Edge(5, 6, 5),
    Edge(5, 8, 50),
    Edge(6, 7, -50),
    Edge(7, 8, -10),
]


print(bellmanFord(graph, 10, 0))
