#pragma once

#include "PyTypeObject.h"

/*
	实现简单的Python中的String类型
*/

typedef struct tagPyStrObject
{
	PyObject_HEAD;
	char value[120];
	long ob_hash;
	int size = 0;
}PyStrObject;

PyObject* PyStr_Create(const string& str);

static void str_print(PyObject* object)
{
	PyStrObject* strObject = reinterpret_cast<PyStrObject*>(object);
	if (!strObject)
		return;

	cout << strObject->value << endl;
}

static PyObject* str_add(PyObject* left, PyObject* right)
{
	PyStrObject* leftObject = reinterpret_cast<PyStrObject*>(left);
	PyStrObject* rightObject = reinterpret_cast<PyStrObject*>(right);

	if (!leftObject || !rightObject)
		return nullptr;

	PyStrObject* result = reinterpret_cast<PyStrObject*>(PyStr_Create(""));
	if (!result)
		return nullptr;

	result->size = leftObject->size >= 120 ? 120 : leftObject->size;
	strncpy_s(result->value, leftObject->value, result->size);
	int catSize = rightObject->size >= (120 - result->size) ? (120 - result->size) : rightObject->size;
	strncat_s(result->value, rightObject->value, catSize);
	result->size += catSize;

	return reinterpret_cast<PyObject*>(result);
}

static long str_hash(PyObject* object)
{
	PyStrObject* strObject = reinterpret_cast<PyStrObject*>(object);
	if (!strObject)
		return -1;

	if (strObject->ob_hash != -1)
		return strObject->ob_hash;

	int len = strObject->size;
	register unsigned char* p = (unsigned char*)strObject->value;
	register long x = *p << 7;
	while (--len >= 0)
		x = (1000003 * x) ^ *p++;

	x ^= strObject->size;
	if (x == -1)
		x = -2;

	strObject->ob_hash = x;

	return x;
}

char PyStrTypeString[] = "str";
PyTypeObject PyStr_Type =
{
	PyObject_HEAD_INIT(&PyType_Type),
	PyStrTypeString,
	str_print,
	str_add,
	str_hash
};

PyObject* PyStr_Create(const string& str)
{
	PyStrObject* obj = new PyStrObject();
	if (!obj)
		return nullptr;

	obj->ob_hash = -1;
	obj->refCount = 1;
	obj->size = str.empty() ? 0 : str.size();
	obj->type = &PyStr_Type;
	memset(obj->value, 0, 120);
	strncpy_s(obj->value, str.c_str(), 119);

	return reinterpret_cast<PyObject*>(obj);
}