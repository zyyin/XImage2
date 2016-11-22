#pragma once
#include "opencv_all.h"

#include "map"
#include "vector"
using namespace std;
using namespace cv;

#define LOG_ERROR printf("error: %s, %d\n", __FUNCTION__, __LINE__); 


#ifndef ALGOFRAMEWORKS_EXPORTS 
#define ALGOFRAMEWORKS_PLUS __declspec(dllimport)
#else
#define ALGOFRAMEWORKS_PLUS __declspec(dllexport)
#endif

enum {
	INTERFACE_TYPE_IMAGE = 0,
	INTERFACE_TYPE_INT,
	INTERFACE_TYPE_FLOAT,
	INTERFACE_TYPE_STRING,
	INTERFACE_TYPE_UNKNOWN,
};
typedef struct ConnectPoint{
	int type;
	int state; // 0 no new data, 1 new data
	Mat image;
	int nVal;
	float fVal;
	string strVal;
	ConnectPoint() { state = false; }
	ConnectPoint(int nType)
	{
		type = nType;
		state = false;
	}
	ConnectPoint& operator = (const ConnectPoint& r)
	{
		type = r.type;
		state = r.state;
		image = r.image;
		nVal = r.nVal;
		fVal = r.fVal;
		strVal = r.strVal;
		return *this;
	}
} ConnectPoint;


class IAlgorithmStratety;

typedef struct ConnectRemotePoint {
	int nSinkIndex;
	IAlgorithmStratety* pNext;
	ConnectRemotePoint(int n, IAlgorithmStratety* p)
	{
		nSinkIndex = n;
		pNext = p;
	}
	ConnectRemotePoint& operator = (const ConnectRemotePoint& r)
	{
		nSinkIndex = r.nSinkIndex;
		pNext = r.pNext;
		return *this;
	}
} ConnectRemotePoint;
class  IAlgorithmStratety
{
public:
	IAlgorithmStratety();

	// virtual abstract interface 
	virtual bool TryRun() = 0;
	virtual const char* GetParametersName() = 0;


	// public functions
	virtual void SetParameter(const char* szKey, float fVal) { m_mapParamerter[szKey] = fVal; }
	virtual void PassDown(int nSrcIndex);

	virtual void FireSink(Mat& image, int nSinkIndex = 0);
	virtual void FireSink(int nVal, int nSinkIndex = 0);
	virtual void FireSink(float fVal, int nSinkIndex = 0);
	virtual void FireSink(const char* szVal, int nSinkIndex = 0);


	virtual bool Connect(IAlgorithmStratety* pNext, int nSinkindex, int nSrcIndex);
	virtual void Disconnect(int nSrcIndex);
	virtual void SetSinkState(int nIndex, bool bState);
	virtual bool GetSinkState(int nIndex);
	virtual int QueryInterface(int nSinkSrc, int nIndex);

	virtual void GetPoint(ConnectPoint& src, int nSinkSrc, int nIndex);

	inline int GetSinkCount() { return m_sink.size(); }
	inline int GetSrcCount() { return m_src.size(); }
	inline double GetTimeCost() { return m_costMillSeconds / m_nPassCount; };
	inline map<int, vector<ConnectRemotePoint> >&  GetConnection(){ return m_mapConnection; }
protected:
	map<int, vector<ConnectRemotePoint> >m_mapConnection;
	map<string, double> m_mapParamerter;
	vector<int> m_passDownOrder;
	vector<ConnectPoint> m_sink;
	vector<ConnectPoint> m_src;
	double m_costMillSeconds;
	int m_nPassCount;
};

typedef IAlgorithmStratety* (*createCallback)(void);
class ClassFactory
{
public:

	friend  IAlgorithmStratety* ClassFactory::createDynamicAlgorithm(const char* name);

	ClassFactory(const char* className, int size, createCallback fun);

	virtual ~ClassFactory();

	static IAlgorithmStratety* createDynamicAlgorithm(const char* name);

	bool IsDynamic() const
	{
		return NULL != _createFun;
	}

	bool IsKindOf(const ClassFactory *info) const
	{
		return info != 0 && (info == this);
	}

	const char* getClassName() const
	{
		return _className;
	}

	int getClassSize() const
	{
		return _classSize;
	}

	IAlgorithmStratety* create();

protected:

	void Register();

	void UnRegister();

private:

	typedef std::map<std::string, ClassFactory*>  ClassTable;

	const char*         _className;
	int                 _classSize;
	createCallback      _createFun;
	static ClassTable*  _classTable;
};
#define DECLARE_DYNAMIC_CLASS() public:\
	static ClassFactory __classFactory; \
	virtual ClassFactory* get_classFactory() const; \
	static IAlgorithmStratety* createObject();

#define IMPLEMENT_DYNAMIC_CLASS(name) \
	ClassFactory name::__classFactory(#name, (int)sizeof(name), name::createObject); \
	ClassFactory* name::get_classFactory() const { return &name::__classFactory; }\
	IAlgorithmStratety* name::createObject() { return new name; }

