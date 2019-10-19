/* Operations code */
typedef enum{
    CREATE,
    UPDATE,
    DELETE
} OPCODE;

/* Structure which contains the data */
typedef struct{
    char destination[16];
    char mask;
    char gateway_ip[16];
    char output_interface[32];
}message_body_t;

typedef struct{
    OPCODE op_code;
    message_body_t msg_body;
}sync_message_t;

/**
 *  message_body
 * sync_message
 */