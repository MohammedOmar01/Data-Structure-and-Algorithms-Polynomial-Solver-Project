#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *filePath = "C:\\input.txt";
char *filePath_output = "C:\\output.txt";
FILE *file;

typedef struct node *ptr;
struct node {
    int co;
    int ex;
    struct node *next;
};                                                              //Welcome to my project //
                                                             // Name : mohammad omar , ID = 1212429//
typedef ptr linked_list;


typedef struct stack_node *ptrt;
struct stack_node {
    linked_list plol;                                         //firstly make an stack , and linked list
    ptrt next;
};
typedef ptrt stack;




stack s = NULL;
stack add_stack = NULL;                                       //Make 4 stacks a global stacks
stack subtract_stack = NULL;
stack multiply_stack = NULL;



linked_list createLinkedList();
stack creat_stack();
void printlist(linked_list l);
ptr add_node(int coefficient, int exponent);
void insert_sorting(linked_list *l, linked_list newnode);
void Menu(int chosen_number);
FILE *File_opening(char *filePath);
void cutThestring(char *mohammadString, linked_list *l);
void push(stack *s_ptr, linked_list l);
linked_list pop(stack *s_ptr);
void read_stack(stack ptr);                                 // list of function that we will use
ptr adding(linked_list l1, linked_list l2);
ptr subtract(linked_list minuend, linked_list subtrahend);
ptr multiply(linked_list l1, linked_list l2);
void adding_operation();
void subtract_operation();
void multiply_operation();
void All_Result();
void writeAllResultsToFile(char *outputPath);
void reverse_print(stack m, int counter);
void print(linked_list l, FILE *outfile);
void write_to_file(char *outputPath);




int main() {
    s = creat_stack();
    add_stack = creat_stack();                                        // inside the main , applied a creation to all global stacks
    subtract_stack = creat_stack();
    multiply_stack = creat_stack();

     int k;
        printf("Welcome to my project 1 Code ^_^ , please pick a number from 1 to 8 \n");
        printf("\nPlease pick a number to start:\n");
        printf("1) Load polynomials from file and push to stack\n");
        printf("2) Print polynomials in the stack\n");
        printf("3) Add all polynomials in the stack\n");
        printf("4) Subtract all polynomials in the stack\n");
        printf("5) Multiply all polynomials in the stack\n");           // the menu
        printf("6) Print all operation results\n");
        printf("7) Write all operation results to file\n");
        printf("8) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &k);

     Menu(k);

    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void Menu(int chosen_number) { // here is my switch statement  that content a number from 1 to 8 , every time the user press a number the switch will go to the case of that number
    switch (chosen_number) {
        case 1: {                                                    // Load polynomials from file and push to the main stack
            file = File_opening(filePath);
            if (file != NULL) {
                printf("--------------------------------------------------------------------\n");
                printf("^_^ File loaded successfully\n");
                printf("2) Print polynomials\n");
                printf("3) Add the polynomials\n");
                printf("4) Subtract the polynomials\n");
                printf("5) Multiply the polynomials\n");
                printf("6) Print all operation results\n");
                printf("7) Write all operation results to file\n");
                printf("8) Exit\n");
                printf("Enter your choice: ");
                char line[50];
                                                                     // Read each line and push it after edits it to the main stack
                while (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\n")] = '\0';
                linked_list l = createLinkedList();
                cutThestring(line, &l);
                push(&s, l);  }                                      // for the first case , it will store the value in the main stack , so we can see every time
                fclose(file);                                        // the polynomials in the file , without losing the data inside it .
            }
            else {
                printf(" No file were loaded check the path of the file\n");}
                int k;
                scanf("%d", &k);
                Menu(k);
            break;
        }
        case 2: {
                char line[50];
                int counter = 1 ;
                file = File_opening(filePath);
                if (file != NULL)
                 {  while (fgets(line, sizeof(line), file)){
                printf("%d) %s\n", counter, line);
                counter++;
                 }
                 }fclose(file);


                printf("--------------------------------------------------------------------\n");
                printf("3) Add all polynomials in the stack\n");
                printf("3) Add all polynomials in the stack\n");
                printf("4) Subtract all polynomials in the stack\n");
                printf("5) Multiply all polynomials in the stack\n");
                printf("6) Print all operation results\n");
                printf("7) Write all operation results to file\n");
                printf("8) Exit\n");
                printf("Enter your choice: ");

                int k;
                scanf("%d", &k);                                     // case tow to print all the polynomials in the main stack ,or to print all the file content.
                Menu(k);                                             // but in this case , if we read the main stack , it will not be in the good order !
                break;                                               // so that i make an traverse function , that its always related to the read stack function
                                                                     // it will read the stack , but the the stack will content the file but in inverse view
                                                                     // so we will revers it (not the stack) the read of the pointer.

        }
        case 3: {

                file = File_opening(filePath);
                char line[50];
                while (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\n")] = '\0';
                linked_list l = createLinkedList();
                cutThestring(line, &l);                              // and here the same think , but to avoid using a copy function that copy the main stack
                push(&add_stack, l);  }                              // I directly open the file another time and store them in the global stack named add stack.
                fclose(file);                                        // all adding algorithm will preform in add stack , and then we will print it (the print function are called inside the adding,sub and multibly functions.

                adding_operation();
                printf("--------------------------------------------------------------------\n");
                printf("4) Subtract all polynomials in the stack\n");
                printf("5) Multiply all polynomials in the stack\n");
                printf("6) Print all operation results\n");
                printf("7) Write all operation results to file\n");
                printf("8) Exit\n");
                printf("Enter your choice: ");
                int k;
                scanf("%d", &k);
                Menu(k);

            break;

        }
        case 4: {
                file = File_opening(filePath);
                char line[50];
                stack temp = creat_stack();
                while (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\n")] = '\0';
                linked_list l = createLinkedList();
                cutThestring(line, &l);
                push(&temp, l);
                }
                fclose(file);                                        // Here there is a small trick , when we phrase all the Polynomial in a linked list and then push all the linked lists
                                                                     // to the sub stack to preform a sub operation ,the stack will when we call the cut of the string function
                                                                     // and preform a the cut and then call the insert and sort function , the stack will be inverse , (the reverse function will not change the stack content and index of it it only print thim in reverse order
                                                                     // to preform a print like the file ,, but the stack is already reversed! in this case we need a temp stack to push all the node in the sub stack
                                                                     // and then pop from the temp , to the main stack .... this will preform the result if sub in logicly true way
                while (temp != NULL) {
                    linked_list poly = pop(&temp);
                    push(&subtract_stack, poly);
                }
                subtract_operation();
                printf("--------------------------------------------------------------------\n");
                printf("5) Multiply all polynomials in the stack\n");
                printf("6) Print all operation results\n");
                printf("7) Write all operation results to file\n");
                printf("8) Exit\n");
                printf("Enter your choice: ");
                int k;
                scanf("%d", &k);
                Menu(k);

            break;

        }
        case 5: {
                file = File_opening(filePath);
                char line[50];
                while (fgets(line, sizeof(line), file)) {
                line[strcspn(line, "\n")] = '\0';
                linked_list l = createLinkedList();
                cutThestring(line, &l);
                push(&multiply_stack, l);  }
                fclose(file);
                                                                     // the adding and multiplication , does not need to reverse the stack not like the sub opration
                                                                     // doing the same think in Previes
                multiply_operation();
                printf("--------------------------------------------------------------------\n");
                printf("6) Print all operation results\n");
                printf("7) Write all operation results to file\n");
                printf("8) Exit\n");
                printf("Enter your choice: ");
                int k;
                scanf("%d", &k);
                Menu(k);

            break;

        }
        case 6: {
                All_Result();
                printf("--------------------------------------------------------------------\n");
                printf("7) Write all operation results to file\n");
                printf("8) Exit\n");
                printf("Enter your choice: ");                       // Printing the the result , the result are already in the global stacks
                int k;
                scanf("%d", &k);
                Menu(k);

            break;

        }
        case 7: {
            write_to_file(filePath_output);                 // Write the result to a file output , the result in the global stacks
                printf("--------------------------------------------------------------------\n");
                printf("8) Exit\n");
                printf("Enter your choice: ");
                int k;
                scanf("%d", &k);
                Menu(k);

            break;

        }
         case 8: {
                printf("Exit the program , I hope you enjoy my program.............^_^\n");

            break;

        }
         default:
            printf(" enter a number from 1 to 8 (only) ^_^\n");
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
stack creat_stack(){ // A function to create a stack , make it easy for us to call it and create a stack.

         stack s = (stack)malloc(sizeof(struct stack_node));
         s = NULL;

         return s ;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void reverse_print(stack m, int counter) { // A function to print the stack in reverse ( like the file content)
    if (m == NULL)
        return;

    reverse_print(m->next, counter);                            // When the read stack is called the the reverse print function , and give him a counter 1, its first check the passing stack is empty or not
    printf("Polynomial %d: ", counter);                         // Then it will preform a recursive call to it self , passing the next node of the stack and the counter it self
    if (m->plol != NULL) {                                      // Why ? because we need to get to the last node in the stack , and make it the first node (or give him the counter to be 1 in the last node)
        printlist(m->plol);                                     // Know when we are in the last down node in stack , we need to check if the Polynomial is not empty , then if yes , print is
    } else {                                                    // The print function we will talk about it , after we print the last down node , we make the counter to ++ so it goes know to the next node after the down (the node after the down node)
        printf("NULL\n");                                       // And that it , it will call it self and then counter ++ and goes back  , these method will print the stack (like the file content)
    }
    counter++;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void read_stack(stack ptr) {// Function to read and print the STACK , it will take a stack (one of the global stacks if you want to read them) then it will
    if (ptr== NULL) {
        printf("Sorry the main stack is empty\n");              // It will take a stack (one of the global stacks if you want to read them) then it will
        return;                                                 // Check if the stack is empty ,then it will make a counter and (to know the node number in stack)
    }                                                           // Then it will go the the
    int counter = 1;
    reverse_print(ptr, counter);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
FILE *File_opening( char *filePath) { // A function to open a file , make it easy in the switch function to call it and open the file.
    file = fopen(filePath, "r");
    if (file == NULL) {
   printf("the file could not opened check the file path\n");   // In case the file is not Opening or not contant any think inside it
    }
    return file;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void cutThestring(char *mohammadString,linked_list *l){// Function to parse a polynomial string into a linked list
    char *p = mohammadString;
    int sign=1,c=0,e=0,index;
    char term[50];
    char *x_pos;
    while (*p != '\0')
    {
       int i = 0;
       if (*p == '+' || *p == '-'){

            if (*p == '+')
            {
                sign = 1;}

            else{
                sign = -1;
            }
            term[i++] = *p;
            p++;
        }
        while (*p != '\0' && *p != '+' && *p != '-'){           // This function will cut and sort the file that content string
                                                                // Every time , the while loop will give this function a one line content string and 1 linked list to store the  coefficient and the exponent inside
            term[i++] = *p++;                                   // The linked list as one node per one index , for example if line content 3x^2+3x  the first linked list content tow node
                }                                               // The first node is 3 and 2  and the second node will content 3 and 1 , and be sure for convert the char number , to an integer number and all the line
            term[i] = '\0';                                     // After it handle all the perverse think , the insert sorting function will come and get this linked list and edit it as a good look (we will explain )
      if (term[0] == '+' || term[0] == '-'){                    // Then it will go back to the calling center and complete from there.

            index = 1;
        }
        else{
            index = 0;
        }

        if (term[index] == 'x'){
            c = 1;
            x_pos = term + index;
        }
        else{
        c = strtol(term + index, &x_pos, 10);
            if (x_pos == term + index){
                c = 1;
            }
        }
        c *= sign;
        if (*x_pos == 'x'){

            x_pos++;

            if (*x_pos == '^'){
                x_pos++;
                e = strtol(x_pos, NULL, 10);
            }
            else{
                e = 1;
            }
        }
        else{

            e = 0;
        }

        ptr temp = add_node(c, e);
        insert_sorting(l, temp);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
linked_list createLinkedList(){// A function to create a LINKED_LIST ,to make it easy for us to call it and create a linked list.
     linked_list l;
     l = (linked_list)malloc(sizeof(struct node));
     l = NULL;
    return l;
 }

///////////////////////////////////////////////////////////////////////////////////////////////////
void insert_sorting(linked_list *l, linked_list newnode) {// Function to insert a node in descending order

   ptr c = *l;
   ptr pre ;                                                // Here is the one of the important function in the program , this function , will get an the head of a linked list , and a new node to insert the new node
                                                            // in the linked list , but in an orderly manner of all the nodes in linked list
 if (newnode == NULL) {                                     // so it get the head of the linked list , pointer on the head , and the new node , then for easy implementation , we make to pointer of stack node (linked list pointer) c will equal the head of the linked list , and the pointer pre , have a null value to assign it in the code
        return;                                             // firstly we will check if the new node , that we need to insert is not null , then we will begin in the if statement to see where the ex of the new node is less that the pointer of the linked list exponent if yes , we will insert it in the before the head , and make it the head
    }                                                       // since its bigger exp , so it should be in the first then return ..... if not , we will go to the while loop

 if ((*l == NULL) || (newnode->ex) > (c->ex)) {
        newnode->next = *l;
        *l = newnode;
        return;
    }


       ptr b = *l;                                         // while loop will check if the variable of the first node of the linked list , is bigger that the new node
       linked_list prev = createLinkedList();              // then the only think will happen is to move to the next node in the linked list and then back to the while loop till we found a node that the exponent of it is bigger
                                                           // if we found an equal exponent then , the only add the coefficient  of them , b != NULL in the function to be sure that we are not in the end of the linked_list
                                                           // but in this case , we need to know if the coffecant of the pointer in the linked lest is zero or not , if yes we need to remove this polynomials
                                                           // and if there is not equal zero of if the ex of the new node is less than every node , so it will insert it at the end of the linked list
while (b != NULL && b->ex > newnode->ex) {
        pre = b;
        b = b->next;
    }



    if (b != NULL && b->ex == newnode->ex) {
        b->co += newnode->co;


        if (b->co == 0) {
            if (pre == NULL) {
                *l = b->next;
            } else {
                prev->next = b->next;
                free(b);
            }

        }
    }
    else {

        newnode->next = b;
        if (pre != NULL) {
            pre->next = newnode;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void printlist(linked_list l) {        // Function to print a linked list node in a good way

    linked_list now = createLinkedList();
    now = l ;
                                                                                                  ////Note////
    int first = 1;
    int expon;
    while (now != NULL) {                                                    // why we need this function ? because the linked list data has tow integer variable, the coefficient and the exponent
        if (now->co == 0) {                                                  // but not a Formally polonmial view , so that we need to add some think to handle it like x and ^ . before and after sorting .

            now = now->next;
        }
         if ((now->co) > 0 && (first==0)) {                 // here is my print list function that will get the a linked list after the function insert sorting done the insert in orderly manner or after the stack is fully , and we need only to print the nodes inside it we can call this function
                  printf(" + ");                            // firstly it will get a linked list (Node) of a stack , then we need to handle the coefficient   and the exp term , so for the first term we add a flag and put we make it equal 1
        }                                                   // then we create a pointer name now , and this pointer are know point to the linked list , or the head of this linked list
         else if (now->co < 0) {                            // so firstly we will skip the term that the coefficient of it is zero , and make the pointer point to the next node of the linked list
            if (first==1) {                                 // so if the coefficient is bigger that zero , and the flag is zero (mean that he is not at the first) , it will print + since the flag is 1 it will skip this if statement
                printf("-");                                // but if the coefficient is negative , in any case print -
                  }                                         // know we need to handle the exponent , by make an if statement and ask if the coefficient   is bigger that zero .
            else if (first==0) {
                printf(" - ");
        }
           }
         if (now->co > 0){
        expon = now->co;
        }
        else{
        expon = -(now->co);
        }
        if (expon != 1 || now->ex == 0){                     // know we need to handle the exponent , by make an if statement and ask if the coefficient is bigger that zero .
            printf("%d", expon);
            if (now->ex != 0){
                printf("x");
            }
        }
        else{
            printf("x");
        }
        if (now->ex > 1){
            printf("^%d", now->ex);
        }
        first = 0;
        now = now->next;
    }
    printf("\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////
ptr add_node(int co, int ex) {                    //A function to create a new node , coefficient and exponent.
    ptr newnode = (ptr)malloc(sizeof(struct node));
    if (newnode != NULL) {
        newnode->co = co;
        newnode->ex = ex;
        newnode->next = NULL;
    }
     else {
        printf("Faild to add new node ,cheack the create_node Function\n");
          }
    return newnode;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void push(stack *ptr, linked_list l) {            // function to push a linked list to one of the Global stacks or any temp stack.
    stack new1 = (stack)malloc(sizeof(struct stack_node));
    if (new1 != NULL) {
        new1->plol = l;
        new1->next = *ptr;
        *ptr = new1;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
linked_list pop(stack *ptr) {                    // function to pop a linked list from one of the global stacks or any temp stack.
    if (*ptr == NULL) {
        return NULL;
    }
        stack temp = *ptr;
        linked_list l = temp->plol;
        *ptr = temp->next;
        return l;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void adding_operation() {                       // function that add all polynomials in the adding stack
    if (add_stack == NULL) {
        printf("The Stack Empty\n");
        return;
    }
        linked_list poly = createLinkedList();
        linked_list sum = createLinkedList();
            while (add_stack != NULL) {                                       // in adding method , there are tow function that handle it
        poly = pop(&add_stack);                                               // this function to receive any data , since we will preform on a global stack named adding stack
        linked_list temp = adding(sum, poly);                                 //so firstly the user will inter number 3 , we will read a file and store them in linked list then pop every line of linked list to the adding stack
        sum = temp;                                                           // then we will call it , it define tow pointer of linked list then we will pop the top element in the stack to sum linked list ,
        }                                                                     // A while loop to check whether the global add stack is empty or not , then we pop the next not from the stack
                                                                              // so we will have node 1  and node 2 , we will make a temp linked list to store the value of adding these tow node temp = node 1 + node 2
        push(&add_stack, sum);                                                // after we add it , we will make the pointer sum equal the temp , when there is no node to add , we only push the sum back to the adding stack and print the value of it .
        printf("The sum of all polynomials is:\n");
        printlist(add_stack->plol);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void subtract_operation() {                  // function that sub all polynomials in the subtract stack

    if (subtract_stack == NULL) {
        printf("The Stack is Empty ");
        return;
    }                                                                         // in this function , the same think of the adding function , but here the one difference think that , the stack is reverse , when i reverse it in switch function
        ptr sub = pop(&subtract_stack);                                       // so its preform as the same, it make a pointer on the top of the stack and save it in linked list name sub
              while (subtract_stack != NULL) {                                // then if the global stack is not empty , just pop the next node (the top one) and make a temp list and go to the sub function to subtract these to linked list , then get back and assign the sun to the temp ( temp is the result of subtraction
        linked_list subb = pop(&subtract_stack);                              // then go back to while loop , to reach the the last node , and make the global stack is empty , so push the sum (that has the final answer ) to the global sub stack and print it .
        linked_list temp = subtract(sub, subb);
        sub = temp;
    }
        push(&subtract_stack, sub);
        printf("The result of subtraction is:\n");
        printlist(subtract_stack->plol);

    }

///////////////////////////////////////////////////////////////////////////////////////////////////
void multiply_operation() {                  // function to multiply all polynomials in the multiply stack
    if (multiply_stack == NULL) {
        printf("there is no polynomial to multiply\n");
        return;
    }
        linked_list mul = createLinkedList();
        mul = pop(&multiply_stack);
              while (multiply_stack != NULL) {                                   // In this function , the same process are done , we create a new pointer in linked list , this pointer will get the value  of the top global stack
        linked_list poly = pop(&multiply_stack);                                 // then we make an while loop to check if the stack is empty or not , we make also a new pointer to the top of the stack ( this pointer will pop the node from the top global stack) and make it his value
        linked_list temp = multiply(mul, poly);                                  // a new temp linked list , will be the destination , and it goes to the function that multiply the tow node , then the value of the temp will be the value of the multibly linked list , and goes back to the while loop
        mul = temp;                                                              // till its Empty , then push the final answer to the Global stack , then print it .
    }
        push(&multiply_stack, mul);
        printf("The result of multiplication is:\n");
        printlist(multiply_stack->plol);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void All_Result() {                         // function to print all operation results
    printf("\n-------------^_^ All the Results ^_^-------------\n");

    if (add_stack != NULL && add_stack->plol != NULL) {
        printf("Addition Result\n");
        printlist(add_stack->plol);
    } else {
        printf("\n No addition result\n");                                        // This function will print all the Global stacks and if the user not enter number of operation like adding
    }                                                                             // He will check whether the stack is contain a a nodes , and also will check if the node contain a variable
                                                                                  // If not , then we will know that the global stack of this operation is empty and he will print it on screen
    if (subtract_stack != NULL && subtract_stack->plol != NULL) {
        printf("\nSubtraction Result\n");
        printlist(subtract_stack->plol);
    } else {
        printf("\n No subtraction result\n");
    }
    if (multiply_stack != NULL && multiply_stack->plol != NULL) {
        printf("\nMultiplication Result\n");
        printlist(multiply_stack->plol);
    } else {
        printf("\nNo multiplication result\n");
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
ptr adding(linked_list l1, linked_list l2) { // function that Add tow linked list
        linked_list result = createLinkedList();
        linked_list p1 = l1;
        linked_list p2 = l2;
          while (p1 != NULL && p2 != NULL) {                                     // And here is the function that add tow linked list , and sort them using the insert sort function
        if ((p1->ex) > (p2->ex)) {                                               // after we pop tow linked list from the adding function (from the global adding stack) we make more three linked list or pointers
        linked_list temp = add_node(p1->co, p1->ex);                             // then we will preform the adding based on the exponent term , and make 3 pointer , 1 is empty , and tow of them are taking to l1 and l2
        insert_sorting(&result, temp);                                           // to preform the adding , while loop to check if one of them are empty , then if the first node of the first linked list , the exponent of him is bigger than
        p1 = p1->next;                                                           // the second one , he will do a temp link and insert the value of the bigger one on it , firstly create node , then insert and sort
        }                                                                        // and the pointer of the first node , will be go to the next node in the linked list 1 , and if it less that the another node in the second linked list
        else if ((p1->ex) < (p2->ex)) {                                          // the same think happen but to l2 , and if they are the same  exponent  , here will do the adding , and we will add the coefficient and make it in (integer)
        linked_list temp = add_node(p2->co, p2->ex);                             // and also we will add a new node and sort it and insert it . all the think are being done in the result linked list its like a temp , but we need there value so without free it
        insert_sorting(&result, temp);                                           // and if one of the linked list is finsh , it will go to the tow while loop
        p2 = p2->next;
        }
        else if( (p1->ex) == (p2->ex))  {
        int sum = p1->co + p2->co;
        if (sum != 0) {
        linked_list temp = add_node(sum, p1->ex);
        insert_sorting(&result, temp);
            }
        p1 = p1->next;
        p2 = p2->next;
        }
    }

         while (p1 != NULL) {
        linked_list temp = add_node(p1->co, p1->ex);
        insert_sorting(&result, temp);
        p1 = p1->next;
    }
          while (p2 != NULL) {
        linked_list temp = add_node(p2->co, p2->ex);
        insert_sorting(&result, temp);
        p2 = p2->next;
    }

    return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
ptr subtract(linked_list l1, linked_list l2) { // function that Add tow linked list
        linked_list result = createLinkedList();
        linked_list p1 = l1;
        linked_list p2 = l2;

           while (p1 != NULL && p2 != NULL) {                              // here is the same as the previous function , bit the different here is when the exponent is equal , we will preform a
        if (p1->ex > p2->ex) {                                             // a subtraction to it , and store it in sub integer . and it act like the previous one .

        linked_list temp = add_node((p1->co), (p1->ex));
        insert_sorting(&result, temp);
        p1 = p1->next;
        }
        else if (p1->ex < p2->ex) {
        linked_list temp = add_node((-p2->co), (p2->ex));
        insert_sorting(&result, temp);
        p2 = p2->next;
        }
        else {
        int sub = p1->co - p2->co;
        if (sub != 0) {
        linked_list temp = add_node(sub, p1->ex);
        insert_sorting(&result, temp);
            }
        p1 = p1->next;
        p2 = p2->next;
        }
    }

             while (p1 != NULL) {
        linked_list temp = add_node((p1->co), (p1->ex));
        insert_sorting(&result, temp);
        p1 = p1->next;
    }


             while (p2 != NULL) {
        linked_list temp = add_node((-p2->co), (p2->ex));
        insert_sorting(&result, temp);

        p2 = p2->next;
    }


        return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
ptr multiply(linked_list l1, linked_list l2) {  // function that multiply tow linked list
        linked_list result = createLinkedList();
        linked_list ptr1 = l1;
                                                                  // In this function its easy to multiply tow linked list , we need tow pointer linked_llist
           while (ptr1 != NULL) {                                 // then when assign the first pointer to the first head of the linked list , then a result linked lest to store the result on it and return the value of it to the calling function
        linked_list ptr2 = l2;                                    // tow while loop to mull the first node in the first linked list , with all the node in the second linked list .
           while (ptr2 != NULL) {                                 // and insert and sort every node we multiply it , to the result linked list , and return the value of the result
        int co = ptr1->co * ptr2->co;
        int ex = ptr1->ex + ptr2->ex;
        linked_list temp = add_node(co, ex);
        insert_sorting(&result, temp);
        ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }

        return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void write_to_file(char *outputPath) {   // function to write on a file output
    FILE *outfile = fopen(outputPath, "w");

        fprintf(outfile, "addition Result is : \n");
    if (add_stack != NULL && add_stack->plol != NULL) {           //
    print(add_stack->plol, outfile);
  } else {
        fprintf(outfile, "The Stack is empty\n");
    }

    fprintf(outfile, "Subtraction Result is : \n");
    if (subtract_stack != NULL && subtract_stack->plol != NULL) {                // these tow parallel function first to write on an output file
        print(subtract_stack->plol, outfile);                                    // each time i ask if global stack are empty , and if the top of the stack are empty or not
  } else {                                                                       // then we will print on the file , the stack content , but we use print function , that phase every number and sign
        fprintf(outfile, "The Stack is empty\n");                                                 // since he cant send to the file (print (print list)) so we make another print function
    }

    fprintf(outfile, "Multipliation Result is : \n");
    if (multiply_stack != NULL && multiply_stack->plol != NULL) {
        print(multiply_stack->plol, outfile);
   } else {
        fprintf(outfile, "The Stack is empty\n");
    }

    fclose(outfile);
    printf("Operation results have been written to the file: %s\n", outputPath);
}

void print(linked_list l, FILE *outfile) {    //function to print the content of the stack (the last linked list node ) to the output file
    ptr c = l;
    int first = 1;
    if (c == NULL) {
      fprintf(outfile, "0\n");
        return;
    }

    while (c != NULL) {
    if (c->co == 0) {
            c = c -> next;

        }

    if (first==1) {
        if (c->co < 0) {
        fprintf(outfile, "-");
            }
    } else {
        if (c->co < 0) {
        fprintf(outfile, " - ");
    } else {
        fprintf(outfile, " + ");
            }
        }

        int co = abs(c->co);
    if (co != 1 || c->ex == 0) {
            fprintf(outfile, "%d", co);
        }
    if (c->ex != 0) {
            fprintf(outfile, "x");
        if (c->ex != 1) {
            fprintf(outfile, "^%d", c->ex);
            }
        }
        first = 0;
        c = c->next;
    }
    fprintf(outfile, "\n");
}
