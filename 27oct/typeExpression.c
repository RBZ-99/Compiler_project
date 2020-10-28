#include<stdio.h>
#include"typeExpression.h"
#include<stdbool.h>
#include"treenode.h"
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

void traverse(tree_node *root) {
	if (root == NULL)
		return;
	
    //print_node(root);
	if(root->sym.is_terminal == false){
        if(root->sym.nt == DECLARATIONSTMT){

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
        else if(root->sym.t == RANGE){
            root->parent.te.jt.dim++;
        }else if(root->sym.t == INTEGER){

            if(root->parent->sym.nt == TYPE){

                char* t = "INTEGER";
                strncpy (root->parent->te.primTE.type,t,sizeof(t));

            }else{

                char* t = "INTEGER";
                strncpy (root->parent->te.jt.type,t,sizeof(t));

            }
        }else if(root->sym.t == REAL){
            
            char* t = "REAL";
            strncpy (root->parent->te.pt.type,t,sizeof(t));

            
        }else if(root->sym.t == BOOLEAN ){
            
            char* t = "BOOLEAN";
            strncpy (root->parent->te.primTE.type,t,sizeof(t));
            
        }else if(root->sym.t == SEMICOL){

            //We are the end of the line

        } 

    }else{ //NON TERMINALS

        if(root->sym.nt == RANGES){


        }else if(root->sym.nt == ){


        }else if(root->sym.nt == ){


        }



    }
        	

	if (root->leftmost_child)
  	{
		tree_node *temp = root->leftmost_child->sibling;

		while (temp != NULL) 
		{
			traverse(temp);
			temp = temp->sibling;
		}
  	}

    return;
}





void printTypeexpressiontable(){    
    for(int i=0;i<3;i++){
        printf("%s %d %d\n", typeExpressionTable[i].name, typeExpressionTable[i].at, typeExpressionTable[i].bt);
    }
    return;
}

