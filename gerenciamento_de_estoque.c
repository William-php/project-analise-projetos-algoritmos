#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Aluno: William dos Santos Ferreira*/

//Estrutura de produto iniciada*
struct Product {
    int id;
    char name[32];
    struct Product *next;
};

//função para inserir na lista | **head = ponteiro de ponteiro da lista de produtos | id = identificador unico do produto
void push(struct Product **head, int id) {
    struct Product *product = (struct Product*)malloc(sizeof(struct Product)); //alloca um espaço de memória do tamanho da estrutura Product
    
    (*product).id = id; //insere o id no produto

    printf("Digite o nome do produto: "); 
    scanf("%s", (*product).name); //insere o nome no produto
    

    (*product).next = *head; //poem o produto novo para apontar para o cabeçalho da lista dos produtos
    (*head) = product; //o cabeçalho agora se inicia a a partir do produto novo
}

//print todos os produtos
void print(struct Product *head) {
    struct Product *products = head; //poem esta variável para receber uma cópia da lista

    while (products != NULL) {
        //enquanto a lista não chegar em um objeto vazio ela segue
        printf("Produto:\nid: %d\nnome: %s\n", (*products).id, (*products).name); 
        products = (*products).next;//o item atual passa para o próximo item da lista
    }
}
//busca produto por nome
void search(struct Product *head) {
    struct Product *products = head;
    char productName[32]; //variável para o usuário digitar o produto que ele deseja
    printf("Digite o nome do produto a ser buscado: ");
    scanf("%s", productName);    
    while (products != NULL) {
        if (strcmp(productName, (*products).name) == 0) //só retorna se o produto que ele digitou for igual ao da lista
            printf("Produto:\nid: %d\nnome: %s\n", (*products).id, (*products).name);
        products = (*products).next;
    }

}
//retorna o tamanho total da lista
int sizeList(struct Product *head) {
    struct Product *products = head;
    int size = 0;

    while (products != NULL) {
        size++;
        products = (*products).next;
    }

    return size;
}
//retorna produto por sua posição na lista
int positionProduct(struct Product *head) {
    struct Product *products = head;
    int position = 0; //posição do produto se inicia em 0
    char productName[32]; //variável para o usuário buscar o produto

    printf("Digite o nome do produto: ");
    scanf("%s", productName);
    while (products != NULL) {
        position++;//a cada iteração a posição ganha +1 para representar a posição do produto pesquisado na lista
        if (strcmp(productName, (*products).name) == 0) {
            return position; //se achar o produto retorna sua posição na lista
        }
        products = (*products).next;
    }
    //se não achar a posição é 0;
    position = 0;
    return position;
}
//apaga um produto da lista de acordo com sua descrição
void deleteN(struct Product **head, int position) {
    printf("Posição do produto: %d\n", position);
    struct Product *prevProducts = *head; //uma lista de um ponto anterior
    struct Product *currentProducts = *head; //lista atual
    //a busca é baseada na posição do produto
    for (int i = 0; i < position; i++) {
        
        if (i == 0 && position == 1) {
            *head = (**head).next; //se o produto estiver na primeira posição, o cabeçalho da lista aponta para o próximo item
            free(currentProducts); //apaga o primeiro item da lista
        } else {
            //se estiver em n-ésima posição e o atual produto for diferente de null
            if (i == position - 1 && currentProducts) {
                (*prevProducts).next = (*currentProducts).next; //a lista anterior terá seu item atual apontando para o próximo item da lista 'atual' ex: anterior: 1 => 2; atual = 2 =>3 apaga o 2 e o 1 aponta para 3
                free(currentProducts); //é apagado o item da posição atual
            } else {
                prevProducts = currentProducts; //lista anterior é atualizada
                if (prevProducts == NULL) break; //se chegar em NULL então a acaba brincadeira
                currentProducts = (*currentProducts).next; //lista atual é passada para o próximo item
            }
        }
    }   
}

// struct Product *sort(struct Product *head) {
//     struct Product *products = (struct Product*)malloc(sizeof(struct Product));
//     struct Product *pReturn = (struct Product*)malloc(sizeof(struct Product));
//     struct Product *productsAux;
//     char str[32], lastStr[32];
//     int n = sizeList(head), i = 0;

//     for (i; i < n; i++) {
//         productsAux = head;
//         if (productsAux != NULL) strcpy(str, (*productsAux).name);
//         while (productsAux != NULL) {
//             if (strcmp(str, (*productsAux).name) > 0 && n == 0) {                
//                 (*products).id = (*productsAux).id;
//                 strcpy((*products).name, (*productsAux).name);
//                 (*products).next = (struct Product*)malloc(sizeof(struct Product));
//                 strcpy(lastStr, str);
//             } else {
//                 if (strcmp(lastStr, (*productsAux).name) > 0 && strcmp((*products).name, (*productsAux).name) != 0) {
//                     (*products).id = (*productsAux).id;
//                     strcpy((*products).name, (*productsAux).name);
//                     (*products).next = (struct Product*)malloc(sizeof(struct Product));
//                 }
//                 (*products).id = (*productsAux).id;
//                 strcpy((*products).name, str);
//                 (*products).next = NULL;
//             }
//             productsAux = (*productsAux).next;
//         }
//         if (i == 0) pReturn = products;
//         head = (*head).next;
//         products = (*products).next;
        
//         //products = (*products).next;
//     }
//     printf("products: %p\n", products);
//     return pReturn;
// }

//Algoritmo de organização, ordem alfabética
void sort(struct Product **head) {
    //cria dois ponteiros de listas auxiliares para ajudarem na operação
    struct Product *secondProducts, *thirdProducts;
    char name[32]; //variável para armazenar o nome do produto
    int id; //variávael para armazenar id do produto
    secondProducts = *head; //a segunda lista recebe a lista iniciado do cabeçalho

    //enquanto esta segunda lista for diferente null, segue
    while (secondProducts != NULL) {
        thirdProducts = (*secondProducts).next; //a terceira lista recebe o item posterior da lista, ou seja  a terceira lista 'começa' do segundo item da lista
        //enquanto esta lista não chegar ao fim, segue
        while (thirdProducts != NULL) {
            //a função strcmp é responsável por compara strings, neste caso, se o primeiro argumento tiver uma string de maior que do segundo argumento, exemplo 'b' > 'a', a condição será uma verdade
            if (strcmp((*secondProducts).name, (*thirdProducts).name) > 0) {
                strcpy(name, (*secondProducts).name); //strcpy, copia uma string para uma variável, neste caso a name = (*secondProducts).name
                id = (*secondProducts).id; //id auxiliar recebe o id do secondProducts
                strcpy((*secondProducts).name, (*thirdProducts).name); //aquele velho quicksort, onde o o nome do produto recebe do produto à frente, pois o produto de third tem um produto que a letra é 'menor'
                (*secondProducts).id = (*thirdProducts).id; //recebe o id
                //o produto da frente recebe o valor da anterior
                strcpy((*thirdProducts).name, name); 
                (*thirdProducts).id = id; 
            }
            thirdProducts = (*thirdProducts).next; // passa para o próximo produto, para realizar as trocas
        }

        secondProducts = (*secondProducts).next;
    }
}

int main() {
    struct Product *products;
    int id = 1, options, size;
    char repeat[1], repeatOpt[1];
    products = NULL;
    
    //SYSTEM
    do {
        
        printf("1 - Para inserir na lista de produtos\n2 - Para visualizar lista\n3 - Para buscar elemento especifico\n4 - Tamanho da lista\n5 - Excluir item da lista\n6 - Organização por ordem alfabética\n");
        scanf("%d", &options);
        
        switch (options) {
            case 1:
                push(&products, id);    
                id++;
                break;
            case 2: 
                print(products);
                break;
            case 3:
                search(products);
                break;
            case 4:
                size = sizeList(products);
                printf("Tamanho da lista: %d\n", size);
                break;
            case 5:
                deleteN(&products, positionProduct(products));
                break;
            case 6:
                sort(&products);
                break;
            default:
                printf("Ações com estoque encerrados\n");
                break;
        }
        
        printf("Deseja continuar ? s - sim | n - não\n");
        scanf("%s", repeat);

    } while (strcmp("s", repeat) == 0);

    printf("Fim\n");
    return 0;
}