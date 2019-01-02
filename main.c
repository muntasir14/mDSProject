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
        if((actualUser1 != NULL) && (actualUser2 != NULL)){
            break;
        }
    }
    
    for(node *temp = actualUser1->nextFriend; temp != NULL; temp = temp->nextFriend){
        
        printf("test: %d\n", strcmp(user2->name, temp->name));
        if((strcmp(user2->name, temp->name) == 0) && (strcmp(user2->location, temp->location) == 0) && (user2->birthyear == temp->birthyear)){
            
            printf("They are already friends\n");
            return;
        }
    }
    
    
    
    user1->nextFriend = actualUser2->nextFriend;
    actualUser2->nextFriend = user1;
    
    user2->nextFriend = actualUser1->nextFriend;
    actualUser1->nextFriend = user2;
    
}

int countFriends(node *user){
    
    int count = 0;
    
    for(node *temp = user->nextFriend; temp != NULL; temp = temp->nextFriend)
        count++;
    
    return count;
}

node* mostFriends(){
    
    node *maxFriendUser = users->next;
    int max = 0;
    
    for(node *temp = users->next; temp != NULL; temp = temp->next){
        
        int numberOfFriends = countFriends(temp);
        if(numberOfFriends > max){
            
            max = numberOfFriends;
            maxFriendUser = temp;
        }
    }
    
    return maxFriendUser;
}

int totalUsers(){
    
    int count = 0;
    for(node *temp = users->next; temp != NULL; temp = temp->next)
        count++;
    
    return count;
}

node* getUsers(){
    
    return users;
}

void removeUser(node *user){
    
    // removing from everyone's friendlist
    for(node *temp1 = users->next; temp1 != NULL; temp1 = temp1->next){
        
        node *temp2 = temp1;
        for(node *temp3 = temp1->nextFriend; temp3 != NULL; temp3 = temp3->nextFriend, temp2 = temp2->nextFriend){
            
            if((strcmp(user->name, temp3->name) == 0) && (strcmp(user->location, temp3->location) == 0) && (user->birthyear == temp3->birthyear)){
                
                temp2->nextFriend = temp3->nextFriend;
                free(temp3);
                break;
            }
        }
    }
    
    for(node *temp1 = users, *temp2 = users->next; temp2 != NULL; temp2 = temp2->next, temp1 = temp1->next){
        
        if((strcmp(user->name, temp2->name) == 0) && (strcmp(user->location, temp2->location) == 0) && (user->birthyear == temp2->birthyear)){
            
            temp1->next = temp2->next;
            free(temp2);
            break;
        }
    }
    
    
}

void commonFriends(node *user1, node *user2){
    
    node *actualUser1 = NULL, *actualUser2 = NULL;
    node *commonFriends = (node*) malloc(sizeof(node));
    commonFriends->next = NULL;
    
    for(node *temp = users->next; temp != NULL; temp = temp->next){
        
        if((strcmp(user2->name, temp->name) == 0) && (strcmp(user2->location, temp->location) == 0) && (user2->birthyear == temp->birthyear)){
            actualUser2 = temp;
        }else if((strcmp(user1->name, temp->name) == 0) && (strcmp(user1->location, temp->location) == 0) && (user1->birthyear == temp->birthyear)){
            actualUser1 = temp;
        }
        if((actualUser1 != NULL) && (actualUser2 != NULL))
            break;
    }
    for(node *temp1 = actualUser1->nextFriend; temp1 != NULL; temp1 = temp1->nextFriend){
        
        for(node *temp2 = actualUser2->nextFriend; temp2 != NULL; temp2 = temp2->nextFriend){
            
            if((strcmp(temp1->name, temp2->name) == 0) && (strcmp(temp1->location, temp2->location) == 0) && (temp1->birthyear == temp2->birthyear)){
                
                node *temp3 = (node*) malloc(sizeof(node));
                strcpy(temp3->name, temp1->name);
                strcpy(temp3->location, temp1->location);
                temp3->birthyear = temp1->birthyear;
                temp3->next = commonFriends->next;
                commonFriends->next = temp3;
            }
        }
    }
    if(commonFriends->next == NULL){
        printf("No Common Friends\n");
        return;
    }
    printf("Common Friend(s) between %s and %s: ", user1->name, user2->name);
    for(node *temp = commonFriends->next; temp != NULL; temp = temp->next)
        printf("%s\t", temp->name);
    printf("\n");
}

void printOldestFriends(){
    
    printf("\n\nName\t\tOldest friend\n\n");
    for(node *temp1 = users->next; temp1 != NULL; temp1 = temp1->next){
        
        node *dummy = temp1->nextFriend;
        if(dummy != NULL){
            for(node *temp2 = temp1->nextFriend; temp2 != NULL; temp2 = temp2->nextFriend){
                
                if(dummy->birthyear > temp2->birthyear)
                    dummy = temp2;
            }
            printf("%s\t\t%s\n", temp1->name, dummy->name);
        }else{
            
            printf("%s\t\tNo friends\n", temp1->name);
        }
        
    }
    
}

void showOptions(){
    
    printf("\n\nEnter 1 to see all users\n");
    printf("Enter 2 to add an user\n");
    printf("Enter 3 to add friends\n");
    printf("Enter 4 to see total users\n");
    printf("Enter 5 to see user who has maximum friends\n");
    printf("Enter 6 to remove an user\n");
    printf("Enter 7 to see oldest friends\n");
    printf("Enter 8 to see common friends\n\n");
}


node* setUserAndGet(){
    
    node *user = (node*) malloc(sizeof(node));
    printf("Name: ");
    scanf("%s", user->name);
    printf("Location: ");
    scanf("%s", user->location);
    printf("Birthyear: ");
    scanf("%d", &user->birthyear);
    
    user->nextFriend = NULL;
    
    return user;
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
                
                temp = setUserAndGet();
                addUser(temp);
                //free(temp);
                break;
            case 3:
                printf("For first friend\n");
                temp1 = setUserAndGet();
                
                printf("For second friend\n");
                temp2 = setUserAndGet();
                
                addFriend(temp1, temp2);
                
                break;
            case 4:
                printf("\n\nTotal Users: %d\n\n", totalUsers());
                break;
            case 5:
                printf("\n\nName: %s\n\n", mostFriends()->name);
                break;
            case 6:
                temp = setUserAndGet();
                removeUser(temp);
                break;
            case 7:
                printOldestFriends();
                break;
            case 8:
                printf("For first friend\n");
                temp1 = setUserAndGet();
                
                printf("For second friend\n");
                temp2 = setUserAndGet();
                commonFriends(temp1, temp2);
                break;
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
