#ifndef SYSFUNC_H
#define SYSFUNC_H
#include <string>
#include <string.h>
using namespace std;
extern int split(const string &src,char *dest,string start,string end,int maxLen);
extern string MakeMd5DigestResp(string realm, string cmd, string uri, string nonce, string username, string password);
#endif // SYSFUNC_H
