using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MPQCore;
using System.Windows.Forms;
namespace testlib
{
    public class Class1 : IPorts
    {
        void IPorts.about()
        {
            MessageBox.Show(".net中转器测试模块(by 月落)", "关于……");
        }

        void IPorts.end()
        {
            unsafe
            {
                ApiPorts.Api_OutPut(SConvert.ToSByte(".net中转器测试模块已结束!"));
            }
        }

        int IPorts.EventFun(string qq, int msgtype, int msgctype, string msgsource, string dop, string bep, string msg, string rawmsg, Backer bker)
        {
            if (msgtype > Consts.消息类型_好友 && msgtype < Consts.消息类型_讨论组临时会话)
            {
                unsafe
                {
                    string back = null;
                    switch (msg)
                    {
                        case ".net测试":
                            back = "测试返回文本！";
                            break;
                        case "测试":
                            back = "此为.net插件模块，使用.net中转适配器适配(by 月落)";
                            break;
                        default:
                            return 1;

                    }
                    ApiPorts.Api_SendMsg(SConvert.ToSByte(qq), msgtype, 0,
    SConvert.ToSByte(msgsource), SConvert.ToSByte(dop), SConvert.ToSByte("测试反馈：" + back));
                }
            }
            return 1;
        }

        string IPorts.info()
        {
            return ".net测试插件模块(by 月落)";
        }

        void IPorts.init()
        {
            unsafe
            {
                ApiPorts.Api_OutPut(SConvert.ToSByte(".net中转器测试模块已启动!"));
            }
        }

        int IPorts.Message(string qq, int type, string rawmsg, string cookie, string sessionkey, string clientkey)
        {
            return 1;
        }

        void IPorts.set()
        {
            MessageBox.Show(".net中转器测试模块(by 月落)\n尚无测试!", "设置……");
        }

        void test()
        {

        }
        //}
    }
}