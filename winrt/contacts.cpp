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
using namespace ABI::Windows::Storage::Streams;
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
		//qDebug() << "Phones Numbers " << phonesCount;
		HSTRING phoneNumber = 0x0;
		for (unsigned int i = 0; i < phonesCount; i++) {
			IContactPhone *_cp;
			contactPhones->GetAt(i, &_cp);
			_cp->get_Number(&phoneNumber);
			phoneNumbers<< QString::fromStdWString(WindowsGetStringRawBuffer(phoneNumber, nullptr));
		}
		return phoneNumbers;
	}
	void getUserImage() {
		IRandomAccessStreamReference *streamReference;
		get_Thumbnail(&streamReference);
		if (streamReference != nullptr) {
			ComPtr<IAsyncOperation<IRandomAccessStreamWithContentType*>> openReadAsync;
			streamReference->OpenReadAsync(&openReadAsync);
			qDebug() << getFullName() << " has image ";
		}

	}
};
Contacts::Contacts(QObject *parent) : QObject(parent){

    qDebug()<<"Is WINRT Contact";

    ComPtr<IContactManagerStatics3> contactManager;
    HRESULT hr = GetActivationFactory(HStringReference(L"Windows.ApplicationModel.Contacts.ContactManager").Get(), &contactManager);
    if (FAILED(hr)){
        qDebug()<<"Failed to get ContactManaget Fabric";
    }
    ComPtr<IAsyncOperation<ContactStore*>> asyncOp;
    //hr = contactManager->RequestStoreAsync(&asyncOp);
	contactManager->RequestStoreAsyncWithAccessType(ContactStoreAccessType_AllContactsReadOnly, &asyncOp);
    if (FAILED(hr)){
        qDebug()<<"Failed to get ContactManaget Fabric";
    }


	auto onAppLicCompletedCallback = Callback<Implements<RuntimeClassFlags<ClassicCom>, IAsyncOperationCompletedHandler<ContactStore*>, FtmBase>>(
		[this](IAsyncOperation<ContactStore*>* operation, AsyncStatus status)
	{
		qDebug() << "On Callback";
//		Started = 0,
//			Completed,
//			Canceled,
//			Error,
        if (status == Error){
            qDebug()<<"Error on loading list";
            emit error();
        }else if (status == AsyncStatus::Started){
			qDebug() << "Operation Started";
		}
		else if (status == AsyncStatus::Completed) {
			qDebug() << "Operation complete";
			IContactStore *contactStore = 0x0;
			operation->GetResults(&contactStore);
			qDebug() << "Contact Store is: " << contactStore;


			IAsyncOperation<IVectorView<Contact*>*> *contactAsync;
			HRESULT hr = contactStore->FindContactsAsync(&contactAsync);
			if (FAILED(hr)) {
				qDebug() << "Failed to get IAsyncOperation<IVectorView<Contact*>*> *contactAsync;";
			}
//			auto onFindContactsAsyncDone = Callback<Implements<RuntimeClassFlags<ClassicCom>, IAsyncOperationCompletedHandler<IVectorView<Contact*>*>, FtmBase>>(
//				[](IAsyncOperation<IVectorView<Contact*>*> *operation, AsyncStatus status)
//			{
//				qDebug() << "On FindContactsAsync Callback";
//				if (status == AsyncStatus::Started) {
//					qDebug() << "Operation Started";
//				}
//				else if (status == AsyncStatus::Completed) {

//				}
//				return S_OK;
//			});
//			//contactAsync->put_Completed()
//			contactAsync->put_Completed(onFindContactsAsyncDone);

			IVectorView<Contact*> *contactListItems = 0x0;
			while (contactListItems == 0x0) {
				contactAsync->GetResults(&contactListItems);
			}
			unsigned int contactsCount;
			contactListItems->get_Size(&contactsCount);
			//qDebug() << "Contacts Sync Is: " << contactListItems << " With Length " << contactsCount;

			QList<ContactModel*>newData;
			for (unsigned int i = 0; i < contactsCount; i++) {
				//for (IContact currentContact: contactListItems){
				IContact *currentContact2 = 0x0;
				contactListItems->GetAt(i, &currentContact2);
				MyContacts *currentContact = reinterpret_cast<MyContacts*>(currentContact2);
				if (currentContact->getPhoneNumbers().count()>0) {
					ContactModel *_cm = new ContactModel();
					_cm->setFullName(currentContact->getFullName());
					_cm->setPhoneNumber(currentContact->getPhoneNumbers().at(0));
					currentContact->getUserImage();
					newData.append(_cm);
				}
			}
			if (newData.count() > 0) {
				nativeDataRetrieveCompleteWithList(newData);
			}


//			ComPtr<IAsyncOperation<IVectorView<Contact*>*>> contactAsync;
//			//IAsyncOperation<Contact> me=
//			HRESULT hr = contactStore->FindContactsAsync(&contactAsync);
//			if (FAILED(hr)) {
//				qDebug() << "Failed to get IAsyncOperation<IVectorView<Contact*>*> *contactAsync;";
//			}

			
		}
		//Asynchronous operation is done
		//	if (status == completed)/
		//	{
		//		// use results from operation->GetResults() as needed...
		//	}
		return S_OK;
	});

	asyncOp->put_Completed(onAppLicCompletedCallback.Get());

//    IContactStore *contactStore = 0x0;
//    while (contactStore==0x0){
//        asyncOp->GetResults(&contactStore);
//    }
//    qDebug()<<"Contact Store is: "<<contactStore;
    
	
}

//IAsyncOperationCompletedHandler<ContactStore*>*handler
QList<ContactModel*> Contacts::getContacts(){
    return m_contactsList;
}

void Contacts::nativeDataRetrieveCompleteWithList(QList<ContactModel*> contactsList){
    m_contactsList = contactsList;
    emit contactsRetrieved(m_contactsList);
}
