"""
graph = [
    [0, 1, 1, float('inf'), float('inf'), float('inf'), float('inf')],
    [float('inf'), 0, float('inf'), 4, float('inf'), float('inf'), float('inf')],
    [float('inf'), 1, 0, float('inf'), float('inf'), float('inf'), float('inf')],
    [float('inf'), float('inf'), -6, 0, 1, 1, float('inf')],
    [float('inf'), float('inf'), float('inf'), float('inf'), 0, 1, 3],
    [float('inf'), float('inf'), float('inf'), float('inf'), float('inf'), 0, 1],
    [float('inf'), float('inf'), float('inf'), float('inf'), float('inf'), float('inf'), 0]
]
"""
graph = [
    [0, 4, float('inf'), float('inf'), float('inf'), float('inf'), 2],
    [float('inf'), -1, 3, float('inf'), float('inf'), float('inf'), float('inf')],
    [float('inf'), float('inf'), 0, 3, 1, float('inf'), float('inf')],
    [float('inf'), float('inf'), float('inf'), 0, float('inf'), -2, float('inf')],
    [float('inf'), float('inf'), float('inf'), float('inf'), 0, 2, float('inf')],
    [float('inf'), float('inf'), float('inf'), float('inf'), float('inf'), 0, float('inf')],
    [float('inf'), float('inf'), float('inf'), float('inf'), 2, float('inf'), 0]
]

n = len(graph)
dp = [[0 for i in range(n)] for j in range(n)]
next = [[0 for i in range(n)] for j in range(n)]


def floydWarshall(m):
    """
    Foloseste programarea dinamica pentru a gasi o matrice de drumuri cele mai scurte catre fiecare nod,
    generand aceasta matrice pentru a avea toate posibilitatile de a ajunge dintr-un nod in altul.

    Apoi reconstruiesc drumul cu matricea Next.
    """
    for i in range(n):
        for j in range(n):
            dp[i][j] = m[i][j]
            if m[i][j] != float('inf'):
                next[i][j] = j

    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dp[i][k] + dp[k][j] < dp[i][j]:
                    dp[i][j] = dp[i][k] + dp[k][j]
                    next[i][j] = next[i][k]

    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dp[i][k] + dp[k][j] < dp[i][j]:
                    dp[i][j] = float('-inf')
                    next[i][j] = -1


def reconstructPath(start, end):
    path = []
    if dp[start][end] == float('inf'):
        return path

    at = start
    while at != end:
        if at == -1:
            return None
        path.append(at)
        at = next[at][end]

    if next[at][end] == -1:
        return None
    path.append(end)
    return path


floydWarshall(graph)
print(reconstructPath(1, 5))



