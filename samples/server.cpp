#include <ucorf/server.h>
#include <ucorf/net_transport.h>
#include "echo.rpc.h"
#include <iostream>
using namespace Echo;

// 1.继承代码生成器生成的类，并重写定义的rpc接口
struct MyEcho : public ::Echo::UcorfEchoService
{
    virtual bool Echo(EchoRequest & request, EchoResponse & response)
    {
        // 处理请求
        response.set_code(request.code());
        return true;
    }
};

int main()
{
    // 2.创建server对象
    ucorf::Server server;

    // 3.注册MyEcho服务
    server.RegisterService(boost::shared_ptr<IService>(new MyEcho));

    // 4.启动监听端口
    ucorf::boost_ec ec = server.Listen("tcp://127.0.0.1:8080");     // 监听本机8080端口

    // 5.启动协程框架主循环
    co_sched.RunLoop();     

    return 0;
}

