#include "socialmedia.h"

#include <stdlib.h>

Database db;
Cache userCache;
Cache postCache;

void printUser(User *user) {
  printf("User: %d, Username: %s, Followers: %d, Following: %d, Liked: %d\n",
         user->userId, user->username, user->numOfFollowers,
         user->numOfFollowing, user->liked);
}

void printPost(Post *post) {
  printf("Post: %d, Author: %s, Likes: %d\n", post->postId,
         post->author->username, post->likes);
}

void printUserCache() { 
  Node* temp = userCache.head;
  printf("UserCache:\n");
  while (temp)
  {
    User *user = (User *)temp -> data;
    printUser(user);
    temp = temp -> next;
  }
}

void printPostCache() { 
  Node* temp = postCache.tail;
  printf("PostCache:\n");
    while (temp)
    {
        Post *post = (Post *)temp -> data;
        printPost(post);
        temp = temp -> prev;
    }
}

Node *createNode(void *data) { 
    Node* temp = (Node *)malloc(sizeof(Node));
    if (!temp) return NULL;
    temp -> data = data;
    temp -> next = NULL;
    temp -> prev = NULL;
    return temp;
}

void appendToCache(Cache *cache, void *data) { /* to append the user and post to their cache respectively */
  Node* check; /* to check if the user/post is already in the cache <-> edge case */
  Node* new = createNode(data); /* create new node */
  if (!new) return;

  if (!cache -> head) { /* if the cache is already empty, make the new node the head of the cache */
    cache -> head = new;
    cache -> tail = new;
    cache -> size ++;
    return;
  }

  /* to check if the user/post is already in the cache <-> edge case */
  check = cache -> head;
  while (check) {
    if (check -> data == data) {
      return;
    }
    check = check -> next;
  }

  if (cache -> size == cache -> capacity) { /* cache_capacity >= 1 */
    removeLast(cache);
  }

  cache -> head -> prev = new;
  new -> next = cache -> head;
  cache -> head = new;
  cache -> size++;
  return;
}

void moveToFront(Cache *cache, Node *node) { 
 Node* temp;
 Node* check;
 
 if (!cache || !node) return; /* NULL parameters handling */
 check = cache -> head ;

 while (check && check != node) {
    check = check -> next;
 }
 if (!check) return; /* if node is not in the cache return nothing */
 
 if (cache -> head == node) /* if node is the head */
 {
  return;
 }

  if (node == cache -> tail) { /* if node is the tail */
    temp = cache -> tail;
    cache -> tail = cache -> tail -> prev;
    cache -> tail -> next = NULL;
    temp -> next = cache -> head;
    cache -> head -> prev = temp;
    temp -> prev = NULL;
    cache -> head = temp;
    return;
  }

  node -> prev -> next = node -> next;
  node -> next -> prev = node -> prev;
  node -> next = cache -> head;
  cache -> head -> prev = node;
  node -> prev = NULL;
  cache -> head = node;
  return;
}


void removeLast(Cache *cache) { 
  Node* temp;
  if (!cache) return;
  temp = cache -> tail;
  if (cache->tail == NULL) {  /* if the cache is already empty */
    return;
  }

  if (cache -> tail == cache -> head) {  /* if the tail and head are the same */
    free(cache -> tail);
    cache -> tail = NULL;
    cache -> head = NULL;
    cache -> size --;
    return;
  }

  cache -> tail = cache -> tail -> prev;
  cache -> tail -> next = NULL;
  cache -> size --;
  free(temp);
  return;
}

User *fetchUser(int userId) {  /* will return a pointer to the user */
  Node* temp = userCache.head;
  int i = 0;
  while (temp) {
      User* user = (User *)temp->data; 
      if (user->userId == userId) {
          moveToFront(&userCache, temp);
          return user;
      }
      temp = temp->next;
  }
  for (i = 0; i < DB_USER_CAPACITY; ++i) {
      if (db.users[i].userId == userId) {
          appendToCache(&userCache, &db.users[i]);
          return &db.users[i];
      }
  }
  return NULL; 
}

Post *fetchPost(int postId) { 
  Node* temp = postCache.head;
  int i = 0;
  while (temp) {
      Post* post = (Post *)temp->data; 
      if (post->postId == postId) {
          moveToFront(&postCache, temp);
          return post;
      }
      temp = temp->next;
  }
  for (i = 0; i < DB_POST_CAPACITY; ++i) {
      if (db.posts[i].postId == postId) {
          appendToCache(&postCache, &db.posts[i]);
          return &db.posts[i];
      }
  }
  return NULL; 
}

void followUser(int followerId, int followedId) {
  /* TODO Fetch followerId, followedId, then update followers of followedId */
  Node* check;
  Node* new_follower;  /* to add to the followers list of the followed person */
  User* follower = fetchUser(followerId);
  User* followed = fetchUser(followedId);
  if (!followed || !follower) return;

  new_follower = (Node *)malloc(sizeof(Node));  /* create new_follower(node) -> to add to the followers list of the followed person */
  if (!new_follower) return;  /* error in the memory allocation for new_follower */
  new_follower -> next = NULL;
  new_follower -> prev = NULL;
  new_follower -> data = follower;

  if (!followed -> followers_tail) {  /* if the follower list of the person to be followed is empty */
    followed -> followers_tail = new_follower;
    followed -> followers_head = new_follower;
    follower -> numOfFollowing++;
    followed -> numOfFollowers++;    
    return;
  }

  /* if follower is already following the person */
  check = followed -> followers_head;
  while (check) {
    if (check -> data == follower) {
      return;
    }
    check = check -> next;
  }
  
  new_follower -> prev = followed -> followers_tail;
  followed -> followers_tail -> next = new_follower;
  followed -> followers_tail = new_follower;
  follower -> numOfFollowing++;
  followed -> numOfFollowers++;
}

void likePost(int userId, int postId) {  /* TODO Fetch userId and postId */ 
  User* user = fetchUser(userId);
  Post* post = fetchPost(postId);
  if (!user || !post) return;
  user -> liked++;
  post -> likes++;
}

void printFollowersInReverse() {
  Node* temp = userCache.tail;
  printf("Followers of all users in UserCache in reverse:\n");
  while (temp) {
    User* user = (User *)temp -> data;
    Node* followers = user -> followers_tail;
    printf("Followers of user with id %d in reverse:\n", user->userId);
    while (followers) {
      User* follower = followers -> data;
      printf("[%d] ", follower -> userId);
      followers = followers -> prev;
    }
    printf("\n");
    temp = temp -> prev;
  }
}

void freeLinkedList(Node *head) {
  /* TODO Free linked list nodes but not data or data's contents! */
  while (head) {
    Node* temp = head;
    head = head -> next;
    free(temp);
  }
}
