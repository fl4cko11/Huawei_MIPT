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

    akr_tree_from_prefix(buf_ptr, &(akr.root_node), &akr);

    char answ;
    int on_play = 1;
    while (on_play) {
        fprintf(stdout, "[akr_play] What you want from akinator: [P] [D]\n");
        fprintf(stdout, "[akr_play] P = play, D = get definiton of unit: ");
        scanf(" %c", &answ);

        if (answ == 'P') {
            akr_play(akr.root_node, &akr);
        
            FILE *datafile = fopen(argv[1], "w");
            akr_update_datafile(akr.root_node, datafile);
            fclose(datafile);
        }

        else if (answ == 'D') {
            char *unit = (char *)calloc(buffers_size, sizeof(char)); 
            fprintf(stdout, "[akr_play] enter unit: ");
            scanf("%s", unit);
            akr_get_def_interface(akr.root_node, unit);
        }

        fprintf(stdout, "[akr_play] One more game? Y/N: ");
        scanf(" %c", &answ);
        if (answ == 'Y') on_play = 1;
        else on_play = 0;
    }
    
    return 0;
}
