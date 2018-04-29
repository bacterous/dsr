#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dsr.h"

#define ERROR -1

struct msg_t {
    uint8_t buffer[MSG_MAX_LEN];
    uint8_t length;
    uint8_t target;
};
//网络结点，address：地址、queue_index:消息队列当前消息个数、msg_queue:消息队列、recv_msg:接收消息缓冲
struct dsr_t {
    uint8_t address;
    int queue_index;
    struct msg_t msg_queue[MSG_BUFFER_SIZE];
    struct msg_t recv_msg;
};

/* private prototypes */
static int queue_message(DSR_Node node, struct msg_t msg);

/* public interface */
//创建结点
DSR_Node DSR_init(uint8_t node_addr)
{
    DSR_Node node;

    node = calloc(1, sizeof(struct dsr_t));
    node->address = node_addr;

    return node;
}
//销毁
void DSR_destroy(DSR_Node *node)
{
    if (*node != NULL)
        free(*node);

    *node = NULL;
}
//发送消息，addr：目的结点 buf：消息内容
int DSR_send(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t length)
{
    if (NULL == node)
        return ERROR;

    struct msg_t msg;
    msg.target = addr;
    memcpy(msg.buffer, buf, length);
    msg.length = length;
    //将处理好的消息放入结点的消息队列
    if (queue_message(node, msg) != 0)
        return ERROR;

    return length;
}
//接收消息
int DSR_receive(DSR_Node node, uint8_t *addr, uint8_t *buf, uint8_t length)
{
    if (NULL == node)
        return ERROR;

    *addr = node->recv_msg.target;
    memcpy(buf, node->recv_msg.buffer, length);

    return node->recv_msg.length;
}
//路由确认
int DSR_getRouteCount(DSR_Node node)
{
    if (NULL == node)
        return ERROR;

    return 0;
}

/* private functions implementations */
//将消息在结点按序排队，并控制消息队列容量
static int queue_message(DSR_Node node, struct msg_t msg)
{
    if (node->queue_index >= MSG_BUFFER_SIZE) {
        return ERROR;
    }
    node->msg_queue[node->queue_index] = msg;
    node->queue_index++;

    return 0;
}


/* testing functions */
//测试消息队列相关信息
const uint8_t * getMsg(DSR_Node node, int index)
{
    return node->msg_queue[index].buffer;
}

int getMsgLen(DSR_Node node, int index)
{
    return node->msg_queue[index].length;
}

uint8_t getMsgTarget(DSR_Node node, int index)
{
    return node->msg_queue[index].target;
}
//设定接收信息内容
void setRcvMsg(DSR_Node node, uint8_t addr, uint8_t *buf, uint8_t buf_len)
{
    node->recv_msg.target = addr;
    memcpy(node->recv_msg.buffer, buf, buf_len);
    node->recv_msg.length = buf_len;
}
//返回结点地址
uint8_t getNodeAddr(DSR_Node node)
{
    return node->address;
}
