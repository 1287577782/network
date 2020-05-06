## Socket api 建立建议TCP客户端、客户端
- 服务端
    - 建立一个socket
    - 绑定接受客户端连接的端口
    - 监听网络监听端口
    - 等待接收客户端连接accept
    - 向客户端发送数据
    - 关闭socket

- 客户端
    - 建立socket
    - 连接服务器
    - 接收服务器信息
    - 关闭socket
