
#include <stdlib.h>
#include <string.h>
#include "rb_tree.h"

/* Correct root pointer. */
static void rb_correct_root(struct rb_tree *t)
{
  if (t->root) {
    struct rb_tree_node *p;
    while ((p = t->root->parent)) {
      t->root = p;
    }
  }
}

/* Rotate tree left at n. */
static void rb_rotate_left(struct rb_tree_node *n)
{
  struct rb_tree_node * p = n->parent;
  struct rb_tree_node * r = n->right;
  struct rb_tree_node * rl = r->left;
  r->parent = p;
  if (p) {
    if (p->left == n) p->left = r;
    else p->right = r;
  }
  n->parent = r;
  r->left = n;
  n->right = rl;
  if (rl) rl->parent = n;
}

/* Rotate tree right at n. */
static void rb_rotate_right(struct rb_tree_node * n)
{
  struct rb_tree_node * p = n->parent;
  struct rb_tree_node * l = n->left;
  struct rb_tree_node * lr = l->right;
  l->parent = p;
  if (p) {
    if (p->left == n) p->left = l;
    else p->right = l;
  }
  n->parent = l;
  l->right = n;
  n->left = lr;
  if (lr) lr->parent = n;
}

static void rb_insert_case1(struct rb_tree_node *n);
static void rb_insert_case2(struct rb_tree_node *n);
static void rb_insert_case3(struct rb_tree_node *n);
static void rb_insert_case4(struct rb_tree_node *n);
static void rb_insert_case5(struct rb_tree_node *n);

void rb_insert_case1(struct rb_tree_node *n)
{
  if (n->parent) rb_insert_case2(n);
  else n->color = BLACK;
}

void rb_insert_case2(struct rb_tree_node *n)
{
  if (n->parent->color == RED) rb_insert_case3(n);
}

void rb_insert_case3(struct rb_tree_node *n)
{
  struct rb_tree_node *p = n->parent;
  struct rb_tree_node *g = p->parent;
  struct rb_tree_node *u = g->left == p ? g->right : g->left;
  if (u && u->color == RED) {
    p->color = BLACK;
    u->color = BLACK;
    g->color = RED;
    rb_insert_case1(g);
  } else {
    rb_insert_case4(n);
  }
}

void rb_insert_case4(struct rb_tree_node *n)
{
  struct rb_tree_node * p = n->parent;
  struct rb_tree_node * g = p->parent;
  if ((n == p->right) && (p == g->left)) {
    rb_rotate_left(p);
    n = n->left;
  } else if ((n == p->left) && (p == g->right)) {
    rb_rotate_right(p);
    n = n->right;
  }
  rb_insert_case5(n);
}

void rb_insert_case5(struct rb_tree_node *n)
{
  struct rb_tree_node * p = n->parent;
  struct rb_tree_node * g = p->parent;
  p->color = BLACK;
  g->color = RED;
  if (n == p->left)
    rb_rotate_right(g);
  else
    rb_rotate_left(g);
}

struct rb_tree *rb_create()
{
  return calloc(1, sizeof(struct rb_tree));
}

struct rb_tree_node *rb_insert(struct rb_tree *t, char *key)
{
  struct rb_tree_node *n = t->root;
  if (n) {
    int cmp;
    struct rb_tree_node *c;
    while (n->key) {
      cmp = strcmp(n->key, key);
      if (cmp > 0) {
        c = n->left;
        if (!c) {
          c = calloc(1, sizeof(*c));
          if (!c) return NULL;
          c->parent = n;
          n->left = c;
        }
        n = c;
      } else if (cmp < 0) {
        c = n->right;
        if (!c) {
          c = calloc(1, sizeof(*c));
          if (!c) return NULL;
          c->parent = n;
          n->right = c;
        }
        n = c;
      } else {
        return n;
      }
    }
  } else {
    n = calloc(1, sizeof(*n));
    t->root = n;
  }
  n->key = key;
  rb_insert_case1(n);
  rb_correct_root(t);
  return n;
}

struct rb_tree_node *rb_lookup(struct rb_tree *t, char *key)
{
  int cmp;
  struct rb_tree_node *n = t->root;
  while (n) {
    cmp = strcmp(n->key, key);
    if (cmp > 0) n = n->left;
    else if (cmp < 0) n = n->right;
    else return n;
  }
  return NULL;
}

struct rb_tree_node *rb_min(struct rb_tree *t)
{
  struct rb_tree_node *n = t->root;
  if (n)
    while (n->left)
      n = n->left;
  return n;
}

struct rb_tree_node *rb_max(struct rb_tree *t)
{
  struct rb_tree_node *n = t->root;
  if (n)
    while (n->right)
      n = n->right;
  return n;
}

struct rb_tree_node *rb_next(struct rb_tree_node *n)
{
  struct rb_tree_node *next = n->right;
  if (next) {
    while (next->left)
      next = next->left;
  } else {
    next = n->parent;
    while (next && next->right == n) {
      n = next;
      next = n->parent;
    }
  }
  return next;
}

int rb_contains(struct rb_tree *t, char *key)
{
  return rb_lookup(t, key) != NULL;
}

void *rb_put(struct rb_tree *t, char *key, void *value)
{
  struct rb_tree_node *n = rb_insert(t, key);
  void *old_value = n->value;
  n->value = value;
  return old_value;
}

void *rb_get(struct rb_tree *t, char *key)
{
  struct rb_tree_node *n = rb_lookup(t, key);
  if (n) return n->value;
  return NULL;
}

