#include "akinator_funcs.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <full path to akr_datafile>\n", argv[0]);
        return 1;
    }

    akr_t akr = {};

    char *prefix_buf = (char *)calloc(buffers_size, sizeof(char));
    prefix_buffer_from_akr_datafile(argv[1], prefix_buf);

    char **buf_ptr = (char **)calloc(1, sizeof(char *));
    *buf_ptr = &prefix_buf[0];
    assert(buf_ptr != nullptr);
    assert(*buf_ptr != nullptr);

    akr_tree_from_prefix(buf_ptr, &(akr.root_node), &akr);

    akr_prefix_dump(akr.root_node);
    fprintf(stderr, "\n");
    
    return 0;
}
