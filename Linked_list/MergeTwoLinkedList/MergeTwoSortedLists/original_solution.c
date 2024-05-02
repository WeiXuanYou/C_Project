struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    struct ListNode* prev_node = malloc(sizeof(struct ListNode));
    prev_node->val = -1;
    prev_node->next = NULL;
    struct ListNode* prev = prev_node;
    
    while(list1 != NULL && list2 != NULL){
        if(list1->val <= list2->val){
            prev->next = list1;
            list1 = list1->next;
        }
        else{
            prev->next = list2;
            list2 = list2->next;
        }
        prev = prev->next;
    }
   prev->next = (list1 == NULL) ? list2:list1;
    return prev_node->next;
}
