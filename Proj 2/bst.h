/*bsh.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey, typename TValue>
class binarysearchtree
{
private:
  struct NODE
  {
    TKey  Key;
	TValue Value;
    NODE* Left;
    NODE* Right;
  };
  
  struct MovieData {
	string NameofMovie;
	int PubYear;
	int Num5Stars;
	int Num4Stars;
	int Num3Stars;
	int Num2Stars;
	int Num1Stars;
	};

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
  void _inorder(NODE* cur)
  {
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " ";
        _inorder(cur->Right);
     }
  }

  int _height(NODE* Root){
     int leftHeight = 0;
     int rightHeight = 0;
     
     if(Root == nullptr){
        return -1;
     }
     leftHeight = _height(Root->Left);
     rightHeight = _height(Root->Right);
     return 1 + max(leftHeight, rightHeight);
     
     
  }
  
//   NODE* binary_helper(binarysearchtree* bstNode){
  
// 	  if(bstNode == nullptr){
// 		  return nullptr;
// 	  }
// 	  if(bstNode->Left != nullptr){
// 		  NODE* newd = new NODE;
// 		  newd->Key = bstNode->Key;
// 		  newd->Value = bstNode->Value;
// 		  binary_helper(bstNode->Left);
		  
// 	  }
// 	  if(bstNode->Right != nullptr){
// 		  NODE* newd = new NODE;
// 		  newd->Key = bstNode->Key;
// 		  newd->Value = bstNode->Value;	  
// 		  binary_helper(bstNode->Right);
// 	  }
//   }
  NODE* binary_helper(NODE* bstNode){
  
	  if(bstNode == nullptr){
		  return nullptr;
	  }
	
	NODE* newd = new NODE;
	//Size++;
	newd->Key = bstNode->Key;
	newd->Value = bstNode->Value;
	
	
	newd->Left = binary_helper(bstNode->Left);
	newd->Right = binary_helper(bstNode->Right);
	return newd;
	  
  }
public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }
// copy constructor:
//
  binarysearchtree(binarysearchtree& other)
  {
	
	Size = other.Size ;
	Root = binary_helper(other.Root);
	
	
  }


  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  //
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  //
  int height()
  {
    int height_size = _height(Root);
    return height_size;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return &(cur->Value);

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  
  
    // if get here, not found
    return nullptr;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // TODO: allocate a new node, store key, initialize
    // pointer fields:
    //
    NODE* this_node = new NODE;
    this_node->Key = key;
	this_node->Value = value;
    this_node->Left = nullptr;
    this_node->Right = nullptr;
   
   
    //
    // 3. link in the new node:
    //
    
   if(prev == nullptr){
      Root = this_node;
   }
   else if(this_node->Key < prev->Key){
      prev->Left = this_node;
   }
   else{
      prev->Right = this_node;
   }

    Size++;
  }

  //
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder()
  {
     cout << "Inorder: ";
     
     _inorder(Root);
     
     cout << endl;
  }

};

