/*****************************************
 ** File:    Llama.h
 ** Project: CMSC 341 Project 1, Fall 2016
 ** Author:  Hemang Bhatt
 ** Date:    10/4/16
 ** Section: 03
 ** E-mail:  hb6@umbc.edu
 **
 ** This file contains Llama class and LlamaUnderflow class declaration, function prototypes
 ** and member variables for the Project 1.
 ***********************************************/




#ifndef _LLAMA_H_
#define _LLAMA_H_

#include <stdexcept>
#include <string>
#include "LlamaNode.h"

using namespace std ;



/* This class throws exeption LlamaUnderflow and Prints message */


class LlamaUnderflow : public std::out_of_range {
    
public:
    
    LlamaUnderflow(const string& what) : std::out_of_range(what) { }
    
} ;



template <class T, int LN_SIZE>
class Llama {
    
public:

  //-------------------------------------------------------
  // Name: Llama()
  // PreCondition: None
  // PostCondition: initialize all of the member veriables and create new LlamaNode
  //---------------------------------------------------------
    Llama() ;

  //-------------------------------------------------------
  // Name: Llama(const Llama<T,LN_SIZE>& other)
  // PreCondition: None
  // PostCondition: make a deep copy of otherStack
  //---------------------------------------------------------
    Llama(const Llama<T,LN_SIZE>& other) ;   // copy constructor



  //-------------------------------------------------------
  // Name: ~Llama()
  // PreCondition: Atleast should have LlamaNode 
  // Postconndition: dynamically allocated memory associated with the host object will be deallocated. 
    ~Llama() ;
    

  //-------------------------------------------------------
  // Name: size()
  // PreCondition: None
  // PostCondition: return the total size of the stack
  //---------------------------------------------------------
    int size() ;

  //-------------------------------------------------------
  // Name: dump()
  // PreCondition: None
  // PostCondition: will print each of the nodes of the llama stack, along with details of how many nodes created, destroied, size of the stack, and weather there is a extra node or not
  //---------------------------------------------------------
    void dump() ;

  //-------------------------------------------------------
  // Name: push()
  // PreCondition: LlamaStack should have atleast one LlamaNode
  // PostCondition: will push data on to the stack, will check to see if new node needs to be created to push data. and if there is a extra node will not creat a extra node to push onto
  //---------------------------------------------------------
    void push(const T& data) ;


  //-------------------------------------------------------
  // Name: pop()
  // PreCondition: None  
  // PostCondition: remove and return the top Item or throw LlamaUnderflow 
  //---------------------------------------------------------
    T pop() ;

  
  //-------------------------------------------------------
  // Name: dup()
  // PreCondition:  None
  // PostCondition: duplicate the top item or throw LlamaUnderflow
  //---------------------------------------------------------
    void dup() ;    //  (top) A B C D -> A A B C D

   //-------------------------------------------------------
  // Name: swap()
  // PreCondition:  None
  // PostCondition: swap the top two elements or throw LlamaUnderflow
  //---------------------------------------------------------
    void swap() ;   //  (top) A B C D -> B A C D

  //-------------------------------------------------------
  // Name: rot()
  // PreCondition:  None
  // PostCondition: Rotate top three elemets or throw LlamaUnderflow 
  //---------------------------------------------------------
    void rot() ;    //  (top) A B C D -> C A B D
//    
//    
    //-------------------------------------------------------
  // Name: peek(int offset)
  // PreCondition:  offset should be positive integer or 0
  // PostCondition: return the items at offset position
  //---------------------------------------------------------
    T peek(int offset) const ;
    
    
    // overloaded assignment operator
    //

    //-------------------------------------------------------
  // Name: =
  // PreCondition:  rhs should be Llama class Object
  // PostCondition: copies data from rhs to host object
  //---------------------------------------------------------
    const Llama<T,LN_SIZE>& operator=(const Llama<T,LN_SIZE>& rhs) ;
    
    
    //
    // Add your public member functions & public data mebers here:
    //

    //-------------------------------------------------------
  // Name: copyStack(const Llama<T,LN_SIZE>& otherStack)
  // PreCondition:  none
  // PostCondition: create host object and copy otherStack
  //---------------------------------------------------------
    void copyStack(const Llama<T,LN_SIZE>& otherStack);
    
private:
    
    bool isStackEmpty;
    bool isExtraNode;
    //
    // 
    //
    
    LlamaNode<T, LN_SIZE>* m_nodePtr;
    LlamaNode<T, LN_SIZE>* m_extraNode;
    int m_size;
    int m_capacity;
    int  m_top;
    int m_nodeSize;
    
    
} ;


#include "Llama.cpp"


#endif
