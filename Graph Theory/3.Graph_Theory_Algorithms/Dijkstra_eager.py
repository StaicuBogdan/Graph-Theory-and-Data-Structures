from heapq import *
from pqdict import PQDict

# li = []
#
# heapify(li)
# heappush(li, (1, 7))
# heappush(li, (1, 3))
# heappush(li, (3, 2))
# heappush(li, (2, 4))
# print(list(li))
#
# heappush(li, (4, 1))
# print(list(li))
#
# print(heappop(li))
# print(heappop(li))
# print(heappop(li))
# print(heappop(li))
# print(heappop(li))

# pq = PQDict()
#
# pq.additem(5, 8)
# pq.additem(3, 4)
# pq.additem(1, 6)
# pq.additem(2, 1)
# print(pq)
#
# pq[2] = 7
# print(pq)
#
# elem, pr = pq.popitem()
# print(elem, pr)
# print(pq)

graph = [
    [(1, 5), (2, 1)],
    [(2, 2), (3, 3), (4, 20)],
    [(1, 3), (4, 12)],
    [(2, 3), (4, 2), (5, 6)],
    [(5, 1)],
    []
]

"""
    O(E*log(V)) - which is really good

    !!! Toate muchiile trebuie sa aiba cost pozitiv !!!

    Functia dijkstra returneaza o lista de distante minime pana la fiecare nod.
    Varianta implementata aici este direct cea Eager, cu indexed priority queue, adica PQDict.
    
    Pornesc de la nodul de start si calculez costul pentru fiecare nod vecin si le inserez in ipq. Apoi algoritmul
    continua sa calculeze distantele(costurile) nodurilor urmatoare in functie de prioritatea cea mai mare
    (valoarea cea mai mica a prioritatii), ignorand nodurile deja vizitate si retinand si o lista de tati ai nodurilor.
    
    Lista de tati da mereu drumul de cost minim pe care s-a ajuns in acel nod, deoarece modifica mereu tatii atunci
    cand modifica si distantele. 
    
"""


def findShortestPath(g, s, e):
    dist, prev = dijkstra(g, s)
    path = []
    if dist[e] == float('inf'):
        return path
    i = e
    while i is not None:
        path.insert(0, i)
        i = prev[i]
    return path


def dijkstra(g, s):
    vis = [False for i in range(len(g))]
    dist = [float('inf') for i in range(len(g))]
    prev = [None for i in range(len(g))]
    dist[s] = 0

    ipq = PQDict()
    ipq.additem(s, 0)
    while len(ipq) != 0:
        index, minValue = ipq.popitem()
        vis[index] = True
        # mica optimizare, daca deja avem distanda mai buna pe alt drum fata de drumul direct dintre 2 noduri, pass
        if dist[index] < minValue:
            continue
        for edge in g[index]:
            # ia toate nodurile vecine nevizitate
            if vis[edge[0]]:
                continue
            # le calculaeza distanta
            newDist = dist[index] + edge[1]
            # si o modifica doar daca este mai mica decat cea care era deja
            if newDist < dist[edge[0]]:
                dist[edge[0]] = newDist
                # apoi modifica si in indexed priority queue, daca nu e, il adauga, daca e, ii updateaza valoarea
                if ipq.get(edge[0]) is None:
                    ipq.additem(edge[0], newDist)
                else:
                    ipq[edge[0]] = newDist
                # si seteaza si tatal de fiecare data pentru a ramane ultimul adica cel cu costul cel mai mic
                prev[edge[0]] = index
    return dist, prev


celMaiScurtDrum = findShortestPath(graph, 3, 1)
print(celMaiScurtDrum)



























