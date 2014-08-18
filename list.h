#ifndef __LIST_H__
#define __LIST_H__

/*
 * simple double cycle links operations
 */
struct list_head {
  struct list_head *prev, *next;
};

#define LIST_HEAD(name) \
    struct list_head name = {&(name), &(name)}

void inline init_list_head(struct list_head *list)
{
    list->prev = list;
    list->next = list;
}


void inline __list_add__(struct list_head *news, struct list_head *prev, struct list_head *next)
{
    news->next = next;
    news->prev = prev;
    next->prev = news;
    prev->next = news;
}

/*
 * double links add node at between head and tail of list 
 * @news: add node
 * @head: list head to add it after
 */
void inline list_add(struct list_head *news, struct list_head* head)
{
    __list_add__(news, head, head->next);
}

#if 0
/*
 * double links add node to tail of list
 * @news: add node
 * @tail: list tail
 */
void inline list_add_to_tail(struct list_head* news, struct list_head *tail)
{
    news->prev = tail;
    news->next = tail->next;
    tail->next->prev = news;
    tail->next = news;
}
#endif

void inline __list_remove__(struct list_head *del, struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
    del->next = del;
    del->prev = del;
}

/*
 * double links delete node at between head and tail of list
 * @del: delete node,
 * @head: list head to delete it after
 */
void inline list_remove(struct list_head *del, struct list_head *head)
{
    __list_remove__(del, head, head->next->next);
}

#if 0
/*
 * double links delete node at tail of list
 * @del: delete node
 */
void inline list_move_from_tail(struct list_head *del)
{
    del->prev->next = del->next;
    del->next->prev = del->prev;
    del->prev = del;
    del->next = del;
}
#endif

#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)

/*
 * struct member addr caculate struct addr
 * @ptr: struct member pointer
 * @type: type of struct
 * @member: struct member name
 */
#define container_of(ptr, type, member)	 ( {		\
    const typeof(((type *)0)->member) *__mptr = (ptr); 	\
    (type *)((char *)__mptr-offsetof(type,member));} )


/*
 * interate over list
 * @pos: current postion at list
 * @head: the head of list
 */
#define list_for_each(pos, head) 			\
   for((pos)=(head->next); (pos)!=(head); pos=pos->next) 

/*
 * get struct pointer
 * @ptr: struct member pointer
 * @type: type of struct
 * @member: struct member name
 */
#define list_entry(ptr, type, member) 			\
   container_of(ptr, type, member)


/*
 * @pos: struct pointer
 * @head: head pointer of list
 * @member: list name
 */
#define list_for_each_entry(pos, head, member)		      	\
   for(pos=list_entry((head)->next, typeof(*pos), member);     	\
        &pos->member!=(head); 				      	\
        pos=list_entry(pos->member.next, typeof(*pos), member))



#endif
