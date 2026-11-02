# Pseudocode

Keys are IATA codes (strings), compared alphabetically. Each node stores one `Airport` record (`node.data`) and pointers node.left` and `node.right`. 

---

## Build — `buildFromArray(data)`

Inserts the records in the order given and checks the BST property after every insert.

```
buildFromArray(data):
    duplicates = 0
    invalid = 0
    for i = 0 to size(data) - 1:
        if INSERT(data[i]) is false:
            duplicates = duplicates + 1
            print "Duplicate code: " + data[i].iata
        if VALIDATE() is false:
            invalid = invalid + 1         
    print "Validated after each of " + size(data) + " inserts: "
          + ("all valid" if invalid = 0 else "INVALID found")
    return duplicates
```

---

## Insert — `INSERT(a)`

Returns true if the airport was added, false if its code is already in the tree (duplicate).

```
INSERT(a):
    newNode = new Node(a)         
    if root = NULL:               
        root = newNode
        count = count + 1
        return true
    cur = root             
    loop forever:
        if a.iata < cur.data.iata:   
            if cur.left = NULL:
                cur.left = newNode
                count = count + 1
                return true
            cur = cur.left
        else if a.iata > cur.data.iata:  
            if cur.right = NULL:
                cur.right = newNode
                count = count + 1
                return true
            cur = cur.right
        else:                        
            delete newNode
            return false
```

---

## Search — `SEARCH(target)`

Prints the search path (every code compared), the number of comparisons, and the airport if found.

```
SEARCH(target):
    comparisons = 0
    cur = root
    print "find " + target
    print "Path: "
    while cur ≠ NULL:
        comparisons = comparisons + 1
        print cur.data.iata
        if target = cur.data.iata:
            print "Comparisons: " + comparisons
            print "Found: " + cur.data.iata, cur.data.name, cur.data.city, cur.data.country
            return true
        if target < cur.data.iata:
            cur = cur.left
        else:
            cur = cur.right
    print "Comparisons: " + comparisons
    print target + " not found"
    return false                      
```

---

## Delete — `DELETE(key)` and `DELETE_code(r, key)`

`DELETE_code` removes `key` from the subtree rooted at `r` and returns the new root of that subtree. It handles the three deletion cases: D1 (leaf), D2 (one child), D3 (two children).

```
DELETE(key):
    root = DELETE_code(root, key)
```

```
DELETE_code(r, key):
    if r = NULL:                     
        return NULL
    if key < r.data.iata:                     
        r.left = DELETE_code(r.left, key)
    else if key > r.data.iata:                  
        r.right = DELETE_code(r.right, key)
    else:                                    
        if r.left = NULL:              // D1 leaf / D2 right child only
            child = r.right
            delete r
            count = count - 1
            return child
        if r.right = NULL:                 // D2 left child only
            child = r.left
            delete r
            count = count - 1
            return child
        s = r.right                  // D3 two children:
        while s.left ≠ NULL:             
            s = s.left
        r.data = s.data                      
        r.right = DELETE_code(r.right, r.data.iata) 
    return r
```

---

## Validate — `VALIDATE()` and `validHelper(node, lo, hi)`

Checks the BST property with the range (lo, hi) method: every node's code must lie strictly between the bounds set by its ancestors.

```
VALIDATE():
    return validHelper(root, "", "~")         
```

```
validHelper(node, lo, hi):
    if node = NULL:
        return true                      
    if not (lo < node.data.iata AND node.data.iata < hi):
        return false                       
    return validHelper(node.left,  lo, node.data.iata) 
       AND validHelper(node.right, node.data.iata, hi)   
```

---

## Range — `RANGE(from, to)` and `rangeHelper(node, from, to, visited, found)`

Lists every airport with `from ≤ code ≤ to` in alphabetical order, skipping subtrees that lie outside the range. `visited` and `found` are shared counters (passed by reference).

```
RANGE(from, to):
    visited = 0
    found = 0
    print "range " + from + " " + to
    rangeHelper(root, from, to, visited, found)
    print "Found " + found + " airports, visited " + visited + " nodes"
    return found
```

```
rangeHelper(node, from, to, visited, found):
    if node = NULL:
        return
    visited = visited + 1
    if from < node.data.iata:            
        rangeHelper(node.left, from, to, visited, found)
    if from ≤ node.data.iata AND node.data.iata ≤ to:  
        print node.data.iata, node.data.name, node.data.city, node.data.country
        found = found + 1
    if node.data.iata < to:         
        rangeHelper(node.right, from, to, visited, found)
```

---

## Balanced build — `REBALANCE()`

Collects the airports in sorted order (inorder), frees the old nodes, and rebuilds the tree with the middle element of each range as the root.

```
REBALANCE():
    v = empty list
    collectInorder(root, v)            
    destroy(root)                      
    root = buildBalanced(v, 0, size(v) - 1)       
    count = size(v)
    print "Rebalanced " + count + " airports"
```

```
collectInorder(node, v):
    if node = NULL:
        return
    collectInorder(node.left, v)
    append node.data to v
    collectInorder(node.right, v)
```

```
destroy(node):
    if node = NULL:
        return
    destroy(node.left)
    destroy(node.right)
    delete node
```

```
buildBalanced(v, lo, hi):
    if lo > hi:
        return NULL
    mid = lo + (hi - lo) / 2          
    n = new Node(v[mid])
    n.left  = buildBalanced(v, lo, mid - 1)    
    n.right = buildBalanced(v, mid + 1, hi)    
    return n
```
