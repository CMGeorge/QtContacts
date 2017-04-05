#ifndef CONTACTS_H
#define CONTACTS_H

#include <QObject>
#include "contactmodel.h"

class Contacts : public QObject
{
    Q_OBJECT
public:
    explicit Contacts(QObject *parent = 0);
    QList<ContactModel*> getContacts();
private:
    QList<ContactModel*> m_contactsList;
signals:
    void contactsRetrieved(QList<ContactModel*>);
public slots:
    void nativeDataRetrieveCompleteWithList(QList<ContactModel*>);
};


#endif // CONTACTS_H
