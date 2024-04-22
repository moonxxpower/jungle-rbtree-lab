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
void left_rotation(rbtree *t, node_t *x) {
  node_t *y = x -> right;

  // y의 왼쪽 서브 트리를 x의 오른쪽 서브 트리로 옮기기
  x -> right = y -> left;

  if (y -> left != t -> nil) {
    y -> left -> parent = x;
  }

  // x의 부모를 y에 연결하기
  y -> parent = x -> parent;

  if (x -> parent == t -> nil) {
    y -> parent = t -> root;
  }

  else if (x == x -> parent -> left) {
    x -> parent -> left = y;
  }

  else {
    x -> parent -> right = y;
  }

  // x를 y의 왼쪽으로 두기
  y -> left = x;
  x -> parent = y;
}

// 우회전
/*

          |
          y
        /   \
      x     y.r
     / \
   x.l x.r  

*/
void right_rotation(rbtree *t, node_t *y) {
  node_t *x = y -> left;

  // x의 오른쪽 서브 트리를 y의 왼쪽 서브 트리로 옮기기
  y -> left = x -> right;

  if (x -> right != t -> nil) {
    x-> right -> parent = y;
  }

  // y의 부모를 x에 연결하기
  x -> parent = y -> parent;

  if (y -> parent == t -> nil) {
    x -> parent = t -> root;
  }

  else if (y == y -> parent -> left) {
    y -> parent -> left = x;
  }

  else {
    y -> parent -> right = x;
  }

  // y를 x의 오른쪽으로 두기
  x -> right = y;
  y -> parent = x;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free(t);
}

// key의 값을 가진 새로운 노드 삽입
node_t *rbtree_insert(rbtree *t, const key_t key) {
  // 새로운 노드 생성
  node_t *new = (node_t *)calloc(1, sizeof(node_t));
  node_t *current = t -> root;

  // 새 노드를 삽입할 위치 탐색
  while (current != t -> nil) {

    // 왼쪽 노드에 삽입
    if (new -> key < current -> key) {
      current -> left = new;
    }

    // 오른쪽 노드에 삽입
    else {
      current -> right = new;
    }
  }

  // 새 노드의 부모 지정
  new -> parent = current;

  // root가 nil일 경우, 새 노드를 트리의 루트로 지정
  if (current == t -> nil) {
    t -> root = new;
  }

  new -> left = t -> nil;
  new -> right = t -> nil;
  new -> color = RBTREE_RED;  // 삽입된 노드는 무조건 red

  rbtree_insert_fixup(t, new);

  return new;
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

// rbtree_erase_fixup(rbtree *t, node_t *p)

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}