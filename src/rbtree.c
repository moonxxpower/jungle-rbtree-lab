#include "rbtree.h"

#include <stdlib.h>

// 새로운 RB Tree 생성
rbtree *new_rbtree(void) {
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
  
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  nil -> color = RBTREE_BLACK;  // nil 노드는 항상 black

  // 초기값 설정
  t -> nil = t -> root = nil;

  return t;
}

// 좌회전
/*

       |
       x
     /   \
   x.l    y            
        /   \
      y.l   y.r

*/
void left_rotation(rbtree *t, node_t *p) {
  node_t *y = x -> right;

  // y의 왼쪽 서브 트리를 x의 오른쪽 서브 트리로 옮기기
  x -> right = y -> left;

  if (y -> left != t -> nil) {
    y -> left -> parent = x;
  }

  // x의 부모를 y에 연결하기
  y -> parent = x -> parent;

  if (x -> parent == t -> nil) {
    y -> parent = t -> root
  }

  elif (x == x -> parent -> left) {
    x -> parent -> left = y;
  }

  else {
    x -> parent -> right = y;
  }

  // x를 y의 왼쪽으로 두기
  y -> left = x;
  x -> parent = y;
}

// void right_rotation(rbtree *t, node_t *p)

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

// rbtree_insert_fixup(rbtree *t, node_t *p)

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

// rbtree_delte_fixup(rbtree *t, node_t *p)

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}