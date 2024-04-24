#include "rbtree.h"

// #include <stdio.h>
#include <stdlib.h>

// 새로운 RB Tree 생성
rbtree * new_rbtree(void) {
  rbtree * t = (rbtree *)calloc(1, sizeof(rbtree));
  
  node_t * nil = (node_t *)calloc(1, sizeof(node_t));
  nil -> color = RBTREE_BLACK;  // nil 노드는 항상 black

  // 초기값 설정
  t -> nil = nil;
  t -> root = nil;

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
void left_rotation(rbtree * t, node_t * x) {
  node_t * y = x -> right;

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
void right_rotation(rbtree * t, node_t * y) {
  node_t * x = y -> left;

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
void delete_node(rbtree * t, node_t * n) {
  if (n == t -> nil) {
    return;
  }

  delete_node(t, n -> left);
  delete_node(t, n -> right);
  free(n);
}

void delete_rbtree(rbtree * t) {
  delete_node(t, t -> root);
  free(t -> nil);
  free(t);
}

// key의 값을 가진 새로운 노드 삽입
node_t * rbtree_insert(rbtree * t, const key_t key) {
  // 새로운 노드 생성
  node_t * new = (node_t *)malloc(sizeof(node_t));
  node_t * p = t -> nil;
  node_t * c = t -> root;

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

  return t -> root;
}

// 삽입 후, RB Tree 속성을 만족하지 않은 부분 재조정
void rbtree_insert_fixup(rbtree * t, node_t * new) {
  // 두개의 red 노드가 연속으로 왔을 때
  while (new -> parent -> color == RBTREE_RED) {

    if (new -> parent == new -> parent -> parent -> left) {
      node_t * uncle = new -> parent -> parent -> right;

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
        right_rotation(t, new -> parent -> parent);
      }

    } else {
      node_t * uncle = new -> parent -> parent -> left;

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
        left_rotation(t, new -> parent -> parent);
      }
    }
  }

  // 루트 노드는 항상 black
  t -> root -> color = RBTREE_BLACK;
}

// RB Tree 내에 해당 key가 있는지 탐색
node_t * rbtree_find(const rbtree * t, const key_t key) {
  node_t* temp = t -> root;

  while (temp != t -> nil) {
    if (temp -> key > key) {
      temp = temp -> left;
    }

    else if (temp -> key < key) {
      temp = temp -> right;
    }

    else {
      return temp;
    }
  }

  return NULL;
}

// RB Tree의 최소 값 찾기
node_t * rbtree_min(const rbtree * t) {
  node_t * p = t -> nil;
  node_t * c = t -> root;

  while (c != t -> nil) {
    p = c;
    c = c -> left;
  }

  return p;
}

// RB Tree의 최대 값 찾기
node_t * rbtree_max(const rbtree * t) {
  node_t * p = t -> nil;
  node_t * c = t -> root;

  while (c != t -> nil) {
    p = c;
    c = c -> right;
  }

  return p;
}

// n을 기준으로 최소 값을 갖는 노드
node_t * node_min(rbtree * t, node_t * n) {
  node_t * temp;
  temp = n;

  while (temp -> left != t -> nil) {
    temp = temp -> left;
  }

  return temp;
}

// 다른 서브 트리로 교체
void transplant(rbtree * t, node_t * u, node_t * v) {
  if (u -> parent == t -> nil) {
    t -> root = v;
  }

  else if (u == u -> parent -> left) {
    u -> parent -> left = v;
  }

  else {
    u -> parent -> right = v;
  }

  v -> parent = u -> parent;
}

// 지정된 노드 삭제
int rbtree_erase(rbtree * t, node_t * erase) {
  node_t * y = erase; 
  node_t * x;
  color_t y_original_color = y -> color;

  // 삭제된 노드를 대체할 노드 찾기
  // 삭제될 노드의 왼쪽이 없을 때
  if (erase -> left == t -> nil) {  
    x = erase -> right;
    transplant(t, erase, erase -> right);
  }

  // 삭제될 노드의 오른쪽이 없을 때
  else if (erase -> right == t -> nil) {
    x = erase -> left;
    transplant(t, erase, erase -> left);
  }

  // 삭제될 노드가 자식 노드 모두를 가지고 있을 때
  else {
    y = node_min(t, erase -> right);
    y_original_color = y -> color;
    x = y -> right;

    // 후임자 노드를 대체하고, 후임자 노드와 삭제될 노드의 자식들이 올바르게 연결하기
    if (y -> parent == erase) {
      x -> parent = y; 
    }

    else {
      transplant(t, y, y -> right);
      y -> right = erase -> right;
      y -> right -> parent = y;
    }

    // 삭제될 노드를 y로 대체하기
    transplant(t, erase, y);
    y -> left = erase -> left;
    y -> left -> parent = y;
    y -> color = erase -> color;
  }

  // 실제로 삭제된 노드가 black일 경우 재조정 필요
  if (y_original_color == RBTREE_BLACK) {
    rbtree_erase_fixup(t, x); 
  }

  free(erase);
  return 0;
}

// 삭제 후, RB Tree 속성을 만족하지 않은 부분 재조정
void rbtree_erase_fixup(rbtree * t, node_t * x) {
  node_t * sibling;

  while (x != t -> root && x -> color == RBTREE_BLACK) {

    // 기준이 되는 노드가 왼쪽에 있을 때
    if(x == x -> parent -> left){
      sibling = x -> parent -> right;

      // 만약 형제가 red일 경우
      if (sibling -> color == RBTREE_RED) {
        sibling -> color = RBTREE_BLACK;
        x -> parent -> color = RBTREE_RED;
        left_rotation(t, x -> parent);
        sibling = x -> parent -> right;
      }

      // 만약 형제와 형제의 자식들 모두 black일 경우
      if (sibling -> left -> color == RBTREE_BLACK && sibling -> right -> color == RBTREE_BLACK) {
        sibling -> color = RBTREE_RED;
        x = x -> parent;
      }

      // 자식들 중 최소 한 개는 red      
      else {

        // 만약 형제가 black, 오른쪽 자식이 red, 왼쪽 자식이 black일 경우        
        if (sibling -> right -> color == RBTREE_BLACK) {
          sibling -> left -> color = RBTREE_BLACK;
          sibling -> color = RBTREE_RED;
          right_rotation(t, sibling);
          sibling = x -> parent -> right;
        }

        // 만약 형제는 black, 형제의 오른쪽 자식이 red일 경우
        sibling -> color = x -> parent -> color;
        x -> parent -> color = RBTREE_BLACK;
        sibling -> right -> color = RBTREE_BLACK;
        left_rotation(t, x -> parent);
        x = t -> root;
      }
    }

    // 기준이 되는 노드가 오른쪽에 있을 때
    else {
      sibling = x -> parent -> left;

      //만약 형제가 red일 경우
      if (sibling -> color == RBTREE_RED) {
        sibling -> color = RBTREE_BLACK;
        x -> parent -> color = RBTREE_RED;
        right_rotation(t, x -> parent);
        sibling = x -> parent -> left;
      }

      // 만약 형제와 형제의 자식들 모두 black일 경우
      if (sibling -> right -> color == RBTREE_BLACK && sibling -> left -> color == RBTREE_BLACK) {
        sibling -> color = RBTREE_RED;
        x = x -> parent;
      }

      // 자식들 중 최소 한 개는 red      
      else {

        // 만약 형제가 black, 왼쪽 자식이 red, 오른쪽 자식이 black일 경우
        if (sibling -> left -> color == RBTREE_BLACK) {
          sibling -> color = RBTREE_RED;
          sibling -> right -> color = RBTREE_BLACK;
          left_rotation(t, sibling);
          sibling = x -> parent -> left;
        }

        // 만약 형제는 black, 형제의 왼쪽 자식이 red일 경우
        sibling -> color = x -> parent -> color;
        x-> parent -> color = RBTREE_BLACK;
        sibling -> left -> color = RBTREE_BLACK;
        right_rotation(t, x -> parent);
        x = t -> root;
      }
    }
  }

  x -> color = RBTREE_BLACK;
}

// 중위 순회하면서 값을 array에 담기
int node_to_array(const rbtree * t, node_t * n, key_t * arr, int i){
  if (n == t -> nil) {
    return i; 
  }

  // i는 인덱스
  i = node_to_array(t, n -> left, arr, i);   
  arr[i++] = n -> key; 
  i = node_to_array(t, n -> right, arr, i);  

  return i;
}

// RB Tree의 내용을 key 순서대로 array로 반환
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t s) {
  node_to_array(t, t -> root, arr, 0);

  return 0;
}

// // 트리를 출력하는 함수
// void print_rbtree(rbtree *t, node_t *node, int space) {
//   if (node == t -> nil)
//     return;

//   space += 10;
//   print_rbtree(t, node -> right, space);

//   printf("\n");
//   for (int i = 10; i < space; i++)
//     printf(" ");
//   printf("[%d(%s)]\n", node -> key, node -> color == RBTREE_RED ? "R" : "B");

//   print_rbtree(t, node -> left, space);
// }

// int main() {
//   rbtree *t = new_rbtree();
//   int key;

//   printf("노드를 삽입하려면 키 값을 입력하세요 (음수를 입력하면 종료):\n");
//   while (scanf("%d", &key) && key >= 0) {
//     rbtree_insert(t, key);
//     print_rbtree(t, t -> root, 0);
//   }

//   printf("삭제할 값을 입력하세요:\n");
//   while (scanf("%d", &key) && key >= 0) {
//     node_t *to_delete = rbtree_find(t, key);
//     if (to_delete) {
//       rbtree_erase(t, to_delete);
//       printf("%d가 트리에서 삭제되었습니다.\n", key);
//       print_rbtree(t, t -> root, 0);
//     } else {
//       printf("%d가 트리에 존재하지 않습니다.\n", key);
//     }
//     printf("삭제할 값을 입력하세요 (음수를 입력하면 종료):\n");
//   }

//   // 트리 메모리 해제
//   delete_rbtree(t);

//   return 0;
// }