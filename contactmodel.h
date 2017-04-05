#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QObject>

class ContactModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QString userImage READ userImage WRITE setUserImage NOTIFY userImageChanged)

    QString m_fullName;

    QString m_phoneNumber;

    QString m_userImage;

public:
    explicit ContactModel(QObject *parent = 0);

    QString fullName() const;
    QString phoneNumber() const;
    QString userImage() const;

signals:

    void fullNameChanged(QString fullName);

    void phoneNumberChanged(QString phoneNumber);

    void userImageChanged(QString userImage);

public slots:
    void setFullName(QString fullName);
    void setPhoneNumber(QString phoneNumber);
    void setUserImage(QString userImage);
};

#endif // CONTACTMODEL_H
