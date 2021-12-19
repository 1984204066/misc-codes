#include "MsgBinaryArchive.h"
// 定义一个有两个成员变量的消息结构
MSG2(stTestMsg,
     float, x,
     std::string, str);
    
// 定义一个有四个成员变量的消息结构
MSG4(A,
     std::list<int>, _list,
     int, _int,
     std::string, _str,
     char, _char);
    
void test()
{
  std::string recvMsgBuf;
    
  // 发送
  {
    MsgPack msgPack;
    
    stTestMsg testmsg = {3.2f,"fdsfd"};
    A a;
    a._char = 'a';
    a._int = 343;
    a._list.push_back(3);
    a._list.push_back(432);
    a._str = "test str";
    
    // 打包消息
    msgPack & a;		// 重置消息缓冲，并打包数据
    msgPack << testmsg;	// 在当前包后面添加数据
    
    // 可以用这两个玩意儿去发送消息了
    const char* msgBuf = msgPack.buffer();
    size_t msgSize = msgPack.size();
    recvMsgBuf.resize(msgSize);
    memcpy((char*)recvMsgBuf.c_str(), msgBuf, msgSize);
  }
    
  // 接收
  {
    MsgUnpack msgUnpack;
    
    stTestMsg testmsg;
    A a;
    
    // 设置接收到的包数据
    msgUnpack.reset(recvMsgBuf.c_str(), recvMsgBuf.size());
    // 解包数据到消息结构体内
    msgUnpack >> a >> testmsg;
  }
}
