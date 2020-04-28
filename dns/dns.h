#pragma once
typedef struct
{
    unsigned short id;       // identification number
    unsigned short flags;
    unsigned short q_count;  // number of question entries
    unsigned short ans_count; // number of answer entries
    unsigned short auth_count; // number of authority entries
    unsigned short add_count; // number of resource entries    
} DNSHeader;
typedef struct _DNSQuery
{
    unsigned short type;
    unsigned short classes;
} DNSQuery;

