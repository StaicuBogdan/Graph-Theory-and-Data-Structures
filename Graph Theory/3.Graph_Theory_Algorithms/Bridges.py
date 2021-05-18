
graph = [
    [1, 2],
    [0, 2],
    [0, 1, 3, 5],
    [2, 4],
    [3],
    [2, 6, 8],
    [5, 7],
    [6, 8],
    [5, 7]
]


id = 0

# in listele astea indicele i reprezinta nodul i
low = [0 for i in range(len(graph))]
ids = [0 for i in range(len(graph))]
visited = [False for i in range(len(graph))]


def findBridges():
    bridges = []
    # For-ul e doar pentru cazul in care avem deja un graj cu mai multe componente conexe
    for i in range(len(graph)):
        if not visited[i]:
            dfs(i, -1, bridges)
    return bridges


def dfs(at, parent, bridges):
    global id
    visited[at] = True
    id += 1
    low[at] = id
    ids[at] = id

    for to in graph[at]:
        if to == parent:
            continue
        if not visited[to]:
            dfs(to, at, bridges)
            low[at] = min(low[at], low[to])
            # Articulation point found via bridge
            if ids[at] < low[to]:
                bridges.append([at, to])
        else:
            low[at] = min(low[at], ids[to])


print(findBridges())









