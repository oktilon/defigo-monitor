#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>

#include "bus.h"
#include "app.h"

#define MATCH_SZ    128
#define NAME_SZ     64
#define IFACE_SZ    256
#define PROPERTY_GET    127

sd_bus *bus = NULL; /** DBus pointer */
const char* unique_name = NULL;

int bus_append_argument(bool is_argument_a_string, const char *argument_to_append, char **arguments_string) {
    if (argument_to_append == NULL) {
        return -1;
    }

    if (arguments_string == NULL) {
        return -1;
    }

    if (*arguments_string == NULL) {
        if (is_argument_a_string) {
            *arguments_string = (char*)calloc(1, strlen("\"") + strlen(argument_to_append) + strlen("\"") + 1);
            memcpy(*arguments_string + strlen(*arguments_string), "\"", strlen("\"") + 1);
            memcpy(*arguments_string + strlen(*arguments_string), argument_to_append, strlen(argument_to_append) + 1);
            memcpy(*arguments_string + strlen(*arguments_string), "\"", strlen("\"") + 1);
        } else {
            *arguments_string = (char*)calloc(1, strlen(argument_to_append) + 1);
            memcpy(*arguments_string, argument_to_append, strlen(argument_to_append) + 1);
        }
    } else {
        if (is_argument_a_string) {
            *arguments_string = (char*)realloc(*arguments_string, strlen(*arguments_string) + strlen(" ") + strlen("\"") + strlen(argument_to_append) + strlen("\"") + 1);
            memcpy(*arguments_string + strlen(*arguments_string), " ", strlen(" ") + 1);
            memcpy(*arguments_string + strlen(*arguments_string), "\"", strlen("\"") + 1);
            memcpy(*arguments_string + strlen(*arguments_string), argument_to_append, strlen(argument_to_append) + 1);
            memcpy(*arguments_string + strlen(*arguments_string), "\"", strlen("\"") + 1);
        } else {
            *arguments_string = (char*)realloc(*arguments_string, strlen(*arguments_string) + strlen(" ") + strlen(argument_to_append) + 1);
            memcpy(*arguments_string + strlen(*arguments_string), " ", strlen(" ") + 1);
            memcpy(*arguments_string + strlen(*arguments_string), argument_to_append, strlen(argument_to_append) + 1);
        }
    }

    return 0;
}

int bus_message_decode(sd_bus_message *m, char **arguments) {
    int error = 0;
    char type = 0;
    char container_type[2] = {0};
    const char *contents = NULL;
    int buffer_size = 0;
    char *string_representation_of_argument = NULL;
    uint8_t argument_byte = 0;
    int argument_boolean = 0;
    int16_t argument_int16 = 0;
    uint16_t argument_uint16 = 0;
    int32_t argument_int32 = 0;
    uint32_t argument_uint32 = 0;
    int64_t argument_int64 = 0;
    uint64_t argument_uint64 = 0;
    double argument_double = 0;
    const char *argument_string = NULL;
    int argument_fd = 0;
    char *arguments_tmp = NULL;
    int count = 0;
    static bool is_array_loop = false;
    bool temp;

    while (sd_bus_message_peek_type(m, &type, &contents) > 0) {
        switch (type) {

            case SD_BUS_TYPE_BYTE:
                error = sd_bus_message_read_basic(m, type, &argument_byte);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%u", argument_byte);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%u", argument_byte);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_BOOLEAN:
                error = sd_bus_message_read_basic(m, type, &argument_boolean);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%d", argument_boolean);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%d", argument_boolean);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_INT16:
                error = sd_bus_message_read_basic(m, type, &argument_int16);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%d", argument_int16);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%d", argument_int16);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_UINT16:
                error = sd_bus_message_read_basic(m, type, &argument_uint16);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%u", argument_uint16);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%u", argument_uint16);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_INT32:
                error = sd_bus_message_read_basic(m, type, &argument_int32);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%d", argument_int32);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%d", argument_int32);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_UINT32:
                error = sd_bus_message_read_basic(m, type, &argument_uint32);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%u", argument_uint32);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%u", argument_uint32);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_INT64:
                error = sd_bus_message_read_basic(m, type, &argument_int64);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%ld", argument_int64);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%ld", argument_int64);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_UINT64:
                error = sd_bus_message_read_basic(m, type, &argument_uint64);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%lu", argument_uint64);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%lu", argument_uint64);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_DOUBLE:
                error = sd_bus_message_read_basic(m, type, &argument_double);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%g", argument_double);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%g", argument_double);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_STRING:
            case SD_BUS_TYPE_OBJECT_PATH:
            case SD_BUS_TYPE_SIGNATURE:
                error = sd_bus_message_read_basic(m, type, &argument_string);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(true, argument_string, arguments);
                if (error < 0)
                    goto error_out;

                break;

            case SD_BUS_TYPE_UNIX_FD:
                error = sd_bus_message_read_basic(m, type, &argument_fd);
                if (error < 0)
                    goto error_out;

                buffer_size = snprintf(NULL, 0, "%d", argument_fd);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "%d", argument_fd);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                break;

            case SD_BUS_TYPE_VARIANT:
                error = sd_bus_message_enter_container(m, type, contents);
                if (error < 0)
                    goto error_out;

                // error = bus_append_argument(false, contents, arguments);
                // if (error < 0)
                //     goto error_out;

                free(arguments_tmp);
                arguments_tmp = NULL;

                temp = is_array_loop;
                is_array_loop = false;
                error = bus_message_decode(m, &arguments_tmp);
                if (error < 0)
                    goto error_out;
                is_array_loop = temp;

                error = bus_append_argument(false, arguments_tmp, arguments);
                if (error < 0)
                    goto error_out;

                error = sd_bus_message_exit_container(m);
                if (error < 0)
                    goto error_out;

                break;

            case SD_BUS_TYPE_ARRAY:
                count = 0;

                error = sd_bus_message_enter_container(m, type, contents);
                if (error < 0)
                    goto error_out;

                free(arguments_tmp);
                arguments_tmp = NULL;
                while (sd_bus_message_at_end(m, false) == 0) {
                    is_array_loop = true;
                    error = bus_message_decode(m, &arguments_tmp);
                    if (error < 0)
                        goto error_out;

                    count++;
                }

                is_array_loop = false;

                buffer_size = snprintf(NULL, 0, "=%d", count);
                string_representation_of_argument = (char*)calloc(1, (size_t) buffer_size + 1);
                error = snprintf(string_representation_of_argument, (size_t) buffer_size + 1, "=%d", count);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, string_representation_of_argument, arguments);
                if (error < 0)
                    goto error_out;

                free(string_representation_of_argument);
                string_representation_of_argument = NULL;

                if (count > 0) {
                    error = bus_append_argument(false, arguments_tmp, arguments);
                    if (error < 0)
                        goto error_out;
                }

                error = sd_bus_message_exit_container(m);
                if (error < 0)
                    goto error_out;

                break;

            case SD_BUS_TYPE_DICT_ENTRY:
            case SD_BUS_TYPE_STRUCT:
                error = sd_bus_message_enter_container(m, type, contents);
                if (error < 0)
                    goto error_out;

                free(arguments_tmp);
                arguments_tmp = NULL;

                while (sd_bus_message_at_end(m, false) == 0) {
                    temp = is_array_loop;
                    is_array_loop = false;
                    error = bus_message_decode(m, &arguments_tmp);
                    if (error < 0)
                        goto error_out;
                    is_array_loop = temp;
                }

                if(type == SD_BUS_TYPE_DICT_ENTRY) {
                    container_type[0] = '{';
                } else {
                    container_type[0] = '(';
                }
                error = bus_append_argument(false, container_type, arguments);
                if (error < 0)
                    goto error_out;

                error = bus_append_argument(false, arguments_tmp, arguments);
                if (error < 0)
                    goto error_out;

                if(type == SD_BUS_TYPE_DICT_ENTRY) {
                    container_type[0] = '}';
                } else {
                    container_type[0] = ')';
                }
                error = bus_append_argument(false, container_type, arguments);
                if (error < 0)
                    goto error_out;


                error = sd_bus_message_exit_container(m);
                if (error < 0)
                    goto error_out;

                break;

            default:
                error = -EINVAL;
                goto error_out;
        }

        if (is_array_loop) {
            break;
        }
    }

    goto out;

error_out:
    free(*arguments);

out:
    free(string_representation_of_argument);
    string_representation_of_argument = NULL;
    free(arguments_tmp);
    arguments_tmp = NULL;

    return (error < 0) ? error : 0;
}


void bus_monitor_handler(sd_bus_message *m) {
    uint8_t uType = 0;
    char name[NAME_SZ + 1] = {0};
    char iface[IFACE_SZ + 1] = {0};
    char *data = NULL;
    bool bName = false;
    const char *pp, *pnm;
    int r = sd_bus_message_get_type(m, &uType);
    if(r < 0) {
        selfLogErr("Failed to get message type(%d): %s", r, strerror(-r));
    }

    const char *piface = sd_bus_message_get_interface(m);
    const char *memb = sd_bus_message_get_member(m);

    if(strcmp(memb, "PropertiesChanged") == 0) { // sa{sv}as
        r = sd_bus_message_read_basic(m, 's', &piface);
        if( r < 0 ) {
            selfLogErr("Failed to read PropertiesChanged interface(%d): %s", r, strerror(-r));
            piface = sd_bus_message_get_interface(m);
        }
    }
    if(strcmp(piface, "org.freedesktop.DBus.Properties") == 0 && strcmp(memb, "Get") == 0) {
        r = sd_bus_message_read_basic(m, 's', &piface);
        if( r < 0 ) {
            selfLogErr("Failed to read Get interface(%d): %s", r, strerror(-r));
            piface = sd_bus_message_get_interface(m);
        }
        r = sd_bus_message_read_basic(m, 's', &memb);
        if( r < 0 ) {
            selfLogErr("Failed to read Get interface(%d): %s", r, strerror(-r));
            piface = sd_bus_message_get_interface(m);
        }
        uType = PROPERTY_GET;
    }
    pp = strstr(piface, MONITOR_NAME_PREFIX);
    if(pp) {
        pnm = piface + strlen(MONITOR_NAME_PREFIX);
        bName = true;
    } else {
        pnm = piface;
    }
    pp = strstr(pnm, ".");
    if(bName) {
        strncpy(name, pnm, NAME_SZ);
        if(pp) {
            name[pp-pnm] = 0;
            strncpy(iface, pp + 1, IFACE_SZ);
        }
    } else {
        strncpy(iface, piface, IFACE_SZ);
    }
    bus_message_decode(m, &data);
    switch(uType) {
        case SD_BUS_MESSAGE_METHOD_CALL:
            selfLogInf("\033[1;31mM \033[1;93m%s \033[0m[\033[1;33m%s\033[0m] (\033[0;35m%s\033[0m) to \033[0;37m%s\033[0m", memb, name, data ? data : "-", iface);
            break;

        case PROPERTY_GET:
            selfLogInf("\033[1;93mP \033[1;95m%s \033[0m[\033[1;33m%s\033[0m] from \033[0;37m%s\033[0m", memb, name, iface);
            break;

        case SD_BUS_MESSAGE_SIGNAL:
            selfLogInf("\033[1;36mS \033[1;32m%s \033[0m[\033[1;33m%s\033[0m] (\033[0;35m%s\033[0m) from \033[0;37m%s\033[0m", memb, name, data ? data : "-", iface);
            break;

        case SD_BUS_MESSAGE_METHOD_RETURN:
            selfLogInf("\033[1;31mR \033[1;32m%s \033[0m[\033[1;33m%s\033[0m] (\033[0;35m%s\033[0m) from \033[0;37m%s\033[0m", memb, name, data ? data : "-", iface);
            break;

        case SD_BUS_MESSAGE_METHOD_ERROR:
            selfLogInf("\033[1;31mE \033[1;32m%s \033[0m[\033[1;33m%s\033[0m] (\033[0;35m%s\033[0m) from \033[0;37m%s\033[0m", memb, name, data ? data : "-", iface);
            break;
    }

}

int bus_init() {
    sd_bus_error err = SD_BUS_ERROR_NULL;
    sd_bus_message *call;
    uint32_t flags = 0u;
    char match[MATCH_SZ] = {0};
    int r = sd_bus_open_system(&bus);
    if(r < 0) {
        selfLogErr("Failed to connect to session bus(%d): %s", r, strerror(-r));
        return r;
    }

    // Prepare match expression
    int sz = snprintf(match, MATCH_SZ, "path_namespace='%s',eavesdrop='true'", MONITOR_PATH_PREFIX);
    if( sz <= 0 ) {
        selfLogErr("Failed to prepare match expression: %d", sz);
        return r;
    }

    // Become monitor
    r = sd_bus_message_new_method_call(bus
        , &call
        , "org.freedesktop.DBus"
        , "/org/freedesktop/DBus"
        , "org.freedesktop.DBus.Monitoring"
        , "BecomeMonitor"
    );
    if( r < 0) {
        selfLogErr("Failed create message(%d): %s", r, strerror(-r));
        return r;
    }

    r = sd_bus_message_open_container(call, 'a', "s");
    if( r < 0) {
        selfLogErr("Failed create message container(%d): %s", r, strerror(-r));
        return r;
    }

    r = sd_bus_message_append_basic(call, 's', match);
    if( r < 0) {
        selfLogErr("Failed append message string(%d): %s", r, strerror(-r));
        return r;
    }

    r = sd_bus_message_close_container(call);
    if( r < 0) {
        selfLogErr("Failed close message container(%d): %s", r, strerror(-r));
        return r;
    }

    r = sd_bus_message_append_basic(call, 'u', &flags);
    if( r < 0) {
        selfLogErr("Failed append message uint(%d): %s", r, strerror(-r));
        return r;
    }

    r = sd_bus_call(bus, call, 0, &err, NULL);
    if( r < 0) {
        selfLogErr("Failed to become Monitor(%d): %s", r, strerror(-r));
        if(err.message) selfLogErr("Failed message: %s", err.message);
        return r;
    }

    r = sd_bus_get_unique_name(bus, &unique_name);
    if (r < 0) {
        selfLogErr("Failed to become Monitor(%d): %s", r, strerror(-r));
        return r;
    } else {
        selfLogInf("Unique name: %s", unique_name);
    }


    // // Subscribe
    // r = sd_bus_add_match(bus, NULL, match, bus_monitor_handler, NULL);
    // if(r < 0) {
    //     selfLogErr("Failed to add match(%d): %s", r, strerror(-r));
    //     return r;
    // } else {
    //     selfLogInf("Added match [%s]", match);
    // }
    return 0;
}


int bus_run() {
    int r;
    sd_bus_message *m = NULL;
    bool isMonitor = false;

    for(;;) {
        if(m) sd_bus_message_unref(m);

        r = sd_bus_process(bus, &m);
        if(r < 0) {
            selfLogErr("process error(%d): %s", -r, strerror(-r));
            return r;
        }

        if(!isMonitor) {
            const char *name;

            /* wait until we lose our unique name */
            if (sd_bus_message_is_signal(m, "org.freedesktop.DBus", "NameLost") <= 0)
                continue;

            r = sd_bus_message_read(m, "s", &name);
            if (r < 0) {
                selfLogErr("read error(%d): %s", -r, strerror(-r));
                return r;
            }

            if (strcmp(name, unique_name) == 0) {
                isMonitor = true;
            }

            continue;
        }

        if(m) {
            bus_monitor_handler(m);

            if (sd_bus_message_is_signal(m, "org.freedesktop.DBus.Local", "Disconnected") > 0) {
                selfLogInf("Connection terminated, exiting.");
                return 0;
            }

            continue;
        }

        if(r > 0) continue;

        r = sd_bus_wait(bus, UINT64_MAX);
        if (r < 0) {
            selfLogErr("wait error(%d): %s", -r, strerror(-r));
            return r;
        }
    }

    return r;
}