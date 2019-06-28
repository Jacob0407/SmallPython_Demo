#pragma once

#include "PyTypeObject.h"

/*
	实现简单的Python中的Int类型
*/


typedef struct tagPyIntObject
{
	PyObject_HEAD;
	int value = 0;
}PyIntObject;

PyObject* PyInt_Create(int value);

static void int_print(PyObject* object)
{
	PyIntObject* intObject = reinterpret_cast<PyIntObject*>(object);
	if (!intObject)
		return;

	cout << intObject->value << endl;
}

static PyObject* int_add(PyObject* left, PyObject* right)
{
	PyIntObject* leftInt = reinterpret_cast<PyIntObject*>(left);
	PyIntObject* rightInt = reinterpret_cast<PyIntObject*>(right);

	if (!leftInt || !rightInt)
		return nullptr;

	PyIntObject* result = reinterpret_cast<PyIntObject*>(PyInt_Create(0));
	if (!result)
		return nullptr;

	result->value = leftInt->value + rightInt->value;

	return reinterpret_cast<PyObject*>(result);
}

static long int_hash(PyObject* object)
{
	return (long)((reinterpret_cast<PyIntObject*>(object))->value);
}

char PyIntTypeString[] = "int";
PyTypeObject PyInt_Type =
{
	PyObject_HEAD_INIT(&PyType_Type),
	PyIntTypeString,
	int_print,
	int_add,
	int_hash
};

PyObject* PyInt_Create(int value)
{
	PyIntObject* object = new PyIntObject();
	if (!object)
		return nullptr;

	object->refCount = 1;
	object->type = &PyInt_Type;
	object->value = value;

	return reinterpret_cast<PyObject*>(object);
}
