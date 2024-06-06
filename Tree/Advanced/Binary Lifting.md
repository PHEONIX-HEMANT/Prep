# Binary Lifting
Binary Lifting is a powerful technique used on trees to efficiently answer queries related to ancestors of nodes. Imagine you have a tree and you want to quickly find the k-th ancestor of a given node. Binary Lifting allows you to do this in logarithmic time (O(log k)) after some pre-processing.

## How it Works

1. Preprocessing:

    - For each node, create a table up[node][i] that stores the 2^i-th ancestor of that node.
    - This table is filled iteratively. For example, up[node][0] is the direct parent of the node, up[node][1] is the grandparent, up[node][2] is the great-grandparent, and so on.

2. Querying:

    - To find the k-th ancestor of a node, decompose k into its binary representation.
    - Starting from the node, iteratively "jump" up the tree using the precomputed up table. For each '1' bit in the binary representation of k, move to the corresponding ancestor.

Example:
Let's say you want to find the 7th ancestor of node 'x' (7 in binary is 111).

1. Jump to the 2^0-th ancestor (1st ancestor) of 'x' using up[x][0].
2. Jump to the 2^1-th ancestor (2nd ancestor) of the current node using up[current_node][1].
3. Jump to the 2^2-th ancestor (4th ancestor) of the current node using up[current_node][2].
You have now reached the 7th ancestor of node 'x'.

```
c++
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOGN = 20; // Adjust based on tree size

vector<int> adj[MAXN];
int up[MAXN][LOGN];

void dfs(int node, int parent) {
    up[node][0] = parent;

    for (int i = 1; i < LOGN; i++) {
        up[node][i] = up[up[node][i - 1]][i - 1]; //using 2^(i-1)th level ancestor
    }

    for (int child : adj[node]) {
        if (child != parent) {
            dfs(child, node);
        }
    }
}

int kthAncestor(int node, int k) {
    for (int i = 0; i < LOGN; i++) {
        if (k & (1 << i)) {
            node = up[node][i];
        }
    }
    return node;
}

int main() {
    // Build the tree (add edges to the 'adj' list)
    // ...

    // Preprocess for binary lifting
    dfs(1, 0); // Assuming the root of the tree is node 1

    // Example query: Find the 7th ancestor of node 5
    int node = 5;
    int k = 7;
    int ancestor = kthAncestor(node, k);
    cout << "The " << k << "-th ancestor of node " << node << " is: " << ancestor << endl;

    return 0;
}

```

## Applications
- Finding the Lowest Common Ancestor (LCA) of two nodes in a tree.
- Answering queries about the path between two nodes (e.g., sum of values on the path).
- Solving problems related to rooted trees and ancestor relationships.
