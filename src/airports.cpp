#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <chrono> // timing
#include <random> // random search codes
#include <algorithm>
using namespace std;

// Make AIRPORT class
class Airport
{
public:
    string iata, name, city, country, icao;
    double lat = 0.0, lon = 0.0;
};

// ----------- Make a helper function to split each line into fields
vector<string> splitCsvLine(const string &line)
{
    vector<string> fields;
    string cur;
    bool inQuotes = false;

    for (int i = 0; i < (int)line.size(); i++)
    {
        char c = line[i]; // look at one character
        if (c == '"')
        { // if current character is ", set inQuotes to true (or opposite of what it was before)
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes)
        { // if encounter a , not in quotes save c to fields and clear c
            fields.push_back(cur);
            cur.clear();
        }
        else
        {
            cur += c; // add a character to the current field name (Countr -> Country)
        }
    }
    fields.push_back(cur);
    return fields;
}

// ----------- Function to load in the data and use helper function to split lines into fields
vector<Airport> loadAirports(const string &path, int &skipped)
{
    vector<Airport> airports;
    skipped = 0;

    // check if dataset can be opened
    ifstream file(path);
    if (!file.is_open())
    {
        cerr << "Could not open " << path << "\n";
        return airports;
    }

    // go through each line of dataset and use helper function to extract fields
    string line;
    while (getline(file, line))
    {
        vector<string> f = splitCsvLine(line);
        if (f.size() < 8 || f[4] == "\\N")
        { // if fields <8 in a line or iata code isn't there, skip
            skipped++;
            continue;
        }
        Airport a; // add fields to the class
        a.name = f[1];
        a.city = f[2];
        a.country = f[3];
        a.iata = f[4];
        a.icao = f[5];
        a.lat = stod(f[6]);
        a.lon = stod(f[7]);
        airports.push_back(a);
    }
    return airports;
}

// ----------- Class for the BST
class AirportBST
{
private:
    struct Node
    { // make nodes
        Airport data;
        Node *left;
        Node *right;
        Node(const Airport &a) : data(a), left(nullptr), right(nullptr) {}
    };

    Node *root;
    int count;

    // ---------- helper function for finding height of the tree
    int HEIGHT(Node *node) const
    {
        if (node == nullptr)
        {
            return -1;
        }
        int leftHeight = HEIGHT(node->left);
        int rightHeight = HEIGHT(node->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    Node *DELETE_code(Node *r, const string &key)
    {
        if (r == nullptr) // step 1: not found
            return nullptr;

        if (key < r->data.iata) // step 2: go left
            r->left = DELETE_code(r->left, key);
        else if (key > r->data.iata) // step 3: go right
            r->right = DELETE_code(r->right, key);
        else
        { // step 4: found it
            if (r->left == nullptr)
            { // D1 leaf / D2 right child only
                Node *child = r->right;
                delete r;
                count--;
                return child;
            }
            if (r->right == nullptr)
            { // D2 left child only
                Node *child = r->left;
                delete r;
                count--;
                return child;
            }
            Node *s = r->right;        // D3 two children:
            while (s->left != nullptr) // find inorder successor
                s = s->left;
            r->data = s->data;                              // copy the WHOLE airport
            r->right = DELETE_code(r->right, r->data.iata); // delete the successor
        }
        return r;
    }

    // Inorder list helper function
    void inorderHelper(Node *node, string &prev, int &outOfOrder, int &printed) const
    {
        if (node == nullptr)
            return;

        inorderHelper(node->left, prev, outOfOrder, printed);

        cout << node->data.iata << " - " << node->data.name
             << ", " << node->data.city << ", " << node->data.country << "\n";
        if (printed > 0 && node->data.iata <= prev)
            outOfOrder++;
        prev = node->data.iata;
        printed++;

        inorderHelper(node->right, prev, outOfOrder, printed);
    }

    void preorderHelper(Node *node, ofstream &out) const
    {
        if (node == nullptr)
            return;
        out << node->data.iata << "\n";
        preorderHelper(node->left, out);
        preorderHelper(node->right, out);
    }

    // task 4c - validate bst
    bool validHelper(Node *node, const string &lo, const string &hi) const
    {
        if (node == nullptr)
            return true;
        if (!(lo < node->data.iata && node->data.iata < hi))
            return false;
        return validHelper(node->left, lo, node->data.iata) && validHelper(node->right, node->data.iata, hi);
    }

    // -------- range task 5
    void rangeHelper(Node *node, const string &from, const string &to,
                     int &visited, int &found) const
    {
        if (node == nullptr)
            return;
        visited++;

        if (from < node->data.iata)
            rangeHelper(node->left, from, to, visited, found);

        if (from <= node->data.iata && node->data.iata <= to)
        {
            cout << node->data.iata << " - " << node->data.name
                 << ", " << node->data.city << ", " << node->data.country << "\n";
            found++;
        }

        if (node->data.iata < to)
            rangeHelper(node->right, from, to, visited, found);
    }

    // task 6
    //  put every airport into inorder
    void collectInorder(Node *node, vector<Airport> &v) const
    {
        if (node == nullptr)
            return;
        collectInorder(node->left, v);
        v.push_back(node->data);
        collectInorder(node->right, v);
    }

    // free every node in the subtree
    void destroy(Node *node)
    {
        if (node == nullptr)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    // build a balanced tree
    Node *buildBalanced(const vector<Airport> &v, int lo, int hi)
    {
        if (lo > hi)
            return nullptr;
        int mid = lo + (hi - lo) / 2;
        Node *n = new Node(v[mid]);
        n->left = buildBalanced(v, lo, mid - 1);
        n->right = buildBalanced(v, mid + 1, hi); //
        return n;
    }

public:
    AirportBST() : root(nullptr), count(0) {}

    // --------- Build the tree (Task 1b)
    bool INSERT(const Airport &a)
    {
        Node *newNode = new Node(a); // step 1
        if (root == nullptr)
        { // step 2: empty tree
            root = newNode;
            count++;
            return true;
        }
        Node *cur = root; // step 3
        while (true)
        {
            if (a.iata < cur->data.iata)
            { // step 5: go left
                if (cur->left == nullptr)
                {
                    cur->left = newNode;
                    count++;
                    return true;
                }
                cur = cur->left;
            }
            else if (a.iata > cur->data.iata)
            { // step 8: go right
                if (cur->right == nullptr)
                {
                    cur->right = newNode;
                    count++;
                    return true;
                }
                cur = cur->right;
            }
            else
            { // step 11: duplicate
                delete newNode;
                return false;
            }
        }
    }

    // function that actually builds the tree with INSERT
    int buildFromArray(const vector<Airport> &data)
    {
        int duplicates = 0;
        int invalid = 0;
        for (int i = 0; i < (int)data.size(); i++)
        {
            if (!INSERT(data[i]))
            {
                duplicates++;
                cout << "Duplicate code: " << data[i].iata << "\n";
            }
            if (!VALIDATE())
                invalid++; // check after every insert
        }
        cout << "Validated after each of " << data.size() << " inserts: "
             << (invalid == 0 ? "all valid" : "INVALID found") << "\n";
        return duplicates;
    }

    int size() const { return count; }

    // ---- call on HEIGHT here so that main can see it
    int height() const { return HEIGHT(root); }

    // ------- avergade depth of all nodes
    double AVGDEPTH() const
    {
        if (root == nullptr)
        {
            return 0.0;
        }
        queue<Node *> Q;
        Q.push(root);
        int level = 0;
        long long total = 0;

        while (!Q.empty())
        {
            int k = Q.size(); // number of nodes on current level
            total += (long long)level * k;

            for (int i = 0; i < k; i++)
            { // remove this level's nodes, add their children
                Node *cur = Q.front();
                Q.pop();
                if (cur->left != nullptr)
                    Q.push(cur->left);
                if (cur->right != nullptr)
                    Q.push(cur->right);
            }
            level++;
        }
        return (double)total / count;
    }

    bool SEARCH(const string &target) const
    {
        int comparisons = 0;
        Node *cur = root;
        cout << "find " << target << "\n";
        cout << "Path: ";
        while (cur != nullptr)
        {
            comparisons++;
            cout << cur->data.iata << " ";
            if (target == cur->data.iata)
            {
                cout << "\nComparisons: " << comparisons << "\n";
                cout << "Found: " << cur->data.iata << " - " << cur->data.name
                     << ", " << cur->data.city << ", " << cur->data.country << "\n\n";
                return true;
            }
            if (target < cur->data.iata)
                cur = cur->left;
            else
                cur = cur->right;
        }
        cout << "\nComparisons: " << comparisons << "\n";
        cout << target << " not found\n\n";
        return false; // step 6
    }

    //--- Delete
    void DELETE(const string &key) { root = DELETE_code(root, key); }

    // -----print level order of top 3 levels
    void PRINTTOP3() const
    {
        if (root == nullptr)
        {
            cout << "(empty tree)\n";
            return;
        }
        queue<Node *> Q;
        Q.push(root);
        int level = 0;

        while (!Q.empty() && level < 3)
        {
            int k = Q.size();
            cout << "Level " << level << ": ";

            for (int i = 0; i < k; i++)
            {
                Node *cur = Q.front();
                Q.pop();
                cout << cur->data.iata << " ";
                if (cur->left != nullptr)
                    Q.push(cur->left);
                if (cur->right != nullptr)
                    Q.push(cur->right);
            }
            cout << "\n";
            level++;
        }
    }

    // Inorder LIST
    void LIST() const
    {
        string prev = "";
        int outOfOrder = 0;
        int printed = 0;

        inorderHelper(root, prev, outOfOrder, printed);

        cout << "\nListed " << printed << " airports\n";
        if (outOfOrder == 0)
            cout << "Sorted: yes\n";
        else
            cout << "Sorted: NO (" << outOfOrder << " out of order)\n";
    }

    // -------task 4b - preorder, build tree from preorder, go through level order to check if same as before
    bool SAVE(const string &path) const
    {
        ofstream out(path);
        if (!out.is_open())
        {
            cerr << "Could not open " << path << " for writing\n";
            return false;
        }
        preorderHelper(root, out);
        cout << "Saved " << count << " codes to " << path << " (preorder)\n";
        return true;
    }

    bool LOAD(const string &path)
    {
        ifstream in(path);
        if (!in.is_open())
        {
            cerr << "Could not open " << path << "\n";
            return false;
        }
        string code;
        int loaded = 0;
        while (getline(in, code))
        { // one code per line
            if (code.empty())
                continue;
            Airport a;
            a.iata = code;
            if (INSERT(a))
                loaded++;
        }
        cout << "Loaded " << loaded << " codes from " << path << "\n";
        return true;
    }

    vector<string> LEVELORDER() const
    {
        vector<string> result;
        if (root == nullptr)
            return result;
        queue<Node *> Q;
        Q.push(root);
        while (!Q.empty())
        {
            Node *cur = Q.front();
            Q.pop();
            result.push_back(cur->data.iata);
            if (cur->left != nullptr)
                Q.push(cur->left);
            if (cur->right != nullptr)
                Q.push(cur->right);
        }
        return result;
    }

    // task 4c
    bool VALIDATE() const
    {
        return validHelper(root, "", "~");
    }

    // task 5
    int RANGE(const string &from, const string &to) const
    {
        int visited = 0, found = 0;
        cout << "range " << from << " " << to << "\n";
        rangeHelper(root, from, to, visited, found);
        cout << "Found " << found << " airports, visited " << visited << " nodes\n";
        return found;
    }

    // task 6
    void REBALANCE()
    {
        vector<Airport> v;
        collectInorder(root, v);
        destroy(root);
        root = buildBalanced(v, 0, (int)v.size() - 1);
        count = (int)v.size();
        cout << "Rebalanced " << count << " airports\n";
    }

    // tiny search with no printing for task 6
    bool FIND(const string &target) const
    {
        Node *cur = root;
        while (cur != nullptr)
        {
            if (target == cur->data.iata)
                return true;
            if (target < cur->data.iata)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return false;
    }
};

// task 6 time funcition
double timeSearches(const AirportBST &t, const vector<string> &queries)
{
    int found = 0;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < (int)queries.size(); i++)
        if (t.FIND(queries[i]))
            found++;
    auto end = chrono::high_resolution_clock::now();
    if (found != (int)queries.size())
        cout << "Warning: only " << found << " of " << queries.size() << " found\n";
    return chrono::duration<double, milli>(end - start).count();
}

// this to make an actual session - not just a fixed script output
//  ---------- session mode: run the main algorithms from the terminal ----------
void runSession()
{
    cout << fixed << setprecision(2);

    // build the tree from the data file
    int skipped = 0;
    vector<Airport> airports = loadAirports("data/airports.dat", skipped);
    AirportBST tree;
    int duplicates = tree.buildFromArray(airports);
    cout << "Loaded " << tree.size() << " airports (" << skipped
         << " lines skipped). Duplicates: " << duplicates << "\n";
    cout << "Height: " << tree.height() << "  Average depth: " << tree.AVGDEPTH() << "\n";
    cout << "Commands: find, insert, remove, validate, range, rebalance, list, height, quit\n";

    string cmd, code, code2;
    while (true)
    {
        cout << "> ";
        if (!(cin >> cmd))
            break;

        if (cmd == "quit")
            break;

        else if (cmd == "load") // load FILE
        {
            string file;
            cin >> file;
            tree = AirportBST(); // start from an empty tree

            if (file.size() >= 4 && file.substr(file.size() - 4) == ".dat")
            {
                // the airports data file: build in file order
                int skipped = 0;
                vector<Airport> airports = loadAirports(file, skipped);
                int duplicates = tree.buildFromArray(airports);
                cout << "Loaded " << tree.size() << " airports (" << skipped
                     << " lines skipped: no IATA code). Duplicates: " << duplicates << "\n";
            }
            else
            {
                // a preorder file made by SAVE
                tree.LOAD(file);
            }
            cout << "Height: " << tree.height() << "  Average depth: " << tree.AVGDEPTH() << "\n";
        }
        else if (cmd == "find")
        {
            cin >> code;
            tree.SEARCH(code);
        }
        else if (cmd == "insert")
        {
            cin >> code;
            Airport a;
            a.iata = code;
            a.name = "(added in session)";
            if (tree.INSERT(a))
                cout << "Inserted " << code << "\n";
            else
                cout << code << " already exists (duplicate)\n";
        }
        else if (cmd == "remove")
        {
            cin >> code;
            int before = tree.size();
            tree.DELETE(code);
            if (tree.size() < before)
                cout << "Removed " << code << "\n";
            else
                cout << code << " not found\n";
        }
        else if (cmd == "validate")
        {
            cout << "Valid BST: " << (tree.VALIDATE() ? "yes" : "no") << "\n";
        }
        else if (cmd == "range")
        {
            cin >> code >> code2;
            tree.RANGE(code, code2);
        }
        else if (cmd == "rebalance")
        {
            tree.REBALANCE();
            cout << "Height: " << tree.height() << "  Average depth: " << tree.AVGDEPTH() << "\n";
        }
        else if (cmd == "list")
        {
            tree.LIST();
        }
        else if (cmd == "height")
        {
            cout << "Height: " << tree.height() << "  Average depth: " << tree.AVGDEPTH() << "\n";
        }
        else
            cout << "Unknown command\n";
    }
}

// Main function to do everything
int main(int argc, char *argv[])
{
    // ./AirportProj session  -> type commands
    // ./AirportProj          -> run the fixed test script
    if (argc > 1 && string(argv[1]) == "session")
    {
        runSession();
        return 0;
    }

    cout << "\n===== Task 1b&c =====\n";
    // Read out the load-in (report size and skipped lines)
    int skipped = 0; // counter starts at 0
    vector<Airport> airports = loadAirports("data/airports.dat", skipped);
    cout << airports.size() << " loaded, " << skipped << " skipped\n";

    // build the tree for real
    AirportBST tree;
    int duplicates = tree.buildFromArray(airports);

    std::cout << "Loaded " << tree.size() << " airports ("
              << skipped << " lines skipped: no IATA code or missing info). Duplicates: "
              << duplicates << "\n";

    cout << "Tree height: " << tree.height() << "\n";

    cout << fixed << setprecision(2)
         << "Average node depth: " << tree.AVGDEPTH() << "\n";

    // ---------- Task 2b: search
    cout << "\n===== Task 2b =====\n";
    tree.SEARCH("JFK"); // code deep in tree
    tree.SEARCH("XYZ"); // not in tree
    tree.SEARCH("GKA"); // root
    tree.SEARCH("XYE"); // leaf
    tree.SEARCH("AAA"); // min
    tree.SEARCH("ZZV"); // max
    cout << "Code smaller than every key: AAAA" << "\n";
    cout << "Code larger than every key: ZZZZ" << "\n";

    // ------ task 3b: delete
    cout << "\n===== Task 3b =====\n";
    cout << "Before:\n";
    tree.PRINTTOP3();
    tree.DELETE("ZZV"); // leaf
    cout << "After:\n";
    tree.PRINTTOP3();
    cout << "Valid BST: " << (tree.VALIDATE() ? "yes" : "no") << "\n";

    cout << "Before:\n";
    tree.PRINTTOP3();
    tree.DELETE("GJT"); // one left child
    cout << "After:\n";
    tree.PRINTTOP3();
    cout << "Valid BST: " << (tree.VALIDATE() ? "yes" : "no") << "\n";

    cout << "Before:\n";
    tree.PRINTTOP3();
    tree.DELETE("AAA"); // one right child
    cout << "After:\n";
    tree.PRINTTOP3();
    cout << "Valid BST: " << (tree.VALIDATE() ? "yes" : "no") << "\n";

    cout << "Before:\n";
    tree.PRINTTOP3();
    tree.DELETE("AEY"); // 2 children
    cout << "After:\n";
    tree.PRINTTOP3();
    cout << "Valid BST: " << (tree.VALIDATE() ? "yes" : "no") << "\n";

    cout << "Before:\n";
    tree.PRINTTOP3();
    tree.DELETE("GKA"); // root
    cout << "After:\n";
    tree.PRINTTOP3();
    cout << "Valid BST: " << (tree.VALIDATE() ? "yes" : "no") << "\n";

    //---- task 3c - own airport
    cout << "\n===== Task 3c =====\n";
    Airport q;
    q.iata = "QQQ";
    q.name = "PLentz Airport";
    q.city = "Sparks";
    q.country = "United States";
    q.icao = "KQQQ";
    q.lat = 0.0;
    q.lon = 0.0;

    cout << "Insert code QQQ \n";
    tree.INSERT(q);
    cout << "Valid BST: " << (tree.VALIDATE() ? "yes" : "no") << "\n";
    tree.SEARCH("QQQ"); //
    cout << "Delete code QQQ \n";
    tree.DELETE("QQQ"); //
    cout << "Valid BST: " << (tree.VALIDATE() ? "yes" : "no") << "\n";
    tree.SEARCH("QQQ"); //

    cout << "\n===== Task 4a =====\n";
    tree.LIST();

    cout << "\n===== Task 4b =====\n";
    tree.SAVE("tree_preorder.txt");

    AirportBST tree2; // new tree
    tree2.LOAD("tree_preorder.txt");

    cout << "Original height: " << tree.height()
         << "   Reloaded height: " << tree2.height() << "\n";
    cout << "Original size: " << tree.size()
         << "   Reloaded size: " << tree2.size() << "\n";

    cout << "Original top 3 levels:\n";
    tree.PRINTTOP3();
    cout << "Reloaded top 3 levels:\n";
    tree2.PRINTTOP3();

    if (tree.LEVELORDER() == tree2.LEVELORDER())
        cout << "Same level order: yes\n";
    else
        cout << "Same level order: NO\n";

    // task 5
    cout << "\n===== Task 5 =====\n";
    AirportBST tree5;
    tree5.buildFromArray(airports);
    tree5.RANGE("BOS", "BWI");

    // task 6
    cout << "\n===== Task 6 =====\n";

    // (1) file order
    AirportBST t1;
    t1.buildFromArray(airports);

    // (2) sorted order
    vector<Airport> sortedAirports = airports;
    sort(sortedAirports.begin(), sortedAirports.end(),
         [](const Airport &a, const Airport &b)
         { return a.iata < b.iata; });
    AirportBST t2;
    t2.buildFromArray(sortedAirports);

    // (3) balanced
    AirportBST t3;
    t3.buildFromArray(airports);
    t3.REBALANCE();

    // same random codes
    mt19937 rng(42);
    uniform_int_distribution<int> pick(0, (int)airports.size() - 1);
    vector<string> queries;
    for (int i = 0; i < 10000; i++)
        queries.push_back(airports[pick(rng)].iata);

    double ms1 = timeSearches(t1, queries);
    double ms2 = timeSearches(t2, queries);
    double ms3 = timeSearches(t3, queries);

    cout << "\n"
         << left << setw(14) << "Build" << setw(10) << "Height"
         << setw(12) << "Avg depth" << "Time for 10,000 searches (ms)\n";
    cout << fixed << setprecision(2);
    cout << setw(14) << "File order" << setw(10) << t1.height() << setw(12) << t1.AVGDEPTH() << ms1 << "\n";
    cout << setw(14) << "Sorted order" << setw(10) << t2.height() << setw(12) << t2.AVGDEPTH() << ms2 << "\n";
    cout << setw(14) << "Balanced" << setw(10) << t3.height() << setw(12) << t3.AVGDEPTH() << ms3 << "\n";
}