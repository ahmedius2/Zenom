#ifndef LOGVARIABLETREEWIDGET_H
#define LOGVARIABLETREEWIDGET_H

#include <QTreeWidget>
#include <datarepository.h>
#include "logvariableitem.h"

class LogVariableTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	LogVariableTreeWidget(QWidget *pParent);

	~LogVariableTreeWidget();

    void setLogVariableList( const LogVariableList& pLogVariableList );

	/*
	Returns the current log variable item in the tree widget.
	*/
	LogVariableItem currentLogVariableItem() const;

	/*
	Returns a list of all selected non-hidden log variable items.
	*/
	QList<LogVariableItem> selectedLogVariableItems() const;

	/*
	Sets the current log variable item in the tree widget.
	*/
	void setCurrentLogVariableItem( LogVariableItem pLogVariableItem );

private:
	
};

#endif // LOGVARIABLETREEWIDGET_H
