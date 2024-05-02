typedef struct ListNode* NodePtr;
NodePtr mergeTwoLists(NodePtr list1, NodePtr list2){
    if(list2 == NULL)
        return list1;
    while(list1 != NULL){
        if(list1->val < list2->val){
            NodePtr new_node = (NodePtr) malloc(sizeof(struct ListNode));
            new_node->val = list1->val;
            new_node->next = list2;
            list2 = new_node;
        }
        else{
            NodePtr temp  = list2;
            if(temp->next != NULL){
                while(temp->next->val < list1->val){
                    temp = temp->next;
                    if(temp->next == NULL) break; 
                }
            }
            NodePtr new_node = (NodePtr) malloc(sizeof(struct ListNode));
            new_node->val = list1->val;
            new_node->next = temp->next;
            temp->next = new_node;
        }
        list1 = list1->next;
    }
    free(list1);
    return list2;
}
