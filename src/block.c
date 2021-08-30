/*
** EPITECH PROJECT, 2019
** block.c
** File description:
** block
*/

#include "lib.h"

block_t *find_block_equal(block_t *block, void *ptr)
{
    if (!ptr)
        return (NULL);
    while (block) {
        if (block->address == ptr)
            return (block);
        block = block->next;
    }
    return (NULL);
}

block_t *find_block(const size_t size, block_t *block)
{
    block_t *last_block = block;
    if (!block)
        return (NULL);
    while (block) {
        if (block->free && block->position == size)
            return (block);
        else if (block->free && block->position > size + sizeof(block_t) + 1) {
            int total = block->position - size;
            void *tmp = block->next;
            block->position = size;
            block->free = false;
            block->next = block->address + size;
            block->next->address = block->next + sizeof(block_t);
            block->next->position = total;
            block->next->next = tmp;
            block->next->previous = block;
            block->next->free = true;
            return (block);
        }
        // bugfix: The value of unused memory is not necessarily 0
        if (block->previous != last_block) {
            return (NULL);
        }
        last_block = block;
        block = block->next;
    }
    return (NULL);
}

void copy_block(block_t *dest, block_t *src)
{
    size_t *pDest;
    size_t *pSrc;
    
    pDest = (size_t*)dest->address;
    pSrc = (size_t*)src->address;
    for (int i = 0; i * sizeof(size_t) < src->position
        && i * sizeof(size_t) < dest->position; ++i)
        pDest[i] = pSrc[i];
}