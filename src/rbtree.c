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
    t -> root = y;
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
    t -> root = x;
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

// 후위 순회를 이용하여 해당 Tree가 사용했던 메모리 전부 반환
void delete_node(rbtree *t, node_t *n) {
  if (n == t -> nil) {
    return;
  }

  delete_node(t, n -> left);
  delete_node(t, n -> right);
  free(n);
}

void delete_rbtree(rbtree *t) {
  delete_node(t, t -> root);
  free(t -> nil);
  free(t);
}

// key의 값을 가진 새로운 노드 삽입
node_t *rbtree_insert(rbtree *t, const key_t key) {
  // 새로운 노드 생성
  node_t *new = (node_t *)calloc(1, sizeof(node_t));
  node_t *p = t -> nil;
  node_t *c = t -> root;

  // 새 노드를 삽입할 위치를 탐색
  while (c != t -> nil) {
    p = c;
    if (key < c -> key) {
      c = c -> left;
    }
    else {
      c = c -> right;
    }
  }

  // 새 노드의 부모 설정
  new -> parent = p;

  // root가 nil일 경우, 새 노드를 트리의 루트로 지정
  if (p == t -> nil) {
    t -> root = new;
  }

  // 부모의 자식 설정
  else if (key < p -> key) {
    p -> left = new;
  }

  else {
    p -> right = new;
  }
  
  new -> key = key;
  new -> left = t -> nil;
  new -> right = t -> nil;
  new -> color = RBTREE_RED;

  rbtree_insert_fixup(t, new);

  return new;
}

// 삽입 후, RB Tree 속성을 만족하지 않은 부분 재조정
void rbtree_insert_fixup(rbtree *t, node_t *new) {
  // 두개의 red 노드가 연속으로 왔을 때
  while (new -> parent -> color == RBTREE_RED) {
    if (new -> parent == new -> parent -> parent -> left) {
      node_t *uncle = new -> parent -> parent -> right;

      // 삼촌이 red일 경우 -> 색깔 변경
      if (uncle -> color == RBTREE_RED) {
        new -> parent -> color = RBTREE_BLACK;
        uncle -> color = RBTREE_BLACK;
        new -> parent -> parent -> color = RBTREE_RED;
        new = new -> parent -> parent;
      }

      // 삼촌이 black일 경우 -> 회전 (위치에 따라 방향 차이 존재)
      else {
        if (new == new -> parent -> right) {
          // 만약 꺾여 있는 경우, 회전하여 펴주기
          new = new -> parent;
          left_rotation(t, new);
      }

        new -> parent -> color = RBTREE_BLACK;
        new -> parent -> parent -> color = RBTREE_RED;
        right_rotation(t, new);
      }

    } else {
      node_t *uncle = new -> parent -> parent -> left;

      // 삼촌이 red일 경우 -> 색깔 변경
      if (uncle -> color == RBTREE_RED) {
        new -> parent -> color = RBTREE_BLACK;
        uncle -> color = RBTREE_BLACK;
        new -> parent -> parent -> color = RBTREE_RED;
        new = new -> parent -> parent;
      }

      // 삼촌이 black일 경우 -> 회전 (위치에 따라 방향 차이 존재)
      else {
        if (new == new -> parent -> left) {
          // 만약 꺾여 있는 경우, 회전하여 펴주기
          new = new -> parent;
          right_rotation(t, new);
        }

        new -> parent -> color = RBTREE_BLACK;
        new -> parent -> parent -> color = RBTREE_RED;
        left_rotation(t, new);
      }
    }
  }

  // 루트 노드는 항상 black
  t -> root -> color = RBTREE_BLACK;
}

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
