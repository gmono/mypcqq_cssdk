#pragma once
using namespace System;
using namespace System::Reflection;
using namespace System::IO;
using namespace System::Text;
namespace MPQCore
{
	public ref class SConvert
	{
	public:
		static char *ToSByte(String^ str)
		{
			auto gbk=Encoding::GetEncoding("GBK");
			auto buffer = gbk->GetBytes(str);
			char *ret = new char[buffer->Length+10];
			int ptr = 0;
			for each(byte c in buffer)
			{
				ret[ptr++] = c;
			}
			ret[buffer->Length] = 0;
			return ret;
		}
		static int GetLength(String^ str)
		{
			auto gbk = Encoding::GetEncoding("GBK");
			auto buffer = gbk->GetBytes(str);
			return buffer->Length;
		}
	};
	public ref class Backer
	{
		//�ش���������
	public:
		Backer(char *backptr)
		{
			this->backptr = backptr;
		}
		//��д�ı�
		void Write(String^ text)
		{
			char *buf = SConvert::ToSByte(text);
			strcpy_s(this->backptr,SConvert::GetLength(text),buf);//��д�ڴ�
			Api_OutPut(buf);
		}
	private:
		char *backptr = nullptr;
	};
	//�йܽӿ�
	public interface class IPorts
	{
		void about();
		void init();
		String^ info();
		void set();
		void end();
		int EventFun(String^ qq, int msgtype, int msgctype, String^ msgsource, String^ dop, String^bep, String^ msg, String^ rawmsg, Backer^ bker);
		int Message(String^ qq, int type, String^ rawmsg, String^ cookie, String^ sessionkey, String^ clientkey);
	};

	IPorts^ LoadPLG(char *path)
	{
		//����һ���ļ�����IPorts����
		String^ spath = gcnew String(path);
		FileInfo^ finfo = gcnew FileInfo(spath);
		Api_OutPut((char *)SConvert::ToSByte(finfo->FullName));//
		if (!finfo->Exists)
		{
			Api_OutPut("�������ļ���");
			return nullptr;//�������ļ�
		}
		try
		{
			Assembly^ asmobj = Assembly::LoadFile(finfo->FullName);
			auto mods = asmobj->GetTypes();
			IPorts^ ret = nullptr;
			for each (auto mod in mods)
			{
				if (mod->GetInterface("MPQCore.IPorts"))
				{
					ret = (IPorts^)Activator::CreateInstance(mod, true);//��������
					break;//ֻȡ��һ��
				}
			}
			if (ret == nullptr) Api_OutPut("ʧ��ԭ��û�л�ȡ��IPorts�ӿ���");
			return ret;
		}
		catch (ReflectionTypeLoadException^ e)
		{
			auto c = (ReflectionTypeLoadException^)e;
			for each(auto a in c->LoaderExceptions)
			{
				Api_OutPut(SConvert::ToSByte(a->Message));
			}
			return nullptr;
		}
		catch (Exception^ e)
		{
			Api_OutPut(SConvert::ToSByte(e->Message));
		}
	}
}
