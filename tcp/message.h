#pragma once

struct DataHeader
{
    short dataLength;
    short cmd;
};

struct Login
{
    char userName[32];
    char passWord[32];
};
//命令
enum CMD 
{
    CMD_LOGIN,
    CMD_LOGOUT
};

struct LoginResult
{
    int result;
};

struct LoginOut
{
    char userName[32];
};

struct Loginoutres
{
    int result;
};

