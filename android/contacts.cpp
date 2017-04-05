#include "contacts.h"

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroid>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Contacts::Contacts(QObject *parent) : QObject(parent)
{
    QAndroidJniObject str = QAndroidJniObject::callStaticObjectMethod("net/reea/ContactsManager", "getContacts", "(Landroid/content/Context;)Ljava/lang/String;", QtAndroid::androidActivity().object<jobject>());



    qDebug() << "Value from java is " << str.toString();
    QJsonDocument document = QJsonDocument::fromJson(str.toString().toLatin1());
    qDebug()<<"JSON OBJECT "<<document;

    if (document.isArray()){
        QJsonArray elementsList = document.array();
        foreach (const QJsonValue &contactItemValue,elementsList){
            QJsonObject contactItem = contactItemValue.toObject();
            ContactModel *contactModel = new ContactModel(this);
            contactModel->setFullName(contactItem.value("name").toString());
            contactModel->setPhoneNumber(contactItem.value("phoneNumber").toString());
            contactsList.append(contactModel);
        }
    }
    emit contactsRetrieved(contactsList);
}
QList<ContactModel*> Contacts::getContacts(){
    return contactsList;
}
