// SmallPython.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

#include <iostream>

#include "PyIntObject.h"
#include "PyStrObject.h"
#include "PyDictObject.h"

PyObject* m_localEnvironment = PyDict_Create();

void ExecuteAdd(string& target, const string& source);
void ExecutePrint(const string& symbol);

// 解析SmallPython语句
void ExecuteCommand(const string& command)
{
	string::size_type pos = 0;
	if ((pos = command.find("print ")) != string::npos)
	{
		// 输出 print 后面的字符
		ExecutePrint(command.substr(6));
	}
	else if ((pos = command.find(" = ")) != string::npos)
	{
		// 执行相加逻辑
		string target = command.substr(0, pos);
		string source = command.substr(pos + 3);
		ExecuteAdd(target, source);
	}
}

void ExecuteAdd(string& target, const string& source)
{
	string::size_type pos = 0;
	PyObject* intValue = PyInt_Create(atoi(source.c_str()));
	PyObject* key = PyStr_Create(target.c_str());
	PyDict_SetItem(m_localEnvironment, key, intValue);
}

void ExecutePrint(const string& symbol)
{
	PyObject* key = PyStr_Create(symbol.c_str());
	PyObject* value = PyDict_GetItem(m_localEnvironment, key);
	if (!value)
		return;

	if (value->type)
		value->type->print(value);
}

char info[] = "**************************Small Python**************************";
char prompt[] = ">>> ";
string m_command;

int main()
{
	cout << info << endl;
	cout << prompt;

	while (getline(cin, m_command))
	{
		if (m_command.empty())
		{
			cout << prompt;
			continue;
		}

		if (m_command == "exit")
			return 0;

		ExecuteCommand(m_command);

		cout << prompt;
	}

	return 0;
}
