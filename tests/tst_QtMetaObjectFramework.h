#include <QtTest>
#include "../src/QtMetaObjectFramework.h"

bool lessThan(const QMetaProperty &p1, const QMetaProperty &p2)
{
	return QString(p1.name()) < QString(p2.name());
}

class Base : public QObject
{
	Q_OBJECT

};

class tst_QtMetaObjectFramework : public Base
{
	Q_OBJECT
	Q_PROPERTY(int prop READ prop);

private:
	int prop() const { return 42; }

private:
	QObject *o1, *o2a, *o2b, *o3;

private slots:
	void initTestCase()
	{
		o1 = new QObject();		o1->setObjectName("o1");
		o2a = new QObject(o1);	o2a->setObjectName("o2a");
		o2b = new QObject(o1);	o2b->setObjectName("o2b");
		o3 = new QObject(o2a);	o3->setObjectName("o3");
	}

	void cleanupTestCase()
	{
		delete o1;
	}

	void testProperties()
	{
		QList<QMetaProperty> props = QtMetaObjectFramework::properties(this);
		qSort(props.begin(), props.end(), lessThan);
		QCOMPARE(props.count(), 2);
		QCOMPARE(QString(props.first().name()), QString("objectName"));
		QCOMPARE(QString(props.last().name()),  QString("prop"));

		props = QtMetaObjectFramework::ownProperties(this);
		QCOMPARE(props.count(), 1);
		QCOMPARE(QString(props.first().name()), QString("prop"));
	}

	void testFullObjectName()
	{
		QCOMPARE(QtMetaObjectFramework::fullObjectName(o1), QString("o1"));
		QCOMPARE(QtMetaObjectFramework::fullObjectName(o2a), QString("o1.o2a"));
		QCOMPARE(QtMetaObjectFramework::fullObjectName(o3), QString("o1.o2a.o3"));
	}

	void testFindChild()
	{
		QCOMPARE(QtMetaObjectFramework::findChild(o1, "o1"), static_cast<QObject *>(0));

		QCOMPARE(QtMetaObjectFramework::findChild(o1, "o2a"), o2a);
		QCOMPARE(QtMetaObjectFramework::findChild(o1, "o2b"), o2b);

		QCOMPARE(QtMetaObjectFramework::findChild(o1, "o3"), static_cast<QObject *>(0));
		QCOMPARE(QtMetaObjectFramework::findChild(o1, "o2a.o3"), o3);
		QCOMPARE(QtMetaObjectFramework::findChild(o1, "o2b.o3"), static_cast<QObject *>(0));
		QCOMPARE(QtMetaObjectFramework::findChild(o2a, "o3"), o3);
		QCOMPARE(QtMetaObjectFramework::findChild(o2b, "o3"), static_cast<QObject *>(0));
	}

	void testRoot()
	{
		QCOMPARE(QtMetaObjectFramework::root(o1), o1);
		QCOMPARE(QtMetaObjectFramework::root(o2a), o1);
		QCOMPARE(QtMetaObjectFramework::root(o3), o1);
	}

	void testHierarchy()
	{
		QCOMPARE(QtMetaObjectFramework::hierarchy(o1), QStringList() << "o1");
		QCOMPARE(QtMetaObjectFramework::hierarchy(o2a), QStringList() << "o1" << "o1.o2a");
		QCOMPARE(QtMetaObjectFramework::hierarchy(o3), QStringList() << "o1" << "o1.o2a" << "o1.o2a.o3");
	}
};

QTEST_MAIN(tst_QtMetaObjectFramework);
