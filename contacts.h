#ifndef CONTACTS_H
#define CONTACTS_H

#include <QObject>
#include "contactmodel.h"

class Contacts : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString errorString READ errorString WRITE setErrorString NOTIFY errorStringChanged)
    Q_PROPERTY(int errorCode READ errorCode WRITE setErrorCode NOTIFY errorCodeChanged)
public:
    explicit Contacts(QObject *parent = 0);
    QList<ContactModel*> getContacts();
    QString errorString() const
    {
        return m_errorString;
    }

    int errorCode() const
    {
        return m_errorCode;
    }

private:
    QList<ContactModel*> m_contactsList;
    QString m_errorString;

    int m_errorCode;

signals:
    void contactsRetrieved(QList<ContactModel*>);
    void error();
    void errorStringChanged(QString errorString);

    void errorCodeChanged(int errorCode);

public slots:
void nativeDataRetrieveCompleteWithList(QList<ContactModel*>);
void setErrorString(QString errorString)
{
    if (m_errorString == errorString)
        return;

    m_errorString = errorString;
    emit errorStringChanged(errorString);
}
void setErrorCode(int errorCode)
{
    if (m_errorCode == errorCode)
        return;

    m_errorCode = errorCode;
    emit errorCodeChanged(errorCode);
}
};


#endif // CONTACTS_H
