#include "Contacts.h"
//#include "winrt/Windows.Globalization.h"
#include "Windows.ApplicationModel.Contacts.h"
#include <Windows.Networking.PushNotifications.h>
#include <ppltasks.h>
#include <wrl.h>
#include <Windows.h>
#include <windows.foundation.h>
#include <wrl/wrappers/corewrappers.h>
#include <QDebug>
//#include "Windows.Phone.PersonalInformation.h"


//using namespace Platform;
//using namespace Windows::Foundation;
//using namespace ABI::Windows::Foundation;
//using namespace ABI::Windows::ApplicationModel::Contacts;
//using namespace Microsoft::WRL;
//using namespace Microsoft::WRL::Wrappers;
//using namespace concurrency;

//using namespace ABI::Windows::Networking::PushNotifications;


using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::ApplicationModel::Contacts;
using namespace ABI::Windows::Networking::PushNotifications;

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace concurrency;

class MyContacts :public IContact, public IContact2, IContact3 {
public:
	MyContacts() {}
	QString getFullName() {
		HSTRING clientName;
		get_Name(&clientName);
		return QString::fromStdWString(WindowsGetStringRawBuffer(clientName, nullptr));
	}
	QStringList getPhoneNumbers() {
		QStringList phoneNumbers;
		IVector<ContactPhone*> *contactPhones;
		unsigned int phonesCount;
		get_Phones(&contactPhones);
		contactPhones->get_Size(&phonesCount);
		qDebug() << "Phones Numbers " << phonesCount;
		HSTRING phoneNumber = 0x0;
		for (int i = 0; i < phonesCount; i++) {
			IContactPhone *_cp;
			contactPhones->GetAt(i, &_cp);
			_cp->get_Number(&phoneNumber);
			phoneNumbers<< QString::fromStdWString(WindowsGetStringRawBuffer(phoneNumber, nullptr));
		}
		return phoneNumbers;
	}
};
Contacts::Contacts(QObject *parent) : QObject(parent){

    qDebug()<<"Is WINRT Contact";

    ComPtr<IContactManagerStatics3> contactManager;
    HRESULT hr = GetActivationFactory(HStringReference(L"Windows.ApplicationModel.Contacts.ContactManager").Get(), &contactManager);
    if (FAILED(hr)){
        qDebug()<<"Failed to get ContactManaget Fabric";
    }
    IAsyncOperation<ContactStore*>* asyncOp;
    //hr = contactManager->RequestStoreAsync(&asyncOp);
	contactManager->RequestStoreAsyncWithAccessType(ContactStoreAccessType_AllContactsReadOnly, &asyncOp);
    if (FAILED(hr)){
        qDebug()<<"Failed to get ContactManaget Fabric";
    }

    IContactStore *contactStore = 0x0;
    while (contactStore==0x0){
        asyncOp->GetResults(&contactStore);
    }
    qDebug()<<"Contact Store is: "<<contactStore;
    IAsyncOperation<IVectorView<Contact*>*> *contactAsync;
    //IAsyncOperation<Contact> me=
    hr = contactStore->FindContactsAsync(&contactAsync);
    if (FAILED(hr)) {
        qDebug() << "Failed to get IAsyncOperation<IVectorView<Contact*>*> *contactAsync;";
    }
    IVectorView<Contact*> *contactListItems = 0x0;
    while (contactListItems == 0x0) {
        contactAsync->GetResults(&contactListItems);
    }
    unsigned int contactsCount;
    contactListItems->get_Size(&contactsCount);
    qDebug() << "Contacts Sync Is: " << contactListItems << " With Length " << contactsCount;
	
    for (unsigned int i = 0; i < contactsCount; i++) {
	//for (IContact currentContact: contactListItems){
		IContact *currentContact2 = 0x0;
        contactListItems->GetAt(i, &currentContact2);
		MyContacts *currentContact = reinterpret_cast<MyContacts*>(currentContact2);
        if (currentContact->getPhoneNumbers().count()>0) {
            ContactModel *_cm = new ContactModel();
            _cm->setFullName(currentContact->getFullName());
			_cm->setPhoneNumber(currentContact->getPhoneNumbers().at(0));
            m_contactsList.append(_cm);
        }
    }
}
QList<ContactModel*> Contacts::getContacts(){
    return m_contactsList;
}

void Contacts::nativeDataRetrieveCompleteWithList(QList<ContactModel*>){

}
