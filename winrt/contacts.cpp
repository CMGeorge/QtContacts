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

Contacts::Contacts(QObject *parent) : QObject(parent){
    qDebug()<<"Is WINRT Contact";
    ComPtr<IContactManagerStatics2> contactManager;
    HRESULT hr = GetActivationFactory(HStringReference(L"Windows.ApplicationModel.Contacts.ContactManager").Get(), &contactManager);
    if (FAILED(hr)){
        qDebug()<<"Failed to get ContactManaget Fabric";
    }
    IAsyncOperation<ContactStore*>* asyncOp;
    hr = contactManager->RequestStoreAsync(&asyncOp);
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

	for (int i = 0; i < contactsCount; i++) {
		IContact *currentContact = 0x0;
		contactListItems->GetAt(i, &currentContact);
		HSTRING clientName;
		currentContact->get_Name(&clientName);
		QString contactName = QString::fromStdWString(WindowsGetStringRawBuffer(clientName, nullptr));
        if (!contactName.isEmpty()) {
			ContactModel *_cm = new ContactModel();
            _cm->setFullName(contactName);
			m_contactsList.append(_cm);
		}
    }
}
QList<ContactModel*> Contacts::getContacts(){
    return m_contactsList;
}

void Contacts::nativeDataRetrieveCompleteWithList(QList<ContactModel*>){

}
