#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
  TreeMap* map = (TreeMap*) malloc(sizeof(TreeMap));
  map->root=NULL;
  map->current=NULL;
  map->lower_than = lower_than;
  return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value)
{
  if(searchTreeMap(tree,key)==NULL)
  {
    if(tree->root == NULL)
    {
      TreeNode *nodo=createTreeNode(key,value);
      tree->root=nodo;
      tree->current=nodo;
      nodo->parent=NULL;
    }
    else
    {
      TreeNode *nodoAct=tree->root;
      while(nodoAct != NULL)
        {
          tree->current=nodoAct;
          if(tree->lower_than(nodoAct->pair->key,key)==0)
          {
            nodoAct=nodoAct->left;
          }
          else
          {
            nodoAct=nodoAct->right;
          }
        }
      TreeNode *nodo=createTreeNode(key,value);
      nodo->parent=tree->current;
      if(tree->lower_than(tree->current->pair->key,key)==0)
      {
        tree->current->left=nodo;
      }
      else
      {
        tree->current->right=nodo;
      }
      tree->current=nodo;
    }
  }
}

TreeNode * minimum(TreeNode * x)
{ 
  while(x->left !=NULL)
    {
      x=x->left;
    }
  return (x); 
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
  if((node->left == NULL)&&(node->right == NULL))
  {
    if(node->parent->left == node)
    {
      node->parent->left = NULL;
    }
    else
    {
      node->parent->right = NULL;
    }
  }
  else
  {
    if((node->left == NULL)||(node->right = NULL))
    {
      if(node->parent < node)
      {
        if(node->left == NULL)
        {
          node->parent->right=node->right;
          node->right->parent=node->parent;
        }
        else
        {
          node->parent->right=node->left;
          node->left->parent= node->parent;
        }
      }
      else
      {
        TreeNode* aux= node->right;
        TreeNode* nodoMinimo=minimum(aux);
        node->pair=nodoMinimo->pair;
        nodoMinimo->parent->left=nodoMinimo->right;
        free(nodoMinimo);
      }
    } 
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key)
{
  TreeNode *nodoAct=tree->root;

  if(tree->root == NULL)
  {
    return NULL;
  }
  else
  {
    while(nodoAct != NULL)
      {
        if(is_equal(tree,nodoAct->pair->key,key)==1)
        {
          tree->current=nodoAct;
          return(nodoAct->pair);
        }
        if(tree->lower_than(nodoAct->pair->key,key)==0)
        {
          nodoAct=nodoAct->left;
        }
        else
        {
          nodoAct=nodoAct->right;
        }
      }
    return NULL;
  }  
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
