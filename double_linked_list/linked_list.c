#include "linked_list.h"

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
};

struct list *list_create(void){
    struct list *list = malloc(sizeof(struct list));
    // Check if memory allocation was successful
    if (list == NULL) return NULL;

    list->first = NULL;
    list->last = NULL;

    return list;
}

size_t list_count(const struct list *list){
    struct list_node *current = list->first; // Make a copy of the first element.
    size_t count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void list_push(struct list *list, ll_data_t item_data){
    struct list_node *newNode = (struct list_node *)malloc(sizeof(struct list_node));
    if (newNode == NULL) return;

    newNode->data = item_data;
    newNode->next = NULL; // The new node will be the last node, so its next pointer should be NULL

    if (list->first == NULL) {
        // If the list is empty, the new node becomes the first and last node
        list->first = newNode;
        list->last = newNode;
        newNode->prev = NULL;
    } else {
        // Otherwise, add the new node at the end of the list
        newNode->prev = list->last;
        list->last->next = newNode;
        list->last = newNode;
    } 
}

ll_data_t list_pop(struct list *list){
    if (list->last == NULL) return -1;

    // Get the data from the last node, because we need to return it.
    ll_data_t data = list->last->data;

    // Update the list
    struct list_node *temp = list->last;
    list->last = list->last->prev;

    if (list->last == NULL) {
        // If the list has become empty, update the first pointer as well
        list->first = NULL;
    } else {
        // Otherwise, update the next pointer of the new last node to NULL
        list->last->next = NULL;
    }

    // Free the memory allocated for the popped node
    free(temp);

    return data;

}

void list_unshift(struct list *list, ll_data_t item_data){
    struct list_node *newNode = (struct list_node *)malloc(sizeof(struct list_node));
    if (newNode == NULL) return;

    newNode->data = item_data; // Set the data for the new node

    if (list->first == NULL) {
        // If the list is empty, the new node becomes both the first and last node
        newNode->prev = NULL;
        newNode->next = NULL;
        list->first = newNode;
        list->last = newNode;
    } else {
        // If the list is not empty, insert the new node at the front
        newNode->prev = NULL;
        newNode->next = list->first;
        list->first->prev = newNode;
        list->first = newNode;
    }
}

ll_data_t list_shift(struct list *list) {
    if (list->first == NULL) return -1;

    // Get the data from the first node
    ll_data_t data = list->first->data;

    // Update the list
    struct list_node *temp = list->first;
    list->first = list->first->next;

    if (list->first == NULL) {
        // If the list becomes empty after shifting, update the last pointer as well
        list->last = NULL;
    } else {
        // Otherwise, update the prev pointer of the new first node to NULL
        list->first->prev = NULL;
    }

    // Free the memory allocated for the shifted node
    free(temp);

    return data;
}

/*   
*    This function traverses the list to find the node with the matching data.
*    Once the node with the matching data is found, it checks if it is the first node, last node, or a node in the middle.
*    If it's the first node, it updates the first pointer accordingly and handles the case when the list becomes empty after deletion.
*    If it's the last node, it updates the last pointer accordingly.
*    If it's a node in the middle, it updates the pointers of the surrounding nodes to bypass the node to be deleted.
*    Finally, it frees the memory allocated for the deleted node. 
*/
void list_delete(struct list *list, ll_data_t data) {
    struct list_node *current = list->first; // Remember to make a copy of the current node!

    // Traverse the list to find the node with the matching data
    while (current != NULL && current->data != data) {
        current = current->next;
    }

    // If the node with the matching data is found
    if (current != NULL) {
        // If the node is the first node
        if (current == list->first) {
            list->first = current->next;
            if (list->first != NULL) {
                list->first->prev = NULL;
            } else {
                // If the list becomes empty after deletion
                list->last = NULL;
            }
        } else if (current == list->last) { // If the node is the last node
            list->last = current->prev;
            list->last->next = NULL;
        } else { // If the node is in the middle
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        // Free the memory allocated for the deleted node
        free(current);
    }
}


void list_destroy(struct list *list) {
    struct list_node *current = list->first;
    struct list_node *next;

    // Traverse the list and free memory for each node
    while (current != NULL) {
        next = current->next; // Store the next node before freeing the current node
        free(current); // Free memory for the current node
        current = next; // Move to the next node
    }

    // Free memory for the list itself
    free(list);
}

