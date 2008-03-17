#ifndef HUNGARIAN_SORT_FILTER_PROXY_MODEL_HH
#define HUNGARIAN_SORT_FILTER_PROXY_MODEL_HH

#include <QSortFilterProxyModel>
#include <QString>

class HungarianSortFilterProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT

  enum CharLessType { CHAR_EQUAL, CHAR_LESS, CHAR_GREATER };

public:
  HungarianSortFilterProxyModel();

private:
  CharLessType charLess(QChar a, QChar b) const;
  bool lessThan (const QModelIndex &left, const QModelIndex &right) const;

  QString abc;
};

#endif	// HUNGARIAN_SORT_FILTER_PROXY_MODEL_HH
