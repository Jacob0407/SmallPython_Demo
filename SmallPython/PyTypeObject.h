#pragma once

#include "PyObject.h"

// 打印
typedef void (*PrintFun)(PyObject* object);
// 相加
typedef PyObject* (*AddFun)(PyObject* left, PyObject* right);
// 取hash值
typedef long (*HashFun)(PyObject* object);

typedef struct tagPyTypeObject
{
	PyObject_HEAD;
	char* name;
	PrintFun print;
	AddFun add;
	HashFun hash;
}PyTypeObject;

PyTypeObject PyType_Type;
