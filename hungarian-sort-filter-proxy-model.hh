#ifndef HUNGARIAN_SORT_FILTER_PROXY_MODEL_HH
#define HUNGARIAN_SORT_FILTER_PROXY_MODEL_HH

#include <QSortFilterProxyModel>
#include <QString>

class HungarianSortFilterProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT

  enum CharLessType { CHAR_EQUAL, CHAR_LESS, CHAR_GREATER };

public:
  HungarianSortFilterProxyModel(QObject *parent = nullptr);

public slots:
  void setFilterStringUnlessShort(const QString &str);

private:
  CharLessType charLess(QChar a, QChar b) const;
  bool lessThan (const QModelIndex &left, const QModelIndex &right) const;

  static const QString abc;
  static const int min_legal_length;
};

#endif	// HUNGARIAN_SORT_FILTER_PROXY_MODEL_HH
