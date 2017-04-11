#include "contacts.h"


Contacts::Contacts(QObject *parent) : QObject(parent){

}
QList<ContactModel*> Contacts::getContacts(){
    return m_contactsList;
}
void Contacts::nativeDataRetrieveCompleteWithList(QList<ContactModel*>){
}
