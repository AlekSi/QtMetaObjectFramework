#include "QtMetaObjectFramework.h"

QList<QMetaProperty> QtMetaObjectFramework::properties(const QMetaObject* metaObject)
{
    return propertiesWithOffset(metaObject, 0);
}

QList<QMetaProperty> QtMetaObjectFramework::properties(const QObject* object)
{
    return properties(object->metaObject());
}

QList<QMetaProperty> QtMetaObjectFramework::ownProperties(const QMetaObject* metaObject)
{
    return propertiesWithOffset(metaObject, metaObject->propertyOffset());
}

QList<QMetaProperty> QtMetaObjectFramework::ownProperties(const QObject* object)
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
