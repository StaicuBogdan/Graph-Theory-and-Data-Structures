# A0 B1 C2 D3 E4 F5 G6 H7

g = [
    [(1, 3), (2, 6)],
    [(2, 4), (3, 4), (4, 11)],
    [(3, 8), (6, 11)],
    [(4, -4), (5, 5), (6, 2)],
    [(7, 9)],
    [(7, 1)],
    [(7, 2)],
    []
]


def topSort(graph):
    n = len(graph)
    v = [False for i in range(n)]
    ordering = [0 for i in range(n)]
    i = n-1

    for at in range(n):
        if not v[at]:
            i = dfs(i, at, v, ordering, graph)

    return ordering


def dfs(i, at, v, ordering, graph):
    v[at] = True

    for edge in graph[at]:
        if not v[edge[0]]:
            i = dfs(i, edge[0], v, ordering, graph)

    ordering[i] = at
    return i-1


print(topSort(g))


def dagShortestPath(graph):
    """
    Fac sortarea topologica si iau primul element din sortare si ii setez costul la zero, apoi parcurg nodurile din graf
    in ordinea din sortarea topologica.

    Pentru fiecare vecin al nodului din graf calculez distanta ca <distanta pana la nod + distanta de la nod la vecin>
    Daca vecinul avea distanta None, o pun direct in lista dist, daca nu, o compar mai intai cu distanta pe care o avea
    si pun minimul, apoi returnez lista de distante.
    """
    topsort = topSort(graph)
    dist = [None for i in range(len(graph))]
    dist[topsort[0]] = 0

    for i in range(len(graph)):
        # nod este nodul din graf
        nod = topsort[i]

        for edge in graph[nod]:
            newDist = dist[nod] + edge[1]
            if dist[edge[0]] is None:
                dist[edge[0]] = newDist
            else:
                dist[edge[0]] = min(dist[edge[0]], newDist)

    return dist


print(dagShortestPath(g))

