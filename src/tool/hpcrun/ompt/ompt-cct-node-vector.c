/******************************************************************************
 * system includes
 *****************************************************************************/

#include <assert.h>



/******************************************************************************
 * local includes
 *****************************************************************************/

#include <hpcrun/messages/messages.h>
#include <hpcrun/memory/hpcrun-malloc.h>
#include "ompt-cct-node-vector.h"

#define PRINT(...) fprintf(stderr, __VA_ARGS__)

/******************************************************************************
 * type definitions 
 *****************************************************************************/

struct ompt_cct_node_vector_s {
  cct_node_t **nodes;
  uint64_t size;
  uint64_t capacity;
}; 


ompt_cct_node_vector_t *ompt_cct_node_vector_init()
{
  ompt_cct_node_vector_t *vector = (ompt_cct_node_vector_t *)hpcrun_malloc(sizeof(ompt_cct_node_vector_t));
  vector->size = 0;
  vector->capacity = 0;
  ompt_cct_node_vector_reserve(vector, 32); // TODO(keren): increase it
  return vector;
}


void ompt_cct_node_vector_reserve(ompt_cct_node_vector_t *vector, uint64_t capacity)
{
  // FIXME(keren): free memory
  if (capacity > vector->capacity) {
    cct_node_t **new_nodes = (cct_node_t **)hpcrun_malloc(sizeof(cct_node_t *) * (capacity));
    size_t i = 0;
    for (; i < vector->size; ++i) {
      new_nodes[i] = vector->nodes[i];
    }
    vector->nodes = new_nodes;
  }
  vector->capacity = capacity;
}


void ompt_cct_node_vector_push_back(ompt_cct_node_vector_t *vector, cct_node_t *node)
{
  if (vector->size == vector->capacity) {
    ompt_cct_node_vector_reserve(vector, vector->capacity * 2);
  }
  vector->nodes[vector->size] = node;
  vector->size++;
}


cct_node_t *ompt_cct_node_vector_get(ompt_cct_node_vector_t *vector, uint64_t host_op_seq_id)
{
  if (host_op_seq_id < vector->size) {
    return vector->nodes[host_op_seq_id];
  } else {
    // out of the bound
    return NULL;
  }
}
