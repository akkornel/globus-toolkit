#if !defined(GLOBUS_I_GRIDFTP_SERVER_CONTROL_H)
#define GLOBUS_I_GRIDFTP_SERVER_CONTROL_H 1

#include "globus_gridftp_server_control.h"
#include "globus_xio.h"

#define GLOBUS_GRIDFTP_SERVER_HASHTABLE_SIZE    256
#define GLOBUS_GRIDFTP_VERSION_CTL              1

GlobusDebugDeclare(GLOBUS_GRIDFTP_SERVER_CONTROL);

#define GlobusGSDebugPrintf(level, message)                                \
    GlobusDebugPrintf(GLOBUS_GRIDFTP_SERVER_CONTROL, level, message)

#define GlobusGridFTPServerDebugEnter()                                     \
    GlobusGSDebugPrintf(                                                    \
        GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_TRACE,                          \
        ("[%s] Entering\n", _gridftp_server_name))

#define GlobusGridFTPServerDebugExit()                                      \
    GlobusGSDebugPrintf(                                                    \
        GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_TRACE,                          \
        ("[%s] Exiting\n", _gridftp_server_name))
    
#define GlobusGridFTPServerDebugExitWithError()                             \
    GlobusGSDebugPrintf(                                                    \
        GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_TRACE,                          \
        ("[%s] Exiting with error\n", _gridftp_server_name))
    
#define GlobusGridFTPServerDebugInternalEnter()                             \
    GlobusGSDebugPrintf(                                                    \
        GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_INTERNAL_TRACE,                 \
        ("[%s] I Entering\n", _gridftp_server_name))

#define GlobusGridFTPServerDebugInternalExit()                              \
    GlobusGSDebugPrintf(                                                    \
        GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_INTERNAL_TRACE,                 \
        ("[%s] I Exiting\n", _gridftp_server_name))
    
#define GlobusGridFTPServerDebugInternalExitWithError()                     \
    GlobusGSDebugPrintf(                                                    \
        GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_INTERNAL_TRACE,                 \
        ("[%s] I Exiting with error\n", _gridftp_server_name))


#define GlobusGridFTPServerErrorParameter(param_name)                       \
    globus_error_put(                                                       \
        globus_error_construct_error(                                       \
            GLOBUS_GRIDFTP_SERVER_CONTROL_MODULE,                           \
            GLOBUS_NULL,                                                    \
            GLOBUS_GRIDFTP_SERVER_CONTROL_ERROR_PARAMETER,                  \
            __FILE__,                                                       \
            _gridftp_server_name,                                           \
            __LINE__,                                                       \
            "Bad parameter, %s",                                            \
            (param_name)))

#define GlobusGridFTPServerErrorMemory(mem_name)                            \
    globus_error_put(                                                       \
        globus_error_construct_error(                                       \
            GLOBUS_GRIDFTP_SERVER_CONTROL_MODULE,                           \
            GLOBUS_NULL,                                                    \
            GLOBUS_GRIDFTP_SERVER_CONTROL_ERROR_MEMORY,                     \
            __FILE__,                                                       \
            _gridftp_server_name,                                           \
            __LINE__,                                                       \
            "Memory allocation failed on %s",                               \
            (mem_name)))

#define GlobusGridFTPServerErrorState(state)                                \
    globus_error_put(                                                       \
        globus_error_construct_error(                                       \
            GLOBUS_GRIDFTP_SERVER_CONTROL_MODULE,                           \
            GLOBUS_NULL,                                                    \
            GLOBUS_GRIDFTP_SERVER_CONTROL_ERROR_STATE,                      \
            __FILE__,                                                       \
            _gridftp_server_name,                                           \
            __LINE__,                                                       \
            "Invalid state: %d",                                            \
            (state)))

#define GlobusGridFTPServerNotAuthenticated()                               \
    globus_error_put(                                                       \
        globus_error_construct_error(                                       \
            GLOBUS_GRIDFTP_SERVER_CONTROL_MODULE,                           \
            GLOBUS_NULL,                                                    \
            GLOBUS_GRIDFTP_SERVER_CONTROL_NO_AUTH,                          \
            __FILE__,                                                       \
            _gridftp_server_name,                                           \
            __LINE__,                                                       \
            "Not yet authenticated."))

#define GlobusGridFTPServerPostAuthenticated()                              \
    globus_error_put(                                                       \
        globus_error_construct_error(                                       \
            GLOBUS_GRIDFTP_SERVER_CONTROL_MODULE,                           \
            GLOBUS_NULL,                                                    \
            GLOBUS_GRIDFTP_SERVER_CONTROL_POST_AUTH,                        \
            __FILE__,                                                       \
            _gridftp_server_name,                                           \
            __LINE__,                                                       \
            "Not yet authenticated."))

#define GlobusGridFTPServerNotACommand()                                    \
    globus_error_put(                                                       \
        globus_error_construct_error(                                       \
            GLOBUS_GRIDFTP_SERVER_CONTROL_MODULE,                           \
            GLOBUS_NULL,                                                    \
            GLOBUS_GRIDFTP_SERVER_CONTROL_NO_COMMAND,                       \
            __FILE__,                                                       \
            _gridftp_server_name,                                           \
            __LINE__,                                                       \
            "Command not implemented."))

#define GlobusGridFTPServerOpSetUserArg(_in_op, _in_arg)                    \
    (_in_op)->user_arg = (_in_arg);                                         \

#define GlobusGridFTPServerOpGetUserArg(_in_op)                             \
    ((_in_op)->user_arg)

#define GlobusGridFTPServerOpGetServer(_in_op)                              \
    ((_in_op)->server)

#define GlobusGridFTPServerOpGetPModArg(_in_op)                             \
    ((_in_op)->pmod_arg)

#define GlobusGridFTPServerOpSetPModArg(_in_op, _in_arg)                    \
    (_in_op)->pmod_arg = (_in_arg);                                         \

struct globus_i_gs_attr_s;

typedef enum globus_i_gsc_debug_levels_e
{ 
    GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_ERROR = 1,
    GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_WARNING = 2,
    GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_TRACE = 4,
    GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_INTERNAL_TRACE = 8,
    GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_INFO = 16,
    GLOBUS_GRIDFTP_SERVER_CONTROL_DEBUG_INFO_VERBOSE = 32
} globus_i_gsc_debug_levels_t;

typedef enum globus_i_gsc_error_type_e
{
    GLOBUS_GRIDFTP_SERVER_CONTROL_ERROR_PARAMETER,
    GLOBUS_GRIDFTP_SERVER_CONTROL_ERROR_STATE,
    GLOBUS_GRIDFTP_SERVER_CONTROL_ERROR_MEMORY,
    GLOBUS_GRIDFTP_SERVER_CONTROL_NO_AUTH,
    GLOBUS_GRIDFTP_SERVER_CONTROL_POST_AUTH,
    GLOBUS_GRIDFTP_SERVER_CONTROL_NO_COMMAND,
    GLOBUS_GRIDFTP_SERVER_CONTROL_MALFORMED_COMMAND
} globus_i_gsc_error_type_t;

typedef enum globus_i_gsc_mlsx_fact_e
{
    GLOBUS_GSC_MLSX_FACT_TYPE = 'T',
    GLOBUS_GSC_MLSX_FACT_MODIFY = 'M',
    GLOBUS_GSC_MLSX_FACT_CHARSET = 'C',
    GLOBUS_GSC_MLSX_FACT_SIZE = 'S',
    GLOBUS_GSC_MLSX_FACT_PERM = 'P',
    GLOBUS_GSC_MLSX_FACT_UNIXMODE = 'U',
    GLOBUS_GSC_MLSX_FACT_UNIQUE = 'Q'
} globus_i_gsc_mlsx_fact_t;

typedef void
(*globus_i_gsc_auth_cb_t)(
    struct globus_i_gsc_op_s *              op,
    globus_result_t                         result,
    void *                                  user_arg);

typedef void
(*globus_i_gsc_resource_cb_t)(
    struct globus_i_gsc_op_s *              op,
    globus_result_t                         result,
    char *                                  path,
    globus_gridftp_server_control_stat_t *  stat_info,
    int                                     stat_count,
    void *                                  user_arg);

typedef void
(*globus_i_gsc_passive_cb_t)(
    struct globus_i_gsc_op_s *              op,
    globus_result_t                         result,
    const char **                           cs,
    int                                     addr_count,
    void *                                  user_arg);

typedef void
(*globus_i_gsc_port_cb_t)(
    struct globus_i_gsc_op_s *              op,
    globus_result_t                         result,
    void *                                  user_arg);

typedef void
(*globus_i_gsc_transfer_cb_t)(
    struct globus_i_gsc_op_s *              op,
    globus_result_t                         result,
    void *                                  user_arg);

typedef struct globus_i_gsc_data_s
{
    int                                     stripe_count;
    void *                                  user_handle;
    globus_gridftp_server_control_data_dir_t dir;
} globus_i_gsc_data_t;

typedef enum globus_i_gsc_op_type_e
{
    GLOBUS_L_GSC_OP_TYPE_DONE,
    GLOBUS_L_GSC_OP_TYPE_AUTH,
    GLOBUS_L_GSC_OP_TYPE_RESOURCE,
    GLOBUS_L_GSC_OP_TYPE_CREATE_PASV,
    GLOBUS_L_GSC_OP_TYPE_CREATE_PORT,
    GLOBUS_L_GSC_OP_TYPE_SEND,
    GLOBUS_L_GSC_OP_TYPE_RECV,
    GLOBUS_L_GSC_OP_TYPE_DESTROY,
    GLOBUS_L_GSC_OP_TYPE_LIST,
    GLOBUS_L_GSC_OP_TYPE_NLST,
    GLOBUS_L_GSC_OP_TYPE_MLSD
} globus_i_gsc_op_type_t;

typedef struct globus_i_gsc_event_data_s
{
    globus_callback_handle_t                periodic_handle;
    int                                     perf_frequency;
    int                                     restart_frequency;
    int                                     stripe_count;
    globus_off_t *                          stripe_total_bytes;
    globus_bool_t                           perf_running;
} globus_i_gsc_event_data_t;

typedef struct globus_i_gsc_handle_opts_s
{
    char                                    mlsx_fact_str[8];
    int                                     parallelism;
    globus_size_t                           send_buf;
    globus_size_t                           receive_buf;
    globus_bool_t                           refresh;
    globus_size_t                           packet_size;
    globus_bool_t                           delayed_passive;
    int                                     port_max;
    int                                     pasv_max;
    globus_bool_t                           passive_only;
    int                                     dc_parsing_alg;
    int                                     perf_frequency;
    int                                     restart_frequency;
    globus_gridftp_server_control_network_protocol_t     port_prt;
    globus_gridftp_server_control_network_protocol_t     pasv_prt;
} globus_i_gsc_handle_opts_t;

typedef struct globus_i_gsc_user_funcs_s
{
    globus_hashtable_t                                  send_cb_table;
    globus_hashtable_t                                  recv_cb_table;
    globus_gridftp_server_control_transfer_cb_t         default_send_cb;
    globus_gridftp_server_control_transfer_cb_t         default_recv_cb;
    globus_gridftp_server_control_auth_cb_t             auth_cb;
    globus_gridftp_server_control_passive_connect_cb_t  passive_cb;
    globus_gridftp_server_control_active_connect_cb_t   active_cb;
    globus_gridftp_server_control_data_destroy_cb_t     data_destroy_cb;
    globus_gridftp_server_control_list_cb_t             list_cb;
    globus_gridftp_server_control_resource_cb_t         resource_cb;
    globus_gridftp_server_control_cb_t                  done_cb;
    globus_gridftp_server_control_abort_cb_t            abort_cb;
} globus_i_gsc_user_funcs_t;

typedef struct globus_i_gsc_restart_s
{
    globus_off_t *                          offset_a;
    globus_off_t *                          length_a;
    int                                     size;
    int                                     ndx;
    globus_priority_q_t                     q;
} globus_i_gsc_restart_t;

typedef struct globus_i_gsc_op_s
{
    globus_i_gsc_op_type_t                  type;

    int                                     ref;
    struct globus_i_gsc_server_handle_s *   server_handle;
    globus_result_t                         res;

    globus_list_t *                         cmd_list;

    /* stuff for auth */
    globus_bool_t                           authenticated;
    char *                                  username;
    char *                                  password;
    gss_cred_id_t                           cred;
    gss_cred_id_t                           del_cred;
    globus_i_gsc_auth_cb_t                  auth_cb;
    globus_i_gsc_resource_cb_t              stat_cb;
    globus_i_gsc_transfer_cb_t              list_cb;

    globus_gridftp_server_control_stat_t *  stat_info;
    int                                     stat_count;

    uid_t                                   uid;

    /* stuff for resource */
    char *                                  path;
    globus_gridftp_server_control_resource_mask_t mask;

    /* stuff for port/pasv */
    char **                                 cs;
    int                                     max_cs;
    int                                     net_prt;
    globus_i_gsc_passive_cb_t               passive_cb;
    globus_i_gsc_port_cb_t                  port_cb;
    globus_i_gsc_transfer_cb_t              transfer_cb;

    char *                                  command;

    /* stuff for transfer */
    char *                                  mod_name;
    char *                                  mod_parms;
    globus_gridftp_server_control_transfer_cb_t user_data_cb;
    globus_bool_t                           transfer_started;

    globus_i_gsc_restart_t *                restart_marker;
    globus_i_gsc_event_data_t               event;

    void *                                  user_arg;
} globus_i_gsc_op_t;

typedef struct globus_i_gsc_attr_s
{
    int                                     version_ctl;
    char *                                  modes;
    char *                                  types;
    char *                                  base_dir;
    char *                                  post_auth_banner;
    char *                                  pre_auth_banner;

    globus_i_gsc_user_funcs_t               funcs;
} globus_i_gsc_attr_t;


extern globus_hashtable_t               globus_i_gs_default_attr_command_hash;

/*
 *  internal functions for adding commands.
 */

/*
 *   959 Structures
 */
typedef enum globus_l_gsc_state_e
{
    GLOBUS_L_GSC_STATE_OPEN,
    GLOBUS_L_GSC_STATE_PROCESSING,
    GLOBUS_L_GSC_STATE_ABORTING,
    GLOBUS_L_GSC_STATE_ABORTING_STOPPING,
    GLOBUS_L_GSC_STATE_STOPPING,
    GLOBUS_L_GSC_STATE_STOPPED,
} globus_l_gsc_state_t;

/* the server handle */
typedef struct globus_i_gsc_server_handle_s
{
    int                                     version_ctl;

    globus_mutex_t                          mutex;

    /*
     *  authentication information
     */
    int                                     ref;

    char *                                  username;
    char *                                  pw;
    gss_cred_id_t                           cred;
    gss_cred_id_t                           del_cred;
    uid_t                                   uid;
    char                                    dcau;
    char                                    prot;
    globus_bool_t                           authenticated;

    char *                                  post_auth_banner;
    char *                                  pre_auth_banner;

    /*
     *  state information  
     */
    char *                                  cwd;
    char                                    type;
    char                                    mode;
    char *                                  modes;
    char *                                  types;
    int                                     stripe_count;

    /* opts state */
    globus_i_gsc_handle_opts_t              opts;

    /*
     *  user function pointers
     */
    void *                                  user_arg;
    void *                                  abort_arg;

    globus_i_gsc_restart_t *                restart_marker;

    globus_i_gsc_user_funcs_t               funcs;

    globus_i_gsc_data_t *                   data_object;

    globus_result_t                         cached_res;
    globus_list_t *                         feature_list;

    /* 
     *  read.c members 
     */
    globus_bool_t                           reply_outstanding;
    globus_xio_handle_t                     xio_handle;
    globus_l_gsc_state_t                    state;
    globus_fifo_t                           read_q;
    globus_fifo_t                           reply_q;
    int                                     abort_cnt;
    globus_hashtable_t                      cmd_table;
    struct globus_i_gsc_op_s *              outstanding_op;
} globus_i_gsc_server_handle_t;

void
globus_i_gsc_terminate(
    globus_i_gsc_server_handle_t *          server_handle,
    globus_bool_t                           nice);

char *
globus_i_gsc_get_help(
    globus_i_gsc_server_handle_t *          server_handle,
    const char *                            command_name);

globus_result_t
globus_i_gsc_intermediate_reply(
    globus_i_gsc_op_t *                     op,
    char *                                  reply_msg);

globus_result_t
globus_i_gsc_authenticate(
    globus_i_gsc_op_t *                     op,
    const char *                            user,
    const char *                            pass,
    gss_cred_id_t                           cred,
    gss_cred_id_t                           del_cred,
    globus_i_gsc_auth_cb_t            cb,
    void *                                  user_arg);

globus_result_t
globus_i_gsc_list(
    globus_i_gsc_op_t *                     op,
    const char *                            path,
    globus_gridftp_server_control_resource_mask_t mask,
    globus_i_gsc_op_type_t                  type,
    globus_i_gsc_transfer_cb_t              list_cb,
    void *                                  user_arg);

globus_result_t
globus_i_gsc_resource_query(
    globus_i_gsc_op_t *                     op,
    const char *                            path,
    globus_gridftp_server_control_resource_mask_t mask,
    globus_i_gsc_resource_cb_t              cb,
    void *                                  user_arg);

globus_result_t
globus_i_gsc_passive(
    globus_i_gsc_op_t *                     op,
    int                                     max,
    int                                     net_prt,
    globus_i_gsc_passive_cb_t               cb,
    void *                                  user_arg);

globus_result_t
globus_i_gsc_port(
    globus_i_gsc_op_t *                     op,
    const char **                           contact_strings,
    int                                     stripe_count,
    int                                     net_prt,
    globus_i_gsc_port_cb_t                  cb,
    void *                                  user_arg);

globus_result_t
globus_i_gsc_send(
    globus_i_gsc_op_t *                     op,
    const char *                            path,
    const char *                            mod_name,
    const char *                            mod_parms,
    globus_i_gsc_transfer_cb_t              data_cb,
    void *                                  user_arg);

globus_result_t
globus_i_gsc_recv(
    globus_i_gsc_op_t *                     op,
    const char *                            path,
    const char *                            mod_name,
    const char *                            mod_parms,
    globus_i_gsc_transfer_cb_t              data_cb,
    void *                                  user_arg);

void
globus_i_gsc_add_commands(
    globus_i_gsc_server_handle_t *          server_handle);

globus_result_t
globus_i_gsc_command_panic(
    globus_i_gsc_op_t *                     op);

char *
globus_i_gsc_concat_path(
    globus_i_gsc_server_handle_t *          i_server,
    const char *                            in_path);

char *
globus_i_gsc_list_single_line(
    globus_gridftp_server_control_stat_t *  stat_info);

char *
globus_i_gsc_list_line(
    globus_gridftp_server_control_stat_t *  stat_info,
    int                                     stat_count);

char *
globus_i_gsc_nlst_line(
    globus_gridftp_server_control_stat_t *  stat_info,
    int                                     stat_count);

char *
globus_i_gsc_mlsx_line_single(
    const char *                            mlsx_fact_string,
    int                                     uid,
    globus_gridftp_server_control_stat_t *  stat_info);

char *
globus_i_gsc_mlsx_line(
    globus_i_gsc_server_handle_t *          server_handle,
    globus_gridftp_server_control_stat_t *  stat_info,
    int                                     stat_count);

char *
globus_i_gsc_string_to_959(
    const char *                            in_str);

globus_i_gsc_restart_t *
globus_i_gsc_restart_create();

void
globus_i_gsc_restart_add(
    globus_i_gsc_restart_t *                restart,
    globus_off_t                            offset,
    globus_off_t                            length);

void
globus_i_gsc_restart_destroy(
    globus_i_gsc_restart_t *                restart);


#endif
