//月落专用易语言常量声明转换器生成
//QQ:973544732
namespace MPQCore
{

	public ref class Consts
	{
	public:

		static const int 消息类型_未定义 = -1;


		static const int 消息类型_好友 = 1;


		static const int 消息类型_群 = 2;


		static const int 消息类型_讨论组 = 3;


		static const int 消息类型_群临时会话 = 4;


		static const int 消息类型_讨论组临时会话 = 5;


		static const int 处理_忽略或取消 = 0;


		static const int 处理_同意或确定 = 10;


		static const int 处理_拒绝 = 20;


		static const int 处理_单向同意 = 10;


		static const int 消息类型_被单向添加好友 = 1000;


		static const int 消息类型_被请求添加好友 = 1001;


		static const int 消息类型_好友状态改变 = 1002;


		static const int 消息类型_被删除好友 = 1003;


		static const int 消息类型_好友签名变更 = 1004;


		static const int 消息类型_说说被评论 = 1005;


		static const int 消息类型_好友正在输入 = 1006;


		static const int 消息类型_好友今天首次发起会话 = 1007;


		static const int 消息类型_被好友抖动 = 1008;


		static const int 消息类型_某人申请加入群 = 2001;


		static const int 消息类型_某人被邀请加入群 = 2002;


		static const int 消息类型_我被邀请加入群 = 2003;


		static const int 消息类型_某人被批准加入了群 = 2005;


		static const int 消息类型_某人退出群 = 2006;


		static const int 消息类型_某人被管理移除群 = 2007;


		static const int 消息类型_某群被解散 = 2008;


		static const int 消息类型_某人成为管理 = 2009;


		static const int 消息类型_某人被取消管理 = 2010;


		static const int 消息类型_群名片变动 = 2011;


		static const int 消息类型_群名变动 = 2012;


		static const int 消息类型_群公告变动 = 2013;


		static const int 消息类型_对象被禁言 = 2014;


		static const int 消息类型_对象被解除禁言 = 2015;


		static const int 消息类型_群管开启全群禁言 = 2016;


		static const int 消息类型_群管关闭全群禁言 = 2017;


		static const int 消息类型_群管开启匿名聊天 = 2018;


		static const int 消息类型_群管关闭匿名聊天 = 2019;


		static const int 消息类型_框架加载完成 = 10000;


		static const int 消息类型_框架即将重启 = 10001;


		static const int 消息类型_添加了一个新的帐号 = 11000;


		static const int 消息类型_QQ登录完成 = 11001;


		static const int 消息类型_QQ被手动离线 = 11002;


		static const int 消息类型_QQ被强制离线 = 11003;


		static const int 消息类型_QQ长时间无响应或掉线 = 11004;


		//返回20可拒绝加载 其他返回值均视为允许
		static const int 消息类型_本插件载入 = 12000;


		//返回20可拒绝启用 其他返回值均视为允许启用
		static const int 消息类型_用户启用本插件 = 12001;


		//无权拒绝
		static const int 消息类型_用户禁用本插件 = 12002;


		//点击方式参考子类型.  1=左键单击 2=右键单击 3=左键双击
		static const int 消息类型_插件被点击 = 12003;


		static const int 消息类型_收到财付通转账 = 80001;


		static const int 队列_未处理 = 0;


		static const int 队列_继续执行 = 1;


		static const int 队列_中断_阻塞 = 2;


		static const int 状态_在线 = 10;


		static const int 状态_离开 = 30;


		static const int 状态_忙碌 = 50;


		static const int 状态_Q我吧 = 60;


		static const int 状态_勿扰 = 70;


		static const int 状态_隐身 = 40;


		static const char * ObjectMsg = "<文本长度: 594>";


		static const bool 插件说明 = true;
	};

}