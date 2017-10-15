#include <stdlib.h>

// dunno how to include this shit yet
#include "../bstrlib.h"

static int default_compare(void *a, void *b) {
    return bstrcmp((bstring) a, (bstring) b);
}

BSTree *BSTree_create(BSTree_compare compare) {
    BSTree *map = calloc(1, sizeof(BSTree));
    check_mem(map);

    map->compare = compare == NULL ? default_compare : compare;

    return map;

error:
    if (map) {
        BSTree_destroy(map);
    }
    return NULL;
}

static int BSTree_destroy_cb(BSTreeNode *node) {
    free(node);
    return 0;
}

void BSTree_destroy(BSTree *map) {
    if (map) {
        BSTree_traverse(map, BSTree_destroy_cb);
        free(map);
    }
}

static inline int BSTree_traverse_nodes(BSTreeNode *node, BSTree_traverse_cb traverse_cb) {
    int rc = 0;

    if (node->left) {
        rc = BSTree_traverse_nodes(node->left, traverse_cb);
        if (rc != 0) {
            return rc;
        }
    }

    if (node->right) {
        rc = BSTree_traverse_nodes(node->right, traverse_cb);
        if (rc != 0) {
            return rc;
        }
    }

    return traverse_cb(node);
}

int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb) {
    if (map->root) {
        return BSTree_traverse_nodes(map->root, traverse_cb);
    }
}



