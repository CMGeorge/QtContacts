#include "Contacts.h"


Contacts::Contacts(QObject *parent) : QObject(parent){

}
QList<ContactModel*> Contacts::getContacts(){
    return contactsList;
}
