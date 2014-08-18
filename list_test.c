#include <stdio.h>
#include "list.h"

struct node{
   struct list_head list;
   int data;
};

void main()
{

   struct list_head *temp = NULL;

   struct node test_node[20];
   struct node *node_pos = NULL;

   int i = 0;

   LIST_HEAD(head);	

   //insert operation
   for(i=0, temp=&head; i<20; i++, temp=temp->next)
   {
	test_node[i].data = i;
	list_add(&(test_node[i].list), temp);
   }

   //over list 
   list_for_each_entry(node_pos, &head, list)
         printf("data is %d\n", node_pos->data);

   //remove operation
   printf("remove operation:\n");
   list_for_each_entry(node_pos, &head, list)
   {
	if(node_pos->data == 8)
        {
	   list_remove(&node_pos->list, node_pos->list.prev);
           break;
	}
   }

   list_for_each_entry(node_pos, &head, list)
     printf("%d\n", node_pos->data);
}
