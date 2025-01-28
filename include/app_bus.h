#include <systemd/sd-bus.h>

typedef struct message_item_struct {
    uint64_t cookie;
    char *memb;
    char *name;
    char *iface;
    struct message_item_struct *next;
} message_item_t;

int bus_init();
int bus_run();