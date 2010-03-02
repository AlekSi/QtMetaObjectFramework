#ifndef QTMETAOBJECTFRAMEWORK_H
#define QTMETAOBJECTFRAMEWORK_H

#include "QtMetaObjectFramework_global.h"
#include <QtCore/QObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QList>
class QMetaObject;

class QTMETAOBJECTFRAMEWORKSHARED_EXPORT QtMetaObjectFramework : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QtMetaObjectFramework)

public:
	static QList<QMetaProperty> properties(const QMetaObject *metaObject);
	static QList<QMetaProperty> properties(const QObject *object);
	static QList<QMetaProperty> ownProperties(const QMetaObject *metaObject);
	static QList<QMetaProperty> ownProperties(const QObject *object);

	/*! Returns object's dot.separated.name */
	static QString fullObjectName(const QObject *object);

	/*! Find child my dot.separated.name */
	static QObject * findChild(const QObject *parent, const QString &name);

	/*! Returns top-level parent for object. */
	static QObject * root(const QObject *object);

private:
    static QList<QMetaProperty> propertiesWithOffset(const QMetaObject *metaObject, int offset);
};


#endif // QTMETAOBJECTFRAMEWORK_H
