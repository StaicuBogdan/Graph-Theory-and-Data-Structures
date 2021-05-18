
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
outEdgeCount = 0

# in listele astea indicele i reprezinta nodul i
low = [0 for i in range(len(graph))]
ids = [0 for i in range(len(graph))]
visited = [False for i in range(len(graph))]
isArt = [False for i in range(len(graph))]


def findArticulationPoints():
    global outEdgeCount
    for i in range(len(graph)):
        if not visited[i]:
            outEdgeCount = 0
            dfs(i, i, -1)
            isArt[i] = (outEdgeCount > 1)
    return isArt


def dfs(root, at, parent):
    global outEdgeCount, id
    if parent == root:
        outEdgeCount += 1
    visited[at] = True
    id += 1
    low[at] = id
    ids[at] = id

    for to in graph[at]:
        if to == parent:
            continue
        if not visited[to]:
            dfs(root, to, at)
            low[at] = min(low[at], low[to])
            # Articulation point found via bridge
            if ids[at] < low[to]:
                isArt[at] = True
            # Articulation point found via cycle
            if ids[at] == low[to]:
                isArt[at] = True
        else:
            low[at] = min(low[at], ids[to])


print(findArticulationPoints())









