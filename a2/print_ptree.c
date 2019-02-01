#include <stdio.h>
#include <stdlib.h>

#include "ptree.h"


int main(int argc, char **argv) {
    // TODO: Update error checking and add support for the optional -d flag
    // printf("Usage:\n\tptree [-d N] PID\n");

    // NOTE: This only works if no -d option is provided and does not
    // error check the provided argument or generate_ptree. Fix this!
    struct TreeNode *root = NULL;
    generate_ptree(&root, strtol(argv[1], NULL, 10));
    print_ptree(root, 0);

    return 0;
}

