#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* ladd;
    struct node* Radd;
    int hight;
}*root=NULL;

 int Bf(struct node* subtree); //calculate balancefactore
 struct node* LLRotation(struct node* root); 
 struct node* RRRotation(struct node* root);
 struct node* RLRotation(struct node* root);
 struct node* LRRotation(struct node* root);
 int Bf(struct node* sub);
 void priorder(struct node* Root);

//******************find & select maximum hight ******
int high(struct node* Root){
     if(Root==NULL)
    return 0;
    
   int hl=high(Root->ladd);
   int hr=high(Root->Radd);
    
  return hl>hr?hl+1:hr+1;         //returns maximum hight frome subtrees
}


//**********************insert node******************
struct node* insert(struct node* root,int data){
    struct node* temp=NULL;
    if(root==NULL){ 
    temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->ladd=temp->Radd=NULL;
    temp->hight=1;
    return temp;
   }
 if(root->data>data)
 root->ladd=insert(root->ladd,data);
 else if(root->data<data)
 root->Radd=insert(root->Radd,data);
 
 root->hight=high(root);
 
 //______ROTATIONS__________
 if(Bf(root)==2 && Bf(root->ladd)==1){
    return root=LLRotation(root);
 }
 if(Bf(root)==2 && Bf(root->ladd)==-1){
   return root=LRRotation(root);
 }
 if(Bf(root)==-2 && Bf(root->Radd)==-1){
    return root= RRRotation(root);
 }
  if(Bf(root)==-2 && Bf(root->Radd)==1){
    return root= RLRotation(root);
 }
 
 return root;
}

//************RLROTATION**********
struct node* RLRotation(struct node* root){
    struct node* temp=root->Radd->ladd;
    root->Radd->ladd=temp->Radd;
    temp->Radd=root->Radd;
    root->Radd=temp->ladd;
    temp->ladd=root;
    temp->Radd->hight=high(temp->Radd);
    root->hight=high(root);
    temp->hight=high(temp);
    return temp;
}


//************LRROTATION**********
struct node* LRRotation(struct node* root){
    struct node* temp=root->ladd->Radd;
    root->ladd->Radd=temp->ladd;
    temp->ladd=root->ladd;
    root->ladd=temp->Radd;
    temp->Radd=root;
    temp->ladd->hight=high(temp->ladd);
    root->hight=high(root);
    temp->hight=high(temp);
    return temp;
}


//************LLROTATION***************
struct node* LLRotation(struct node* root){
    struct node* temp=root->ladd;
    root->ladd=temp->Radd;
    temp->Radd=root;
    root->hight=high(root);
    temp->hight=high(temp);
    return temp;
}

//************RRRotation****************
struct node* RRRotation(struct node* root){
    struct node* temp=root->Radd;
    root->Radd=temp->ladd;
    temp->ladd=root;
    root->hight=high(root);
    temp->hight=high(temp);
    return temp;
}


//**********Balance facter calculation*********
int Bf(struct node* sub){             
    int hl=sub && sub->ladd?sub->ladd->hight:0;
    int hr=sub && sub->Radd?sub->Radd->hight:0;
    return hl-hr;
}
void priorder(struct node* Root){
    if(Root!=NULL){
        printf("\n%d %d",Root->data,Root->hight);
        priorder(Root->ladd);
        priorder(Root->Radd);
    }return;
}
void main(){
    root=insert(root,-1);
    root=insert(root,1);
    root=insert(root,-6);
    root=insert(root,-7);
    root=insert(root,-4);
    root=insert(root,-3);
    priorder(root);
}
