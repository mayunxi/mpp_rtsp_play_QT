#include "sysfunc.h"
#include "MD5.hpp"
int split(const string &src,char *dest,string start,string end,int maxLen)
{
    size_t pos = src.find(start);
    size_t b = src.find_first_of(end,pos);
    string tmp = src.substr(pos+start.length()+1,b-pos-start.length()-2);

    if (tmp.length() > maxLen)
    {
        printf("out of memory\n");
        return -1;
    }
    memcpy(dest,tmp.c_str(),tmp.length());
    return 0;
}

/***********************************************************************************************
* 函数名   ：			MakeMd5DigestResp
* 函数功能 ：			数字摘要认证
* 输入参数 ：			realm
                        cmd
                        uri
                        nonce
                        username
                        password
* 输出参数 ：			无
* 返回值   ：			用于进行数字摘要鉴权的信息
***********************************************************************************************/
#define MD5_BUF_SIZE 64
string MakeMd5DigestResp(string realm, string cmd, string uri, string nonce, string username, string password)
{
    string tmp("");
    //char ha1buf[MD5_BUF_SIZE] = { 0 };
    //char ha2buf[MD5_BUF_SIZE] = { 0 };
    //char habuf[MD5_BUF_SIZE] = { 0 };

    tmp.assign("");
    tmp = username + ":" + realm + ":" + password;
    string ha1buf = getMD5Code(tmp);
    //ha1buf[MD5_SIZE] = '\0';

    tmp.assign("");
    tmp = cmd + ":" + uri;
    string ha2buf = getMD5Code(tmp);
    //ha2buf[MD5_SIZE] = '\0';

    tmp.assign(ha1buf);
    tmp = tmp + ":" + nonce + ":" + ha2buf;
    string habuf = getMD5Code(tmp);
    //habuf[MD5_SIZE] = '\0';

    tmp.assign("");
    tmp.assign(habuf);

    return tmp;
}
///***********************************************************************************************
//* 函数名   ：			MakeBasicResp
//* 函数功能 ：			Base64认证
//* 输入参数 ：			username	用户名
//						password	密码
//* 输出参数 ：			无
//* 返回值   ：			用于进行Base64认证的信息
//***********************************************************************************************/
//string Rtsp_stream_receiver::MakeBasicResp(string username, string password)
//{
//	if (username.length() <= 0)
//	{
//		username.assign(m_uri.m_username);
//		password.assign(m_uri.m_password);
//	}
//	string tmp = username + ":" + password;
//	char * encodedBytes = base64Encode(tmp.c_str(), tmp.length());
//	if (NULL == encodedBytes)
//	{
//		return "";
//	}
//	tmp.assign(encodedBytes);
//	delete[] encodedBytes;

//	return tmp;
//}
////base64Encode,和 md5都是来自开源库，就简单两个文件，可以上网搜下，文件名为base64.h，md5util.h
