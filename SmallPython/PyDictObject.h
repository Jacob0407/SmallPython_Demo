#pragma once

#include "PyTypeObject.h"
#include <map>

/*
	实现简单的Python中的Dict类型
*/

typedef struct tagPyDictObject
{
	PyObject_HEAD;
	map<long, PyObject*> dict;
}PyDictObject;

PyObject* PyDict_GetItem(PyObject* target, PyObject* key)
{
	long keyHashValue = (key->type)->hash(key);
	const map<long, PyObject*>& dict = (reinterpret_cast<PyDictObject*>(target))->dict;
	const auto it = dict.find(keyHashValue);
	if (it == dict.end())
		return nullptr;

	return it->second;
}

int PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value)
{
	long keyHashValue = (key->type)->hash(key);
	PyDictObject* dictObject = reinterpret_cast<PyDictObject*>(target);
	dictObject->dict[keyHashValue] = value;

	return 0;
}

static void PyDict_Print(PyObject* object)
{
	PyDictObject* dictObject = reinterpret_cast<PyDictObject*>(object);
	cout << "{";
	for (const auto& it : dictObject->dict)
	{
		if (!it.second)
			continue;

		cout << it.first << " : ";
		if (it.second->type)
			it.second->type->print(it.second);

		cout << ", ";
	}

	cout << "}" << endl;
}

char PyDictTypeString[] = "dict";
PyTypeObject PyDict_Type =
{
	PyObject_HEAD_INIT(&PyType_Type),
	PyDictTypeString,
	PyDict_Print,
	0,
	0
};

PyObject* PyDict_Create()
{
	PyDictObject* object = new PyDictObject();
	object->refCount = 1;
	object->type = nullptr;

	return reinterpret_cast<PyObject*>(object);
}