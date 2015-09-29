
#include <stdio.h>
#include "rb_tree.h"

void dump(struct rb_tree *t)
{
  struct rb_tree_node *n;
  for (n = rb_min(t); n; n = rb_next(n)) {
    printf("%s = %s\n", n->key, n->value);
  }
}

int main(const int argc, const char **argv)
{
  struct rb_tree *t = rb_create();

  rb_put(t, "1", "Hello");
  rb_put(t, "2", "World");
  printf("%s, %s!\n", rb_get(t, "1"), rb_get(t, "2"));

  dump(t);

  return 0;
}
