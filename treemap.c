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
  while(x->left != NULL)
    {
      x=x->left;
    }
    return x; 
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
   if(node->right == NULL && node->left == NULL)
   {
        if(node == tree->root)
        {
            tree->root = NULL;
            tree->current = NULL;
        }
        else if(node->parent->right == node)
            node->parent->right = NULL;
        else
            node->parent->left = NULL;
    }
    else if(node -> right == NULL || node -> left == NULL)
    {  
        if(node == tree->root)
        {
          if(node->left != NULL)
        {
          tree->root = node->left;
          node->left->parent = NULL;
        }
        else
        {
          tree->root = node->right;
          node->right->parent = NULL;
        }
    }
        else if(node == node->parent->left)
        {
            if(node->left != NULL)
            {
              node->left->parent = node->parent;
              node->parent->left = node->left;
            }
            else
            {
              node->right->parent = node->parent;
              node->parent->right = node->right;
            }
        }
        else
        {
            if(node->left != NULL)
            {
              node->parent->right = node->left;
              node->left->parent = node->parent;
            }
            else
            {
              node->parent->right = node->right;
              node->right->parent = node->parent;
            }
        }
    }
    else{
        TreeNode *auxNode = minimum(node->right);
        node->pair=auxNode->pair;
        removeNode(tree, auxNode);
        tree->current = node;
    }
}


void eraseTreeMap(TreeMap * tree, void* key)
{
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


Pair * upperBound(TreeMap * tree, void* key)
{
  Pair* aux=searchTreeMap(tree,key);
  if(aux!=NULL)
  {
    aux=aux;
  }
  else
  {
    if(tree->lower_than(tree->current->pair->key,key)!=1)
    {
      return tree->current->pair;
    }
    aux= nextTreeMap(tree);
  }
  return aux;
}

Pair * firstTreeMap(TreeMap * tree) 
{
  TreeNode* node=minimum(tree->root);
  return node->pair;
}

Pair * nextTreeMap(TreeMap * tree)
{
  TreeNode* aux;
  if(tree->current->right!=NULL)
  {
    aux=minimum(tree->current->right);
  }
  else
  {
     while(tree->current->parent!=NULL && tree->lower_than(tree->current->pair->key,tree->current->parent->pair->key)!=1)
    {
      tree->current=tree->current->parent;
    }
    aux=tree->current->parent;
  }
  tree->current=aux;
  
  if(tree->current==NULL)
  {
    return NULL;
  }
  return aux->pair;
}
