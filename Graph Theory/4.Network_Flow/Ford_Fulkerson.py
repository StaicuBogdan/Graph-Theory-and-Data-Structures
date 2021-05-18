"""
Eficienta lui Ford Fulkerson depinde de felul in care determinam path-urile catre nodul final, avand astfel, cu un dfs
complexitate de O(fE) unde f e flow-ul maxim.

Ppate fi imbunatatit cu Edmonds-Karp, care e practic la fel doar ca foloseste BFS in loc de DFS.
Si mai sunt si alte metode dar nu le mai fac eu acum.


Asta nu stiu daca mai continui, e de la William Fiset, dar e putin ciudat codul

class Edge:
    def __init__(self, fr, to, capacity):
        self.fr = fr
        self.to = to
        self.capacity = capacity
        self.flow = 0
        self.residual = None

    def isReidual(self):
        return self.capacity == 0

    def remainingCapacity(self):
        return self.capacity - self.flow

    def augment(self, bottleneck):
        self.flow += bottleneck
        self.residual.flow -= bottleneck

    def toString(self, s, t):
        # u = "s" if s == self.fr else ("t" if t == self.fr else self.fr)
        return f"Edge {self.fr} -> {self.to} | flow = {self.flow} | capacity = {self.capacity} | is residual = {self.isReidual()}\n"


class Graph:
    def __init__(self, nodes, s, t):
        self.s = s
        self.t = t
        self.visitedToken = 1
        self.visited = [0 for i in range(nodes)]
        self.graph = [[] for i in range(nodes)]

    def addEdge(self, fr, to, capacity):
        e1 = Edge(fr, to, capacity)
        e2 = Edge(to, fr, 0)
        e1.residual = e2
        e2.residual = e1
        self.graph[fr].append(e1)
        self.graph[to].append(e2)

"""


class Graph:

    def __init__(self, graph):
        self.graph = graph  # residual graph
        self.ROW = len(graph)
        # self.COL = len(gr[0])

    '''Returns true if there is a path from source 's' to sink 't' in
    residual graph. Also fills parent[] to store the path '''

    def DFS(self, s, t, parent, visited):

        # Mark all the vertices as not visited
        # Mark the source node as visited and enqueue it
        visited[s] = True

        # Get all adjacent vertices of the dequeued vertex u
        # If a adjacent has not been visited, then mark it
        for ind, val in enumerate(self.graph[s]):
            if visited[ind] is False and val > 0:
                visited[ind] = True
                parent[ind] = s
                self.DFS(ind, t, parent, visited)

        return True if visited[t] else False

    # Returns tne maximum flow from s to t in the given graph
    def FordFulkerson(self, source, sink):
        # This array is filled by BFS and to store path
        parent = [-1] * self.ROW
        visited = [False] * self.ROW
        max_flow = 0  # There is no flow initially

        # Augment the flow while there is path from source to sink
        while self.DFS(source, sink, parent, visited):

            # Find minimum residual capacity of the edges along the
            # path filled by BFS. Or we can say find the maximum flow
            # through the path found.
            path_flow = float("Inf")
            s = sink
            while s != source:
                path_flow = min(path_flow, self.graph[parent[s]][s])
                s = parent[s]

            # Add path flow to overall flow
            max_flow += path_flow

            # update residual capacities of the edges and reverse edges
            # along the path
            v = sink
            while v != source:
                u = parent[v]
                self.graph[u][v] -= path_flow
                self.graph[v][u] += path_flow
                v = parent[v]

            visited = [False] * self.ROW

        return max_flow


# Create a graph given in the above diagram

graph = [[0, 16, 13, 0, 0, 0],
         [0, 0, 10, 12, 0, 0],
         [0, 4, 0, 0, 14, 0],
         [0, 0, 9, 0, 0, 20],
         [0, 0, 0, 7, 0, 4],
         [0, 0, 0, 0, 0, 0]]

g = Graph(graph)

source = 0
sink = 5

print("The maximum possible flow is %d " % g.FordFulkerson(source, sink))

