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

public:
	int prop() const { return 42; }

private slots:
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
};

QTEST_MAIN(tst_QtMetaObjectFramework);
