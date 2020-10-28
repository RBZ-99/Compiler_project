#include<stdio.h>
#include"typeExpression.h"
#include<stdbool.h>

# define MAX_VAR 100

void traverseParseTree(parseTree* t){
    
    if(t == NULL) return;
    
    //root

    while(t->sibling != NULL){
        traverseParseTree(t->sibling);
    }

    while(t != NULL){
        
        if(traverse->s.is_terminal == false){
            if(traverse->s.nt == DECLARATIONSTMT){

                //Populate the typeExpression table

            }else if(traverse->s.nt == ASSIGNMENTSTMT){

                //Check type compatibility from type expression table
            }
        }



        if(traverse->sibling != NULL) traverse = traverse->sibling;
        else traverse = traverse->parent->left_most_child->left_most_child
    }


}

void traverse(TREENODE *root) {
	if (root == NULL)
		return;
	
    //print_node(root);
	if(root->s.is_terminal == false){
        if(root->s.nt == DECLARATIONSTMT){

        //Populate the typeExpression table
        travreseDeclarestmt(root);

        }else if(root->s.nt == ASSIGNMENTSTMT){

        //Check type compatibility from type expression table
        traverseAssignmentStmt(root);
        }
    }


    if (root->leftmost_child)
		traverse(root->leftmost_child);
	

	if (root->leftmost_child)
  	{
		tree_node *temp = root->leftmost_child->sibling;

		while (temp != NULL) 
		{
			traverse(temp);
			temp = temp->sibling;
		}
  	}
}


void traverseDeclareStmt(TREENODE* root){
    if (root == NULL)
		return;

    //TERMINALS
    if(root->sym.is_terminal == true){
        
        //CHECKS VARID
        if(root->sym.t == VARID){

        }
        if(root->sym.nt == RANGES){
            root->parent.te.jt.dim++;
        } 

    }else{ //NON TERMINALS

        if(root->sym.nt == RANGES){


        }



    }



}



void printTypeexpressiontable(){    
    for(int i=0;i<3;i++){
        printf("%s %d %d\n", typeExpressionTable[i].name, typeExpressionTable[i].at, typeExpressionTable[i].bt);
    }
    return;
}

