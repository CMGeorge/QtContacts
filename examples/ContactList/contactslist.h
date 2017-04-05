#ifndef CONTACTSLISTMODEL_H
#define CONTACTSLISTMODEL_H

#include <QtCore/QAbstractListModel>
#include "contactmodel.h"

class ContactsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ContactRoles{
        ID = Qt::UserRole+1,
        FirstName,
        LastName,
        FullName,
        UserImage,
        Phone,
        Invited,
        Member
    };

    explicit ContactsListModel(QObject *parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<ContactModel*>m_contactList;
protected:
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
private slots:
    void contactListRetrieveComplete(QList<ContactModel*>);
};

#endif // CONTACTSLISTMODEL_H
