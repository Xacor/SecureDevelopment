#include "accountlist.h"

AccountList::AccountList(QObject *parent): QObject{parent}
{
    mItems.append({QStringLiteral("vk.com"), QStringLiteral("user"), QStringLiteral("password"), false});
    mItems.append({QStringLiteral("vk1.co121212121212"), QStringLiteral("user1"), QStringLiteral("password1"), false});
    mItems.append({QStringLiteral("vk.com2"), QStringLiteral("user2"), QStringLiteral("password2"), false});
}

QVector<AccountItem> AccountList::items() const
{
    return mItems;
}

bool AccountList::setItemAt(int index, const AccountItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const AccountItem &oldItem = mItems.at(index);
    if (item.site == oldItem.site && item.username == oldItem.username && item.password == oldItem.password && item.deleted == oldItem.deleted)
        return false;

    mItems[index] = item;
    return true;
}

void AccountList::appendItem()
{
    emit preItemAppended();

    AccountItem item;
    mItems.append(item);

    emit postItemAppended();
}

void AccountList::removeItem()
{
    for (int i = 0; i < mItems.size();) {
        if (mItems.at(i).deleted) {
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}
