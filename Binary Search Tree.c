#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define CLEAR "CLS"

typedef struct btnode bintree;
struct btnode {
    int value;
    bintree *left;
    bintree *right;
};

// First Option - element insertion
bintree *insertElement(bintree **root, int value, bintree *res) {

    if(res == NULL){
        bintree *novo, *y = NULL, *aux=*root;
        novo = (bintree *) malloc(sizeof(bintree));
        novo->left = novo->right = NULL;
        novo->value = value;
        if (*root == NULL) *root = novo;
        else {
            while(aux != NULL) {
                y = aux;
                if (value < aux->value) aux = aux->left;
                else aux = aux->right;
            }
            if ((y != NULL) && (value < y->value)) y->left = novo;
            else y->right = novo;
        }
        printf("Element successfully added.\n");
        return(novo);
    }else printf("Repeated element.");

    return *root;
}

bintree *findMinimun(bintree *root){
	while(root->left != NULL) root = root->left;
	return root;
}

// Second Option - element removal
bintree *removeElement(bintree **root, bintree *rem){

    bintree *aux=*root,*ant=*root,*aux1=*root,*ant1=*root;
    int left, right;

    // Value Removal
    while(aux != NULL){

        /*
        First Case: node does note have children
        Second Case: node has one child
        Third Case: node has two children
        */

        // Searching for the value and the previous node
        if((aux->value) > (rem->value)){
            ant = aux;
            aux = aux->left;
            right = 0;
        }
        else if((aux->value) < (rem->value)){
            ant = aux;
            aux = aux->right;
            // Boolean value
            right = 1;

        // Otherwise, the value was found
        }else{
            // Checking how many children the node has
            // First Case
            if((aux->left == NULL) && (aux->right == NULL)){
				// If the value is the root
				if (aux == *root)
					*root = NULL;
				aux = NULL;
				// Boolean Test
				if (right)
                    ant->right = NULL;
				else
                    ant->left = NULL;
			}
			// Second Case - if the child is in the right
			else if (aux->left == NULL) {
				// Root must be deleted
				// Make the right value as the new root
				if (aux == *root)
					*root = aux->right;
				else if (right){
                    ant->right = aux->right;
				}
				else
                    ant->left = aux->right;
                aux = NULL;
			}
			// Second Case - if the child is in the left
			else if (aux->right == NULL) {
				if (aux == *root)
					*root = aux->left;
				else if (right){
                    ant->right = aux->left;
				}
				else
                    ant->left = aux->left;
                aux = NULL;
			}

			// Third Case
			else{
				ant1 = aux;

				// Searching for the left node most on the right part of the tree
				aux1 = aux->left;
				// Boolean value to indicate the path
				left = 1;

				while (aux1->right) {
					ant1 = aux1;
					aux1 = aux1->right;
					left = 0;
				}

				// Changing the pointer from the previous node that must be replaced
				if (aux1->left == NULL) {
					if (left == 0)
						ant1->right = NULL;
				  	else
						ant1->left = NULL;
				}
				else{
					if (left == 0)
                        ant1->right = aux1->left;
				  	else
                        ant1->left = aux1->left;
				}

				// Replacing value that must be removed
				if (aux == *root) {
					aux = aux1;
					aux->right = ant->right;
					aux->left = ant->left;
					*root = aux;
				}
				else if (right) {
					aux = aux1;
					aux->right = ant->right->right;
					aux->left = ant->right->left;
					ant->right = aux;
				}
				else {
					aux = aux1;
					aux->right = ant->left->right;
					aux->left = ant->left->left;
					ant->left = aux;
				}
				aux = NULL;
			}

        }
    }
    free(rem);
}

// Third Option - element search
bintree *binarieSearch(bintree *root, int search) {
    while (root != NULL) {
        if (search < root->value) root = root->left;
        else if (search > root->value) root = root->right;
        else return(root);
    }
    return(NULL);
}

void inOrder(bintree *root){
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ",root->value);
        inOrder(root->right);
    }
}

void postOrder(bintree *root){
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ",root->value);
    }
}

void preOrder(bintree *root){
    if (root != NULL) {
        printf("%d ",root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Fourth Option - list of elements
void listElements(bintree *root){
    printf("Choose a print method: 1.LPR, 2.LRP, 3. PLR\n\n");

    int op = getch();

    switch(op){
        case '1':   printf("LPR - In order\n");
                    inOrder(root);
                    break;
        case '2':   printf("LRP - Post-order\n");
                    postOrder(root);
                    break;
        case '3':   printf("LRP - Pre-order\n");
                    preOrder(root);
                    break;
        default:    printf("Unavailable option.\n");
                    break;
    }
}

void imprimeMenu() {
    printf("================================================================\n");
    printf("|                  Binary Search Tree                          |\n");
    printf("================================================================\n");
    printf("| Operations:                                                  |\n");
    printf("| 1) Add an Element                                            |\n");
    printf("| 2) Remove an Element                                         |\n");
    printf("| 3) Search for an Element                                     |\n");
    printf("| 4) List Elements                                             |\n");
    printf("| 5) Exit                                                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("Choose an option: ");
}

int main() {

    bintree *root, *res, *temp;
    root = NULL;
    char opcao = '0';
    int ok = 1;
    int value, search;

    while(ok){
        system(CLEAR);
        imprimeMenu();
        opcao = getch();

        switch(opcao) {

            case '1':   printf("Add an element.\n\n");
                        printf("Type the element to be added: ");
                        scanf("%d", &value);

                        res = binarieSearch(root, value);

                        insertElement(&root,value, res);

						getch();
						break;

            case '2': 	printf("Remove an element.\n\n");
                        printf("Type the element to be deleted: ");
                        scanf("%d", &value);

                        temp = binarieSearch(root, value);

                        if(temp == NULL) printf("Element not found.\n");
                        else{
                            removeElement(&root,temp);
                            printf("Element successfully removed.\n");
                        }

						getch();
						break;

            case '3': 	printf("Search for an element.\n\n");

                        printf("Type the element to be searched: ");
                        scanf("%d", &search);

                        res = binarieSearch(root, search);

                        if(res == NULL){
                            printf("Element not found.");
                        }else{
                            printf("Element %d found.", search);
                        }

						getch();
						break;

            case '4': 	printf("List elements.\n\n");
                        listElements(root);

                        getch();
						break;

            case '5': 	printf("End of execution.\n");
                        ok = 0;

                        getchar();
						break;

            default: 	printf("\n\nUnavailable option.");
						getchar();
						break;
        }
    }

    return 0;

}
