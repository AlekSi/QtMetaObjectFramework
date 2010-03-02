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

QObject * QtMetaObjectFramework::findChild(const QObject *parent, const QString &name)
{
	Q_ASSERT(parent);
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
