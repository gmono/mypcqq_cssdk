#include "Stdafx.h"
#include "constc.h"
//#include "mypcqq_dllport.h"	//这是自动变量名的port声明
#include "mypcqq_dlport_raw.h" //这是中文变量名的声明
#include "IPorts.h"
using namespace System;
using namespace MPQCore;
//使用模块定义文件
#define dllexp __declspec(dllexport) 
#pragma comment(linker, "/EXPORT:about=_about@0") 
#pragma comment(linker, "/EXPORT:set=_set@0") 
#pragma comment(linker, "/EXPORT:end=_end@0") 
#pragma comment(linker, "/EXPORT:EventFun=_EventFun@36") 
#pragma comment(linker, "/EXPORT:Message=_Message@24")
#pragma comment(linker, "/EXPORT:info=_info@0")

#include <cstring>
extern "C"
{
	//这里不声明无法正常导出
	void __stdcall set();
	void __stdcall about();
	int __stdcall end();
	int __stdcall EventFun(char *qq, int msgtype, int msgctype, char *msgsource, char *dop, char *bep, char *msg, char *rawmsg, char *backptr);
	int __stdcall Message(char *qq, int type, char *rawmsg, char *cookie, char *sessionkey, char *clientkey);
	char * __stdcall info();
}
//此类用于保存全局托管对象
private ref class Common
{
public:
	static IPorts^ portobj=nullptr;
	static bool test()
	{
		if (portobj == nullptr)
		{
			//MessageBox(0, "还没有加载.Net插件模块", "错误", 0);
			return false;
		}
		return true;
	}
};
///
/// \brief set 但插件被按下设置后被调用
///
void __stdcall set()
{
	if (Common::test()) Common::portobj->set();
}
///
/// \brief about 按下关于时被调用
///
void __stdcall about()
{
	
	if (Common::test()) Common::portobj->about();
	else
	{
		//通过关于来加载
		Common::portobj = LoadPLG("Plugin\\testlib.dll");

		if (Common::test()) Common::portobj->init();
		else
		{
			Api_OutPut(".net插件模块加载 失败!");
		}
	}
}
///
/// \brief end 结束时被调用
/// \return 返回非0成功 亦可不返回或为空
int __stdcall end()
{
	if (Common::test()) Common::portobj->end();
	ApiPorts::Api_OutPut(".net中转器，已结束！");//中转器通知
	return 1;
}
///
/// \brief EventFun
/// \param qq 多QQ登录情况下用于识别是哪个Q
/// \param msgtype 信息唯一标识-1 未定义事件 1 好友信息 2,群信息 3,讨论组信息 4,临时会话 1001,被添加好友 1002,好友在线状态改变 1003 被删除好友 1004 签名变更 2001 某人申请加入群 2002 某人被邀请加入群 2003 我被邀请加入群 2005 某人被批准加入了群 2006 某人退出群  2007 某人被管理移除群 2008 某群被解散 2009 某人成为管理员 2010 某人被取消管理员 2011 群名片变动 2012 群名变动//暂未解析 2013 群公告变动
/// \param msgctype 对象申请、被邀请入群事件下该值为1时即对象为不良成员
/// \param msgsource 信息的源头  群号,好友QQ,讨论组ID,临时会话对象QQ等
/// \param dop 主动触发这条信息的对象 T人时为T人的管理员QQ
/// \param bep 被动接受这条信息的对象 T人时为被T对象的QQ
/// \param msg 视情况而定的信息内容  申请入群时为入群理由,添加好友为附加信息,T人之类的为空
/// \param rawmsg 经过解密后的封包字节数据或json结构信息
/// \param backptr 信息回传指针。 视情况而定的返回附加文本信息  拒绝好友申请时则为拒绝理由 方式:’写到内存("测试",参_信息回传文本指针_Out)
/// \return 该函数被动响应各种各样的会话、系统事件
///
int __stdcall EventFun(char *qq,int msgtype,int msgctype,char *msgsource,char *dop,char *bep,char *msg,char *rawmsg,char *backptr)
{
	//if (msgtype > Consts::消息类型_好友&&msgtype<Consts::消息类型_讨论组临时会话&&strcmp(msg,"测试")==0)
	//{
	//	ApiPorts::Api_SendMsg(qq, msgtype, 0, msgsource, dop, "hello");
	//	return 1;
	//}
	if (Common::test())
	{
		//类型转换
		String^ sqq = gcnew String(qq);
		String^ smsc = gcnew String(msgsource);
		String^ sdop = gcnew String(dop);
		String^ sbep = gcnew String(bep);
		String^ smsg = gcnew String(msg);
		String^ srawmsg = gcnew String(rawmsg);
		Backer^ bker = gcnew Backer(backptr);

		Common::portobj->EventFun(sqq, msgtype, msgctype, smsc, sdop, sbep, smsg, srawmsg, bker);
	}

    //返回值-1 已收到信息但拒绝处理
    //返回0 没有收到信息或不被处理
    //返回1 被处理完毕,继续执行其他插件
    //返回2 被处理完毕,阻塞信息不再处理其他插件

    //特殊返回值:
    //0 忽略/取消该事件(如被添加好友 申请加入群
    //10 同意/批准该事件(如被添加好友 申请加入群
    //20 不同意/拒绝该事件(如被添加好友 申请加入群
    //30 单向同意该事件(仅用于被添加好友
	return 1;
}
///该函数收到所有通信信息  返回值-1 已收到信息但拒绝处理   返回0 没有收到信息或不被处理 返回1 被处理完毕,继续执行其他插件 返回2 被处理完毕,阻塞信息不再处理其他插件
/// 框架有可能登录多个QQ  该信息是来自此QQ
///1 UDP收到的原始信息 2 UDP发送的信息
///经过QQApi_Tea加密的通信原文
///用于QQ相关的各种网页接口操作,可直接提交替代登录
/// 通信包所用的加密秘钥
///登录网页服务用的秘钥'
int __stdcall Message(char *qq, int type, char *rawmsg, char *cookie, char *sessionkey, char *clientkey)
{
	if (Common::test())
	{
		//类型转换
		String^ sqq = gcnew String(qq);
		String^ scook = gcnew String(cookie);
		String^ sskey = gcnew String(sessionkey);
		String^ sckey = gcnew String(clientkey);
		String^ sraw = gcnew String(rawmsg);
		return Common::portobj->Message(sqq, type, sraw, scook, sskey, sckey);
	}
	//返回值-1 已收到信息但拒绝处理
	//返回0 没有收到信息或不被处理
	//返回1 被处理完毕,继续执行其他插件
	//返回2 被处理完毕,阻塞信息不再处理其他插
	return 1;
}

void init()
{
	DPLS_INIT_LOADALLPORT();
	//这里写初始化代码
	Api_OutPut(".net中转器，已启动！");
	Api_OutPut("插件右键关于……以启动加载测试");
}

//返回说明
char *infobuf = nullptr;
char * __stdcall info()
{
	if (infobuf) 
	{
		delete infobuf;
	}
	if (Common::test())
	{
		String^ str = Common::portobj->info();
		infobuf = SConvert::ToSByte(str);
		return infobuf;
		//为保险起见 避免错误释放或者内存泄漏 这里使用动态分配缓冲区的方法
	}
	return ".net插件模块尚未加载！";

}
