//
//  main.c
//  mishtiiDS
//
//  Created by "" on 31/12/18.
//  Copyright © 2018. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


struct FriendList{
    
    struct FriendList *next;
};

typedef struct FriendList friendListNode;

struct Users{
    
    char name[30];
    char location[20];
    int birthyear;
    struct FriendList *friends;
    struct Users *next;
};

typedef struct Users node;

node *users = NULL;

void allUsers(){
    
    if(users->next == NULL){
        
        printf("There are no users!\n");
    }else{
        
        for(node *temp = users->next; temp != NULL; temp = temp->next){
            
            printf("%s\n", temp->name);
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

void showOptions(){
    
    
}

void controlPanel(){
    
    char ch = '\0';
    node *temp;
    do{
        scanf("%c", &ch);
        showOptions();
        
        switch (ch) {
            case '1':
                
                allUsers();
                break;
            case '2':
                
                temp = (node*) malloc(sizeof(node));
                printf("Name: ");
                scanf("%s", temp->name);
                printf("Location: ");
                scanf("%s", temp->location);
                printf("Birthyear: ");
                scanf("%d", &temp->birthyear);
                temp->friends = (friendListNode*) malloc(sizeof(friendListNode));
                temp->friends->next = NULL;
                addUser(temp);
                break;
                
            default:
                printf("Invalid Option!\n");
                break;
        }
        
    }while(ch != 'Q');
}

int main(int argc, const char * argv[]) {
    
    users = (node*) malloc(sizeof(node));
    users->next = NULL;
    
    controlPanel();
    
    return 0;
}
