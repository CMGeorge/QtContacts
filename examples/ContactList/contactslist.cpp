#include "contactslist.h"
#include "contacts.h"
#include <QDebug>
ContactsListModel::ContactsListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    Contacts *contacts = new Contacts(this);
    m_contactList = contacts->getContacts();
    qDebug()<<"We should have "<<m_contactList.count();
}

int ContactsListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return m_contactList.count();
}

QVariant ContactsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ContactModel *contactModel = m_contactList.at(index.row());
    QVariant returnValue;
    switch (role) {
    case ID:{
        //TODO: Should be implemented?
    }
        break;
    case FirstName:{
        //TODO: Should be implemented?
    }
        break;
    case LastName:{
        //TODO: Should be implemented?
    }
        break;
    case FullName:{
        //TODO: Should be implemented?
        returnValue = contactModel->fullName();
    }
        break;
    case UserImage:{
        //TODO: Should be implemented?
    }
        break;
    case Phone:{
        //TODO: Should be implemented?
        returnValue = contactModel->phoneNumber();
    }
        break;
    case Invited:{
        //TODO: Should be implemented?
    }
        break;
    case Member:{
        //TODO: Should be implemented?
    }
        break;
    }
    return returnValue;
}

QHash<int, QByteArray> ContactsListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ID] = "contactId";
    roles[FirstName] = "firstName";
    roles[LastName] = "lastName";
    roles[FullName] = "name";
    roles[UserImage] = "userImage";
    roles[Phone] = "phone";
    roles[Invited] = "alreadyInvited";
    roles[Member] = "isMember";
    return roles;
}

void ContactsListModel::contactListRetrieveComplete(QList<ContactModel*>){

}
