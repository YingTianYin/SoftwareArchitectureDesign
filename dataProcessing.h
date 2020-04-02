#pragma once
#include "p_DataBaseOp.h"
#include <regex>
using namespace DBHelper;
using namespace std;
const string host = "localhost";  //因为是作为本机测试，所以填写的是本地IP
const string user = "root";       //连接MySQL的用户名
const string passwd = "123456"; //你的用户密码
const string db = "bookstore";      //所要连接的数据库的名字
unsigned int port = 3306;           //这是MySQL的服务器的端口，如果没有修改过的话就是3306。
const char* unix_socket = NULL;
DBConf dbc(host, user, passwd, db, "GBK", port);
p_DataBaseOp dbo(dbc);
int calculate(string a) {
	return (a[0] - '0') * 7 + (a[1] - '0') * 9 + (a[2] - '0') * 10 
		+ (a[3] - '0') * 5 + (a[4] - '0') * 8 + (a[5] - '0') * 4 
		+ (a[6] - '0') * 2 + (a[7] - '0') * 1 + (a[8] - '0') * 6 
		+ (a[9] - '0') * 3 + (a[10] - '0') * 7 + (a[11] - '0') * 9 
		+ (a[12] - '0') * 10 + (a[13] - '0') * 5 + (a[14] - '0') * 8 
		+ (a[15] - '0') * 4 + (a[16] - '0') * 2;
}
char idJudge(string a) {
	int k = calculate(a) % 11;
	if (k == 0)
		return '1';
	else if (k == 1)
		return '0';
	else if (k == 2)
		return 'X';
	else
		return '0' + 12 - k;
}
bool validInfo(OrderInfo oi)
{
	string idCard = oi.getId();//OrderInfo里面加了
	/*string getId()
		{
			return _id;
		}*/
	bool idBool = idCard[17] == idJudge(idCard);
	string phoneNum = oi.getPhone();
	//OrderInfo里面加了
	/*string getPhone()
		{
			return _phone;
		}*/
	std::regex   regPhone("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");
	bool phoneBool= regex_match(phoneNum, regPhone);
	string name = oi.getName();
	//OrderInfo里面加了
	/*string getName()
		{
			return _name;
		}*/
	std::regex   regName("^[\u4E00-\u9FA5A-Za-z0-9]+$");
	bool nameBool = regex_match(name, regName);

	return (idBool && nameBool)|| (phoneBool && nameBool);
}
bool surplusCompare(OrderInfo oi)
{
	return dbo.isMaskExist(oi.getPlace, oi.getType);
}
int updateDB(OrderInfo oi)
{
	return dbo.deleteMaskInfo(oi.getPlace, oi.getType);
}