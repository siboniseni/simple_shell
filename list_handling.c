lists.c code

#include "shell.h"

/**
 * addNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *addNode(list_t **head, const char *str, int num)
{
    list_t *new_head;

    if (!head)
        return (NULL);
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);
    my_memset((void *)new_head, 0, sizeof(list_t));
    new_head->num = num;
    if (str)
    {
        new_head->str = my_strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }
    new_head->next = *head;
    *head = new_head;
    return (new_head);
}

/**
 * addNode_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *addNode_end(list_t **head, const char *str, int num)
{
    list_t *new_node, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);
    my_memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;
    if (str)
    {
        new_node->str = my_strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next != NULL)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;
    return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
    size_t count = 0;

    while (h != NULL)
    {
        my_puts(h->str ? h->str : "(nil)");
        my_puts("\n");
        h = h->next;
        count++;
    }
    return (count);
}

/**
 * delete_node_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_index(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int count = 0;

    if (!head || !*head)
        return (0);

    if (index == 0)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return (1);
    }
    node = *head;
    while (node != NULL)
    {
        if (count == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        count++;
        prev_node = node;
        node = node->next;
    }
    return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
    list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;
    head = *head_ptr;
    node = head;
    while (node != NULL)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
    *head_ptr = NULL;
}
