#include "contactmodel.h"

ContactModel::ContactModel(QObject *parent) : QObject(parent)
{

}

//GETTER
QString ContactModel::fullName() const
{
    return m_fullName;
}

QString ContactModel::phoneNumber() const
{
    return m_phoneNumber;
}

QString ContactModel::userImage() const
{
    return m_userImage;
}
//SETTER
void ContactModel::setFullName(QString fullName)
{
    if (m_fullName == fullName)
        return;

    m_fullName = fullName;
    emit fullNameChanged(fullName);
}
void ContactModel::setPhoneNumber(QString phoneNumber)
{
    if (m_phoneNumber == phoneNumber)
        return;

    m_phoneNumber = phoneNumber;
    emit phoneNumberChanged(phoneNumber);
}
void ContactModel::setUserImage(QString userImage)
{
    if (m_userImage == userImage)
        return;

    m_userImage = userImage;
    emit userImageChanged(userImage);
}
