#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <libtree.h>

struct s1 {
  int key;
  struct rbtree_node node;
};


int my_cmp(const struct rbtree_node *a, const struct rbtree_node *b);


int main(int argc, char **argv)
{
  struct rbtree       tree;
  struct s1          *obj;
  struct rbtree_node *curr_node;

  int i;

  rbtree_init(&tree,my_cmp,0);

  for (i = 0; i < 1000000; i++) {
    obj = malloc(sizeof(struct s1));
    obj->key = i;
    rbtree_insert(&obj->node, &tree);
  }

  printf("Completed tree insertion\n");

  curr_node = rbtree_first(&tree);

  for (i = 0; i < 1000000; i++) {
    obj = rbtree_container_of(curr_node, struct s1, node);
    if (obj->key != i) {
      printf("Unexpected key\n");
      exit(1);
    }
    curr_node = rbtree_next(curr_node);
  }

  printf("Completed tree validation\n");

/* #  define rbtree_container_of(node, type, member) */

}

int my_cmp(const struct rbtree_node *a, const struct rbtree_node *b)
{
  struct s1 *p = rbtree_container_of(a, struct s1, node);
  struct s1 *q = rbtree_container_of(b, struct s1, node);
  
  return p->key - q->key;
}
