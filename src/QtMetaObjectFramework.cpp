#include "QtMetaObjectFramework.h"
#include <QtDebug>

QList<QMetaProperty> QtMetaObjectFramework::properties(const QMetaObject *metaObject)
{
    return propertiesWithOffset(metaObject, 0);
}

QList<QMetaProperty> QtMetaObjectFramework::properties(const QObject *object)
{
    return properties(object->metaObject());
}

QList<QMetaProperty> QtMetaObjectFramework::ownProperties(const QMetaObject *metaObject)
{
    return propertiesWithOffset(metaObject, metaObject->propertyOffset());
}

QList<QMetaProperty> QtMetaObjectFramework::ownProperties(const QObject *object)
{
    return ownProperties(object->metaObject());
}

QList<QMetaProperty> QtMetaObjectFramework::propertiesWithOffset(const QMetaObject *metaObject, int offset)
{
    QList<QMetaProperty> result;
    const int count = metaObject->propertyCount();
    for (int i=offset; i<count; ++i)
        result << metaObject->property(i);
    return result;
}

QString QtMetaObjectFramework::fullObjectName(const QObject *object)
{
	Q_ASSERT(object);
	QString name = object->objectName();
	Q_ASSERT(!name.isEmpty());
	QObject *p = object->parent();
	while(p) {
		Q_ASSERT(!p->objectName().isEmpty());
		name = p->objectName() + "." + name;
		p = p->parent();
	}
	return name;
}


QObject * QtMetaObjectFramework::findChild(const QObject *parent, const QString &name)
{
	Q_ASSERT(parent);
	Q_ASSERT(!name.isEmpty());
	const QObjectList children = parent->children();
	const QString directChildName = name.contains(".") ? name.section(".", 0, 0) : name;
	const QString otherChildrenNames = name.section(".", 1);
	foreach(QObject *child, children) {
		if (child->objectName() == directChildName) {
			if (otherChildrenNames.isEmpty())
				return child;
			else
				return findChild(child, otherChildrenNames);
		}
	}
	return 0;
}

QObject * QtMetaObjectFramework::root(const QObject *object)
{
	Q_ASSERT(object);
	QObject *p = const_cast<QObject *>(object);
	while(p->parent()) {
		p = p->parent();
	}
	return p;
}
