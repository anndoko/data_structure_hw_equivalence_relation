//
//  Equivalence.cpp
//  DataStructure_homework4[equivalence]
//
//  Created by Yu-An Ko on 2016/5/7.
//  Copyright © 2016年 Yu-An Ko. All rights reserved.
//
#include "List.hpp"

void Equivalence()
//PHASE 1 - input: the equivalence pairs
//PHASE 2 - output: the equivalence classes
{
    //read the input file: equiv.in
    ifstream inFile("equiv.in", ios::in);
    
    //print the error message and exit if the file cannot be opened
    if(!inFile){
        cerr << "Cannot open input file" << endl;
        return;
    }
    
    int i, j, n;
    
    inFile >> n; //read the 1st line (number of objects) of the input file
    
    //initialize seq and out
    ListNodePtr* seq = new ListNodePtr[n];
    Boolean* out = new Boolean[n]; //Boolean out[12];
    for(i = 0; i < n; i++){
        seq[i] = 0;
        out[i] = FALSE;
    }
    
    while(inFile.good()){
        
        inFile >> i >> j;
        
        ListNode* x = new ListNode(j);
        x->link = seq[i];  //add j to seq[i]
        x->copy_link = seq[i];
        seq[i] = x;
                
        ListNode* y = new ListNode(i);
        y->link = seq[j];  //add i to seq[j]
        y->copy_link = seq[j];
        seq[j] = y;
    }
    
    //--------------- PHASE 2 ---------------//
    //output: the equivalence classes
    
    for(i = 0; i < n; i++)
        if(out[i] == FALSE) { //FALSE: not printed yet
            cout << endl << "A new class: " << i;
            out[i]= TRUE; //TRUE: printed
            ListNode* x = seq[i];
            ListNode* top = 0; //initialize the stack
            while(1) {		//find rest of class
                while(x) {	//process until x = 0
                    j = x->data;
                    if(out[j] == FALSE) {
                        cout<<", "<<j;
                        out[j] = TRUE;
                        ListNode *y = x->link;
                        x->link = top;
                        top = x;
                        x = y;
                    }
                    else x = x->link;
                } //end of while(x)
                if (!top) break; //exit when the stack is empty
                else{
                    x = seq[top->data];
                    top = top->link;  // unstack
                }
            } //end of while(1)
        } //end of if(out[i]=FALSE)
    
    //--------------- FREE THE MEMORY ---------------//
    cout << endl;
    
    for(i = 0; i < n; i++){
        while(seq[i]){
            cout << "here " << i << endl;
            ListNode* delnode = seq[i];
            seq[i] = delnode->copy_link;
            delete delnode;
        }
    }
    delete []seq;
    delete []out;
    
}; // end of equivalence