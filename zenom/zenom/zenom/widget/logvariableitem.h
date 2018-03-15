#ifndef LOGVARIABLEITEM_H
#define LOGVARIABLEITEM_H

#include <logvariable.h>
#include <QSettings>
#include <QPointF>

struct LogVariableItem
{
public:
	LogVariableItem(LogVariable* pLogVariable = NULL, int pRow = -1, int pCol = -1);

	~LogVariableItem();

	void saveSettings( QSettings& pSettings );
	void loadSettings( QSettings& pSettings );

	void set( LogVariable* pLogVariable, int pRow, int pColumn );
	LogVariable* logVariable() const;
	int row() const;
	int column() const;
    int size() const;
    QPointF heapElement(int pIndex) const;

    bool isNull() const;
    bool isValid() const;
	double lastHeapElement();
    double lastTime();

    QString name() const;

private:
	LogVariable* mLogVariable;
	int mRow;
	int mCol;
};

#endif // LOGVARIABLEITEM_H
