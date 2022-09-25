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
  }
  
  
  
}

TreeNode * minimum(TreeNode * x)
{

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{

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
