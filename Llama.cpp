/*****************************************
 ** File:    Llama.cpp
 ** Project: CMSC 341 Project 1, Fall 2016
 ** Author:  Hemang Bhatt
 ** Date:    10/4/16
 ** Section: 03
 ** E-mail:  hb6@umbc.edu
 **
 ** This file contains Llama class implemention.
 ** See the Llama.h file for function header.
 ***********************************************/

#ifndef LLAMA_CPP
#define LLAMA_CPP

#include <iostream>
#include <string>

#include "Llama.h"
#include "LlamaNode.h"
using namespace std;


// Create LlamaNode and Initialize member variables

template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama()
{
    m_top = -1;
    m_size = 0;
    m_nodePtr = new LlamaNode<T, LN_SIZE>;
    m_nodeSize = LN_SIZE;
    m_capacity = m_nodeSize;
    m_nodePtr->m_next = NULL;
    m_extraNode = NULL;
    isStackEmpty = true;
    isExtraNode = false;
    
}


// copy constructor
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama(const Llama<T,LN_SIZE>& other)
{
  // creates host object and copies other stack
    copyStack(other);
}

// deallocate dynamically allocated node
template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::~Llama()
{
    if (isExtraNode)
    {
        delete m_extraNode;
	m_extraNode = NULL;
    }
    
    while (m_nodePtr != NULL)
    {
        LlamaNode<T, LN_SIZE>* temp;
        temp = m_nodePtr->m_next;
        delete m_nodePtr;
        m_nodePtr = temp;
        
    }
    m_nodePtr = NULL;
    
}

// return the size of the stack
template <class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size() { return m_size; }

// print necessary information to debug
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>:: dump()
{
    
    cerr << endl << "***** " << "Llama Stack Dump " << "*****" << endl;
    cerr << "LN_SIZE = " << m_nodeSize << endl;
    cerr << "# of items in the stack = " << m_size << endl;
    cerr << "# of nodes created  = " << m_nodePtr-> newCount << endl;
    cerr << "# of nodes destroyed = " << m_nodePtr-> deleteCount << endl << endl;
    
    
    if (!isExtraNode)
    {
        cerr << "This stack does not have an extra node." << endl << endl;
    }
    
    else if (isExtraNode)
    {
        cerr << "This stack has an extra node: " << m_extraNode << endl << endl;
    }
    
    int tempPos = m_top;

    // prints out nodes address and values

    if (m_nodePtr != NULL)
    {
        
        LlamaNode<T, LN_SIZE>* temp = m_nodePtr;
        cerr << "Stack contents, top to bottom" << endl;
        
        do
        {
            cerr << "----- " << temp << " -----" <<  endl;
       
            for (int i = tempPos; i >= 0; i--)
            {
                cerr << temp->arr[i] << endl;
            }
            
            temp = temp->m_next;
            tempPos = m_nodeSize - 1;
            
        } while(temp != NULL);

    }
    
    
    cerr << "----- " << "bottom of stack" << " -----" << endl << endl;
    cerr << "*****************************************" << endl;
}
 


template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>:: push(const T& data)
{

    
    
    /*
     if top is less than node size
     push data and increment top
     */
    
    
    if (m_top < (m_nodeSize-1))
    {

        m_nodePtr->arr[++m_top] = data;
        ++m_size;
        
        //cout << m_nodePtr->arr[m_top] << endl;
    }
    
    // if node is full
    else
    {
        // check for the extra Node
        
        if(isExtraNode)
        {
            //"ExtraNode not equal to null"
            
            m_extraNode->m_next = m_nodePtr;
            m_nodePtr = m_extraNode;
            m_extraNode = NULL;
            isExtraNode = false;
            m_top = -1;
            m_nodePtr->arr[++m_top] = data;
            ++m_size;
            

        }

	// if there is no extra node, create new node
        else if (!isExtraNode)
        {
            //cout << "Extra Node does not exist" << endl;
            
            LlamaNode<T, LN_SIZE>* temp = new LlamaNode<T, LN_SIZE>;
            m_capacity += m_nodeSize;
            temp->m_next = m_nodePtr;
            m_nodePtr = temp;
            m_top = -1;
            m_nodePtr->arr[++m_top] = data;
            ++m_size;
            
            
            
        }
        
    }

    isStackEmpty = false;
}


// pop items if the stack is not empty
// if stack empty, throw llamaUnderflow
// if extraNode exist and current node is less than half
// then delete extraNode
template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>:: pop()
{
    if ((m_nodePtr->m_next == NULL) && (m_top == -1))
    {
        isStackEmpty = true;
    }
    
    
    if (isStackEmpty)
    {
        throw LlamaUnderflow ("popping empty stack");
    }
    

    else if (m_top == -1)
    {
        if ((!isExtraNode) && (m_nodePtr->m_next != NULL))
        {
            m_extraNode = m_nodePtr;
            m_nodePtr = m_nodePtr->m_next;
            m_top = m_nodeSize - 1;
            isExtraNode = true;
        }
    }
    
    T pop = m_nodePtr->arr[m_top--];
    m_size--;
    
    if ( (m_top < int (m_nodeSize/2)) && isExtraNode)
    {
        m_extraNode->m_next = NULL;
        delete m_extraNode;
        m_capacity -= m_nodeSize;
        m_extraNode = NULL;
        isExtraNode = false;
    }
    
    if ((m_top == -1) && (!isExtraNode) && (m_nodePtr->m_next != NULL) )
    {
        isExtraNode = true;
        m_extraNode = m_nodePtr;
        m_nodePtr = m_nodePtr -> m_next;
        m_top = m_nodeSize - 1;
    }

    return pop;
}


//  (top) A B C D -> A A B C D

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dup()
{
    if (isStackEmpty)
    {
        throw LlamaUnderflow("Stack is empty");
    }
    else
        this->push(m_nodePtr->arr[m_top]);
    
}

//  (top) A B C D -> B A C D
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>:: swap()
{
    if (m_size < 2)
    {
        throw LlamaUnderflow("Stack has less than two items. Can not swap");
    }
    
    else
    {
        T temp1 = this->pop();
        T temp2 = this->pop();
        this->push(temp1);
        this->push(temp2);
    }
}

//  (top) A B C D -> C A B D
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE> :: rot()
{
    
    if (m_size < 3)
    {
        throw LlamaUnderflow("Stack has less than three items. Can not rotate.");
    }
    
    else
    {
        
        T top1 = this->pop();
        T top2 = this->pop();
        T top3 = this->pop();
        
        this->push(top2);
        this->push(top1);
        this->push(top3);
    
    }
    
}


// return the elements at offset position
template <class T, int LN_SIZE>
T  Llama<T, LN_SIZE> :: peek(int offset) const
{
    //cerr <<" Inside peek" << endl;
    
    
    if (offset > m_size - 1)
    {
        throw LlamaUnderflow("To large offset for peek");
    }
    
    //bool topNode = true;
    int counter = 0;
    //int node = 0;
    
    LlamaNode<T, LN_SIZE>* temp = m_nodePtr;
    
    if (offset < (m_size % m_nodeSize))
    {
        return temp->arr[m_top-offset];
    }
    
    // Next Node
    temp = temp->m_next;
    int limit = ((m_size % m_nodeSize) + m_nodeSize) ;
    //pos =
    
    while (offset > limit-1)
    {
        temp = temp->m_next;
        limit += m_nodeSize;
        counter++;
    }

    
    return temp->arr[limit-offset-1];
    
    
}

// overloaded assignment operator
// if not the same object, destroy
// and then call copyStack
template <class T, int LN_SIZE>
const Llama<T, LN_SIZE>& Llama<T, LN_SIZE>:: operator=(const Llama<T,LN_SIZE>& rhs)
{
    if (this != &rhs) //avoid self-copy
      {
	// destructor code

	if (isExtraNode)
	  {
	    delete m_extraNode;
	    m_extraNode = NULL;
	  }

	while (m_nodePtr != NULL)
	  {
	    LlamaNode<T, LN_SIZE>* temp;
	    temp = m_nodePtr->m_next;
	    delete m_nodePtr;
	    m_nodePtr = temp;

	  }

	m_nodePtr = NULL;
	// ends here



        copyStack(rhs);
      }

    return *this;
}



// create and copy stack from otherStack
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::copyStack(const Llama<T, LN_SIZE>& otherStack)
{
    

    LlamaNode<T, LN_SIZE>* tempNode = NULL;
    LlamaNode<T, LN_SIZE>* topNode = NULL;
    LlamaNode<T, LN_SIZE>* temp = NULL;
    
    // create necessary node and copy data
    temp = new LlamaNode<T, LN_SIZE>;
    topNode = temp;
    m_nodePtr = temp;
    // save address of temp into top;
    if(otherStack.isExtraNode)
    {
        tempNode = new LlamaNode<T, LN_SIZE>;
        m_extraNode = tempNode;
        m_extraNode->m_next = topNode;
        isExtraNode = true;
    }
    
    if (!otherStack.isStackEmpty)
    {

      for (int i = 0; i < LN_SIZE; i++)
	{
	  m_nodePtr->arr[i] = otherStack.m_nodePtr->arr[i]; 
	}
        
        LlamaNode<T, LN_SIZE>* tempOther = otherStack.m_nodePtr;
        
        while (tempOther->m_next != NULL)
        {
            temp = new LlamaNode<T, LN_SIZE>;
            temp -> m_next = NULL;
            m_nodePtr->m_next = temp;
            m_nodePtr = m_nodePtr -> m_next;
            temp = NULL;
            tempOther = tempOther->m_next;
            for (int i = 0; i < LN_SIZE; i++ )
            {
                m_nodePtr->arr[i] = tempOther->arr[i];
            }
        }
        
    }
    
    
    isStackEmpty = otherStack.isStackEmpty;
    isExtraNode = otherStack.isExtraNode;
    
    m_nodePtr = topNode;
    
    m_size = otherStack.m_size;
    m_capacity = otherStack.m_capacity;
    m_top = otherStack.m_top;
    m_nodeSize = otherStack.m_nodeSize;
    
    
}


#endif
