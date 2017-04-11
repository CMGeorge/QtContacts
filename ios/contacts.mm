#include "contacts.h"
#import "UIKit/UIKit.h"
#import <Contacts/Contacts.h>
#include <QDebug>

class ContactsIOS{
    
    public:
        Contacts *qContacts;
        ContactsIOS(){

        }
        void getIOSLessOrEqul9Contacts(){

        }
        void getIOSGraterThan9Contacts(){
            if ([CNContactStore class]) {
                CNEntityType entityType = CNEntityTypeContacts;
                if( [CNContactStore authorizationStatusForEntityType:entityType] == CNAuthorizationStatusNotDetermined)
                {
                    CNContactStore * contactStore = [[CNContactStore alloc] init];
                    [contactStore requestAccessForEntityType:entityType completionHandler:^(BOOL granted, NSError * _Nullable error) {
                        if(granted){
                            qDebug()<<"Permision request granted";
                            getAllContacts();
                            qContacts->nativeDataRetrieveCompleteWithList(m_contactsList);
//                            return m_contactsList;
                        }
                    }];
                }
                else if( [CNContactStore authorizationStatusForEntityType:entityType]== CNAuthorizationStatusAuthorized)
                {
                    qDebug()<<"Contacts autorisation already granted";
                    getAllContacts();
                    qContacts->nativeDataRetrieveCompleteWithList(m_contactsList);
//                    return m_contactsList;
                }
            }else{
                qDebug()<<"NO CNCOntactStore found";
            }
            
        }
        void getAllContacts(){
            if([CNContactStore class])
            {
                //iOS 9 or later
                NSError* contactError;
                CNContactStore* addressBook = [[CNContactStore alloc]init];
                [addressBook containersMatchingPredicate:[CNContainer predicateForContainersWithIdentifiers: @[addressBook.defaultContainerIdentifier]] error:&contactError];
                NSArray * keysToFetch =@[CNContactEmailAddressesKey, CNContactPhoneNumbersKey, CNContactFamilyNameKey, CNContactGivenNameKey, CNContactPostalAddressesKey];
                CNContactFetchRequest * request = [[CNContactFetchRequest alloc]initWithKeysToFetch:keysToFetch];
                BOOL success = [addressBook enumerateContactsWithFetchRequest:request error:&contactError usingBlock:^(CNContact * __nonnull contact, BOOL * __nonnull stop){
                    qDebug()<<"Should parse contact ...  "<<contact.givenName<<" with phone number "<<[[[contact.phoneNumbers valueForKey:@"value"] valueForKey:@"digits"] firstObject] ;
                    if ([[contact.phoneNumbers valueForKey:@"value"] valueForKey:@"digits"] != NULL){
                        ContactModel *_cm = new ContactModel();
                        _cm->setFullName(QString::fromNSString(contact.givenName));
                        _cm->setPhoneNumber(QString::fromNSString([[[contact.phoneNumbers valueForKey:@"value"] valueForKey:@"digits"] firstObject]));
                        m_contactsList.append(_cm);
                    }
                }];
                        qDebug()<<"Enumeration complete";
            }
        }
    
private:
    QList<ContactModel*>m_contactsList;
};

Contacts::Contacts(QObject *parent) : QObject(parent){
    qDebug()<<"Using IOS Contacts";
    ContactsIOS *iosContacts = new ContactsIOS();
    iosContacts->qContacts = this;
    if([[UIDevice currentDevice].systemVersion floatValue] <= 9.0){
        //        [self getContacts];
        qDebug()<<"IOS is less than 9";
//        qDebug()<<iosContacts->getIOSLessOrEqul9Contacts();
    } else {
        qDebug()<<"IOS is grater than 9";
        iosContacts->getIOSGraterThan9Contacts();
        //        [self contactScan];
    }

}
QList<ContactModel*> Contacts::getContacts(){
    return m_contactsList;
}

void Contacts::nativeDataRetrieveCompleteWithList(QList<ContactModel *> contactList){
    qDebug()<<"Retrieved "<<contactList.count()<<" elements ";
    m_contactsList = contactList;
}
