//
//  main.c
//  mishtiiDS
//
//  Created by "" on 31/12/18.
//  Copyright © 2018. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Users{
    
    char name[30];
    char location[20];
    int birthyear;
    struct Users *nextFriend;
    struct Users *next;
};

typedef struct Users node;

node *users = NULL;

void allUsers(){
    
    if(users->next == NULL){
        
        printf("There are no users!\n");
    }else{
        
        for(node *temp = users->next; temp != NULL; temp = temp->next){
            
            printf("%s\t", temp->name);
            for(node *temp2 = temp->nextFriend; temp2 != NULL; temp2 = temp2->nextFriend)
                printf("%s\t", temp2->name);
            printf("\n");
        }
    }
}

void addUser(node *newUser){
    
    if(newUser->birthyear <= 2005){
        
        newUser->next = users->next;
        users->next = newUser;
    }else{
        
        printf("The user is not atleast 13\n");
        free(newUser);
    }
}

void addFriend(node *user1, node *user2){
    
    node *actualUser1 = NULL, *actualUser2 = NULL;
    
    for(node *temp = users->next; temp != NULL; temp = temp->next){
        
        if((strcmp(user2->name, temp->name) == 0) && (strcmp(user2->location, temp->location) == 0) && (user2->birthyear == temp->birthyear)){
            actualUser2 = temp;
        }else if((strcmp(user1->name, temp->name) == 0) && (strcmp(user1->location, temp->location) == 0) && (user1->birthyear == temp->birthyear)){
            actualUser1 = temp;
        }
        if((actualUser1 != NULL) && (actualUser2 != NULL))
            break;
    }
    
    for(node *temp = actualUser1->nextFriend; temp != NULL; temp = temp->nextFriend){
        
        printf("test: %d\n", strcmp(user2->name, temp->name));
        if((strcmp(user2->name, temp->name) == 0) && (strcmp(user2->location, temp->location) == 0) && (user2->birthyear == temp->birthyear)){
            
            printf("They are already friends\n");
            return;
        }
    }
    
    printf("error before\n");
    
    // check if user1 and user2 exists
    
    
    
    user1->nextFriend = actualUser2->nextFriend;
    actualUser2->nextFriend = user1;
    
    user2->nextFriend = actualUser1->nextFriend;
    actualUser1->nextFriend = user2;
    
}


void showOptions(){
    
    printf("Enter 1 to see all users\n");
    printf("Enter 2 to see add a user\n");
    printf("Enter 3 to see add friends\n");
}

void controlPanel(){
    
    int option;
    node *temp, *temp1, *temp2;
    do{
        
        showOptions();
        scanf("%d", &option);
        
        switch (option) {
            case 1:
                
                allUsers();
                break;
            case 2:
                
                temp = (node*) malloc(sizeof(node));
                printf("Name: ");
                scanf("%s", temp->name);
                printf("Location: ");
                scanf("%s", temp->location);
                printf("Birthyear: ");
                scanf("%d", &temp->birthyear);
                temp->nextFriend = NULL;
                addUser(temp);
                //free(temp);
                break;
            case 3:
                printf("For first friend\n");
                temp1 = (node*) malloc(sizeof(node));
                printf("Name: ");
                scanf("%s", temp1->name);
                printf("Location: ");
                scanf("%s", temp1->location);
                printf("Birthyear: ");
                scanf("%d", &temp1->birthyear);
                temp1->nextFriend = NULL;
                
                printf("For second friend\n");
                temp2 = (node*) malloc(sizeof(node));
                printf("Name: ");
                scanf("%s", temp2->name);
                printf("Location: ");
                scanf("%s", temp2->location);
                printf("Birthyear: ");
                scanf("%d", &temp2->birthyear);
                temp2->nextFriend = NULL;
                
                addFriend(temp1, temp2);
                //free(temp1);
                //free(temp2);
            default:
                printf("Invalid Option!\n");
                break;
        }
        
    }while(option != 0);
}

int main(int argc, const char * argv[]) {
    
    users = (node*) malloc(sizeof(node));
    users->next = NULL;
    
    controlPanel();
    
    return 0;
}
