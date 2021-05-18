

class TreeNode:
    def __init__(self, id, parent, children):
        self.id = id
        self.parent = parent
        self.children = children


def rootTree(g, rootId):
    root = TreeNode(rootId, None, [])
    return buildTree(g, root, None)


def buildTree(g, node, parent):
    for childId in g[node.id]:
        if parent is not None and childId == parent.id:
            continue
        child = TreeNode(childId, node, [])
        node.children.append(child)
        buildTree(g, child, node)
    return node


def treeCenters(g):
    n = len(g)
    degree = [0 for i in range(n)]
    leaves= []
    for i in range(n):
        degree[i] = len(g[i])
        if degree[i] == 0 or degree[i] == 1:
            leaves.append(i)
            degree[i] = 0
    count = len(leaves)
    while count < n:
        new_leaves = []
        for node in leaves:
            for neighbour in g[node]:
                degree[neighbour] -= 1
                if degree[neighbour] == 1:
                    new_leaves.append(neighbour)
            degree[node] = 0
        count += len(new_leaves)
        leaves = new_leaves.copy()
    return leaves


def treesAreIsomorphic(tree1, tree2):
    tree1_centers = treeCenters(tree1)
    tree2_centers = treeCenters(tree2)

    tree1_rooted = rootTree(tree1, tree1_centers[0])
    tree1_encoded = encode(tree1_rooted)

    for center in tree2_centers:
        tree2_rooted = rootTree(tree2, center)
        tree2_encoded = encode(tree2_rooted) 

        if tree1_encoded == tree2_encoded:
            return True
        return False


def encode(node):
    if node is None:
        return

    labels = []
    for child in node.children:
        labels.append(encode(child))

    labels.sort()

    result = ""
    for label in labels:
        result += label

    return "(" + result + ")"


###################################################
# graful e salvat ca lista de adiacenta


m = [
    [1],
    [0, 3, 4],
    [3],
    [1, 2, 6, 7],
    [1, 5, 8],
    [4],
    [3, 9],
    [3],
    [4],
    [6]
]


t1 = [
    [1],
    [0, 2, 4],
    [1],
    [4, 5],
    [1, 3],
    [3]
]

t2 = [
    [1],
    [0, 2],
    [1, 4],
    [4],
    [2, 3, 5],
    [4]
]


centers = treeCenters(m)
print(centers)
print(treesAreIsomorphic(t1, t2))