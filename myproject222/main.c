#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define maximum_size 83     //prime number

struct Node{
    char name[50];
    char active_ingredient[50];
    char category[50];
    char indication[50];
    char expiry_date[10];
    int count;
    char company[40];
    int IndicationsN;
    char indicationS[5][50];
    struct Node* left;
    struct Node* right;
};
typedef struct Node* NodesBst;

typedef struct node {
    char name[50];
    char active_ingredient[50];
    char category[50];
    char indication[50];
    char expiry_date[10];
    int count;
    char company[40];
}HashNode;

typedef struct HashTable {
    HashNode* data[maximum_size];
    int size;
}HashTable;

//functions prototypes
NodesBst MakeEmpty( NodesBst root );
NodesBst searching( char BstName[], NodesBst root );
NodesBst MIN( NodesBst root );
NodesBst MAX( NodesBst root );
NodesBst Insert( char BstName[], char BstActive_ingredient[], char BstCategory[],char BstIndication[],
                 char BstExpiry_date[], int BstCount, char BstCompany[], NodesBst root );
NodesBst Delete( char BstName[], NodesBst root );
NodesBst ReadMeds ( NodesBst root );
void Add_Medicine( NodesBst root );
void Update_Medicine( NodesBst root );
void Update_Count( NodesBst root );
void Print_Medicine( NodesBst root );
void List_Cateagory ( NodesBst root, char BstCategory[] );
void List_Indications( NodesBst root, char BstIndication[]);
NodesBst Delete_Company( char BstCompany[], NodesBst root );
void Save_medicine( NodesBst root, FILE *out );
NodesBst searchingCompany( char BstCompany[], NodesBst root );
int FunctionH(char* name);
void Print_Hash(HashTable* table);
void Hash_Size(HashTable* table);
void FunctionHprint(HashTable* table);
void Add_Record(HashTable* table, HashNode* med);
void searching_Hash(HashTable* table, char* name);
void Delete_Hash(HashTable* table, char* name);
void Save_Hash(HashTable* table);

void main() {
    NodesBst root= NULL;
    root= ReadMeds( root);
    FILE *out, *in;
    char line[150];
    printf("\t\t\t***********************************\n");
    printf("\t\t\t** WELCOME TO main Menu **\n");
    printf("\t\t\t***********************************\n");
    printf("\t\t\t             Khalid Sami \n");
    printf("\t\t\t***********************************\n");
        while(1) {

            printf("\t\t\t\t\tMENU\n\n\n");
            printf("\t1----- Add a medicine\n");
            printf("\t2----- Update a medicine\n");
            printf("\t3----- Update the count\n");
            printf("\t4----- Print all the medicines\n");
            printf("\t5-----List medicines by indication\n");
            printf("\t6----- List medicines by category\n");
            printf("\t7-----Delete a medicine\n");
            printf("\t8-----Delete medicines by company\n");
            printf("\t9----- Save medicines\n");
            printf("10----- GO TO HASHTABLE MAIN MENU!! UPLOAD PHARAMCY.TXT\n");

            printf("0. Exit\n");
            printf("***********************************************************************\n");
            int choice;
            printf("Choose a number from 1-10!!: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    Add_Medicine(root);
                    break;
                case 2:
                    Update_Medicine(root);
                    break;
                case 3:
                    Update_Count(root);
                    break;
                case 4:
                    Print_Medicine(root);
                    break;
                case 5:
                    printf("indication: ");
                    char BstIndication[50];
                    scanf("%s", BstIndication);
                    List_Indications(root, BstIndication);
                    break;
                case 6:
                    printf("category: ");
                    char BstCategory[50];
                    scanf("%s", BstCategory);
                    List_Cateagory (root, BstCategory);

                    break;
                case 7:
                    printf("Name of medicine you want to delete: ");
                    char BstName[50];
                    scanf("%s", BstName);
                    root = Delete(BstName, root);
                    break;
                case 8:
                    printf("name of company want to delete: ");
                    char BstCompany[40];
                    scanf("%s", BstCompany);
                    root = Delete_Company(BstCompany, root);
                    break;
                case 9:
                    printf("your file has been save succesfully  :D!!");
                    out = fopen("Pharmacy.txt", "w");
                    Save_medicine( root, out );
                    fclose(out);
                    break;
                case 0:
                    exit(0);
            case 10:
                in = fopen("Pharmacy.txt", "r");
                HashTable* table;
                table->size = 0;
                if (in == NULL) {
                    printf("Pharmacy.txt doesnt open!! \n");
                    exit(1);
                }
                for (int i = 0; i < maximum_size; i++) {
                    table->data[i] = NULL;
                }
                while(fgets(line,sizeof(line), in) != NULL){
                    HashNode* med = (HashNode*) malloc(sizeof(HashNode));
                    for (int i = 0; i < 150; i++) {
                        if (line[i] == ' ')
                            line[i] = '_';
                    }
                    sscanf(line, "%[a-zA-Z_0-9]:%[a-zA-Z_0-9]:%[a-zA-Z_0-9]:%[^:]:%[^:]:%d:%[a-zA-Z_0-9]",
                           med->name, med->active_ingredient, med->category, med->indication,
                           med->expiry_date, &med->count, med->company);
                    Add_Record(table, med);
                }
                fclose(in);
                while(1){
                    HashNode* temp = (HashNode*) malloc(sizeof(HashNode));
                    char BstName2[50];
                    printf("\t\t\t***********************************\n");
                    printf("\t\t\t** WELCOME TO Hash table Menu **\n");
                    printf("\t\t\t***********************************\n");
                    printf("\t\t\t             Khalid Sami \n");
                    printf("\t\t\t***********************************\n");
                    printf("\t\t\t\t\tMENU\n\n\n");
                    printf("\t1. Print the hash table\n");
                    printf("\t2. Insert a NEW record\n");
                    printf("\t3. Print function\n");
                    printf("\t4. Print the size of the hash table\n");
                    printf("\t5. Search for a data\n");
                    printf("\t6. Delete a data\n");
                    printf("\t7. Save\n");
                    printf("\t0. Exit\n");
                    printf("***********************************************************************\n");
                    printf("Choose an option: ");
                    scanf("%d", &choice);
                    printf("**********************************************************************\n");
                    switch (choice) {
                        case 1:
                            Print_Hash(table);
                            break;
                        case 2:
                            printf("Enter the name of the medicine: ");
                            scanf("%s", temp->name);
                            printf("Enter the active ingredient: ");
                            scanf("%s", temp->active_ingredient);
                            printf("Enter the category: ");
                            scanf("%s", temp->category);
                            printf("Enter the indication: ");
                            scanf("%s", temp->indication);
                            printf("Enter the expiry date: ");
                            scanf("%s", temp->expiry_date);
                            printf("Enter the count: ");
                            scanf("%d", &temp->count);
                            printf("Enter the company: ");
                            scanf("%s", temp->company);
                            Add_Record(table, temp);
                            break;
                        case 3:
                            FunctionHprint(table);
                            break;
                        case 4:
                            Hash_Size(table);
                            break;
                        case 5:
                            printf("name of the medicine to searching: ");
                            scanf("%s", BstName2);
                            searching_Hash(table, BstName2);
                            break;
                        case 6:
                            printf("medicine you want to delete: ");
                            scanf("%s", BstName2);
                            Delete_Hash(table, BstName2);
                            break;
                        case 7:
                            Save_Hash(table);
                            break;
                        case 0:
                            exit(0);
                        default:
                            printf("WRONGGGG!!\n");
                            break;
                    }
                }
            default:
                printf("TRY AGAIN FROM choose A NUMBER IN menu\n");
                break;
        }
    }
}


NodesBst Insert( char BstName[], char BstActive_ingredient[], char BstCategory[],char BstIndication[],
                 char BstExpiry_date[], int BstCount, char BstCompany[], NodesBst root ){
    if( root == NULL ){
        root = (struct Node*) malloc( sizeof( struct Node ) );
        if( root == NULL)
            printf("NO space");
        else{
            strcpy(root->name, BstName);

            strcpy(root->active_ingredient, BstActive_ingredient);
            strcpy(root->category, BstCategory);
            strcpy(root->indication, BstIndication);
            char* token;
            int i=0;
            token = strtok(BstIndication, ",");
            while(token != NULL){
                root->IndicationsN++;
                strcpy(root->indicationS[i], token);
                token = strtok(NULL, ",");
                i++;
            }
            strcpy(root->expiry_date, BstExpiry_date);
            root->count = BstCount;
            strcpy(root->company, BstCompany);
            root->left = root->right = NULL;
        }
    }
    else if( strcmp(BstName, root->name) < 0 ){
        root->left = Insert( BstName, BstActive_ingredient, BstCategory,
                             BstIndication,BstExpiry_date, BstCount, BstCompany, root->left );
    }
    else if( strcmp(BstName, root->name) > 0 ){
        root->right = Insert( BstName, BstActive_ingredient, BstCategory,
                              BstIndication,BstExpiry_date, BstCount, BstCompany, root->right );
    }
    return root;
}
//non-recursive implementation of the MIN
NodesBst MIN( NodesBst root ){
    if( root != NULL )
        while( root->left != NULL )
            root = root->left;
    return root;
}

//non-recursive implementation of MAX
NodesBst MAX( NodesBst root ){
    if( root != NULL )
        while( root->right != NULL )
            root = root->right;
    return root;
}

NodesBst Delete( char BstName[], NodesBst root ){
    NodesBst Cells;
    if( root == NULL )
        printf( "Medicine not found\n" );
    else if( strcmp( BstName, root->name ) < 0 )    //left >>>>
        root->left = Delete( BstName, root->left );
    else if( strcmp( BstName,root->name ) > 0 )    //right>>>>
        root->right = Delete( BstName, root->right );
    else
    if( root->left && root->right )//if it has 2 children
    {
        //replace with smallest in right sub
        Cells= MIN( root->right );
        strcpy(root->name, Cells->name);
        strcpy(root->active_ingredient, Cells->active_ingredient);
        strcpy(root->category, Cells->category);
        strcpy((char *) root->indication, (char *) Cells->indication);
        strcpy(root->expiry_date, Cells->expiry_date);
        root->count = Cells->count;
        strcpy(root->company, Cells->company);
        root->right = Delete( root->name, root->right );
    }
    else    //if it has no children or only 1
    {
        Cells= root;
        if( root->left == NULL )
           //0 children
            root = root->right;
        else if( root->right == NULL )
            root = root->left;
        free( Cells);
    }
    return root;
}

//read data and put it in the BST
NodesBst ReadMeds( NodesBst root ) {
    FILE *in;
    char BstName[50], BstActive_ingredient[50], BstCategory[50], BstIndication[40], BstExpiry_date[8], BstCompany[40];
    int BstCount;
    in = fopen("Meds.txt", "r");
    if (in == NULL) {
        printf("file no opening !!!\n");
        exit(1);
    }
    char line[150];
    while (fgets(line, sizeof(line), in) != NULL) {
        for (int i = 0; i < 150; i++) {
            if(line[i] == ' ')//beacuse file doesnt read spaces so i replace a space with a _
                line[i] = '_';
        }
        sscanf(line, "%[a-zA-Z0-9_]:%[a-zA-Z0-9_]:%[a-zA-Z0-9_]:%[a-zA-Z0-9,_]:%[a-zA-Z0-9/]:%d:%[a-zA-Z0-9_]", BstName, BstActive_ingredient, BstCategory, BstIndication, BstExpiry_date, &BstCount, BstCompany);
        root = Insert(BstName, BstActive_ingredient, BstCategory, BstIndication, BstExpiry_date, BstCount, BstCompany, root);
    }
    fclose(in);
    return root;
}

//add a new medicine to the BST
void Add_Medicine( NodesBst root ){
    char BstName[50], BstActive_ingredient[50], BstCategory[50], BstIndication[40], BstExpiry_date[8], BstCompany[40];
    int BstCount;
    printf("Enter the name of the the new medicine: ");
    scanf("%s", BstName);
    printf("Enter the active ingredient: ");
    scanf("%s", BstActive_ingredient);
    printf("Enter the category: ");
    scanf("%s", BstCategory);
    printf("Enter the indication: ");
    scanf("%s", BstIndication);
    printf("Enter the expiry date: ");
    scanf("%s", BstExpiry_date);
    printf("Enter the count: ");
    scanf("%d", &BstCount);
    printf("Enter the company: ");
    scanf("%s", BstCompany);
    root = Insert(BstName, BstActive_ingredient, BstCategory, BstIndication, BstExpiry_date, BstCount, BstCompany, root);
}

//update a medicine with new data
void Update_Medicine( NodesBst root ){
    char BstName[50], BstActive_ingredient[50], BstCategory[50], BstIndication[40], BstExpiry_date[8], BstCompany[40];
    int BstCount;
    printf("Enter the name of the medicine you want to update: ");
    scanf("%s", BstName);
    root = searching(BstName, root);//search for the name of medicine
    if(root == NULL){
        printf("Medicine not found\n");//if medicine is not in Bst
    }
    else{
        root = Delete(BstName, root);//if its found we delete the old data and get new data
        printf("Enter the new name of the medicine: ");
        scanf("%s", BstName);
        printf("Enter the new active ingredient: ");
        scanf("%s", BstActive_ingredient);
        printf("Enter the new category: ");
        scanf("%s", BstCategory);
        printf("Enter the new indication: ");
        scanf("%s", BstIndication);
        printf("Enter the new expiry date: ");
        scanf("%s", BstExpiry_date);
        printf("Enter the new count: ");
        scanf("%d", &BstCount);
        printf("Enter the new company: ");
        scanf("%s", BstCompany);
        root = Insert(BstName, BstActive_ingredient, BstCategory, BstIndication, BstExpiry_date, BstCount, BstCompany, root);
    }
}
//searching for a data in BST
NodesBst searching( char BstName[], NodesBst root ){
    if( root == NULL )//if it is not found return null
        return NULL;
    if( strcmp( BstName, root->name ) < 0 )//we searching in the tree if its left or right node
        return searching( BstName, root->left );
    else if( strcmp( BstName, root->name) > 0 )// here is right
        return searching( BstName, root->right );
    else
        return root;
}

//update medicine count
void Update_Count( NodesBst root ){
    char BstName[50];
    int BstCount;
    printf("Enter the name of the medicine you wnt to update count: ");
    scanf("%s", BstName);
    root = searching(BstName, root);//we search for the medicine
    if(root == NULL){
        printf("Medicine not found\n");// if medicine not found
    }
    else{
        printf("Enter the new count: ");
        scanf("%d", &root->count);//we found the medicine and update the new count
    }
}

//function to print all the medicine in order
void Print_Medicine( NodesBst root ){
    if( root ){
        Print_Medicine( root->left );//we start from the left
        printf("%s %s %s %s %s %d %s\n", root->name, root->active_ingredient, root->category, root->indication,
               root->expiry_date, root->count, root->company);
        Print_Medicine( root->right );
    }
}

//function to list category of a medicine and find if it is found
void List_Cateagory ( NodesBst root, char BstCategory[]){
    if( root != NULL ){
        List_Cateagory ( root->left, BstCategory);
        if(strcmp(root->category, BstCategory) == 0){//we try finding the category
            if(root->count == 0){
                printf("%s - not found", root->name); //if the category is not found in any of meds
            }
            else{
                printf("has it = %s\n", root->name);//if its found
            }
        }
        List_Cateagory ( root->right, BstCategory);
    }
}

//function to list indication of a medicine and find if it is found
void List_Indications( NodesBst root, char BstIndication[]){
    if( root != NULL ){
        List_Indications( root->left, BstIndication);
        for (int i = 0; i < 5; ++i) {
            if(strcmp(root->indicationS[i], BstIndication) == 0){
                if(root->count == 0){
                    printf("%s - not found", root->name);
                }
                else{
                    printf("has it =%s\n", root->name);
                }
            }
        }
        List_Indications( root->right, BstIndication);
    }
}

NodesBst Delete_Company( char BstCompany[], NodesBst root ){
// This function will delete all the nodes of a specific company
    while (1){
        NodesBst Cells=NULL;
// searchingCompany function will search for the company in the BST
        Cells = searchingCompany(BstCompany, root);
        if(Cells == NULL){
// if company not found then break the loop
            break;
        }
        else{
// Delete function is called to delete the specific node
            root = Delete(Cells->name, root);
        }
    }
    return root;
}
//save the medicines in the tree to a file
// save the medicines in the tree to a file
void Save_medicine( NodesBst root, FILE *out ){
    if (out == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
// check if the root is not null
    if( root != NULL ){
// recursively save left subtree
        Save_medicine( root->left, out );
        char line[150];
// copy the data of the node to a line
        sprintf(line, "%s:%s:%s:%s:%s:%d:%s", root->name, root->active_ingredient, root->category, root->indication,
                root->expiry_date, root->count, root->company);
// replace "" with "_"
        for (int i = 0; i < 150; i++) {
            if(line[i] == ' '){
                line[i] = '_';
            }
        }
// write the line to the file
        fprintf(out, "%s\n", line);
// recursively save right subtree
        Save_medicine( root->right, out );
    }
}

//searching a node in the tree by company name
//search for medicine(s) by company name in the tree and return the first found node
NodesBst searchingCompany( char BstCompany[], NodesBst root ){
    if( root != NULL ){
        if(strcmp(root->company, BstCompany) == 0){
            return root;
        }
        else{
            NodesBst Cells;
            Cells = searchingCompany( BstCompany, root->left);
            if(Cells == NULL){
                Cells = searchingCompany( BstCompany, root->right);
            }
            return Cells;
        }
    }
    else{
        return NULL;
    }
}
// Function to generate a hash value for a given string using the first 5 characters
// The function takes in a string as input and returns an integer value as the hash
// It calculates the sum of the ASCII values of the first 5 characters of the string
// and takes the modulo of that sum with the maximum size of the hash table
// The resulting value is used as the index for the hash table
int FunctionH(char* name) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += name[i];
    }
    return sum % maximum_size;
}

//function to print the hash table data including empty spots
void Print_Hash(HashTable* table){
    for (int i = 0; i < maximum_size; i++) {
        if(table->data[i]->name == NULL){
            printf("cell %d -> empty cell\n", i);
        }
        else{
            printf("cell %d -> %s\n", i, table->data[i]->name);
        }
    }
}

//function to print the count of non-empty spots in a hash table
void Hash_Size(HashTable* table) {
    int count = 0;
    for (int i = 0; i < maximum_size; i++) {
        if (table->data[i] != NULL) {
            count++;
        }
    }
    printf("The size of the hash table is %d\n", count);
}

//prints the hash function
void FunctionHprint(HashTable* table) {
    printf("The hash function used is (x + i^2) mod %d, where x is the input key, i is the number of collisions, and mod %d is the size of the hash table.\n", maximum_size, maximum_size);
}// FunctionHprint() is a function that prints the hash function being used in the program. It explains that the hash function is of the form (x + i^2) mod maximum_size, where x is the input key, i is the number of collisions, and mod maximum_size is the size of the hash table.

//insert a new medicine to the table
void Add_Record(HashTable* table, HashNode* med) {
    int c = 0, i = FunctionH(med->name);
    while (table->data[i] != NULL) {
//increment number of collisions
        c++;
//use the quadratic probing method to find the next empty spot in the table
        i = (FunctionH(med->name) + c * c ) % maximum_size;
    }
//insert the new medicine into the empty spot
    table->data[i] = med;
//increment the size of the table
    table->size++;
//print the number of collisions that happened in this insertion
    printf("%d collisions happened in %s :D!\n", c,
           table->data[i]->name);
}
//search for a medicine
void searching_Hash(HashTable* table, char* name) {
    int c = 0, i = FunctionH(name);
    while (1) {
        if (table->data[i] == NULL || table->data[i]->name == NULL) {
            printf("Medicine not found.\n");
            return;
        }
        if (strcmp(table->data[i]->name, name) == 0) {
            break;
        }
        c++;
        i = (FunctionH(name) + c * c ) % maximum_size;
    }
    printf("%d collisions happened before searchinging the medicine.\n", c);
    printf("Name: %s\n", table->data[i]->name);
    printf("Active Ingredient: %s\n", table->data[i]->active_ingredient);
    printf("Category: %s\n", table->data[i]->category);
    printf("Indication: %s\n", table->data[i]->indication);
    printf("Expiry Date: %s\n", table->data[i]->expiry_date);
    printf("Count: %d\n", table->data[i]->count);
    printf("Company: %s\n", table->data[i]->company);
}
// This function is used to delete a specific medicine from the hash table using its name as the key.
// It starts by calculating the initial index using the hash function with the input name, and then it iterates
void Delete_Hash(HashTable* table, char* name) {
    int c = 0, i = FunctionH(name);
    while (1) {
        if (table->data[i] == NULL) {
            printf("Record with name %s not found.\n", name);
            return;
        }
        if (strcmp(table->data[i]->name, name) == 0) {
            break;
        }
        c++;
        i = (FunctionH(name) + c * c ) % maximum_size;
    }
    free(table->data[i]);
    table   ->data[i] = NULL;
    table->size--;
    printf("Record with name %s deleted successfully!\n", name);
}


//function to save the medicines data to the file
void Save_Hash(HashTable* table) {
    FILE *out = fopen("Pharmacy.txt", "w");
    if (out == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < maximum_size; i++) {
        HashNode* medicine = table->data[i];
        if (medicine != NULL) {
            char line[150];
            sprintf(line, "%s:%s:%s:%s:%s:%d:%s", medicine->name, medicine->active_ingredient,
                    medicine->category, medicine->indication, medicine->expiry_date,
                    medicine->count, medicine->company);
            for (int j = 0; j < 150; j++) {
                if(line[j] == '_'){
                    line[j] = ' ';
                }
            }
            fprintf(out, "%s\n", line);
        }
    }
    fclose(out);
    printf("Data saved successfully to Pharmacy.txt!\n");
}

