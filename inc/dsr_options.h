#ifndef DSR_OPTIONS_H
#define DSR_OPTIONS_H

#include <stdint.h>

#define ERROR_CREATE_MSG 0
//路由请求，请求号、目的地址、地址列表、长度
struct rreq_option {
    uint8_t id;
    uint8_t target;
    uint8_t *addr_list;
    uint8_t addr_list_len;
};
//路由回复，地址列表、长度
struct rrep_option {
    uint8_t *addr_list;
    uint8_t addr_list_len;
};
//路由错误，错误类型、源、目的
struct rerr_option {
    uint8_t err_type;
    uint8_t source;
    uint8_t target;
};
//请求确认，请求号
struct areq_option {
    uint8_t id;
};
//回复确认，请求号、源、目的
struct arep_option {
    uint8_t id;
    uint8_t source;
    uint8_t target;
};
//路由
struct rout_option {
    uint8_t segments_left;
    uint8_t *addr_list;
    uint8_t addr_list_len;
};
//数据
struct data_option {
    uint8_t *data;
    uint8_t data_len;
};

int createRREQMsg(uint8_t *buf, uint8_t length, struct rreq_option *header);
int createRREPMsg(uint8_t *buf, uint8_t length, struct rrep_option *header);
int createRERRMsg(uint8_t *buf, uint8_t length, struct rerr_option *header);
int createAREQMsg(uint8_t *buf, uint8_t length, struct areq_option *header);
int createAREPMsg(uint8_t *buf, uint8_t length, struct arep_option *header);
int createROUTMsg(uint8_t *buf, uint8_t length, struct rout_option *header);
int createDATAMsg(uint8_t *buf, uint8_t length, struct data_option *header);

#endif /* DSR_OPTIONS_H */
