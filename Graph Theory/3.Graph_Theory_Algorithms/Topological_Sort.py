# A0 B1 C2 D3 E4 F5 G6 H7 I8 J9 K10 L11 M12
g = [
    [3],
    [3],
    [0, 1],
    [6, 7],
    [0, 3, 5],
    [9, 10],
    [8],
    [8, 9],
    [11],
    [11, 12],
    [9],
    [],
    []
]

noduri = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M"]


def topSort(graph):
    """
    Sortarea topologica returneaza o ordonare a nodurilor in asa fel incat niciun nod din lista nu are muchie catre
    un nod care e inaintea lui in lista. TopSort merge doar pe grafuri aciclice orientate (DAG - directed acyclic graph)

    Practic iau mai intai datele, n nr de noduri, v lista de vizitati, ordering e lista finala ordonata topologic,
    si i e indicele la care trebuie adaugat nodul in lista ordering.

    Apoi incep cu oricare nod din graf si, daca nu e vizitat, apelez dfs pe el, iar in dfs prima data cand ajunge
    jos de tot adauga nodul in capatul listei ordering si cand se intoarce recursia, practic dfs returneaza indicele
    la care trebuie adaugat nodul in ordering, de fiecare data i-1.

    Dfs parcurge toti vecinii nevizitati(obvious).

    Rezultatul dat pe graful de mai sus e corect, l-am verificat pe foaie.
    """
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
        if not v[edge]:
            i = dfs(i, edge, v, ordering, graph)

    ordering[i] = at
    return i-1


lista = topSort(g)
print(lista)
for nod in lista:
    print(noduri[nod], end=" ")

