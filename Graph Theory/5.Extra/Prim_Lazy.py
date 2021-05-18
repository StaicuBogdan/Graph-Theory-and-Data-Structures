from pqdict import PQDict

graph = [
    [(0, 1, 10), (0, 2, 1), (0, 3, 4)],
    [(1, 0, 10), (1, 2, 3), (1, 4, 0)],
    [(2, 0, 1), (2, 1, 3), (2, 3, 2), (2, 5, 8)],
    [(3, 0, 4), (3, 2, 2), (3, 5, 2), (3, 6, 7)],
    [(4, 1, 0), (4, 5, 1), (4, 7, 8)],
    [(5, 2, 8), (5, 3, 2), (5, 4, 1), (5, 6, 6), (5, 7, 9)],
    [(6, 3, 7), (6, 5, 6), (6, 7, 12)],
    [(7, 4, 8), (7, 5, 9), (7, 6, 12)]
]

n = len(graph)
m = n-1
pq = PQDict()
visited = [False] * n


# s e indicele nodului de start
def lazyPrim(s=0):
    global m
    edgeCount, mstCost = 0, 0
    mstEdges = [None] * m

    addEdges(s)

    while len(pq) > 0 and edgeCount != m:
        edge, priority = pq.popitem()
        nodeIndex = edge[1]

        if visited[nodeIndex]:
            continue

        mstEdges[edgeCount] = edge
        edgeCount += 1
        mstCost += edge[2]

        addEdges(nodeIndex)

    if edgeCount != m:
        return None

    return mstCost, mstEdges


def addEdges(nodeIndex):
    # marcam nodul curent ca vizitat
    visited[nodeIndex] = True

    # iterez prin restul muchiilor si le adaug in pq pe cele care nu duc in noduri vizitate
    edges = graph[nodeIndex]
    for edge in edges:
        if not visited[edge[1]]:
            pq.additem(edge, edge[2])


cost, mst = lazyPrim()
print(f"Costul arborelui este {cost}\n")
for edge in mst:
    print(edge)

