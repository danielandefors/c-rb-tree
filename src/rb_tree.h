
/* A red-black tree. */
struct rb_tree
{
  struct rb_tree_node *root;
  int (*compare)(const void*, const void*);
};

/** Node color */
enum rb_color
{
  RED = 0,
  BLACK = 1
};

/* A node in a red black tree */
struct rb_tree_node
{
  enum rb_color color;
  void *key;
  void *value;
  struct rb_tree_node *parent;
  struct rb_tree_node *left;
  struct rb_tree_node *right;
};

/*
 * Create a new empty tree with the given compare function.
 */
struct rb_tree *rb_create(int (*compare)(const void*, const void*));

/*
 * Insert a value into the tree. If the key already exists in the tree it
 * returns a pointer to its node. Otherwise it inserts a new node into the
 * tree and returns a pointer to the new node.
 */
struct rb_tree_node *rb_insert(struct rb_tree *t, void *key);

/*
 * Find the node with the given key. If such a node exists in the tree it
 * will be returned. Otherwise the function returns NULL.
 */
struct rb_tree_node *rb_lookup(struct rb_tree *t, void *key);

/*
 * Get the node with the tree's minimum key.
 */
struct rb_tree_node *rb_min(struct rb_tree *t);

/*
 * Get the node with the tree's maximum key.
 */
struct rb_tree_node *rb_max(struct rb_tree *t);

/*
 * Get the next node (in increasing key order).
 */
struct rb_tree_node *rb_next(struct rb_tree_node *n);

/*
 * Check if a key exists in the tree.
 */
int rb_contains(struct rb_tree *t, void *key);

/*
 * Inserts the key and value into the tree. Returns the old value bound to the
 * key, if any.
 */
void *rb_put(struct rb_tree *t, void *key, void *value);

/*
 * Get the value bound to key.
 */
void *rb_get(struct rb_tree *t, void *key);

