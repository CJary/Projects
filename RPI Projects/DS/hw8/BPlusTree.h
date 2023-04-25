/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
    BPlusTreeNode() : parent(NULL) {};
    bool is_leaf();
    bool contains(const T& key);

    //For grading only. This is bad practice to have, because
    //it exposes a private member variable.
    BPlusTreeNode* get_parent() { return parent; }

    //We need this to let BPlusTree access private members
    friend class BPlusTree<T>;
private:
    bool contains(const T& key,std::size_t low,std::size_t high);
    std::vector<T> keys;
    std::vector<BPlusTreeNode*> children;
    BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
    for( int i=0; i<children.size(); i++){
        if(children[i]){
            return false;
        }
    }
    return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
    return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
    if(low>high){
        return false;
    }
    if(low==high){
        return key == keys[low];
    }
    std::size_t mid = (low+high)/2;
    if(key<=keys[mid]){
        return contains(key,0,mid);
    }
    else{
        return contains(key,mid+1,high);
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

using namespace std;
template <class T>
class BPlusTree {
public:
    // Constructors & Destructor

    // Constructor to initialize the object with a given size and a NULL root
    BPlusTree(int s) {
        top_root = NULL;
        size = s;
    }

    // Copy constructor to create a new object as a copy of the existing one
    BPlusTree(const BPlusTree<T>& og) {
        size = og.size;
        top_root = this->copyTree(og.top_root, NULL);
    }

    // Assignment operator to copy the existing object to the new one
    BPlusTree<T>& operator=(const BPlusTree<T>& og) {
        if (&og != this) {
            // Destroy the current tree
            this->destroy_tree(top_root);
            // Copy the root and size of the existing tree
            top_root = this->copyTree(og.top_root, NULL);
            size = og.size;
        }
        return *this;
    }

    // Destructor to free the memory used by the tree
    ~BPlusTree() {
        this->destroy_tree(top_root);
        top_root = NULL;
    }

    // Find & Insert

    // Find the node with a given key in the tree
    BPlusTreeNode<T>* find(const T& key) const {
        return find(key, top_root);
    }

    // Insert a new key in the tree
    void insert(const T& key) {
        insert(key, top_root, NULL);
    }

    // Print(s)

    // Helper function to print the tree sideways
    void sidewaysH(ostream& outfile, BPlusTreeNode<T>* p, int level) const;

    // Print the tree sideways to the output stream
    void print_sideways(ostream& outfile) const;

    // Print the tree in breadth-first order to the output stream
    void print_BFS(ostream& outfile) const;

private:
// Pointer to the root node of the B+ tree
    BPlusTreeNode<T>* top_root;
// The number of keys that can be stored in each node of the tree
    int size;

// Helper function to recursively copy a tree
    BPlusTreeNode<T>* copyTree(BPlusTreeNode<T>* og_root, BPlusTreeNode<T>* the_parent) {
        // base case: reached the end of the tree
        if (og_root == NULL) {
            return NULL;
        }

        // Allocate a new node and copy the values from the original node
        BPlusTreeNode<T>* new_tree = new BPlusTreeNode<T>();
        new_tree->keys = og_root->keys;
        new_tree->parent = the_parent;

        // Recursively copy children nodes
        for (int i = 0; i < og_root->children.size(); i++) {
            BPlusTreeNode<T>* copy = copyTree(og_root->children[i], new_tree);
            new_tree->children.push_back(copy);
        }

        return new_tree;
    }

// Helper function to recursively delete a tree
    void destroy_tree(BPlusTreeNode<T>* p) {
        // base case: reached the end of the tree
        if (p == NULL) {
            return;
        }

        // Recursively delete children nodes
        typename vector<BPlusTreeNode<T>*>::iterator itr = p->children.begin();
        while (itr != p->children.end()) {
            destroy_tree(*itr);
            itr = p->children.erase(itr);
        }

        // Delete the current node
        delete p;
    }

// Helper function to recursively find a node with a given key
    BPlusTreeNode<T>* find(const T& key, BPlusTreeNode<T>* p) const {
        // base case: empty tree or leaf node reached
        if (p == NULL || p->is_leaf()) {
            return p;
        }

        // Find the index of the child node to search
        int i = 0;
        for (; i < p->keys.size(); i++) {
            if (key < p->keys[i]) {
                break;
            }
        }

        // Recursively search the child node
        return find(key, p->children[i]);
    }

    // Splits the keys of a B+ tree node into two vectors, with num_elements
    // keys in the second vector, and the rest in the first vector.
    void split_keys(vector<T>& og, vector<T>& new_node_keys, int num_elements) {
        while (new_node_keys.size() != num_elements) {
            new_node_keys.insert(new_node_keys.begin(), og.back()); // Move key from end of first vector to beginning of second vector
            og.pop_back(); // Remove last key from first vector
        }
    }

    // Splits the children of a B+ tree node into two vectors, with num_elements
    void split_children(vector<BPlusTreeNode<T>*>& og, vector<BPlusTreeNode<T>*>& new_node_keys,
                        int num_elements, BPlusTreeNode<T>* new_child) {
        while (new_node_keys.size() != num_elements) {
            new_node_keys.insert(new_node_keys.begin(), og.back()); // Move child from end of first vector to beginning of second vector
            new_node_keys.front()->parent = new_child; // Set parent pointer of new child to new child node
            og.pop_back(); // Remove last child from first vector
        }
    }

    // Sets the parent pointers of a parent node and a new child node to a new parent node.
    void set_parent_pointers(BPlusTreeNode<T>*& p, BPlusTreeNode<T>*& new_child,
                             BPlusTreeNode<T>* new_parent) {
        p->parent = new_parent;
        new_child->parent = new_parent;
    }

    // Updates the parent node of a B+ tree node after a split operation.
    void update_parent_node(BPlusTreeNode<T>*& p, BPlusTreeNode<T>* new_child,
                            BPlusTreeNode<T>*& new_parent) {
        if (p->is_leaf()) {
            // Add first key of new child node to new parent node
            new_parent->keys.push_back(new_child->keys.front());
        }
        else {
            new_parent->keys.push_back(p->keys.back()); // Add last key of first child node to new parent node
            p->keys.pop_back(); // Remove last key from first child node
        }

        new_parent->children.push_back(p); // Add first child node to new parent node
        new_parent->children.push_back(new_child); // Add new child node to new parent node
    }


    void insert(const T& key, BPlusTreeNode<T>*& p, BPlusTreeNode<T>* the_parent) {
        // If tree is empty, create a new root node and insert the key.
        if (this->top_root == NULL) {
            this->top_root = new BPlusTreeNode<T>();
            this->top_root->keys.push_back(key);
            return;
        }

        // Find the appropriate leaf node to insert the key.
        int i = 0;
        for (; i < p->keys.size() && key >= p->keys[i]; i++) {
        }

        bool split = false;
        if (p->is_leaf()) {
            // Insert the key into the leaf node.
            typename vector<T>::iterator itr = p->keys.begin();
            p->keys.insert(itr + i, key);

            // Check if the parent node needs to be split.
            if (the_parent == NULL && p->keys.size() >= this->size) {
                split = true;
            }
        }
        else {
            // Recursively insert the key into the child node.
            insert(key, p->children[i], p);

            // If child node did not need to be split, return.
            if (p->children[i]->keys.size() < this->size) {
                return;
            }
            else {
                // Split the child node.
                BPlusTreeNode<T>* new_child = new BPlusTreeNode<T>();
                new_child->parent = p;
                int first_half = p->children[i]->keys.size() / 2;
                int second_half = 0;
                if (p->children[i]->is_leaf()){
                    second_half = p->children[i]->keys.size() - first_half;
                }

                // Split keys of the child node.
                split_keys(p->children[i]->keys, new_child->keys, second_half);

                T parent_key = p->children[i]->keys.back();
                if (p->children[i]->is_leaf()) {
                    parent_key = new_child->keys.front();
                }

                // Insert the new key and child node into the parent node.
                typename vector<T>::iterator keys_itr = p->keys.begin();
                typename vector<BPlusTreeNode<T>*>::iterator c_itr = p->children.begin();
                p->keys.insert(keys_itr + i, parent_key);
                p->children.insert(c_itr + i + 1, new_child);

                // Check if the parent node needs to be split.
                if (the_parent == NULL && p->keys.size() >= this->size) {
                    split = true;
                }
            }
        }

        // If the parent node needs to be split, split it.
        if (split) {
            // Calculate the size of the two nodes.
            int first_half = p->keys.size() / 2;
            int second_half = 0;
            if (p->is_leaf()){
                second_half = p->keys.size() - first_half;
            }
            else {
                second_half = p->keys.size() - first_half - 1;
            }

            // Create a new child node and split keys.
            BPlusTreeNode<T>* new_child = new BPlusTreeNode<T>();
            split_keys(p->keys, new_child->keys, second_half);

            // Split children nodes for non-leaf node.
            if (!p->is_leaf()) {
                split_children(p->children, new_child->children,
                               second_half + 1, new_child);
            }

            // create new parent node
            BPlusTreeNode<T>* new_parent = new BPlusTreeNode<T>();
            set_parent_pointers(p, new_child, new_parent);

            // update new parent node's keys and children
            update_parent_node(p, new_child, new_parent);

            top_root = new_parent;
        }
    }


};

/*
 *
 * ALL THE PRINT FUNCTIONS BELOW
 *
 */

//Implementation for the call of print_sideways
template <class T>
void BPlusTree<T>::print_sideways(ostream &outfile) const {
    sidewaysH(outfile, top_root, 0);
}


//Implementation for the helper print_sideways function
template <class T>
void BPlusTree<T>::sidewaysH(ostream &outfile, BPlusTreeNode<T> *p, int level) const {
    // Check if the B+ tree is empty
    if (this->top_root == NULL) {
        outfile << "Tree is empty." << endl;
        return;
    }

    // Calculate the number of children and split them into two groups
    int num_children = p->children.size();
    int left_start = 0;
    int left_end = num_children / 2;
    int right_start = left_end;
    int right_end = num_children;

    // Recursively print the left child nodes
    for (int i = left_start; i < left_end; i++) {
        sidewaysH(outfile, p->children[i], level + 1);
    }

    // Print the keys of the current node, indented by level
    for (int i = 0; i < level; i++) {
        outfile << '\t';
    }
    outfile << p->keys[0];
    for (int i = 1; i < p->keys.size(); i++) {
        outfile << ',' << p->keys[i];
    }
    outfile << endl;

    // Recursively print the right child nodes
    for (int i = right_start; i < right_end; i++) {
        sidewaysH(outfile, p->children[i], level + 1);
    }
}


//implementation of the print_BFS outside class
template <class T>
void BPlusTree<T>::print_BFS(ostream &outfile) const {
    // Check if the B+ tree is empty
    if (this->top_root == NULL) {
        outfile << "Tree is empty." << endl;
        return;
    }

    // Initialize a First In First Out wait
    vector<BPlusTreeNode<T>*> wait;
    wait.push_back(this->top_root);
    vector<int> levels;
    levels.push_back(0);

    int prev_level = 0;
    while (wait.size() != 0) {

        // Get the current node to be processed
        BPlusTreeNode<T>* current = wait.front();
        wait.erase(wait.begin());
        int level = levels.front();
        levels.erase(levels.begin());

        // Print indentation based on the level of the node
        if (level == prev_level && level > 0) {
            outfile << '\t';
        }
        else if (level != prev_level) {
            outfile << endl;
        }

        // Print the keys of the current node
        outfile << current->keys[0];
        for (int i = 1; i < current->keys.size(); i++)
            outfile << ',' << current->keys[i];

        // Add the children of the current node to the wait queue
        for (int i = 0; i < current->children.size(); i++) {
            wait.push_back(current->children[i]);
            levels.push_back(level + 1);
        }

        // Update the previous level
        prev_level = level;
    }
    outfile << endl;
}

#endif