"""
Practic, fac DFS si imi da o parcurgere a grafului, dar aceea nu e si Eulerian Path, deoarece nu parcurge toate muchiile
ci doar toate nodurile. Asa ca atunci cand se intoarce recursia, la fiecare nod verific daca mai are muchii nevizitate,
adica daca numarul din lista out este diferit de zero si apelez dfs si pt muchiile acelea, apoi inserez nodul in
capul listei de solutie, astfel cand se termina recursia, va fi returnat un Eulerian Path complet.

Complexitate O(E), toate computatiile sunt liniare in functie de nr de muchii. tot. calcularea gradelor in/out, recursia

"""

graph = [
    [],
    [2, 3],
    [2, 4, 4],
    [1, 2, 5],
    [3, 6],
    [6],
    [3]
]

l_in = [0 for i in range(len(graph))]
l_out = [0 for i in range(len(graph))]

m = sum([len(i) for i in graph]) # numarul de muchii ale grafului

path = []


def findEulerianPath():
    countInOutDegrees()
    if not graphHasEulerianPath():
        return

    dfs(findStartNode())

    # returnam path doar daca am vizitat toate muchiile. Poate graful nu e conex, deci nu avem eulerian path deloc
    if len(path) == m+1:
        return path
    return


def countInOutDegrees():
    for i in range(len(graph)):
        for j in graph[i]:
            l_out[i] += 1
            l_in[j] += 1


def graphHasEulerianPath():
    start_nodes = end_nodes = 0
    for i in range(len(graph)):
        if l_out[i] - l_in[i] > 1 or l_in[i] - l_out[i] > 1:
            return False
        elif l_out[i] - l_in[i] == 1:
            start_nodes += 1
        elif l_in[i] - l_out[i] == 1:
            end_nodes += 1
    # ambele sunt 0 => eulerian circuit (care e si path), sau sunt 1 ambele , deci avem un path
    return (end_nodes == 0 and start_nodes == 0) or (end_nodes == 1 and start_nodes == 1)


def findStartNode():
    start = 0
    for i in range(len(graph)):
        # cand avem nod de start unic
        if l_out[i] - l_in[i] == 1:
            return i

        # daca nu avem nod unic de start, incepem de la primul nod care are vreo muchie outgoing
        # de asemenea, previne dfs-ul de la a incepe dintr-un nod singleton
        if l_out[i] > 0:
            start = i
    return start


def dfs(at):
    # cat timp inca mai sunt muchii out din nodul ala
    while l_out[at] != 0:
        l_out[at] -= 1
        dfs(graph[at][l_out[at]])
    path.insert(0, at)


print(findEulerianPath())

