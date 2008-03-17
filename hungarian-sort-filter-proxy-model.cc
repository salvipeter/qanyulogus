#include "hungarian-sort-filter-proxy-model.hh"

HungarianSortFilterProxyModel::HungarianSortFilterProxyModel() :
  QSortFilterProxyModel()
{
  abc = QString::fromUtf8("aábcdeéfghiíjklmnoóöőpqrstuúüűvwxyz");
}

HungarianSortFilterProxyModel::CharLessType
HungarianSortFilterProxyModel::
charLess(QChar a, QChar b) const
{
  int const x = abc.indexOf(a, 0, sortCaseSensitivity());
  int const y = abc.indexOf(b, 0, sortCaseSensitivity());

  if(x < 0 && y < 0) {
    if(a == b)
      return CHAR_EQUAL;
    if(a < b)
      return CHAR_LESS;
    return CHAR_GREATER;
  }

  if(x == y)
    return CHAR_EQUAL;
  if(x < y)
    return CHAR_LESS;
  return CHAR_GREATER;
}

bool HungarianSortFilterProxyModel::
lessThan (const QModelIndex &left, const QModelIndex &right) const
{
  QVariant const va = left.data(sortRole());
  QVariant const vb = right.data(sortRole());
  if(va.type() != QVariant::String || vb.type() != QVariant::String)
    return QSortFilterProxyModel::lessThan(left, right);

  QString const a = va.toString();
  QString const b = vb.toString();

  int const na = a.length();
  int const nb = b.length();
  int index = 0;
  while(true) {
    if(index == na && index == nb)
      return false;
    else if(index == na)
      return true;
    else if(index == nb)
      return false;
    CharLessType less = charLess(a[index], b[index]);
    if(less != CHAR_EQUAL)
      return less == CHAR_LESS;
    ++index;
  }
}
