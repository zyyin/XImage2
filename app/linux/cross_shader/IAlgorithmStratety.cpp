#include "IAlgorithmStratety.h"


IAlgorithmStratety::IAlgorithmStratety()
{
	m_nPassCount = 1;
	m_costMillSeconds = 0;
}

void IAlgorithmStratety::FireSink(Mat& image, int nSinkIndex)
{
	if (nSinkIndex >= m_sink.size())
		return;
	m_sink[nSinkIndex].image = image;
	SetSinkState(nSinkIndex, true);
	//unsigned long dwStart = ();
	if (TryRun())
	{
		m_nPassCount++;
		//m_costMillSeconds += GetTickCount() - dwStart;
		for (int i = 0; i < m_passDownOrder.size(); i++)
		{
			PassDown(m_passDownOrder[i]);
		}
	}
}
void IAlgorithmStratety::FireSink(int nVal, int nSinkIndex)
{

}
void IAlgorithmStratety::FireSink(float fVal, int nSinkIndex)
{

}
void IAlgorithmStratety::FireSink(const char* szVal, int nSinkIndex)
{

}

bool IAlgorithmStratety::Connect(IAlgorithmStratety* pNext, int nSinkindex, int nSrcIndex)
{
	if (!pNext)
		return false;
	if (QueryInterface(1, nSrcIndex) != pNext->QueryInterface(0, nSinkindex))
		return false;
	m_mapConnection[nSrcIndex].push_back(ConnectRemotePoint(nSinkindex, pNext));
	return true;
}

void IAlgorithmStratety::Disconnect(int nSrcIndex)
{
	map<int, vector<ConnectRemotePoint> >::iterator iter;
	iter = m_mapConnection.begin();
	for (; iter != m_mapConnection.end(); iter++)
	{
		if (iter->first == nSrcIndex)
		{
			m_mapConnection.erase(iter);
			break;
		}
	}
}
void IAlgorithmStratety::PassDown(int nSrcIndex)
{
	map<int, vector<ConnectRemotePoint> >::iterator iter;
	iter = m_mapConnection.begin();
	for (; iter != m_mapConnection.end(); iter++)
	{
		if (nSrcIndex == iter->first)
		{
			int type = QueryInterface(1, iter->first);

			for (int i = 0; i < iter->second.size(); i++)
			{
				if (type == INTERFACE_TYPE_IMAGE)
					iter->second[i].pNext->FireSink(m_src[iter->first].image, iter->second[i].nSinkIndex);
				else if (type == INTERFACE_TYPE_INT)
					iter->second[i].pNext->FireSink(m_src[iter->first].nVal, iter->second[i].nSinkIndex);
				else if (type == INTERFACE_TYPE_FLOAT)
					iter->second[i].pNext->FireSink(m_src[iter->first].fVal, iter->second[i].nSinkIndex);
				else if (type == INTERFACE_TYPE_STRING)
					iter->second[i].pNext->FireSink(m_src[iter->first].strVal.c_str(), iter->second[i].nSinkIndex);
			}
		}

	}
}
void IAlgorithmStratety::SetSinkState(int nIndex, bool bState)
{
	if (nIndex < 0)
		return;
	m_sink[nIndex].state = bState;
}
bool IAlgorithmStratety::GetSinkState(int nIndex)
{
	if (nIndex < 0)
		return false;
	return m_sink[nIndex].state;
}
int IAlgorithmStratety::QueryInterface(int nSinkSrc, int nIndex)
{
	if (nIndex < 0)
		return INTERFACE_TYPE_UNKNOWN;
	if (nSinkSrc == 0)
	{
		if (nIndex >= m_sink.size())
			return INTERFACE_TYPE_UNKNOWN;
		return m_sink[nIndex].type;
	}
	if (nSinkSrc == 1)
	{
		if (nIndex >= m_src.size())
		{
			return INTERFACE_TYPE_UNKNOWN;
		}
		return m_src[nIndex].type;
	}
	return INTERFACE_TYPE_UNKNOWN;
}

void IAlgorithmStratety::GetPoint(ConnectPoint& src, int nSinkSrc, int nIndex)
{
	if (nSinkSrc == 0)
	{
		src = m_sink[nIndex];
	}
	if (nSinkSrc == 1)
	{
		src = m_src[nIndex];
	}
}




ClassFactory::ClassTable* ClassFactory::_classTable = NULL;
ClassFactory::ClassFactory(const char* className, int size, createCallback fun)
: _className(className)
, _classSize(size)
, _createFun(fun)
{
	Register();
}
ClassFactory::~ClassFactory()
{
	UnRegister();
}
IAlgorithmStratety* ClassFactory::createDynamicAlgorithm(const char* name)
{
	ClassTable::iterator pos = _classTable->find(name);
	if (pos == _classTable->end())
	{
		throw("Not found the class of this name in rtti table");
	}
	return pos->second->create();
}

void ClassFactory::Register()
{
	if (NULL == _classTable)
	{
		_classTable = new ClassTable;
	}

	ClassTable::iterator pos = _classTable->find(_className);
	if (pos != _classTable->end())
	{
		throw("The class of this name is already in rtti table");
	}
	(*_classTable)[_className] = this;
}

void ClassFactory::UnRegister()
{
	if (NULL != _classTable)
	{
		_classTable->erase(_classTable->find(_className));
		if (_classTable->size() == 0)
		{
			delete _classTable;
			_classTable = NULL;
		}

	}
}

IAlgorithmStratety* ClassFactory::create()
{
	return _createFun ? (*_createFun)() : NULL;
}
